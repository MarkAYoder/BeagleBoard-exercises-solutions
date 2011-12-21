/*
 * video_osd.h
 */

#include <xdc/std.h>
#include <ti/sdo/dmai/Buffer.h>
#include <ti/sdo/dmai/BufferGfx.h>

/* SUCCESS and FAILURE definitions for video display functions */
#define VOSD_SUCCESS  0
#define VOSD_FAILURE -1

/*  Function prototypes */
int video_osd_place( Buffer_Handle osdDisplay, Buffer_Handle picture );

int video_osd_scroll( Buffer_Handle osdDisplay, 
                      Buffer_Handle picture,
                      int x_scroll, 
                      int y_scroll );

int video_osd_circframe( Buffer_Handle osdDisplay, 
                         unsigned int fillval, 
                         unsigned char trans );

