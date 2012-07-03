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

#include "manual_cache_ops.h"


/************************************************************
* Explicit External Declarations                            *
************************************************************/

extern void    *C6RUN_MEM_malloc(size_t size);

// Memory cache management routines
extern void     C6RUN_CACHE_globalInv( void );
extern void     C6RUN_CACHE_globalWb( void );
extern void     C6RUN_CACHE_inv(void *ptr,size_t size);
extern void     C6RUN_CACHE_wb(void *ptr,size_t size);


/************************************************************
* Local Macro Declarations                                  *
************************************************************/

#define BUF_SIZE (1024)


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
  int i = 0;
  int32_t retSum, localSum;
  
  int32_t *inBuf = (int32_t *) C6RUN_MEM_malloc(BUF_SIZE*sizeof(int32_t));
  int32_t *outBuf = (int32_t *) C6RUN_MEM_malloc(BUF_SIZE*sizeof(int32_t));  
  
  
  // Prep data for call
  localSum = 0;
  for (i=0; i<BUF_SIZE; i++)
  {
    inBuf[i] = i;
    localSum += inBuf[i];
  }

  // Writeback array data before calling manual test function
  C6RUN_CACHE_globalWb();
  retSum = manual_inbuf_global_test(inBuf, BUF_SIZE);
  if (retSum != localSum)
  {
    printf("manual_inbuf_global_test() failed\n");
    printf("Returned Sum = %d, Local Sum = %d\n",retSum, localSum);
    exit(1);
  }
  printf("manual_inbuf_global_test() passed\n");
  printf("Returned Sum = %d, Local Sum = %d\n",retSum, localSum);
  


  // Prep data for call
  localSum = 0;
  for (i=0; i<BUF_SIZE; i++)
  {
    inBuf[i] = 2*i;
    localSum += inBuf[i];
  }
  
  retSum = inbuf_test(inBuf, BUF_SIZE);
  if (retSum != localSum)
  {
    printf("inbuf_test() failed\n");
    printf("Returned Sum = %d, Local Sum = %d\n",retSum, localSum);
    exit(1);
  }
  printf("inbuf_test() passed\n");
  printf("Returned Sum = %d, Local Sum = %d\n",retSum, localSum);
  
  

  // Prep data for call
  localSum = 0;
  for (i=0; i<BUF_SIZE; i++)
  {
    inBuf[i] = i;
    localSum += inBuf[i];
  }

  // Writeback array data before calling manual test function
  C6RUN_CACHE_wb((void *)inBuf, (size_t)(BUF_SIZE * sizeof(int32_t)));
  retSum = manual_inbuf_test(inBuf, BUF_SIZE);
  if (retSum != localSum)
  {
    printf("manual_inbuf_test() failed. \n");
    printf("Returned Sum = %d, Local Sum = %d\n",retSum, localSum);
    exit(1);
  }
  printf("manual_inbuf_test() passed\n");
  printf("Returned Sum = %d, Local Sum = %d\n",retSum, localSum);
  
    
  manual_outbuf_test(outBuf, BUF_SIZE);
  // Invalidate buffer before trying to use it
  C6RUN_CACHE_inv((void *)inBuf, (size_t)(BUF_SIZE * sizeof(int32_t)));

  // Validate returned values
  for (i=0; i<BUF_SIZE; i++)
  {
    if (outBuf[i] != i)
    {
      printf("manual_outbuf_test() failed\n");
      exit(1);
    }
  }
  printf("manual_outbuf_test() passed\n");
  
  
  outbuf_test(outBuf, BUF_SIZE);
  
  // Validate returned values
  for (i=0; i<BUF_SIZE; i++)
  {
    if (outBuf[i] != 2*i)
    {
      printf("outbuf_test() failed\n");
      exit(1);
    }
  }
  printf("outbuf_test() passed\n");
  
    

  manual_outbuf_global_test(outBuf, BUF_SIZE);
  // Invalidate buffer before trying to use it
  C6RUN_CACHE_globalInv();
  
  // Validate returned values
  for (i=0; i<BUF_SIZE; i++)
  {
    if (outBuf[i] != i)
    {
      printf("manual_outbuf_test() failed\n");
      exit(1);
    }
  }
  printf("manual_outbuf_test() failed\n");
  
    
  return 0;
}


/***********************************************************
* Local Function Definitions                               *
***********************************************************/


/***********************************************************
* End file                                                 *
***********************************************************/
