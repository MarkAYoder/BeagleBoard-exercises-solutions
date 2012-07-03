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

#include "vector_args.h"


/************************************************************
* Explicit External Declarations                            *
************************************************************/

void *C6RUN_MEM_malloc(size_t size);
void  C6RUN_MEM_free(void *ptr);


/************************************************************
* Local Macro Declarations                                  *
************************************************************/

#define ARRAY_CNT (5)
#define INIT_VAL  (1)


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
    signed char result;
    signed char *data = C6RUN_MEM_malloc(sizeof(signed char) * ARRAY_CNT);
    
    for (i =0; i<ARRAY_CNT; i++)
    {
      data[i] = INIT_VAL;
    }
    
    result = vector_arg_c(ARRAY_CNT,data);
    
    C6RUN_MEM_free(data);
    
    printf("Result = %hhd\n",result);
  }

  // unsigned char input
  {
    unsigned char result;
    unsigned char *data = C6RUN_MEM_malloc(sizeof(unsigned char) * ARRAY_CNT);
    
    for (i =0; i<ARRAY_CNT; i++)
    {
      data[i] = INIT_VAL;
    }
    
    result = vector_arg_uc(ARRAY_CNT,data);
    
    C6RUN_MEM_free(data);
    
    printf("Result = %hhd\n",result);
  }
  
  
  // signed short input
  {
    short result;
    short *data = C6RUN_MEM_malloc(sizeof(short) * ARRAY_CNT);
    
    for (i =0; i<ARRAY_CNT; i++)
    {
      data[i] = INIT_VAL*10;
    }
    
    result = vector_arg_s(ARRAY_CNT,data);
    
    C6RUN_MEM_free(data);
    
    printf("Result = %hd\n",result);
  }

  // unsigned short input
  {
    unsigned short result;
    unsigned short *data = C6RUN_MEM_malloc(sizeof(unsigned short) * ARRAY_CNT);
    
    for (i =0; i<ARRAY_CNT; i++)
    {
      data[i] = INIT_VAL*10;
    }
    
    result = vector_arg_us(ARRAY_CNT,data);
    
    C6RUN_MEM_free(data);
    
    printf("Result = %hd\n",result);
  }
  
  // signed int input
  {
    signed int result;
    signed int *data = C6RUN_MEM_malloc(sizeof(signed int) * ARRAY_CNT);
    
    for (i =0; i<ARRAY_CNT; i++)
    {
      data[i] = INIT_VAL*100;
    }
    
    result = vector_arg_i(ARRAY_CNT,data);
    
    C6RUN_MEM_free(data);
    
    printf("Result = %d\n",result);
  }

  // unsigned int input
  {
    unsigned int result;
    unsigned int *data = C6RUN_MEM_malloc(sizeof(unsigned int) * ARRAY_CNT);
    
    for (i =0; i<ARRAY_CNT; i++)
    {
      data[i] = INIT_VAL*100;
    }
    
    result = vector_arg_ui(ARRAY_CNT,data);
    
    C6RUN_MEM_free(data);
    
    printf("Result = %d\n",result);
  }
   
  // signed long long input
  {
    signed long long result;
    signed long long *data = C6RUN_MEM_malloc(sizeof(signed long long) * ARRAY_CNT);
    
    for (i =0; i<ARRAY_CNT; i++)
    {
      data[i] = INIT_VAL*10000;
    }
    
    result = vector_arg_ll(ARRAY_CNT,data);
    
    C6RUN_MEM_free(data);
    
    printf("Result = %lld\n",result);
  }
  
  // unsigned long long input
  {
    unsigned long long result;
    unsigned long long *data = C6RUN_MEM_malloc(sizeof(unsigned long long) * ARRAY_CNT);
    
    for (i =0; i<ARRAY_CNT; i++)
    {
      data[i] = INIT_VAL*10000;
    }
    
    result = vector_arg_ull(ARRAY_CNT,data);
    
    C6RUN_MEM_free(data);
    
    printf("Result = %lld\n",result);
  }  

  // float input
  {
    float result;
    float *data = C6RUN_MEM_malloc(sizeof(float) * ARRAY_CNT);
    
    for (i =0; i<ARRAY_CNT; i++)
    {
      data[i] = ((float)INIT_VAL)/10;
    }
    
    result = vector_arg_f(ARRAY_CNT,data);
    
    C6RUN_MEM_free(data);
    
    printf("Result = %0.6f\n",result);
  }  

  // double input
  {
    double result;
    double *data = C6RUN_MEM_malloc(sizeof(double) * ARRAY_CNT);
    
    for (i =0; i<ARRAY_CNT; i++)
    {
      data[i] = ((float)INIT_VAL)/100;
    }
    
    result = vector_arg_d(ARRAY_CNT,data);
    
    C6RUN_MEM_free(data);
    
    printf("Result = %0.6f\n",result);
  }
  
  return 0;
}


/***********************************************************
* Local Function Definitions                               *
***********************************************************/


/***********************************************************
* End file                                                 *
***********************************************************/
