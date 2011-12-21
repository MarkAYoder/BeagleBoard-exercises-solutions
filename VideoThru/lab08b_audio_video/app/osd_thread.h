/*
 * osd_thread.h
 */

/* Success and failure definitions for the thread */
#define OSD_THREAD_SUCCESS (void *)  0
#define OSD_THREAD_FAILURE (void *) -1

/* Thread environment definition (i.e. what it needs to operate) */
typedef struct osd_thread_env
{
    int quit;               // Thread will run as long as quit = 0
} osd_thread_env;

/* Function prototypes */
void *osd_thread_fxn( void *arg );

