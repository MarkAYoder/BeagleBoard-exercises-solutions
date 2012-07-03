/*
 * vector_args.c
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

#include "vector_args.h"

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
#ifdef local_type
  #undef local_type
#endif
#define local_type signed char
local_type vector_arg_c ( int cnt, INBUF local_type *arg )
{
  int i;
  static local_type sum = 0;
  for (i = 0; i < cnt; i++)
  {
    sum+=arg[i];
  }
  return sum;
}

#undef local_type
#define local_type unsigned char
local_type vector_arg_uc ( int cnt, INBUF local_type *arg )
{
  int i;
  static local_type sum = 0;
  for (i = 0; i < cnt; i++)
  {
    sum+=arg[i];
  }
  return sum;
}

#undef local_type
#define local_type short
local_type vector_arg_s ( int cnt, INBUF local_type *arg )
{
  int i;
  static local_type sum = 0;
  for (i = 0; i < cnt; i++)
  {
    sum+=arg[i];
  }
  return sum;
}

#undef local_type
#define local_type unsigned short
local_type vector_arg_us ( int cnt, INBUF local_type *arg )
{
  int i;
  static local_type sum = 0;
  for (i = 0; i < cnt; i++)
  {
    sum+=arg[i];
  }
  return sum;
}

#undef local_type
#define local_type int
local_type vector_arg_i ( int cnt, INBUF local_type *arg )
{
  int i;
  static local_type sum = 0;
  for (i = 0; i < cnt; i++)
  {
    sum+=arg[i];
  }
  return sum;
}

#undef local_type
#define local_type unsigned int
local_type vector_arg_ui ( int cnt, INBUF local_type *arg )
{
  int i;
  static local_type sum = 0;
  for (i = 0; i < cnt; i++)
  {
    sum+=arg[i];
  }
  return sum;
}

#undef local_type
#define local_type long long
local_type vector_arg_ll ( int cnt, INBUF local_type *arg )
{
  int i;
  static local_type sum = 0;
  for (i = 0; i < cnt; i++)
  {
    sum+=arg[i];
  }
  return sum;
}

#undef local_type
#define local_type unsigned long long
local_type vector_arg_ull ( int cnt, INBUF local_type *arg )
{
  int i;
  static local_type sum = 0;
  for (i = 0; i < cnt; i++)
  {
    sum+=arg[i];
  }
  return sum;
}

#undef local_type
#define local_type float
local_type vector_arg_f ( int cnt, INBUF local_type *arg )
{
  int i;
  static local_type sum = 0;
  for (i = 0; i < cnt; i++)
  {
    sum+=arg[i];
  }
  return sum;
}

#undef local_type
#define local_type double
local_type vector_arg_d ( int cnt, INBUF local_type *arg )
{
  int i;
  static local_type sum = 0;
  for (i = 0; i < cnt; i++)
  {
    sum+=arg[i];
  }
  return sum;
}


/***********************************************************
* Local Function Definitions                               *
***********************************************************/


/***********************************************************
* End file                                                 *
***********************************************************/
