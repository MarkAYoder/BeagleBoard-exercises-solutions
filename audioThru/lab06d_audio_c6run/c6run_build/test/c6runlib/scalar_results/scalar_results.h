/*
 * scalar_results.h
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
 

#ifndef _SCALAR_RESULTS_H_
#define _SCALAR_RESULTS_H_

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

// Signed char test functions
extern signed char scalar_result_c_zero ( void );
extern signed char scalar_result_c_one ( void );
extern signed char scalar_result_c_negone ( void );
extern signed char scalar_result_c_max ( void );
extern signed char scalar_result_c_min ( void );

// Unsigned char test functions
extern unsigned char scalar_result_uc_zero ( void );
extern unsigned char scalar_result_uc_one ( void );
extern unsigned char scalar_result_uc_max ( void );

// Signed short test functions
extern signed short scalar_result_s_zero ( void );
extern signed short scalar_result_s_one ( void );
extern signed short scalar_result_s_negone ( void );
extern signed short scalar_result_s_max ( void );
extern signed short scalar_result_s_min ( void );

// Unsigned short test functions
extern unsigned short scalar_result_us_zero ( void );
extern unsigned short scalar_result_us_one ( void );
extern unsigned short scalar_result_us_max ( void );

// Signed int test functions
extern signed int scalar_result_i_zero ( void );
extern signed int scalar_result_i_one ( void );
extern signed int scalar_result_i_negone ( void );
extern signed int scalar_result_i_max ( void );
extern signed int scalar_result_i_min ( void );

// Unsigned int test functions
extern unsigned int scalar_result_ui_zero ( void );
extern unsigned int scalar_result_ui_one ( void );
extern unsigned int scalar_result_ui_max ( void );

// Signed long test functions
extern signed long scalar_result_l_zero ( void );
extern signed long scalar_result_l_one ( void );
extern signed long scalar_result_l_negone ( void );
extern signed long scalar_result_l_max ( void );
extern signed long scalar_result_l_min ( void );

// Unsigned long test functions
extern unsigned long scalar_result_ul_zero ( void );
extern unsigned long scalar_result_ul_one ( void );
extern unsigned long scalar_result_ul_max ( void );

// Signed long long test functions
extern signed long long scalar_result_ll_zero ( void );
extern signed long long scalar_result_ll_one ( void );
extern signed long long scalar_result_ll_negone ( void );
extern signed long long scalar_result_ll_max ( void );
extern signed long long scalar_result_ll_min ( void );

// Unsigned long long test functions
extern unsigned long long scalar_result_ull_zero ( void );
extern unsigned long long scalar_result_ull_one ( void );
extern unsigned long long scalar_result_ull_max ( void );

// Float test functions
extern float scalar_result_f_zero ( void );
extern float scalar_result_f_one ( void );
extern float scalar_result_f_negone ( void );
extern float scalar_result_f_max ( void );
extern float scalar_result_f_min ( void );

// Double test functions
extern double scalar_result_d_zero ( void );
extern double scalar_result_d_one ( void );
extern double scalar_result_d_negone ( void );
extern double scalar_result_d_max ( void );
extern double scalar_result_d_min ( void );


/***********************************************************
* End file                                                 *
***********************************************************/

#ifdef __cplusplus
}
#endif

#endif //_SCALAR_RESULTS_H_

