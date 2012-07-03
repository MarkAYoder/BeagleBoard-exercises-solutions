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

#include "scalar_results.h"


/************************************************************
* Explicit External Declarations                            *
************************************************************/


/************************************************************
* Local Macro Declarations                                  *
************************************************************/


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

  // Signed char results
  {
    signed char result;

    printf("signed char results\n");
    printf("===================\n");    
    
    result = scalar_result_c_zero();
    printf("\tZero: Result = %hhd\n",result);
    result = scalar_result_c_one();
    printf("\tOne: Result = %hhd\n",result);
    result = scalar_result_c_negone();
    printf("\tNegOne: Result = %hhd\n",result);
    result = scalar_result_c_max();
    printf("\tMax: Result = %hhd\n",result);
    result = scalar_result_c_min();
    printf("\tMin: Result = %hhd\n",result);    
  }

  // Unsigned char results
  {
    unsigned char result;
    
    printf("unsigned char results\n");
    printf("=====================\n");
    
    result = scalar_result_uc_zero();
    printf("\tZero: Result = %hhu\n",result);
    result = scalar_result_uc_one();
    printf("\tOne: Result = %hhu\n",result);
    result = scalar_result_uc_max();
    printf("\tMax: Result = %hhu\n",result);
  }
  
  // Signed short results
  {
    signed short result;

    printf("signed short results\n");
    printf("====================\n");
    
    result = scalar_result_s_zero();
    printf("\tZero: Result = %hd\n",result);
    result = scalar_result_s_one();
    printf("\tOne: Result = %hd\n",result);
    result = scalar_result_s_negone();
    printf("\tNegOne: Result = %hd\n",result);
    result = scalar_result_s_max();
    printf("\tMax: Result = %hd\n",result);
    result = scalar_result_s_min();
    printf("\tMin: Result = %hd\n",result);    
  }

  // Unsigned short results
  {
    unsigned short result;
    
    printf("unsigned short results\n");
    printf("======================\n");
    
    result = scalar_result_us_zero();
    printf("\tZero: Result = %hu\n",result);
    result = scalar_result_us_one();
    printf("\tOne: Result = %hu\n",result);
    result = scalar_result_us_max();
    printf("\tMax: Result = %hu\n",result);
  }
  
  // Signed int results
  {
    signed int result;
    
    printf("signed int results\n");
    printf("==================\n");
    
    result = scalar_result_i_zero();
    printf("\tZero: Result = %d\n",result);
    result = scalar_result_i_one();
    printf("\tOne: Result = %d\n",result);
    result = scalar_result_i_negone();
    printf("\tNegOne: Result = %d\n",result);
    result = scalar_result_i_max();
    printf("\tMax: Result = %d\n",result);
    result = scalar_result_i_min();
    printf("\tMin: Result = %d\n",result);    
  }

  // Unsigned int results
  {
    unsigned int result;
    
    printf("unsigned int results\n");
    printf("====================\n");
    
    result = scalar_result_ui_zero();
    printf("\tZero: Result = %u\n",result);
    result = scalar_result_ui_one();
    printf("\tOne: Result = %u\n",result);
    result = scalar_result_ui_max();
    printf("\tMax: Result = %u\n",result);
  }    

  // Signed long results
  {
    signed long result;
    
    printf("signed long results\n");
    printf("===================\n");
    
    result = scalar_result_l_zero();
    printf("\tZero: Result = %ld\n",result);
    result = scalar_result_l_one();
    printf("\tOne: Result = %ld\n",result);
    result = scalar_result_l_negone();
    printf("\tNegOne: Result = %ld\n",result);
    result = scalar_result_l_max();
    printf("\tMax: Result = %ld\n",result);
    result = scalar_result_l_min();
    printf("\tMin: Result = %ld\n",result);    
  }

  // Unsigned long results
  {
    unsigned long result;
    
    printf("unsigned long results\n");
    printf("=====================\n");
    
    result = scalar_result_ul_zero();
    printf("\tZero: Result = %lu\n",result);
    result = scalar_result_ul_one();
    printf("\tOne: Result = %lu\n",result);
    result = scalar_result_ul_max();
    printf("\tMax: Result = %lu\n",result);
  }
  
  // Signed long long results
  {
    signed long long result;
    
    printf("signed long long results\n");
    printf("========================\n");
    
    result = scalar_result_ll_zero();
    printf("\tZero: Result = %lld\n",result);
    result = scalar_result_ll_one();
    printf("\tOne: Result = %lld\n",result);
    result = scalar_result_ll_negone();
    printf("\tNegOne: Result = %lld\n",result);
    result = scalar_result_ll_max();
    printf("\tMax: Result = %lld\n",result);
    result = scalar_result_ll_min();
    printf("\tMin: Result = %lld\n",result);    
  }

  // Unsigned long long results
  {
    unsigned long long result;
    
    printf("unsigned long long results\n");
    printf("==========================\n");
    
    result = scalar_result_ull_zero();
    printf("\tZero: Result = %llu\n",result);
    result = scalar_result_ull_one();
    printf("\tOne: Result = %llu\n",result);
    result = scalar_result_ull_max();
    printf("\tMax: Result = %llu\n",result);
  }

  // Float results
  {
    float result;
    
    printf("float results\n");
    printf("=============\n");
    
    result = scalar_result_f_zero();
    printf("\tZero: Result = %0.6g\n",result);
    result = scalar_result_f_one();
    printf("\tOne: Result = %0.6g\n",result);
    result = scalar_result_f_negone();
    printf("\tNegOne: Result = %0.6g\n",result);
    result = scalar_result_f_max();
    printf("\tMax: Result = %0.6g\n",result);
    result = scalar_result_f_min();
    printf("\tMin: Result = %0.6g\n",result);    
  }
  
  // Double results
  {
    double result;
    
    printf("double results\n");
    printf("==============\n");
    
    result = scalar_result_d_zero();
    printf("\tZero: Result = %0.6g\n",result);
    result = scalar_result_d_one();
    printf("\tOne: Result = %0.6g\n",result);
    result = scalar_result_d_negone();
    printf("\tNegOne: Result = %0.6g\n",result);
    result = scalar_result_d_max();
    printf("\tMax: Result = %0.6g\n",result);
    result = scalar_result_d_min();
    printf("\tMin: Result = %0.6g\n",result);    
  }
  
  return 0;
}


/***********************************************************
* Local Function Definitions                               *
***********************************************************/


/***********************************************************
* End file                                                 *
***********************************************************/
