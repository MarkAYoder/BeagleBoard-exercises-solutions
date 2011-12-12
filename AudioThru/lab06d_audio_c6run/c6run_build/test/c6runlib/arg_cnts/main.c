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

// Main Test harness code
int main()
{
  int cnt=0;
  int i;

  // Zero arg test
  {
    i = arg_cnt_0();
    printf("ArgCnt = %d, Result = %d\n",cnt,i);
    cnt++;
  }
  
  // One arg test
  {
    i = arg_cnt_1(1);
    printf("ArgCnt = %d, Result = %d\n",cnt,i);
    cnt++;
  }

  // Two arg test
  {
    i = arg_cnt_2(1,2);
    printf("ArgCnt = %d, Result = %d\n",cnt,i);
    cnt++;
  }
  
  // Three arg test
  {
    i = arg_cnt_3(1,2,3);
    printf("ArgCnt = %d, Result = %d\n",cnt,i);
    cnt++;
  }
  
  // Four arg test
  {
    i = arg_cnt_4(1,2,3,4);
    printf("ArgCnt = %d, Result = %d\n",cnt,i);
    cnt++;
  }
  
  // Five arg test
  {
    i = arg_cnt_5(1,2,3,4,5);
    printf("ArgCnt = %d, Result = %d\n",cnt,i);
    cnt++;
  }
  
  // Six arg test
  {
    i = arg_cnt_6(1,2,3,4,5,6);
    printf("ArgCnt = %d, Result = %d\n",cnt,i);
    cnt++;
  }
  
  // Seven arg test
  {
    i = arg_cnt_7(1,2,3,4,5,6,7);
    printf("ArgCnt = %d, Result = %d\n",cnt,i);
    cnt++;
  }
  
  // Eight arg test
  {
    i = arg_cnt_8(1,2,3,4,5,6,7,8);
    printf("ArgCnt = %d, Result = %d\n",cnt,i);
    cnt++;
  }
  
  // Nine arg test
  {
    i = arg_cnt_9(1,2,3,4,5,6,7,8,9);
    printf("ArgCnt = %d, Result = %d\n",cnt,i);
    cnt++;
  }
  
  // Ten arg test
  {
    i = arg_cnt_10(1,2,3,4,5,6,7,8,9,10);
    printf("ArgCnt = %d, Result = %d\n",cnt,i);
    cnt++;
  }
  
  // Eleven arg test
  {
    i = arg_cnt_11(1,2,3,4,5,6,7,8,9,10,11);
    printf("ArgCnt = %d, Result = %d\n",cnt,i);
    cnt++;
  }
  
  // Twelve arg test
  {
    i = arg_cnt_12(1,2,3,4,5,6,7,8,9,10,11,12);
    printf("ArgCnt = %d, Result = %d\n",cnt,i);
    cnt++;
  }

  // Thirteen arg test
  {
    i = arg_cnt_13(1,2,3,4,5,6,7,8,9,10,11,12,13);
    printf("ArgCnt = %d, Result = %d\n",cnt,i);
    cnt++;
  }
  
  // And so on...

  return 0;
}


/***********************************************************
* Local Function Definitions                               *
***********************************************************/


/***********************************************************
* End file                                                 *
***********************************************************/
