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

#include "scalar_typedef_args.h"


/************************************************************
* Explicit External Declarations                            *
************************************************************/


/************************************************************
* Local Macro Declarations                                  *
************************************************************/

#define LOOP_CNT (5)
#define INIT_VAL (1)

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

  // signed char input
  {
    int8_t result = INIT_VAL;
    
    for (i =0; i<LOOP_CNT; i++)
    {
      result = scalar_arg_c(result);
    }
    printf("Result = %hhd\n",result);
  }

  // unsigned char input
  {
    uint8_t result = INIT_VAL;
    
    for (i =0; i<LOOP_CNT; i++)
    {
      result = scalar_arg_uc(result);
    }
    printf("Result = %hhd\n",result);
  }
  
  // signed short input
  {
    int16_t result = INIT_VAL*10;
    
    for (i =0; i<LOOP_CNT; i++)
    {
      result = scalar_arg_s(result);
    }
    printf("Result = %hd\n",result);
  }

  // unsigned short input
  {
    uint16_t result = INIT_VAL*10;
    
    for (i =0; i<LOOP_CNT; i++)
    {
      result = scalar_arg_us(result);
    }
    printf("Result = %hd\n",result);
  }
  
  // signed int input
  {
    int32_t result = INIT_VAL*100;
    
    for (i =0; i<LOOP_CNT; i++)
    {
      result = scalar_arg_i(result);
    }
    printf("Result = %d\n",result);
  }

  // unsigned int input
  {
    uint32_t result = INIT_VAL*100;
    
    for (i =0; i<LOOP_CNT; i++)
    {
      result = scalar_arg_ui(result);
    }
    printf("Result = %d\n",result);
  }
  
  // signed long long input
  {
    int64_t result = INIT_VAL*10000;
    
    for (i =0; i<LOOP_CNT; i++)
    {
      result = scalar_arg_ll(result);
    }
    printf("Result = %lld\n",result);
  }

  // unsigned long long input
  {
    uint64_t result = INIT_VAL*10000;
    
    for (i =0; i<LOOP_CNT; i++)
    {
      result = scalar_arg_ull(result);
    }
    printf("Result = %lld\n",result);
  }
  
  return 0;
}


/***********************************************************
* Local Function Definitions                               *
***********************************************************/


/***********************************************************
* End file                                                 *
***********************************************************/
