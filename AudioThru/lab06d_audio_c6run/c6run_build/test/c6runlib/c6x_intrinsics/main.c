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
#include <string.h>

#include <sys/time.h>

#include "DSP_iir.h"


/************************************************************
* Explicit External Declarations                            *
************************************************************/

void *C6RUN_MEM_malloc(size_t size);
void *C6RUN_MEM_memalign(size_t alignment, size_t size);
void  C6RUN_MEM_free(void *ptr);


/************************************************************
* Local Macro Declarations                                  *
************************************************************/

#define ARRAY_CNT (20)

#define NUM_COEFS (10)


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
  int i;
  int nCoefs = NUM_COEFS;
  
  short coefs[NUM_COEFS] = 
  {
    0x0100,0x8010,0x9000,0x0080,0x0000,0x01FF,0x8F10,0x90DC,0x0A8F,0x1BBB
  };
  
  short state[NUM_COEFS] = 
  {
    0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
  };

  short input[ARRAY_CNT] = 
  {
    0x010,0x0010,0x0010,0x0010,0x0010,0x0010,0x0010,0x0010,0x0010,0x0010,
    0x010,0x0010,0x0010,0x0010,0x0010,0x0010,0x0010,0x0010,0x0010,0x0010,
  };
  short result[ARRAY_CNT];

  // Allocate and fill buffers that we can pass to the DSP
  short *state_dsp = (short *) C6RUN_MEM_memalign(8,sizeof(short)*NUM_COEFS);
  short *coefs_dsp = (short *) C6RUN_MEM_memalign(8,sizeof(short)*NUM_COEFS);
  memcpy(state_dsp,state,sizeof(short)*NUM_COEFS);
  memcpy(coefs_dsp,coefs,sizeof(short)*NUM_COEFS);
  
  for (i = 0; i<ARRAY_CNT; i++)
  {
    result[i] = DSP_iir ( input[i], coefs_dsp, nCoefs, state_dsp);
    printf("result[%d] = 0x%04X\n",i,result[i]);
  }

  C6RUN_MEM_free(coefs_dsp);
  C6RUN_MEM_free(state_dsp);
  
  return 0;
}


/***********************************************************
* Local Function Definitions                               *
***********************************************************/


/***********************************************************
* End file                                                 *
***********************************************************/
