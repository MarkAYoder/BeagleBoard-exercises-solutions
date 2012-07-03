/*
 * scalar_results.c
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

#include <inttypes.h>
#include <limits.h>
#include <float.h>

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

// Signed char test functions
signed char scalar_result_c_zero ( void )
{
  return ((signed char) 0);
}

signed char scalar_result_c_one ( void )
{
  return ((signed char) 1);
}

signed char scalar_result_c_negone ( void )
{
  return ((signed char) -1);
}

signed char scalar_result_c_max ( void )
{
  return ((signed char) SCHAR_MAX);
}

signed char scalar_result_c_min ( void )
{
  return ((signed char) SCHAR_MIN);
}


// Unsigned char test functions
unsigned char scalar_result_uc_zero ( void )
{
  return ((unsigned char) 0);
}

unsigned char scalar_result_uc_one ( void )
{
  return ((unsigned char) 1);
}

unsigned char scalar_result_uc_max ( void )
{
  return ((unsigned char) UCHAR_MAX);
}



// Signed short test functions
signed short scalar_result_s_zero ( void )
{
  return ((signed short) 0);
}

signed short scalar_result_s_one ( void )
{
  return ((signed short) 1);
}

signed short scalar_result_s_negone ( void )
{
  return ((signed short) -1);
}

signed short scalar_result_s_max ( void )
{
  return ((signed short) SHRT_MAX);
}

signed short scalar_result_s_min ( void )
{
  return ((signed short) SHRT_MIN);
}


// Unsigned short test functions
unsigned short scalar_result_us_zero ( void )
{
  return ((unsigned short) 0);
}

unsigned short scalar_result_us_one ( void )
{
  return ((unsigned short) 1);
}

unsigned short scalar_result_us_max ( void )
{
  return ((unsigned short) USHRT_MAX);
}



// Signed int test functions
signed int scalar_result_i_zero ( void )
{
  return ((signed int) 0);
}

signed int scalar_result_i_one ( void )
{
  return ((signed int) 1);
}

signed int scalar_result_i_negone ( void )
{
  return ((signed int) -1);
}

signed int scalar_result_i_max ( void )
{
  return ((signed int) INT_MAX);
}

signed int scalar_result_i_min ( void )
{
  return ((signed int) INT_MIN);
}


// Unsigned int test functions
unsigned int scalar_result_ui_zero ( void )
{
  return ((unsigned int) 0);
}

unsigned int scalar_result_ui_one ( void )
{
  return ((unsigned int) 1);
}

unsigned int scalar_result_ui_max ( void )
{
  return ((unsigned int) UINT_MAX);
}



// Signed long test functions
signed long scalar_result_l_zero ( void )
{
  return ((signed long) 0);
}

signed long scalar_result_l_one ( void )
{
  return ((signed long) 1);
}

signed long scalar_result_l_negone ( void )
{
  return ((signed long) -1);
}

signed long scalar_result_l_max ( void )
{
  return ((signed long) LONG_MAX);
}

signed long scalar_result_l_min ( void )
{
  return ((signed long) LONG_MIN);
}


// Unsigned long test functions
unsigned long scalar_result_ul_zero ( void )
{
  return ((unsigned long) 0);
}

unsigned long scalar_result_ul_one ( void )
{
  return ((unsigned long) 1);
}

unsigned long scalar_result_ul_max ( void )
{
  return ((unsigned long) ULONG_MAX);
}



// Signed long long test functions
signed long long scalar_result_ll_zero ( void )
{
  return ((signed long long) 0);
}

signed long long scalar_result_ll_one ( void )
{
  return ((signed long long) 1);
}

signed long long scalar_result_ll_negone ( void )
{
  return ((signed long long) -1);
}

signed long long scalar_result_ll_max ( void )
{
  return ((signed long long) LLONG_MAX);
}

signed long long scalar_result_ll_min ( void )
{
  return ((signed long long) LLONG_MIN);
}


// Unsigned long long test functions
unsigned long long scalar_result_ull_zero ( void )
{
  return ((unsigned long long) 0);
}

unsigned long long scalar_result_ull_one ( void )
{
  return ((unsigned long long) 1);
}

unsigned long long scalar_result_ull_max ( void )
{
  return ((unsigned long long) ULLONG_MAX);
}


// Float test functions
float scalar_result_f_zero ( void )
{
  return ((float) 0.0);
}

float scalar_result_f_one ( void )
{
  return ((float) 1.0);
}

float scalar_result_f_negone ( void )
{
  return ((float) -1.0);
}

float scalar_result_f_max ( void )
{
  return ((float) FLT_MAX);
}

float scalar_result_f_min ( void )
{
  return ((float) FLT_MIN);
}

// Double test functions
double scalar_result_d_zero ( void )
{
  return ((double) 0.0);
}

double scalar_result_d_one ( void )
{
  return ((double) 1.0);
}

double scalar_result_d_negone ( void )
{
  return ((double) -1.0);
}

double scalar_result_d_max ( void )
{
  return ((double) DBL_MAX);
}

double scalar_result_d_min ( void )
{
  return ((double) DBL_MIN);
}


/***********************************************************
* Local Function Definitions                               *
***********************************************************/


/***********************************************************
* End file                                                 *
***********************************************************/
