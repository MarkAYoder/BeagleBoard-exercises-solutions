#include <stdio.h>                                    // always include stdio.h
#include <stdlib.h>                                   // always include stdlib.h
#include "debug.h"


#include <ti/sdo/dmai/Dmai.h>
#include <ti/sdo/dmai/BufTab.h>
#include <ti/sdo/dmai/Buffer.h>
#include <ti/sdo/dmai/BufferGfx.h>

#include "picture.h"

/*
 *  readPictureBmp
 *
 *  reads a picture from a 24-bit RGB bitmap file into a dmai buffer object
 *  Stores data in 32-bit ARGB format with transparency as attribute field
 *
 *  INPUTS
 *  char *fileName  -- pointer to '\0' terminated string, name of pic file
 *  int height      -- height of the picture
 *  int width       -- width of the picture
 *  UInt8 transparency -- transparency for picture. 0x00 is transparent, 
 *                        0xFF is fully opaque
 *  
 *  OUTPUTS
 *  Buffer_Handle *writeBuffer_byRef  -- Buffer Handle, passed by reference
 *                 can be null on input. Will be returned with handle to
 *                 a created buffer holding picture data
 */
int readPictureBmp(char *fileName, Buffer_Handle *writeBuffer_byRef, 
    int height, int width, UInt8 transparency)
{

    BufferGfx_Dimensions    pictureDims;
    Buffer_Attrs            pictureAttrs = Buffer_Attrs_DEFAULT;

    int                     status       = read_picture_SUCCESS;
    FILE                    *inputFile   = NULL;                   // input file pointer
    unsigned int            *picturePtr  = NULL;

    int i,j;

    pictureAttrs.type = Buffer_Type_GRAPHICS;

    // read picture in with no offset, application can provide this
    pictureDims.x = 0;
    pictureDims.y = 0;

    // Initialize buffer attributes
    pictureDims.width = width;
    pictureDims.height = height;
    pictureDims.lineLength = width * 4;

    // Create dmai buffer to hold picture array
    *writeBuffer_byRef = Buffer_create( width * height * 4, &pictureAttrs );

    BufferGfx_setDimensions( *writeBuffer_byRef, &pictureDims );


    /* Open the display picture for OSD */    
    if( ( inputFile = fopen( fileName, "r" ) ) == NULL ) 
    {
        ERR( "Failed to open input file %s\n", fileName );
        status = (int) read_picture_FAILURE;
        return status;
    }

    DBG( "Opened file %s with FILE pointer %p\n", fileName, inputFile );


    /* Read in picture */
    // Place transparency for banner into picture array so it doesn't have
    //       to be added every frame when scrolling
    picturePtr = (unsigned int *) Buffer_getUserPtr( *writeBuffer_byRef );

    // Bitmap file format starts in bottom left corner
    picturePtr += (height - 1) * width;

    // Throw away the header
    fread( picturePtr, 4, 12, inputFile );

    for(i=0; i<height; i++)
    {
        for(j=0; j<width; j++)
        {
            if(fread(picturePtr, 3, 1, inputFile) < 1)
            { 
                ERR("Error reading osd picture from file\n");
                fclose(inputFile);
                status = read_picture_FAILURE;
                return status;
            }
            *picturePtr++ |= (transparency << 24);
        }
         // bitmap file format starts in bottom left corner
         picturePtr -= 2 * width; 
    }

    fclose( inputFile );

    return status;
}

