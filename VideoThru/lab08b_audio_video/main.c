/*
 *   main.c
 *
 * ============================================================================
 * Copyright (c) Texas Instruments Inc 2005
 *
 * Use of this software is controlled by the terms and conditions found in the
 * license agreement under which this software has been supplied or provided.
 * ============================================================================
 */

// Standard Linux headers
#include     <stdio.h>	// Always include this header
#include     <stdlib.h>	// Always include this header
#include     <signal.h>	// Defines signal-handling functions (i.e. trap Ctrl-C)
#include     <unistd.h>	// sleep()
#include     <pthread.h>

// Application headers
#include     "debug.h"
#include     "audio_thread.h"
#include     "video_thread.h"
#include "thread.h"

/* Global thread environments */
audio_thread_env audio_env = {0};
video_thread_env video_env = {0};

/* Thread handles */
pthread_t audioThread, videoThread;
void *audioThreadReturn, *videoThreadReturn;

/* Store previous signal handler and call it */
void (*pSigPrev)(int sig);

/* Callback called when SIGINT is sent to the process (Ctrl-C) */
void signal_handler(int sig) {
    DBG( "Ctrl-C pressed, cleaning up and exiting..\n" );

    audio_env.quit = 1;
#ifdef _DEBUG_
    sleep(1);
#endif
    video_env.quit = 1;

    if( pSigPrev != NULL )
        (*pSigPrev)( sig );
}

//*****************************************************************************
//*  main
//*****************************************************************************
int main(int argc, char *argv[])
{
/* The levels of initialization for initMask */
#define VIDEOTHREADATTRSCREATED 0x1
#define VIDEOTHREADCREATED      0x2
#define AUDIOTHREADCREATED      0x4
    unsigned int    initMask  = 0;
    int             status    = EXIT_SUCCESS;

    void *videoThreadReturn;
    void *audioThreadReturn;

    /* Set the signal callback for Ctrl-C */
    pSigPrev = signal( SIGINT, signal_handler );

    /* Make video frame buffer visible */
    system("cd ..; ./vid1Show");

    // Call audio thread function
    DBG( "Creating audio thread\n" );

    if(launch_pthread(&audioThread, REALTIME, 99, &audio_thread_fxn, &audio_env) 
		!= thread_SUCCESS){
	ERR("pthread create failed for audio thread\n");
	status = EXIT_FAILURE;
	goto cleanup;
	}
    initMask |= AUDIOTHREADCREATED;    
#ifdef _DEBUG_
    sleep(1);
#endif
    /* Create a thread for video */
    DBG( "Creating video thread\n" );

    /* Create a thread for video loopthru */
    if(launch_pthread(&videoThread, TIMESLICE, 0, &video_thread_fxn, &video_env) 
		!= thread_SUCCESS){
	ERR("pthread create failed for video thread\n");
	status = EXIT_FAILURE;
	goto cleanup;
	}
    initMask |= VIDEOTHREADCREATED;    

    sleep(1);

cleanup:
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

    /* Make video frame buffer invisible */
    system("cd ..; ./resetVideo");

    exit( status );
}
