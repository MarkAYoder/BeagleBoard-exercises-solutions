/*
 * main.c
 */

/*
 * Copyright (C) 2010 Texas Instruments Incorporated - http://www.ti.com/ 
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

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

#include <sys/time.h>

#include "malloc_test.h"


/************************************************************
* Explicit External Declarations                            *
************************************************************/


/************************************************************
* Local Macro Declarations                                  *
************************************************************/

#define TOTAL_MEM (1024*1024)

/************************************************************
* Local Typedef Declarations                                *
************************************************************/


/************************************************************
* Local Function Declarations                               *
************************************************************/

static double LOCAL_elapsed_usec(void);


/************************************************************
* Local Variable Definitions                                *
************************************************************/


/************************************************************
* Global Variable Definitions                               *
************************************************************/


/************************************************************
* Global Function Definitions                               *
************************************************************/

// Main Test harness code
int main()
{
  int i;
  
  // Allocate 1 MB of memory in 64 byte chunks
  {
  #undef  BUF_SIZE
  #define BUF_SIZE (64)
    void *ptr[(TOTAL_MEM/BUF_SIZE)];
    LOCAL_elapsed_usec();
    for (int i=0; i<(TOTAL_MEM/BUF_SIZE); i++)
    {
      ptr[i] = malloc(BUF_SIZE);
    }
    printf("Malloc %d byte buffers, per op time elapsed: %0.6f\n",BUF_SIZE,LOCAL_elapsed_usec()/(TOTAL_MEM/BUF_SIZE));
    
    LOCAL_elapsed_usec();
    for (int i=0; i<(TOTAL_MEM/BUF_SIZE); i++)
    {
      free(ptr[i]);
    }
    printf("Free %d byte buffers, per op time elapsed: %0.6f\n",BUF_SIZE,LOCAL_elapsed_usec()/(TOTAL_MEM/BUF_SIZE));
  }
  
  // Allocate 1 MB of memory in 256 byte chunks
  {
  #undef  BUF_SIZE
  #define BUF_SIZE (128)
    void *ptr[(TOTAL_MEM/BUF_SIZE)];
    LOCAL_elapsed_usec();
    for (int i=0; i<(TOTAL_MEM/BUF_SIZE); i++)
    {
      ptr[i] = malloc(BUF_SIZE);
    }
    printf("Malloc %d byte buffers, per op time elapsed: %0.6f\n",BUF_SIZE,LOCAL_elapsed_usec()/(TOTAL_MEM/BUF_SIZE));
    
    LOCAL_elapsed_usec();
    for (int i=0; i<(TOTAL_MEM/BUF_SIZE); i++)
    {
      free(ptr[i]);
    }
    printf("Free %d byte buffers, per op time elapsed: %0.6f\n",BUF_SIZE,LOCAL_elapsed_usec()/(TOTAL_MEM/BUF_SIZE));
  }
  
  // Allocate 1 MB of memory in 256 byte chunks
  {
  #undef  BUF_SIZE
  #define BUF_SIZE (256)
    void *ptr[(TOTAL_MEM/BUF_SIZE)];
    LOCAL_elapsed_usec();
    for (int i=0; i<(TOTAL_MEM/BUF_SIZE); i++)
    {
      ptr[i] = malloc(BUF_SIZE);
    }
    printf("Malloc %d byte buffers, per op time elapsed: %0.6f\n",BUF_SIZE,LOCAL_elapsed_usec()/(TOTAL_MEM/BUF_SIZE));
    
    LOCAL_elapsed_usec();
    for (int i=0; i<(TOTAL_MEM/BUF_SIZE); i++)
    {
      free(ptr[i]);
    }
    printf("Free %d byte buffers, per op time elapsed: %0.6f\n",BUF_SIZE,LOCAL_elapsed_usec()/(TOTAL_MEM/BUF_SIZE));
  }

  // Allocate 1 MB of memory in 1024 byte chunks
  {
  #undef  BUF_SIZE
  #define BUF_SIZE (1024)
    void *ptr[(TOTAL_MEM/BUF_SIZE)];
    LOCAL_elapsed_usec();
    for (int i=0; i<(TOTAL_MEM/BUF_SIZE); i++)
    {
      ptr[i] = malloc(BUF_SIZE);
    }
    printf("Malloc %d byte buffers, per op time elapsed: %0.6f\n",BUF_SIZE,LOCAL_elapsed_usec()/(TOTAL_MEM/BUF_SIZE));
    
    LOCAL_elapsed_usec();
    for (int i=0; i<(TOTAL_MEM/BUF_SIZE); i++)
    {
      free(ptr[i]);
    }
    printf("Free %d byte buffers, per op time elapsed: %0.6f\n",BUF_SIZE,LOCAL_elapsed_usec()/(TOTAL_MEM/BUF_SIZE));
  }  
  
  // Allocate 1 MB of memory in 2048 byte chunks
  {
  #undef  BUF_SIZE
  #define BUF_SIZE (2048)
    void *ptr[(TOTAL_MEM/BUF_SIZE)];
    LOCAL_elapsed_usec();
    for (int i=0; i<(TOTAL_MEM/BUF_SIZE); i++)
    {
      ptr[i] = malloc(BUF_SIZE);
    }
    printf("Malloc %d byte buffers, per op time elapsed: %0.6f\n",BUF_SIZE,LOCAL_elapsed_usec()/(TOTAL_MEM/BUF_SIZE));
    
    LOCAL_elapsed_usec();
    for (int i=0; i<(TOTAL_MEM/BUF_SIZE); i++)
    {
      free(ptr[i]);
    }
    printf("Free %d byte buffers, per op time elapsed: %0.6f\n",BUF_SIZE,LOCAL_elapsed_usec()/(TOTAL_MEM/BUF_SIZE));
  }  

  // Allocate 1 MB of memory in 4096 byte chunks
  {
  #undef  BUF_SIZE
  #define BUF_SIZE (4096)
    void *ptr[(TOTAL_MEM/BUF_SIZE)];
    LOCAL_elapsed_usec();
    for (int i=0; i<(TOTAL_MEM/BUF_SIZE); i++)
    {
      ptr[i] = malloc(BUF_SIZE);
    }
    printf("Malloc %d byte buffers, per op time elapsed: %0.6f\n",BUF_SIZE,LOCAL_elapsed_usec()/(TOTAL_MEM/BUF_SIZE));
    
    LOCAL_elapsed_usec();
    for (int i=0; i<(TOTAL_MEM/BUF_SIZE); i++)
    {
      free(ptr[i]);
    }
    printf("Free %d byte buffers, per op time elapsed: %0.6f\n",BUF_SIZE,LOCAL_elapsed_usec()/(TOTAL_MEM/BUF_SIZE));
  }

  // Allocate 1 MB of memory in 16K byte chunks
  {
  #undef  BUF_SIZE
  #define BUF_SIZE (16*1024)
    void *ptr[(TOTAL_MEM/BUF_SIZE)];
    LOCAL_elapsed_usec();
    for (int i=0; i<(TOTAL_MEM/BUF_SIZE); i++)
    {
      ptr[i] = malloc(BUF_SIZE);
    }
    printf("Malloc %d byte buffers, per op time elapsed: %0.6f\n",BUF_SIZE,LOCAL_elapsed_usec()/(TOTAL_MEM/BUF_SIZE));
    
    LOCAL_elapsed_usec();
    for (int i=0; i<(TOTAL_MEM/BUF_SIZE); i++)
    {
      free(ptr[i]);
    }
    printf("Free %d byte buffers, per op time elapsed: %0.6f\n",BUF_SIZE,LOCAL_elapsed_usec()/(TOTAL_MEM/BUF_SIZE));
  }

  // Allocate 1 MB of memory in 32K byte chunks
  {
  #undef  BUF_SIZE
  #define BUF_SIZE (32*1024)
    void *ptr[(TOTAL_MEM/BUF_SIZE)];
    LOCAL_elapsed_usec();
    for (int i=0; i<(TOTAL_MEM/BUF_SIZE); i++)
    {
      ptr[i] = malloc(BUF_SIZE);
    }
    printf("Malloc %d byte buffers, per op time elapsed: %0.6f\n",BUF_SIZE,LOCAL_elapsed_usec()/(TOTAL_MEM/BUF_SIZE));
    
    LOCAL_elapsed_usec();
    for (int i=0; i<(TOTAL_MEM/BUF_SIZE); i++)
    {
      free(ptr[i]);
    }
    printf("Free %d byte buffers, per op time elapsed: %0.6f\n",BUF_SIZE,LOCAL_elapsed_usec()/(TOTAL_MEM/BUF_SIZE));
  }
  
  // Allocate 1 MB of memory in 64K byte chunks
  {
  #undef  BUF_SIZE
  #define BUF_SIZE (64*1024)
    void *ptr[(TOTAL_MEM/BUF_SIZE)];
    LOCAL_elapsed_usec();
    for (int i=0; i<(TOTAL_MEM/BUF_SIZE); i++)
    {
      ptr[i] = malloc(BUF_SIZE);
    }
    printf("Malloc %d byte buffers, per op time elapsed: %0.6f\n",BUF_SIZE,LOCAL_elapsed_usec()/(TOTAL_MEM/BUF_SIZE));
    
    LOCAL_elapsed_usec();
    for (int i=0; i<(TOTAL_MEM/BUF_SIZE); i++)
    {
      free(ptr[i]);
    }
    printf("Free %d byte buffers, per op time elapsed: %0.6f\n",BUF_SIZE,LOCAL_elapsed_usec()/(TOTAL_MEM/BUF_SIZE));
  }
  
  // Allocate 1 MB in single chunk
  {
  #undef  BUF_SIZE
  #define BUF_SIZE (1*1024*1024)
    void *ptr;
    LOCAL_elapsed_usec();
    ptr = malloc(BUF_SIZE);
    printf("Malloc %d byte buffer, per op time elapsed: %0.6f\n",BUF_SIZE,LOCAL_elapsed_usec());
    
    LOCAL_elapsed_usec();
    free(ptr);
    printf("Free %d byte buffer, per op time elapsed: %0.6f\n",BUF_SIZE,LOCAL_elapsed_usec());
  }  
  
  // Allocate 2 MB in single chunk
  {
  #undef  BUF_SIZE
  #define BUF_SIZE (2*1024*1024)
    void *ptr;
    LOCAL_elapsed_usec();
    ptr = malloc(BUF_SIZE);
    printf("Malloc %d byte buffer, per op time elapsed: %0.6f\n",BUF_SIZE,LOCAL_elapsed_usec());
    
    LOCAL_elapsed_usec();
    free(ptr);
    printf("Free %d byte buffer, per op time elapsed: %0.6f\n",BUF_SIZE,LOCAL_elapsed_usec());
  }  
  
  // Allocate 4 MB in single chunk
  {
  #undef  BUF_SIZE
  #define BUF_SIZE (4*1024*1024)
    void *ptr;
    LOCAL_elapsed_usec();
    ptr = malloc(BUF_SIZE);
    printf("Malloc %d byte buffer, per op time elapsed: %0.6f\n",BUF_SIZE,LOCAL_elapsed_usec());
    
    LOCAL_elapsed_usec();
    free(ptr);
    printf("Free %d byte buffer, per op time elapsed: %0.6f\n",BUF_SIZE,LOCAL_elapsed_usec());
  }  
  
  // Allocate 8 MB in single chunk
  {
  #undef  BUF_SIZE
  #define BUF_SIZE (8*1024*1024)
    void *ptr;
    LOCAL_elapsed_usec();
    ptr = malloc(BUF_SIZE);
    printf("Malloc %d byte buffer, per op time elapsed: %0.6f\n",BUF_SIZE,LOCAL_elapsed_usec());
    
    LOCAL_elapsed_usec();
    free(ptr);
    printf("Free %d byte buffer, per op time elapsed: %0.6f\n",BUF_SIZE,LOCAL_elapsed_usec());
  }  
  
  // Allocate 12 MB in single chunk
  {
  #undef  BUF_SIZE
  #define BUF_SIZE (12*1024*1024)
    void *ptr;
    LOCAL_elapsed_usec();
    ptr = malloc(BUF_SIZE);
    printf("Malloc %d byte buffer, per op time elapsed: %0.6f\n",BUF_SIZE,LOCAL_elapsed_usec());
    
    LOCAL_elapsed_usec();
    free(ptr);
    printf("Free %d byte buffer, per op time elapsed: %0.6f\n",BUF_SIZE,LOCAL_elapsed_usec());
  }  
  
  // Allocate 16 MB in single chunk
  {
  #undef  BUF_SIZE
  #define BUF_SIZE (16*1024*1024)
    void *ptr;
    LOCAL_elapsed_usec();
    ptr = malloc(BUF_SIZE);
    printf("Malloc %d byte buffer, per op time elapsed: %0.6f\n",BUF_SIZE,LOCAL_elapsed_usec());
    
    LOCAL_elapsed_usec();
    free(ptr);
    printf("Free %d byte buffer, per op time elapsed: %0.6f\n",BUF_SIZE,LOCAL_elapsed_usec());
  }    
  
  malloc_test();
  
  return 0;
}


/***********************************************************
* Local Function Definitions                               *
***********************************************************/

static double LOCAL_elapsed_usec(void)
{
  double elapsed;
  struct timeval currentTime;
  static struct timeval previousTime;

  gettimeofday(&currentTime, 0);
  elapsed = (currentTime.tv_sec + 1e-6 * currentTime.tv_usec) -
            (previousTime.tv_sec + 1e-6 * previousTime.tv_usec);

  previousTime = currentTime;
  return elapsed;
}

/***********************************************************
* End file                                                 *
***********************************************************/
