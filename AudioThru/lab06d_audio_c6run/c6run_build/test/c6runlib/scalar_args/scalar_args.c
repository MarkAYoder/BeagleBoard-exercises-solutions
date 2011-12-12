/*
 * scalar_args.c
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

#include "scalar_args.h"

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

signed char scalar_arg_c ( signed char arg )
{
  static signed char sum = 0;
  sum+=arg;
  return sum;
}

unsigned char scalar_arg_uc (unsigned char arg)
{
  static unsigned char sum = 0;
  sum+=arg;
  return sum;
}

short scalar_arg_s ( short arg )
{
  static short sum = 0;
  sum+=arg;
  return sum;
}

unsigned short scalar_arg_us (unsigned short arg)
{
  static unsigned short sum = 0;
  sum+=arg;
  return sum;
}

int scalar_arg_i ( int arg )
{
  static int sum = 0;
  sum+=arg;
  return sum;
}

unsigned int scalar_arg_ui (unsigned int arg)
{
  static unsigned int sum = 0;
  sum+=arg;
  return sum;
}

long scalar_arg_l ( long arg )
{
  static long sum = 0;
  sum+=arg;
  return sum;
}

unsigned long scalar_arg_ul (unsigned long arg)
{
  static unsigned long sum = 0;
  sum+=arg;
  return sum;
}

long long scalar_arg_ll ( long long arg )
{
  static long long sum = 0;
  sum+=arg;
  return sum;
}

unsigned long long scalar_arg_ull (unsigned long long arg)
{
  static unsigned long long sum = 0;
  sum+=arg;
  return sum;
}

float scalar_arg_f (float arg)
{
  static float sum = 0.0;
  sum+=arg;
  return sum;
}

double scalar_arg_d (double arg)
{
  static double sum = 0.0;
  sum+=arg;
  return sum;
}


/***********************************************************
* Local Function Definitions                               *
***********************************************************/


/***********************************************************
* End file                                                 *
***********************************************************/
