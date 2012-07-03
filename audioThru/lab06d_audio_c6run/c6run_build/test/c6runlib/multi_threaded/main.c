/*
 * main.c
 */

/*
 * Copyright (C) 2011 Texas Instruments Incorporated - http://www.ti.com/ 
 */

/* 
 *  Redistribution and use in source and binary forms, with or without 
 *  modification, are permitted provided that the following conditions 
 *  are met:
 *
 *    Redistributions of source code must retain the above copyright 
 *    notice, this list of conditions and the following disclaimer.
 *
 *    Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the 
 *    documentation and/or other materials provided with the   
 *    distribution.
 *
 *    Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS 
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT 
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 *  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT 
 *  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
 *  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT 
 *  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 *  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 *  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT 
 *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE 
 *  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include <pthread.h>

#include "multi_threaded.h"

/************************************************************
* Explicit External Declarations                            *
************************************************************/

#if defined(DSP_IN_USE)
  extern int C6RUN_libInit(void);
  extern void *C6RUN_MEM_malloc(size_t size);
  extern void C6RUN_MEM_free(void *ptr);
#endif


/************************************************************
* Local Macro Declarations                                  *
************************************************************/

#define NUMTHREADS (3)
#define PASS (0xAA5511EE)


/************************************************************
* Local Typedef Declarations                                *
************************************************************/


/************************************************************
* Local Function Declarations                               *
************************************************************/

static void *threadfunc(void * pThreadNum);


/************************************************************
* Local Variable Definitions                                *
************************************************************/


/************************************************************
* Global Variable Definitions                               *
************************************************************/

int32_t *pOutadd, *pOutsub, *pOutmult;


/************************************************************
* Global Function Definitions                               *
************************************************************/

int main ()
{
  int32_t i;
  pthread_t thread[NUMTHREADS];
  void *status;
  
  // Allocate mem for buffers
#if defined(DSP_IN_USE)
  C6RUN_libInit();

  // Must be dynamic using C6RUN APIs in order to give to the DSP
  pOutadd   = (int32_t *) C6RUN_MEM_malloc(4);
  pOutsub   = (int32_t *) C6RUN_MEM_malloc(4);
  pOutmult  = (int32_t *) C6RUN_MEM_malloc(4);
#else
  pOutadd   = (int32_t *) malloc(4);
  pOutsub   = (int32_t *) malloc(4);
  pOutmult  = (int32_t *) malloc(4);
#endif

  for (i = 0; i < NUMTHREADS; i++)
  {
	  // Create independent threads each of which will execute function */
	  pthread_create( &thread[i], NULL, threadfunc, (void *)i);
  }

  for (i = 0; i < NUMTHREADS; i++)
  {
    printf("Waiting for thread %d\n", i);
    pthread_join(thread[i], &status);
    if ( ((int32_t)status) != PASS)
    {
      printf("---->Thread %d failed.\n", i);
      exit(1);
    }
    else
    {
      printf("---->Thread %d returns.\n", i);

      // Print results as the threads end
      if (i == 0)
      {
        printf("  -----> Add: %d\n", *pOutadd);
      }
      else if (i == 1)
      {
        printf("  -----> Sub: %d\n", *pOutsub);
      }
      else if (i == 2)
      {
        printf("  -----> Mult: %d\n", *pOutmult);
      }
    }
  }

#if defined(DSP_IN_USE)
  C6RUN_MEM_free(pOutadd);
  C6RUN_MEM_free(pOutsub);
  C6RUN_MEM_free(pOutmult);
#else
  free(pOutadd);
  free(pOutsub);
  free(pOutmult);
#endif
    
  return 0;
}



/***********************************************************
* Local Function Definitions                               *
***********************************************************/

static void *threadfunc(void * pThreadNum)
{
  int32_t i = (int32_t) pThreadNum;

	printf("--->Entered thread number: %d \n", i);

  if (i == 0 )
  {
    multi_threaded_add(10, pOutadd);
  }
  else if (i == 1 )
  {
    multi_threaded_sub(10, pOutsub);
  }
  else if (i == 2 )
  {
    multi_threaded_mult(10, pOutmult);
  }

  return ((void *)PASS);
}


/***********************************************************
* End file                                                 *
***********************************************************/