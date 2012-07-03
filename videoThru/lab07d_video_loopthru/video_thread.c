/*
 *    video_thread.c
 */

//* Standard Linux headers **
#include     <stdio.h>		// Always include stdio.h
#include     <stdlib.h>		// Always include stdlib.h
#include     <string.h>		// Defines memset and memcpy methods
#include     <sys/ioctl.h>	// Defines driver ioctl method
#include     <linux/fb.h>	// Defines framebuffer driver methods
#include     <asm/types.h>	// Standard typedefs required by v4l2 header
#include     <linux/videodev2.h>	// v4l2 driver definitions

//* Application headers files **
#include     "debug.h"		// DBG and ERR macros
#include     "video_thread.h"	// Video thread definitions
#include     "video_osd.h"	// OSD device functions
#include     "video_output.h"	// Display device functions
#include     "video_input.h"	// Display device functions

//* Video capture and display devices used **
#define     FBVID_GFX      "/dev/fb0"
#define     FBVID_VID0     "/dev/fb1"
#define     FBVID_VID1     "/dev/fb2"
#define     V4L2_DEVICE    "/dev/video0"

//* Input and Picture files **
#define     PICTUREFILE     "Rose640x480.bmp"

//* Double-buffered display, triple-buffered capture **
#define     NUM_DISP_BUFS   2
#define	    NUM_CAP_BUFS    3

//* Other Definitions **
#define     SCREEN_BPP      2		// Bytes per pixel, 2 for video buffer
// #define     D1_WIDTH        720
// #define     D1_HEIGHT       480	// NTSC Format
#define     D1_WIDTH        640
#define     D1_HEIGHT       480		// Small Format
// #define     D1_WIDTH        320
// #define     D1_HEIGHT       240	// Small Format
//#define   D1_HEIGHT       576		// PAL Format

//* Macro for clearing structures **
#define     CLEAR(x)       memset ( &(x), 0 , sizeof(x) )

//*******************************************************************************
//*  video_thread_fxn                                                          **
//*******************************************************************************
//*  Global Variables:                                                         *
//*      fb_var_screeninfo -- fbdev variable screen info                       *
//*                        -- defined in video_osd.c (ref'd in video_osd.h)    *
//*                        -- used to get D1 Height/Width dimensions from      *
//*                           the fbdev video display driver (set by bootargs) *
//*                                                                            *
//*  Input Parameters:                                                         *
//*      void *envPtr  --  a pointer to a video_thread_env structure as        *
//*                     defined in video_thread.h                              *
//*                 --  originally used to pass variable used to break out of  *
//*                     real time processing loop; another element is added to *
//*                     environment structure in codec engine lab exercises    *
//*                 --  not used by lab07a, but used in remaining video labs   *
//*                                                                            *
//*   envPtr.quit   --  when quit != 0, thread will cleanup and exit           *
//*                                                                            *
//*  Return Value:                                                             *
//*      void *     --  VIDEO_THREAD_SUCCESS or VIDEO_THREAD_FAILURE as        *
//*                     defined in video_thread.h                              *
//******************************************************************************
void *video_thread_fxn( void *envByRef )
{

// Variables and definitions
// *************************

    // Thread parameters and return value
    video_thread_env * envPtr = envByRef;                  // < see above >
    void             * status = VIDEO_THREAD_SUCCESS;      // < see above >

    // The levels of initialization for initMask
    #define     OSDSETUPCOMPLETE             0x1
    #define     DISPLAYDEVICEINITIALIZED     0x2
    #define     CAPTUREDEVICEINITIALIZED     0x4

    unsigned  int   initMask =  0x0;	// Used to only cleanup items that were init'd

    // Capture and display driver variables
    FILE *osdPictureFile = NULL;           // Input file pointer for osd picture file
    int osdFd = 0;	// OSD file descriptor
    int fbFd  = 0;	// Video fb driver file desc

    unsigned int *osdDisplay;	// OSD display buffer

    int captureFd = 0;		// Capture driver file descriptor
    VideoBuffer *vidBufs;	// Capture frame descriptors
    unsigned  int numVidBufs = NUM_CAP_BUFS;	// Number of capture frames
    int captureWidth;		// Width of a capture frame
    int captureHeight;		// Height of a capture frame
    int captureSize = 0;	// Bytes in a capture frame
    struct  v4l2_buffer   v4l2buf;	// Stores a dequeue'd frame

    #define     PICTURE_WIDTH      640
    #define     PICTURE_HEIGHT     480
    unsigned  int      picture[ PICTURE_HEIGHT		// OSD picture
                                   * PICTURE_WIDTH ];

    char * displays[ NUM_DISP_BUFS ];	// Display frame pointers
    int   displayWidth;			// Width of a display frame
    int   displayHeight;		// Height of a display frame
    int   displayBufSize = 0;		// Bytes in a display frame
    int   displayIdx = 0;		// Frame being displayed
    int   workingIdx = 1;		// Next frame, being built
    char * dst;				// Pointer to working frame

// Thread Create Phase -- secure and initialize resources
// ******************************************************

    // Setup video OSD
    // ***************

    // Initialize video attribute window
    if( video_osd_setup( &osdFd, FBVID_GFX, 0x00, &osdDisplay ) == VOSD_FAILURE ) {
        ERR( "Failed video_osd_setup in video_thread_function\n" );
        status = VIDEO_THREAD_FAILURE;
        goto cleanup;
    }
    // Record that the osd was setup
    initMask |= OSDSETUPCOMPLETE;

    // Place a circular alpha-blended OSD frame around video screen
    video_osd_circframe( osdDisplay, 0xa000ff00);  //AARRGGBB

    // Open the display picture for OSD
    if( ( osdPictureFile = fopen( PICTUREFILE, "r" ) ) == NULL ) {
        ERR( "Failed to open OSD (i.e. picture) file %s\n", PICTUREFILE );
        status = VIDEO_THREAD_FAILURE;
        goto  cleanup ;
    }

    DBG( "Opened file %s with FILE pointer %p\n", PICTUREFILE, osdPictureFile );

   //Skip BMP header information 
   fseek(osdPictureFile, 54, SEEK_SET);

    // Read in OSD display picture into memory, then close picture file
    if( fread( picture, sizeof( int ), PICTURE_HEIGHT * PICTURE_WIDTH,
	 osdPictureFile ) < PICTURE_HEIGHT * PICTURE_WIDTH ) {
        ERR( "Error reading osd picture from file\n" );
        fclose( osdPictureFile );
        goto cleanup;
    }

    fclose  ( osdPictureFile );

    DBG( "OSD Picture read successful, placing picture\n" );

    video_osd_place(osdDisplay, picture, 100, 100, PICTURE_WIDTH, PICTURE_HEIGHT);

    // Initialize the video display device
    // ***********************************

    displayWidth  = D1_WIDTH;           // Rather than use #defines for width/height
    displayHeight = D1_HEIGHT;
    //displayWidth  = osdInfo.xres;     // Get width/height from driver settings
    //displayHeight = osdInfo.yres;     //   configured as Linux boot variables

    if( video_output_setup( &fbFd, FBVID_VID0, displays, NUM_DISP_BUFS,
     &displayWidth, &displayHeight, ZOOM_1X )
         == VOUT_FAILURE ) {
        ERR( "Failed video_output_setup on %s in video_thread_function\n",
		FBVID_GFX );
        status = VIDEO_THREAD_FAILURE;
        goto cleanup;
    }

    // Calculate size of a display buffer (in bytes)
    displayBufSize  = displayWidth * displayHeight * SCREEN_BPP;

    // Record that display device was opened in initialization bitmask
    initMask       |= DISPLAYDEVICEINITIALIZED;

    // Initialize the video capture device
    // ***********************************

    captureWidth   = D1_WIDTH;
    captureHeight  = D1_HEIGHT;

    if( video_input_setup( &captureFd, V4L2_DEVICE, &vidBufs, &numVidBufs, 
			&captureWidth, &captureHeight )
         == VIN_FAILURE ) {
        ERR( "Failed video_input_setup in video_thread_function\n" );
        status = VIDEO_THREAD_FAILURE;
        goto cleanup;
    }

    // Calculate size of a raw frame (in bytes)
    captureSize  = captureWidth * captureHeight * SCREEN_BPP;

    DBG( "captureSize = %d\n", captureSize);

    // Record that capture device was opened in initialization bitmask
    initMask    |= CAPTUREDEVICEINITIALIZED;

// Thread Execute Phase -- perform I/O and processing
// **************************************************

    // Processing loop
    DBG( "Entering video_thread_fxn processing loop.\n" );

    int frameNumber = 0;
    int skipFrame = 100;	// Display message for 1 out of this many frames

    while( !envPtr->quit )
    {

       // Initialize v4l2buf buffer for DQBUF call
        CLEAR( v4l2buf );
        v4l2buf.type   = V4L2_BUF_TYPE_VIDEO_CAPTURE;
        v4l2buf.memory = V4L2_MEMORY_MMAP;

        // Wait for video frame to be available
        // *************************************************************
        //  We eliminated the wait_for_frame() call because we now     *
        //  use the V4L2 capture driver in blocking mode.              *
        //                                                             *
        //  if( wait_for_frame( captureFd ) == VIN_FAILURE )           *
        //  {                                                          *
        //      ERR( "Wait_for_frame failed in video_thread_fxn\n" );  *
        //      status = VIDEO_THREAD_FAILURE;                         *
        //      break;                                                 *
        //  }                                                          *
        // *************************************************************

        // Dequeue a frame buffer from the capture device driver
        if( ioctl( captureFd, VIDIOC_DQBUF, &v4l2buf ) == -1 ) {
            ERR( "VIDIOC_DQBUF failed in video_thread_fxn\n" );
            status = VIDEO_THREAD_FAILURE;
            break;
        }

        // Set display index to "working" buffer in fbdev display driver
        dst = displays[ workingIdx ];

	if(frameNumber % skipFrame == 0)
	    DBG("%d: dst = %d, ", frameNumber, (int) dst);

        // Read raw video data from camera to display

	memcpy(dst, vidBufs[ v4l2buf.index ].start, captureSize);

        // Issue capture buffer back to capture device driver
        if( ioctl( captureFd, VIDIOC_QBUF, &v4l2buf ) == -1 ) {
            ERR( "VIDIOC_QBUF failed in video_thread_fxn\n" );
            status = VIDEO_THREAD_FAILURE;
            break;
        }

        // Calculate the next buffer for display/work
        displayIdx = ( displayIdx + 1 ) % NUM_DISP_BUFS;
        workingIdx = ( workingIdx + 1 ) % NUM_DISP_BUFS;

	if(frameNumber % skipFrame == 0)
	    DBG( "displayIdx = %d, workingIdx = %d\n", displayIdx, workingIdx);

        // Flip display and working buffers
        flip_display_buffers( fbFd, displayIdx );

	frameNumber++;
#ifdef HACK
	if(frameNumber > 1000)
	    break;
#endif
    }

    DBG( "Exited video_thread_fxn processing loop\n" );


// Thread Delete Phase -- free up resources allocated by this file
// ***************************************************************

cleanup:

    DBG( "Starting video thread cleanup to return resources to system\n" );

    // Close the video drivers
    // ***********************
    //  - Uses the initMask to only free resources that were allocated.

    // Cleanup osd
    if( initMask & OSDSETUPCOMPLETE ) {
        video_osd_cleanup( osdFd, osdDisplay );
    }

    // Close video capture device
    if( initMask & CAPTUREDEVICEINITIALIZED ) {
        video_input_cleanup( captureFd, vidBufs, numVidBufs );
    }

    // Close video display device
    if( initMask & DISPLAYDEVICEINITIALIZED ) {
        video_output_cleanup( fbFd, displays, NUM_DISP_BUFS );
    }


    // Return from video_thread_fxn function
    // *************************************

    // Return the status at exit of the thread's execution
    DBG( "Video thread cleanup complete. Exiting video_thread_fxn\n" );
    return status;
}

