/*
 * scalar_typedef_args.c
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

#include "scalar_typedef_args.h"

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

int8_t   scalar_arg_c    ( int8_t    arg )
{
  static int8_t sum = 0;
  sum+=arg;
  return sum;
}

uint8_t  scalar_arg_uc   ( uint8_t   arg )
{
  static uint8_t sum = 0;
  sum+=arg;
  return sum;
}

int16_t  scalar_arg_s    ( int16_t   arg )
{
  static int16_t sum = 0;
  sum+=arg;
  return sum;
}

uint16_t scalar_arg_us   ( uint16_t  arg )
{
  static uint16_t sum = 0;
  sum+=arg;
  return sum;
}

int32_t  scalar_arg_i    ( int32_t   arg )
{
  static int32_t sum = 0;
  sum+=arg;
  return sum;
}

uint32_t scalar_arg_ui   ( uint32_t  arg )
{
  static uint32_t sum = 0;
  sum+=arg;
  return sum;
}

int64_t  scalar_arg_ll   ( int64_t   arg )
{
  static int64_t sum = 0;
  sum+=arg;
  return sum;
}

uint64_t scalar_arg_ull  ( uint64_t  arg )
{
  static uint64_t sum = 0;
  sum+=arg;
  return sum;
}


/***********************************************************
* Local Function Definitions                               *
***********************************************************/


/***********************************************************
* End file                                                 *
***********************************************************/
