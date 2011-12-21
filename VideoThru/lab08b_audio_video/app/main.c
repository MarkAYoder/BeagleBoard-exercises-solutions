/*
 *   main.c
 */

/* Standard Linux headers */
#include <stdio.h>                              //  Always include this header
#include <stdlib.h>                             //  Always include this header
#include <signal.h>                             //  Defines signal-handling functions
#include <unistd.h>                             //  Defines sleep function

#include <pthread.h>                            // Posix thread types

/* Codec Engine headers */
#include <xdc/std.h>                            // xdc definitions, must come 1st
#include <ti/sdo/ce/CERuntime.h>                // defines CERuntime_init
#include <ti/sdo/ce/utils/trace/TraceUtil.h>    // CE Tracing utility

/* Application headers */
#include "debug.h"
#include "thread.h"
#include "audio_thread.h"
#include "video_thread.h"
#include "osd_thread.h"

/* DMAI headers */
#include <ti/sdo/dmai/Dmai.h>

/* The engine to use in this application */
#define ENGINE_NAME     "encodedecode"           // As defined in engine .cfg file

/* Global thread environments */
audio_thread_env audio_env = {0};
video_thread_env video_env = {0};
osd_thread_env osd_env = {0};

/* Store previous signal handler and call it */
void (*pSigPrev)(int sig);

/* Callback called when SIGINT is sent to the process (Ctrl-C) */
void signal_handler(int sig)
{
    DBG( "Ctrl-C pressed, cleaning up and exiting..\n" );
    audio_env.quit = 1;

/*  If we're in debug mode, pause to give the prev thread time  *
 *     so that feedback of the two threads doesn't interleave   */
#ifdef _DEBUG_
    sleep( 1 );
#endif
    video_env.quit = 1;

#ifdef _DEBUG_
    sleep( 1 );
#endif
    osd_env.quit = 1;

    if( pSigPrev != NULL )
        (*pSigPrev)( sig );
}


/******************************************************************************
 * main
 ******************************************************************************/
int main(int argc, char *argv[])
{
/* The levels of initialization for initMask */
#define AUDIOTHREADATTRSCREATED 0x1
#define AUDIOTHREADCREATED      0x2
#define VIDEOTHREADATTRSCREATED 0x4
#define VIDEOTHREADCREATED      0x8
#define OSDTHREADATTRSCREATED   0x10
#define OSDTHREADCREATED        0x20
    unsigned int    initMask  = 0;
    int             status    = EXIT_SUCCESS;

    pthread_t       audioThread, videoThread, osdThread;

    void *audioThreadReturn;
    void *videoThreadReturn;
    void *osdThreadReturn;

    /* Set the signal callback for Ctrl-C */
    pSigPrev = signal( SIGINT, signal_handler );

    /* Always call Dmai_init before using any dmai methods */
    Dmai_init();

    /* Create a thread for audio */
    DBG( "Creating audio thread\n" );

    if( launch_pthread( &audioThread, REALTIME, 
                        sched_get_priority_max( SCHED_RR ),
                        audio_thread_fxn, 
                        (void *) &audio_env ) 
	    != thread_SUCCESS )
    {
        ERR( "Failed to create audio thread\n" );
        status = EXIT_FAILURE;
        video_env.quit = 1;
        osd_env.quit = 1;
        goto cleanup;
    }

    initMask |= AUDIOTHREADCREATED;

#ifdef _DEBUG_
    sleep( 1 );
#endif


    /* Create a thread for video */

    DBG( "Creating video thread\n" );

    if( launch_pthread( &videoThread, 
                        TIMESLICE, 
                        0, 
                        video_thread_fxn, 
                        (void *) &video_env ) 
        != thread_SUCCESS )
    {
        ERR( "Failed to create video thread\n" );
        status = EXIT_FAILURE;
        audio_env.quit = 1;
        osd_env.quit = 1;
        goto cleanup;
    }

    initMask |= VIDEOTHREADCREATED;


#ifdef _DEBUG_
    sleep( 1 );
#endif

    /* Create a thread for osd */
    DBG( "Creating osd thread\n" );

    if( launch_pthread( &osdThread, 
                        TIMESLICE, 
                        0, 
                        osd_thread_fxn, 
                        (void *) &osd_env ) 
        != thread_SUCCESS )
    {
        ERR( "Failed to create osd thread\n" );
        status = EXIT_FAILURE;
        audio_env.quit = 1;
        video_env.quit = 1;
        goto cleanup;
    }

    initMask |= OSDTHREADCREATED;


cleanup:
    /* Main thread will wait here until audio and video threads terminate */
    /* If we're in debug mode, pause for a few seconds to give threada    */
    /*      time to initialize before displaying message                  */
#ifdef _DEBUG_
    sleep( 5 );
#endif

    printf( "All application threads started\n" );
    printf( "\tPress Ctrl-C to exit\n" );


    /* Wait until the audio thread terminates */
    if ( initMask & AUDIOTHREADCREATED ) 
    {
        pthread_join( audioThread, &audioThreadReturn );

        if( audioThreadReturn == AUDIO_THREAD_FAILURE )
            DBG( "Audio thread exited with FAILURE status\n" );
        else
            DBG( "Audio thread exited with SUCCESS status\n" );
    }

    /* Wait until the video thread terminates */
    if ( initMask & VIDEOTHREADCREATED ) 
    {
        pthread_join( videoThread, &videoThreadReturn );

        if( videoThreadReturn == VIDEO_THREAD_FAILURE )
            DBG( "Video thread exited with FAILURE status\n" );
        else
            DBG( "Video thread exited with SUCCESS status\n" );
    }


    /* Wait until the osd thread terminates */
    if ( initMask & OSDTHREADCREATED ) 
    {
        pthread_join( osdThread, &osdThreadReturn );

       if( osdThreadReturn == OSD_THREAD_FAILURE )
           DBG( "Osd thread exited with FAILURE status\n" );
    else
           DBG( "Osd thread exited with SUCCESS status\n" );
    }

    exit( status );
}

