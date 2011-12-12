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

#include "memory_tests.h"


/************************************************************
* Explicit External Declarations                            *
************************************************************/

extern void    *C6RUN_MEM_malloc(size_t size);
extern void    *C6RUN_MEM_calloc(size_t nelem, size_t elsize);
extern void    *C6RUN_MEM_realloc(void *oldPtr,size_t size);
extern void    *C6RUN_MEM_memalign(size_t alignment, size_t size);
extern void     C6RUN_MEM_free(void* ptr);
extern void     C6RUN_MEM_printStats(void);

extern uint32_t C6RUN_MEM_binSize;


/************************************************************
* Local Macro Declarations                                  *
************************************************************/

#define MIN_BUF_SIZE    (32)
#define MAX_BUF_SIZE    (1024)
#define BUF_CNT         (1024)

/************************************************************
* Local Typedef Declarations                                *
************************************************************/


/************************************************************
* Local Function Declarations                               *
************************************************************/


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
  int i, j, k;
  int32_t **buffers;
  
  
  buffers = (int32_t **) malloc(BUF_CNT*sizeof(int32_t *));

#if (1)
  // Test 1: malloc many identical sized buffers and then free in the same order allocated
  for (j = MIN_BUF_SIZE; j <= MAX_BUF_SIZE; j<<=1)
  {
    printf("Test 1: Buffers of size 0x%08X.\n",j);

    for (i = 0; i < BUF_CNT; i++)
    {
      buffers[i] = (int32_t *) C6RUN_MEM_malloc(j);
      if (buffers[i] == NULL)
      {
        printf("Allocation failed for buffer #%d.\n",i);
        exit(1);
      }
    }

    for (i = 0; i < BUF_CNT; i++)
    {
      C6RUN_MEM_free(buffers[i]);
      buffers[i] = NULL;
    }
    printf("        Passed!\n");
  }
 
  // Check to make sure no memory is in use 
  C6RUN_MEM_printStats();
#endif

#if (1)
  // Test 2: malloc many identical sized buffers and then free in the reverse order allocated
  for (j = MIN_BUF_SIZE; j <= MAX_BUF_SIZE; j<<=1)
  {
    printf("Test 2: Buffers of size 0x%08X.\n",j);
    for (i = 0; i < BUF_CNT; ++i)
    {
      buffers[i] = (int32_t *) C6RUN_MEM_malloc(j);
      if (buffers[i] == NULL)
      {
        printf("Allocation failed for buffer #%d.\n",i);
        exit(1);
      }
    }

    for (i = (BUF_CNT); i > 0; --i)
    {
      C6RUN_MEM_free(buffers[i-1]);
      buffers[i] = NULL;
    }
    printf("        Passed!\n");
  }
  
  // Check to make sure no memory is in use
  C6RUN_MEM_printStats();
#endif

#if (1)
  // Test 3: use malloced buffers as input buffers to the DSP
  for (j = MIN_BUF_SIZE; j <= MAX_BUF_SIZE; j<<=1)
  { 
    printf("Test 3: Buffers of size 0x%08X.\n",j);
    
    // Allocate the buffers
    printf("  Allocate\n");
    for (i = 0; i < BUF_CNT; ++i)
    {
      buffers[i] = (int32_t *) C6RUN_MEM_malloc(j);
      if (buffers[i] == NULL)
      {
        printf("Allocation failed for buffer #%d.\n",i);
        exit(1);
      }
    }

    
    // Prepare the input buffers, call the DSP
    printf("  Call the DSP\n");
    for (i = 0; i < BUF_CNT; ++i)
    {
      int64_t retVal, sum = 0;
      
      for (k=0; k< (j>>2); k++)
      {
        buffers[i][k] = k;
        sum += k;
      }

      retVal = inbuf_test(buffers[i], (j>>2));
      if (retVal != sum)
      {
        printf("inbuf_test (retVal = %lld) function failure for buffer #%d.\n",retVal,i);
        exit(1);
      }
      
      //Make sure the input buffer was not modified
      for (k=0; k< (j>>2); k++)
      {
        if (buffers[i][k] != k)
        {
          printf("inbuf_test buffer corrupt failure for buffer #%d.\n",i);
          for (k=0; k<(j>>2); k++)
          {
            printf("buffers[%d][%d] = %d\n",i,k,buffers[i][k]);
          }
          exit(1);
        }
      }
    }
    
    
    // Free the buffers
    printf("  Free\n");
    for (i=0; i<BUF_CNT; i++)
    {
      C6RUN_MEM_free(buffers[i]);
      buffers[i] =  NULL;
    }

    C6RUN_MEM_printStats();    
    
    printf("        Passed!\n");
  }
#endif

#if (1)
  // Test 3: use malloced buffers as input buffers to the DSP
  for (j = MIN_BUF_SIZE; j <= MAX_BUF_SIZE; j<<=1)
  { 
    printf("Test 4: Buffers of size 0x%08X.\n",j);
    
    // Allocate the buffers
    printf("  Allocate\n");
    for (i = 0; i < BUF_CNT; ++i)
    {
      buffers[i] = (int32_t *) C6RUN_MEM_malloc(j);
      if (buffers[i] == NULL)
      {
        printf("Allocation failed for buffer #%d.\n",i);
        exit(1);
      }
    }

    
    // Prepare the input buffers, call the DSP
    // This test uses a partial buffer, passing a pointer from the middle of the buffer
    // instead of from buffer base
    printf("  Call the DSP\n");
    for (i = 0; i < BUF_CNT; ++i)
    {
      int64_t retVal, sum = 0;
      
      for (k=(j>>3); k< (j>>2); k++)
      {
        buffers[i][k] = k;
        sum += k;
      }

      retVal = inbuf_test(&(buffers[i][j>>3]), (j>>3));
      if (retVal != sum)
      {
        printf("inbuf_test (retVal = %lld) function failure for buffer #%d.\n",retVal,i);
        exit(1);
      }
    }
    
    
    // Free the buffers
    printf("  Free\n");
    for (i=0; i<BUF_CNT; i++)
    {
      C6RUN_MEM_free(buffers[i]);
      buffers[i] =  NULL;
    }

    C6RUN_MEM_printStats();    
    
    printf("        Passed!\n");
  }
#endif 
  
  return 0;
}



/***********************************************************
* Local Function Definitions                               *
***********************************************************/


/***********************************************************
* End file                                                 *
***********************************************************/
