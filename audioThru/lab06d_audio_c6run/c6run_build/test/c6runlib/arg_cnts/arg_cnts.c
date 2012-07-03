/*
 * arg_cnts.c
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

#include "arg_cnts.h"

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

int arg_cnt_0 ( void )
{
  return 0;
}

int arg_cnt_1 ( int arg1 )
{
  int sum = 0;
  sum=arg1;
  return sum;
}

int arg_cnt_2 ( int arg1, int arg2 )
{
  int sum = 0;
  sum = arg1 + arg2;
  return sum;
}

int arg_cnt_3 ( int arg1, int arg2, int arg3 )
{
  int sum = 0;
  sum = arg1 + arg2 + arg3;
  return sum;
}

int arg_cnt_4 ( int arg1, int arg2, int arg3, int arg4 )
{
  int sum = 0;
  sum = arg1 + arg2 + arg3 + arg4;
  return sum;
}

int arg_cnt_5 ( int arg1, int arg2, int arg3, int arg4, int arg5 )
{
  int sum = 0;
  sum = arg1 + arg2 + arg3 + arg4 + arg5;
  return sum;
}

int arg_cnt_6 ( int arg1, int arg2, int arg3, int arg4, int arg5, int arg6 )
{
  int sum = 0;
  sum = arg1 + arg2 + arg3 + arg4 + arg5 + arg6;
  return sum;
}

int arg_cnt_7 ( int arg1, int arg2, int arg3, int arg4, int arg5, int arg6, int arg7 )
{
  int sum = 0;
  sum = arg1 + arg2 + arg3 + arg4 + arg5 + arg6 + arg7;
  return sum;
}

int arg_cnt_8 ( int arg1, int arg2, int arg3, int arg4, int arg5, int arg6, int arg7, int arg8 )
{
  int sum = 0;
  sum = arg1 + arg2 + arg3 + arg4 + arg5 + arg6 + arg7 + arg8;
  return sum;
}

int arg_cnt_9 ( int arg1, int arg2, int arg3, int arg4, int arg5, int arg6, int arg7, int arg8, int arg9 )
{
  int sum = 0;
  
  sum = arg1 + arg2 + arg3 + arg4 + arg5 + arg6 + arg7 + arg8 + arg9;
  
  return sum;
}

int arg_cnt_10 ( int arg1, int arg2, int arg3, int arg4, int arg5, int arg6, int arg7, int arg8, int arg9, int arg10 )
{
  int sum = 0;
  
  sum = arg1 + arg2 + arg3 + arg4 + arg5 + arg6 + arg7 + arg8 + arg9 + arg10;
  
  return sum;
}

int arg_cnt_11 ( int arg1, int arg2, int arg3, int arg4, int arg5, int arg6, int arg7, int arg8, int arg9, int arg10, int arg11 )
{
  int sum = 0;
  
  sum = arg1 + arg2 + arg3 + arg4 + arg5 + arg6 + arg7 + arg8 + arg9 + arg10 + arg11;
  
  return sum;
}


int arg_cnt_12 ( int arg1, int arg2, int arg3, int arg4, int arg5, int arg6, int arg7, int arg8, int arg9, int arg10, int arg11, int arg12 )
{
  int sum = 0;
  
  sum = arg1 + arg2 + arg3 + arg4 + arg5 + arg6 + arg7 + arg8 + arg9 + arg10 + arg11 + arg12;
  
  return sum;
}


int arg_cnt_13 ( int arg1, int arg2, int arg3, int arg4, int arg5, int arg6, int arg7, int arg8, int arg9, int arg10, int arg11, int arg12, int arg13 )
{
  int sum = 0;
  
  sum = arg1 + arg2 + arg3 + arg4 + arg5 + arg6 + arg7 + arg8 + arg9 + arg10 + arg11 + arg12 + arg13;
  
  return sum;
}



/***********************************************************
* Local Function Definitions                               *
***********************************************************/


/***********************************************************
* End file                                                 *
***********************************************************/
