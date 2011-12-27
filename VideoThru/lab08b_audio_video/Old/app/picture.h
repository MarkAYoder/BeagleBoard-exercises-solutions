#include <stdio.h>		// always include stdio.h
#include <stdlib.h>		// always include stdlib.h

#include <ti/sdo/dmai/Dmai.h>
#include <ti/sdo/dmai/BufTab.h>
#include <ti/sdo/dmai/Buffer.h>
#include <ti/sdo/dmai/BufferGfx.h>

#define read_picture_SUCCESS 0
#define read_picture_FAILURE -1

int readPictureBmp( char *fileName, 
                    Buffer_Handle *writeBuffer_byRef, 
                    int height, 
                    int width, 
                    UInt8 transparency );

