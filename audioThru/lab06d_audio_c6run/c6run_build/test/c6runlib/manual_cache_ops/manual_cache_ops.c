/*
 * manual_cache_ops.c
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

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include <limits.h>
#include <float.h>

#include "manual_cache_ops.h"

/************************************************************
* Explicit External Declarations                            *
************************************************************/

extern void     C6RUN_CACHE_globalInv( void );
extern void     C6RUN_CACHE_globalWb( void );
extern void     C6RUN_CACHE_inv(void *ptr,size_t size);
extern void     C6RUN_CACHE_wb(void *ptr,size_t size);


/************************************************************
* Local Macro Declarations                                  *
************************************************************/


/************************************************************
* Local Typedef Declarations                                *
************************************************************/


/************************************************************
* Local Function Declarations                               *
************************************************************/

static int32_t LOCAL_sumBuffer(int32_t *buf, int32_t cnt);


/************************************************************
* Local Variable Definitions                                *
************************************************************/


/************************************************************
* Global Variable Definitions                               *
************************************************************/


/************************************************************
* Global Function Definitions                               *
************************************************************/

int32_t manual_inbuf_test(NONE int32_t *inBuf, int32_t cnt)
{ 
  C6RUN_CACHE_inv(inBuf, (size_t) (cnt * sizeof(int32_t)) );
  
  return LOCAL_sumBuffer(inBuf, cnt);
}

int32_t manual_inbuf_global_test(NONE int32_t *inBuf, int32_t cnt)
{ 
  C6RUN_CACHE_globalInv();
  
  return LOCAL_sumBuffer(inBuf, cnt);
}

int32_t inbuf_test(INBUF int32_t *inBuf, int32_t cnt)
{ 
  return LOCAL_sumBuffer(inBuf, cnt);
}



void manual_outbuf_test(NONE int32_t *outBuf, int32_t cnt)
{
  int i;
  
  for (i = 0; i < cnt; i++)
  {
    outBuf[i] = i;
  }
  
  C6RUN_CACHE_wb(outBuf, (size_t) (cnt * sizeof(int32_t)) );
}

void manual_outbuf_global_test(NONE int32_t *outBuf, int32_t cnt)
{
  int i;
  
  for (i = 0; i < cnt; i++)
  {
    outBuf[i] = i;
  }
  
  C6RUN_CACHE_globalWb();
}

void outbuf_test(OUTBUF int32_t *outBuf, int32_t cnt)
{
  int i;
  
  for (i = 0; i < cnt; i++)
  {
    outBuf[i] = 2*i;
  }
}




/***********************************************************
* Local Function Definitions                               *
***********************************************************/

static int32_t LOCAL_sumBuffer(int32_t *buf, int32_t cnt)
{
  int i;
  int32_t sum = 0;

  for (i = 0; i < cnt; i++)
  {
    sum += buf[i];
  }
  return sum;
}


/***********************************************************
* End file                                                 *
***********************************************************/
