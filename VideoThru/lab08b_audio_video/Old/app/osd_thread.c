/*
 * osd_thread.c
 */

/* Standard Linux headers */
#include <stdio.h>                                   // always include stdio.h
#include <stdlib.h>                                  // always include stdlib.h
#include <string.h>                                  // defines memset and memcpy methods

/* DMAI headers */
#include <ti/sdo/dmai/Dmai.h>
#include <ti/sdo/dmai/Display.h>
#include <ti/sdo/dmai/BufTab.h>
#include <ti/sdo/dmai/Buffer.h>
#include <ti/sdo/dmai/BufferGfx.h>

/* Extended OSD support for ARGB */
#include <ti/tto/myDisplay/myDisplay.h>

/* Application header files */
#include "debug.h"
#include "video_osd.h"
#include "osd_thread.h"
#include "picture.h"

/* Input file */
#define PICTUREFILE "ti_rgb24_640x80.bmp"
#define PICTURE_HEIGHT 80
#define PICTURE_WIDTH 640
#define TRANSP 0xFF

#define NUM_BUFS 2

/*************************************************************************/
/* osd_thread_fxn                                                        */
/*  input parameters:                                                    */
/*      void *envByRef       --  pointer to osd_thread_env structure     */
/*                               as defined in osd_thread.h              */
/*                                                                       */
/*          envByRef->quit   -- when quit != 0, thread will exit         */
/*                                                                       */
/*  return value:                                                        */
/*      void *     --  OSD_THREAD_SUCCESS or OSD_THREAD_FAILURE as       */
/*                     defined in osd_thread.h                           */
/*************************************************************************/
void *osd_thread_fxn(void *envByRef)
{
/* Thread parameters and return value */
    osd_thread_env *env    = envByRef;              // see above
    void           *status = OSD_THREAD_SUCCESS;    // see above

/* The levels of initialization for initMask */
#define OSDSETUPCOMPLETE     0x1
    unsigned int       initMask       = 0x0;

/* Capture and display driver variables */

    myDisplay_Attrs   oAttrs = myDisplay_Attrs_O3530_OSD_DEFAULT;
    Display_Handle    hOsd = NULL;

    Buffer_Handle     oBuf = NULL, bannerBuf = NULL;
    BufferGfx_Dimensions   bannerDim;

/* OSD scrolling variables */
    int xoffset = 0;
    int yoffset = 0;

/* other variables */
    int i;

    // enable alpha blending
    system("echo 1 > /sys/devices/platform/omapdss/manager0/alpha_blending_enabled");

    //    Set osd attributes
    oAttrs.videoStd = VideoStd_VGA;
    oAttrs.numBufs = NUM_BUFS;
    oAttrs.rotation = 90;
    oAttrs.videoOutput = Display_Output_LCD;
    oAttrs.colorSpace = myColorSpace_ARGB;

    //     Open OSD device
    hOsd = myDisplay_fbdev_create(NULL, &oAttrs);

    if(hOsd == NULL)
    {
        ERR( "Failed to open handle to OSD driver in osd_thread_fxn\n" );
        status = OSD_THREAD_FAILURE;
        goto cleanup;
    }

// create banner buffer and read banner picture

    if( readPictureBmp( PICTUREFILE, &bannerBuf, PICTURE_HEIGHT, PICTURE_WIDTH, TRANSP ) !=
        read_picture_SUCCESS )
    {
        ERR( "Failed to read banner bitmap in osd_thread_fxn\n" );
        status = OSD_THREAD_FAILURE;
        goto cleanup;
    }

    DBG("OSD Picture read successful, placing picture\n");


#define PIC_X_OFFSET 0
#define PIC_Y_OFFSET 400

    //  Set banner offset
    BufferGfx_getDimensions(bannerBuf, &bannerDim);

    bannerDim.x = PIC_X_OFFSET;
    bannerDim.y = PIC_Y_OFFSET;

    BufferGfx_setDimensions(bannerBuf, &bannerDim);

    //  Place banner and circular transparent frame in the OSD buffers
    DBG ( "Number of buffers to place = %d \n", oAttrs.numBufs );
    for(i = 0; i< oAttrs.numBufs; i++) 
    {
        myDisplay_fbdev_get(hOsd, &oBuf);

        // color in 24-bit RGB
        // transparency in 8 bit, 0xFF = fully opaque frame
        video_osd_circframe(oBuf, 0x0000FF, 0x80);

        DBG ( "Buffer %d; Circframe placed, calling video_osd_place \n", i );

        video_osd_place(oBuf, bannerBuf);

        DBG ( "Buffer %d; Place successful \n", i );

        myDisplay_fbdev_put(hOsd, oBuf);
    }

    initMask |= OSDSETUPCOMPLETE;

    DBG("Entering osd_thread_fxn processing loop.\n");
    while (!env->quit) {
    // Calculate parameters for scrolling banner
#define X_RATE 5
#define Y_RATE 0
        xoffset += X_RATE;
        yoffset += Y_RATE; 
        if(xoffset >= PICTURE_WIDTH)
            xoffset = 0;
        if(yoffset >= PICTURE_HEIGHT)
            yoffset = 0;

       // Get an OSD frame, scroll the banner, and put it for display
        myDisplay_fbdev_get(hOsd, &oBuf);

        video_osd_scroll(oBuf, bannerBuf, xoffset, yoffset);

        myDisplay_fbdev_put(hOsd, oBuf);
     }

cleanup:
    DBG("Exited osd_thread_fxn processing loop\n");
    DBG("\tStarting osd thread cleanup\n");
    /* Thread Cleanup Phase -- free resources no longer needed by thread */
    /* Uses the init_bitmask to only free resources that were allocated  */

    /* Cleanup osd */
    if (initMask & OSDSETUPCOMPLETE) 
    {
        Display_delete(hOsd);
    }

    /* Return the status of thread execution */
    DBG( "\tOSD thread cleanup complete. Exiting osd_thread_fxn\n" );
    return status;
}

