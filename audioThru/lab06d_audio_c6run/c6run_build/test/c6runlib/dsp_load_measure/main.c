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

#include <unistd.h>
#include <sys/time.h>

#include "dsp_load_measure.h"


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


typedef unsigned long long timestamp_t;

static timestamp_t get_timestamp ()
{
#if defined(_TMS320C6X)
  // There is no gettimeofday in DSP RTS or DSP/BIOS
  return (timestamp_t) clock();
#elif defined(__GNUC__)
  struct timeval now;
  gettimeofday (&now, NULL);
  return  now.tv_usec + (timestamp_t)now.tv_sec * 1000000;
#endif
}


// Main Test harness code
int main()
{
  volatile int loadVal;
  double secs=0;
  int i;
  int nTimes = 3;
  
  timestamp_t t0, t1;
  
  // First run outside loop
  t0 = get_timestamp();
  loadVal = dsp_load_measure_0();
  t1 = get_timestamp();
  
  sleep(1);

  // Main calling timing loop
  t0 = get_timestamp();
  for (i = 0; i < nTimes; i++)
  {
    loadVal = dsp_load_measure_0();
  }
  t1 = get_timestamp();

  // Total time for all calls
  secs = (t1 - t0) / 1000000.0;
  
  printf("Test 1:\n");
  printf("  DSP core load: %03d %%\n",loadVal);
  printf("  Time per call: %0.6f seconds.\n", (secs / ((double)nTimes)));
  
  
  // First run outside loop
  t0 = get_timestamp();
  loadVal = dsp_load_measure_1();
  t1 = get_timestamp();
  
  sleep(1);

  // Main calling timing loop
  t0 = get_timestamp();
  for (i = 0; i < nTimes; i++)
  {
    loadVal = dsp_load_measure_1();
  }
  t1 = get_timestamp();

  // Total time for all calls
  secs = (t1 - t0) / 1000000.0;
  
  printf("Test 2:\n");
  printf("  DSP core load: %03d %%. \n",loadVal);
  printf("  Time per call: %0.6f seconds.\n", (secs / ((double)nTimes)));
  
  
  // First run outside loop
  t0 = get_timestamp();
  loadVal = dsp_load_measure_2();
  t1 = get_timestamp();

  sleep(1);
  
  // Main calling timing loop
  t0 = get_timestamp();
  for (i = 0; i < nTimes; i++)
  {
    loadVal = dsp_load_measure_2();
  }
  t1 = get_timestamp();

  // Total time for all calls
  secs = (t1 - t0) / 1000000.0;
  
  printf("Test 3:\n");
  printf("  DSP core load: %03d %%. \n",loadVal);
  printf("  Time per call: %0.6f seconds.\n", (secs / ((double)nTimes)));  
  
  
  // First run outside loop
  t0 = get_timestamp();
  loadVal = dsp_load_measure_3();
  t1 = get_timestamp();
  
  sleep(1);

  // Main calling timing loop
  t0 = get_timestamp();
  for (i = 0; i < nTimes; i++)
  {
    loadVal = dsp_load_measure_3();
  }
  t1 = get_timestamp();

  // Total time for all calls
  secs = (t1 - t0) / 1000000.0;
  
  printf("Test 4:\n");
  printf("  DSP core load: %03d %%. \n",loadVal);
  printf("  Time per call: %0.6f seconds.\n", (secs / ((double)nTimes)));    
  
  dsp_load_test();
  
  return 0;
}


/***********************************************************
* Local Function Definitions                               *
***********************************************************/


/***********************************************************
* End file                                                 *
***********************************************************/
