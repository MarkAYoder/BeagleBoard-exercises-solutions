/*
 * vector_args.h
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
 

#ifndef _VECTOR_ARGS_H_
#define _VECTOR_ARGS_H_

// Prevent C++ name mangling
#ifdef __cplusplus
extern "C" {
#endif

/***********************************************************
* Global Macro Declarations                                *
***********************************************************/


/***********************************************************
* Global Typedef Declarations                              *
***********************************************************/


/***********************************************************
* Global Variable Declarations                             *
***********************************************************/


/***********************************************************
* Global Function Declarations                             *
***********************************************************/

#ifdef local_type
  #undef local_type
#endif
#define local_type signed char
local_type vector_arg_c ( int cnt, local_type *arg );

#undef local_type
#define local_type unsigned char
local_type vector_arg_uc ( int cnt, local_type *arg );

#undef local_type
#define local_type short
local_type vector_arg_s ( int cnt, local_type *arg );

#undef local_type
#define local_type unsigned short
local_type vector_arg_us ( int cnt, local_type *arg );

#undef local_type
#define local_type int
local_type vector_arg_i ( int cnt, local_type *arg );

#undef local_type
#define local_type unsigned int
local_type vector_arg_ui ( int cnt, local_type *arg );

#undef local_type
#define local_type long long
local_type vector_arg_ll ( int cnt, local_type *arg );

#undef local_type
#define local_type unsigned long long
local_type vector_arg_ull ( int cnt, local_type *arg );

#undef local_type
#define local_type float
local_type vector_arg_f ( int cnt, local_type *arg );

#undef local_type
#define local_type double
local_type vector_arg_d ( int cnt, local_type *arg );


/***********************************************************
* End file                                                 *
***********************************************************/

#ifdef __cplusplus
}
#endif

#endif //_VECTOR_ARGS_H_

