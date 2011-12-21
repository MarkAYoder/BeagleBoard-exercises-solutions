/*
 *  video_thread.c
 */

/* Standard Linux headers */
#include <stdio.h>                               // always include stdio.h
#include <stdlib.h>                              // always include stdlib.h
#include <string.h>                              // defines memset and memcpy methods

/* Codec Engine headers */
#include <xdc/std.h>                             // xdc definitions. Must come 1st

/* DMAI headers */
#include <ti/sdo/dmai/Dmai.h>
#include <ti/sdo/dmai/Capture.h>
#include <ti/sdo/dmai/Display.h>
#include <ti/sdo/dmai/Buffer.h>
#include <ti/sdo/dmai/BufferGfx.h>

/* Application header files */
#include "debug.h"                               // DBG and ERR macros
#include "video_thread.h"                        // Video thread definitions

/* Align buffers to this cache line size (in bytes)*/
#define BUFSIZEALIGN        128

/* Macro for clearing structures */
#define CLEAR(x) memset (&(x), 0, sizeof (x))

/* Numbers of video buffers needed */
#define NUM_CAPTURE_BUFS 3
#define NUM_DISPLAY_BUFS 2
#define NUM_DECODER_BUFS 3


/**************************************************************************
 * video_thread_fxn                                                       *
 **************************************************************************/
/*  input parameters:                                                    */
/*      void *envByRef       --  pointer to video_thread_env structure   */
/*                               as defined in video_thread.h            */
/*                                                                       */
/*          envByRef.quit    -- when quit != 0, thread will exit         */
/*          env->engineName -- string value specifying name of           */
/*                              engine configuration for Engine_open     */
/*                                                                       */
/*  return value:                                                        */
/*      void *     --  VIDEO_THREAD_SUCCESS or VIDEO_THREAD_FAILURE as   */
/*                     defined in video_thread.h                         */
/*************************************************************************/
void *video_thread_fxn( void *envByRef )
{
/*  Thread parameters and return value */
    video_thread_env *env    = envByRef;                     // see above
    void             *status = VIDEO_THREAD_SUCCESS;         // see above

/*  The levels of initialization for initMask */
#define OSDSETUPCOMPLETE         0x1
#define DISPLAYDEVICEINITIALIZED 0x2
#define CAPTUREDEVICEINITIALIZED 0x4
    unsigned int initMask = 0x0;            // Used to only cleanup items that were init'ed

/*  Capture variables */
    Capture_Attrs     cAttrs = Capture_Attrs_OMAP3530_DEFAULT;
    Capture_Handle    hCapture = NULL;
    Buffer_Handle     cBuf;

/*  Display variables */
    Display_Attrs     dAttrs = Display_Attrs_O3530_VID_DEFAULT;
    Display_Handle    hDisplay = NULL;
    Buffer_Handle     dBuf;

    BufferGfx_Attrs  gfxAttrs = BufferGfx_Attrs_DEFAULT;
    BufTab_Handle    hBufTabCapture        = NULL;
    BufTab_Handle    hBufTabDisplay        = NULL;
    VideoStd_Type    videoStd;
    Int32            bufSize;


/* Thread Create Phase -- secure and initialize resources */

/* Setup Capture */

    /* Detect type of video (i.e. video standard) connected to the EVM's video input */
    if ( Capture_detectVideoStd( NULL, &videoStd, &cAttrs ) < 0 ) 
    {
        printf( "Failed to detect input video standard, input connected?\n" );
        goto cleanup;
    }

    /* Calculate buffer size needed given a color space */
    bufSize = BufferGfx_calcSize( videoStd, ColorSpace_UYVY );
    bufSize = ( bufSize + 4096) & ( ~0xFFF );

    if ( bufSize < 0 ) 
    {
        printf( "Failed to calculate size for video driver buffers\n" );
        goto cleanup;
    }

    /* Calculate the dimensions of the video standard */
    if ( BufferGfx_calcDimensions( videoStd,
                                   ColorSpace_UYVY, 
                                   &gfxAttrs.dim ) 
         < 0 ) 
    {
        printf( "Failed to calculate dimensions for video driver buffers\n" );
        goto cleanup;
    }

    gfxAttrs.colorSpace = ColorSpace_UYVY;

    /* Create a table of buffers to use with the capture driver */
    hBufTabCapture = BufTab_create( NUM_CAPTURE_BUFS, 
                                    bufSize,
                                    BufferGfx_getBufferAttrs( &gfxAttrs ) );

    if ( hBufTabCapture == NULL ) 
    {
        printf( "Failed to allocate contiguous buffers\n" );
        goto cleanup;
    }

    /* Create the capture driver instance */
    cAttrs.numBufs = NUM_CAPTURE_BUFS;
    hCapture = Capture_create( hBufTabCapture, &cAttrs );

    if( hCapture == NULL ) 
    {
        ERR( "Failed Capture_create in video_thread_function\n" );
        status = VIDEO_THREAD_FAILURE;
        goto cleanup;
    }

    /* Record that capture device was opened in initialization bitmask */
    initMask |= CAPTUREDEVICEINITIALIZED;

/* Setup Display */

    /* Set output standard to match input */
    dAttrs.videoStd = Capture_getVideoStd( hCapture );
    dAttrs.numBufs = NUM_DISPLAY_BUFS;
    dAttrs.rotation = 90;

    /* Create a table of buffers to use with the display driver  */
    hBufTabDisplay = BufTab_create( NUM_DISPLAY_BUFS, 
                                    bufSize,
                                    BufferGfx_getBufferAttrs( &gfxAttrs ) );

    if ( hBufTabDisplay == NULL ) 
    {
        printf( "Failed to allocate contiguous buffers\n" );
        goto cleanup;
    }

    /* Create the display driver instance */
    hDisplay = Display_create( hBufTabDisplay, &dAttrs );
    if( hDisplay == NULL )
    {
        ERR( "Failed to open handle to Display driver in video_thread_fxn\n" );
        status = VIDEO_THREAD_FAILURE;
        goto cleanup;
    }

    /* Record that display device was opened in initialization bitmask */
    initMask |= DISPLAYDEVICEINITIALIZED;


/* Thread Execute Phase -- perform I/O and processing */

    DBG( "Entering video_thread_fxn processing loop.\n" );

    while ( !env->quit )
    {
        Capture_get( hCapture, &cBuf );
        Display_get( hDisplay, &dBuf );

        memcpy( Buffer_getUserPtr( dBuf ),
                Buffer_getUserPtr( cBuf ),
                Buffer_getSize( dBuf ) );

        Capture_put( hCapture, cBuf );
        Display_put( hDisplay, dBuf );
    }


cleanup:
    /* Thread Delete Phase -- free resources no longer needed by thread */

    DBG( "Exited video_thread_fxn processing loop\n" );
    DBG( "\tStarting video thread cleanup to return resources to system\n" );

    /* Use the initMask to only free resources that were allocated     */
    /* Nothing to be done for mixer device, it was closed after init   */

    /* Close video capture device */
    if ( initMask & CAPTUREDEVICEINITIALIZED ) 
    {
        Capture_delete( hCapture );
    }

    /* Close video display device */ 
    if ( initMask & DISPLAYDEVICEINITIALIZED ) 
    {
        Display_delete( hDisplay );
    }

    /* Return the status of the thread execution */
    DBG( "\tVideo thread cleanup complete. Exiting video_thread_fxn.\n" );
    return (void *)status;
}

