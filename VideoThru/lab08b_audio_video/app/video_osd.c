/*
 * video_osd.c
 *
 * Provides helper functions for placing banners and semi-transparent 
 *     border on OSD display
 */

/* Standard Linux headers */
#include <stdio.h>                                // always include stdio.h
#include <stdlib.h>                               // always include stdlib.h
#include <string.h>                               // defines memset and memcpy methods

#include <fcntl.h>                                // defines open, read, write methods
#include <unistd.h>                               // defines close and sleep methods
#include <sys/mman.h>                             // defines mmap method
#include <sys/ioctl.h>                            // defines ioctl method

#include <linux/fb.h>                             // defines framebuffer driver methods

/* Application header files */
#include "video_osd.h"                            // video driver definitions
#include "debug.h"                                // DBG and ERR macros


/***************************************************************************
 *  video_osd_place
 ***************************************************************************/
/*  input parameters:                                                     */
/*      Buffer_Handle osdDisplay   -- mmap'ed location of osd window      */
/*            osdDisplay buffer must have following dimensions set:       */
/*      BufferGfx_Dimensions.linelength -- x dimension (virtual) of osd   */
/*                                         in bytes                       */
/*      Buffer_Handle picture      -- bitmapped ARGB picture array        */
/*            picture buffer must have following dimensions set:          */
/*      BufferGfx_Dimensions.x -- x offset to place picture in osd        */
/*      BufferGfx_Dimensions.x -- y offset to place picture in osd        */
/*      BufferGfx_Dimensions.height -- y dimension of picture             */
/*      BufferGfx_Dimensions.linelength -- x dimension of picture in bytes*/
/*                                                                        */
/*  NOTE: this function does not check offsets and picture size against   */
/*      dimensions of osd  window. If your math is wrong, you will        */
/*      get a segmentation fault (or worse)                               */
/*                                                                        */
/**************************************************************************/
int video_osd_place( Buffer_Handle osdDisplay, Buffer_Handle picture )
{
    int i;
    unsigned char *displayOrigin, *pictureOrigin;

    BufferGfx_Dimensions osdDims, pictureDims;

    /* Get OSD and ATTR window dimensions */
    BufferGfx_getDimensions( osdDisplay, &osdDims );
    BufferGfx_getDimensions( picture, &pictureDims );


    displayOrigin = ( unsigned char * ) Buffer_getUserPtr( osdDisplay );
    pictureOrigin = ( unsigned char * ) Buffer_getUserPtr( picture );

    displayOrigin = &displayOrigin[pictureDims.y * osdDims.lineLength + pictureDims.x * 4]; 

    for( i=0; i< pictureDims.height ; i++ )
    {
        memcpy( &displayOrigin[i * osdDims.lineLength], 
            &pictureOrigin[i * pictureDims.lineLength], pictureDims.lineLength );
    }

    return VOSD_SUCCESS;
}

/***************************************************************************
 *  video_osd_scroll
 **************************************************************************/
/*  input parameters:                                                     */
/*      Buffer_Handle osdDisplay   -- mmap'ed location of osd window      */
/*            osdDisplay buffer must have following dimensions set:       */
/*      BufferGfx_Dimensions.linelength -- x dimension (virtual) of osd   */
/*                                         in bytes                       */
/*      Buffer_Handle picture      -- bitmapped ARGB picture array        */
/*            picture buffer must have following dimensions set:          */
/*      BufferGfx_Dimensions.x -- x offset to place picture in osd        */
/*      BufferGfx_Dimensions.x -- y offset to place picture in osd        */
/*      BufferGfx_Dimensions.height -- y dimension of picture             */
/*      BufferGfx_Dimensions.linelength -- x dimension of picture in bytes*/
/*                                                                        */
/*      int x_scroll -- scrolling x offset (does not affect picture       */
/*                      placement, only scrolling offset w/in defined box */
/*      int y_scroll -- scrolling y offset (does not affect picture       */
/*                      placement, only scrolling offset w/in defined box */
/*                                                                        */
/*                                                                        */
/*  NOTE: this function does not check offsets and picture size against   */
/*      dimensions of osd  window. If your math is wrong, you will        */
/*      get a segmentation fault (or worse)                               */
/*                                                                        */
/**************************************************************************/

int video_osd_scroll( Buffer_Handle osdDisplay, 
                      Buffer_Handle picture,
                      int x_scroll, int y_scroll )
{
    int i;
    BufferGfx_Dimensions osdDims, pictureDims;
    unsigned char *displayOrigin, *pictureOrigin;

    /* Get OSD and ATTR window dimensions */
    BufferGfx_getDimensions( osdDisplay, &osdDims );
    BufferGfx_getDimensions( picture, &pictureDims );

    /* Calculate origin for picture placement */
    displayOrigin = ( unsigned char * ) Buffer_getUserPtr( osdDisplay );
    pictureOrigin = ( unsigned char * ) Buffer_getUserPtr( picture );

    displayOrigin = &displayOrigin[pictureDims.y * osdDims.lineLength + pictureDims.x * 4];

    for(i=0; i<pictureDims.height - y_scroll; i++)
    {
        memcpy(&displayOrigin[i*osdDims.lineLength], 
                &pictureOrigin[((i+y_scroll)*pictureDims.lineLength) + x_scroll * 4],
                (pictureDims.width-x_scroll) * 4);
        memcpy(&displayOrigin[(i*osdDims.lineLength) + (pictureDims.width-x_scroll)*4], 
                &pictureOrigin[(i+y_scroll)*pictureDims.lineLength],
                x_scroll * 4);

    }
    
    for(i=pictureDims.height - y_scroll; i<pictureDims.height; i++)
    {
        memcpy(&displayOrigin[i*osdDims.lineLength], 
                &pictureOrigin[((i-pictureDims.height+y_scroll)*pictureDims.lineLength) + x_scroll * 4], 
                (pictureDims.width-x_scroll) * 4);
        memcpy(&displayOrigin[(i*osdDims.lineLength) + (pictureDims.width -x_scroll) * 4], 
                &pictureOrigin[((i-pictureDims.height+y_scroll)*pictureDims.lineLength)], 
                x_scroll * 4);
    }

    return VOSD_SUCCESS;
}

/***************************************************************************
 *  video_osd_circframe
 **************************************************************************/
/*  input parameters:                                                     */
/*      Buffer_Handle osdDisplay   -- mmap'ed location of osd window      */
/*      unsigned int fillval       -- color fill for the frame in RGB24   */
/*      unsigned char trans          -- transparency value for the frame  */
/*                         0x00 = transparent frame (so you won't see it) */
/*                                                                        */
/**************************************************************************/
int video_osd_circframe( Buffer_Handle osdDisplay, 
                         unsigned int fillval,
                         unsigned char trans )
{
    int i, j;
    float x, y, x_scale, y_scale;
    unsigned int ifillval, iblankval;
    unsigned char *displayOrigin;
    BufferGfx_Dimensions osdDims;

    ifillval = fillval;
    ifillval = fillval & (0x00FFFFFF);
    ifillval = fillval | (trans << 24);

    iblankval = 0x00000000;

    /* Get OSD window dimensions */
    BufferGfx_getDimensions(osdDisplay, &osdDims);

    x_scale = (float) (osdDims.width >> 1);
    y_scale = (float) (osdDims.height >> 1);

    // Get pointer to window
    displayOrigin = (unsigned char *) Buffer_getUserPtr(osdDisplay);

// Radius of circular frame. A value of 1 will exactly touch screen border.
#define RADIUS 0.9

    // Calculate circle boundary and place color and transparency
    for( j=0; j<osdDims.height; j++ )
    {
        for( i=0; i<osdDims.width; i++ )
        {
            x = (float) i - x_scale;
            y = (float) j - y_scale;
            if( ((x*x / (x_scale*x_scale)) + (y*y/(y_scale*y_scale))) > RADIUS )
            {
                *((unsigned int *)(&displayOrigin[j*(osdDims.lineLength) + i * sizeof(int)])) = ifillval;
            } 
            else 
            {
                displayOrigin[j*(osdDims.lineLength) + i * sizeof(int)] = iblankval;
            }       
        }
    }

    return VOSD_SUCCESS;
}

