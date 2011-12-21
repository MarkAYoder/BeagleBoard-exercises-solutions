/*
 *   audio_thread.c
 */

/* Standard Linux headers */
#include <stdio.h>                               // always include stdio.h
#include <stdlib.h>                              // always include stdlib.h
#include <string.h>                              // defines memset and memcpy methods

/* Codec Engine headers */
#include <xdc/std.h>                             // xdc definitions. Must come 1st

/* DMAI headers */
#include <ti/sdo/dmai/Dmai.h>
#include <ti/sdo/dmai/Sound.h>
#include <ti/sdo/dmai/Buffer.h>

/* Application header files */
#include "debug.h"                               // DBG and ERR macros
#include "audio_thread.h"                        // Audio thread definitions

/* The sample rate of the audio codec.*/
#define SAMPLE_RATE 44100

/* The gain (0-100) of the left channel.*/
#define LEFT_GAIN 100

/* The gain (0-100) of the right channel.*/
#define RIGHT_GAIN 100

/*  Parameters for audio thread execution */
#define BLOCKSIZE 4096


/*************************************************************************
 * audio_thread_fxn                                                      *
 *************************************************************************/
/*  input parameters:                                                    */
/*      void *envByRef       --  pointer to audio_thread_env structure   */
/*                               as defined in audio_thread.h            */
/*                                                                       */
/*          envByRef.quit    -- when quit != 0, thread will exit         */
/*          env->engineName -- string value specifying name of           */
/*                              engine configuration for Engine_open     */
/*                                                                       */
/*  return value:                                                        */
/*      void *     --  AUDIO_THREAD_SUCCESS or AUDIO_THREAD_FAILURE as   */
/*                     defined in audio_thread.h                         */
/*************************************************************************/
void *audio_thread_fxn(void *envByRef)
{
/*  Thread parameters and return value */
    audio_thread_env *env = envByRef;                   // see above
    void    	     *status = AUDIO_THREAD_SUCCESS;	// see above


/*  The levels of initialization for initMask */
#define ALSA_INITIALIZED        0x1
#define INPUT_BUFFER_ALLOCATED  0x2
#define OUTPUT_BUFFER_ALLOCATED 0x4

/* Only used to cleanup items that were initialized */
    unsigned int initMask = 0x0;            // Used to only cleanup items that were init'ed

/*  Input and output buffer variables  */
    int blksize = BLOCKSIZE;

    Buffer_Attrs bAttrs   = Buffer_Attrs_DEFAULT;
    Sound_Attrs  sAttrs   = Sound_Attrs_STEREO_DEFAULT;

    Buffer_Handle hBufIn  = NULL, hBufOut = NULL;
    Sound_Handle hSound   = NULL;


/* Thread Create Phase -- secure and initialize resources */

    system("amixer cset name='Analog Left AUXL Capture Switch' 1");
    system("amixer cset name='Analog Right AUXR Capture Switch' 1");

    /* Initialize sound device */
    sAttrs.channels   = 2;
    sAttrs.mode       = Sound_Mode_FULLDUPLEX;
    sAttrs.soundInput = Sound_Input_LINE;
    sAttrs.sampleRate = 44100;
    sAttrs.soundStd   = Sound_Std_ALSA;
    sAttrs.bufSize    = 4096;

    hSound = Sound_create( &sAttrs );
    if( hSound==NULL )
    {
        ERR( "Failed to obtain handle to sound object\n" );
        status = AUDIO_THREAD_FAILURE;
        goto cleanup;
    }

    /* Record that input ALSA device was opened in initialization bitmask */
    initMask |= ALSA_INITIALIZED;

    /* Create input read buffer */
    hBufIn = Buffer_create( blksize, &bAttrs );
    if( hBufIn == NULL )
    {
        ERR( "Failed to allocate memory for input block (%d)\n", blksize );
        status = AUDIO_THREAD_FAILURE;
        goto cleanup;
    }

    DBG( "Allocated input audio buffer of size %d\n", blksize );

    /* Record that the output buffer was allocated in bitmask */
    initMask |= INPUT_BUFFER_ALLOCATED;


    /* Initialize the output audio buffer */

    hBufOut = Buffer_create( blksize, &bAttrs );
    if( hBufOut == NULL )
    {
        ERR( "Failed to allocate memory for output audio buffer (%d)\n", blksize );
        status = AUDIO_THREAD_FAILURE;
        goto cleanup;
    }

    DBG( "Allocated output audio buffer of size %d\n", blksize );

    /* Record that the output buffer was allocated in bitmask */
    initMask |= OUTPUT_BUFFER_ALLOCATED;


/* Prime the pump */

    Buffer_setNumBytesUsed( hBufIn, Buffer_getSize( hBufIn ) );
	if( Sound_read( hSound, hBufIn ) < 0 ) 
    {
        ERR( "Sound_read failed in audio_thread_fxn\n" );
        status = AUDIO_THREAD_FAILURE;
        goto cleanup;
    }

   Buffer_setNumBytesUsed( hBufIn, Buffer_getSize( hBufIn ) );
   Sound_write( hSound, hBufIn );

   Buffer_setNumBytesUsed( hBufIn, Buffer_getSize( hBufIn ) );
   Sound_write( hSound, hBufIn );


/* Thread Execute Phase -- perform I/O and processing */

    DBG( "Entering audio_thread_fxn processing loop\n" );
    while ( !env->quit )
    {
        /*  Read input buffer from ALSA input device */
        if( Sound_read( hSound, hBufIn ) < 0 )
        {
            ERR( "Sound_read failed in audio_thread_fxn\n" );
            status = AUDIO_THREAD_FAILURE;
            break;
        }

        memcpy( Buffer_getUserPtr( hBufOut ),
                Buffer_getUserPtr( hBufIn ),
                Buffer_getSize( hBufOut ) );

        /* Write output buffer into ALSA output device */

        // Workaround for copy codec not filling in bytes consumed
        Buffer_setNumBytesUsed( hBufOut, Buffer_getSize( hBufOut ) );

        Sound_write( hSound, hBufOut );
    }


cleanup:
    /* Thread Delete Phase -- free resources no longer needed by thread */

    DBG("Exited audio_thread_fxn processing loop\n");
    DBG("\tStarting audio thread cleanup to return resources to system\n");

    /* Use the initMask to only free resources that were allocated     */
    /* Nothing to be done for mixer device, it was closed after init   */

    /* Note the ALSA output device must be closed before anything else */
    /*      if this driver expends it's backlog of data before it is   */
    /*      closed, it will lock up the application.                   */


    /* Free output buffer */
    if( initMask & OUTPUT_BUFFER_ALLOCATED )
    {
        Buffer_delete( hBufOut );
    }

    /* Close ALSA device */
    if( initMask & ALSA_INITIALIZED )
        Sound_delete( hSound );

    /* Free input buffer */
    if( initMask & INPUT_BUFFER_ALLOCATED )
    {
        Buffer_delete( hBufIn );
    }


    /* Return the status of the thread execution */
    DBG( "\tAudio thread cleanup complete. Exiting audio_thread_fxn\n" );
    return status;
}

