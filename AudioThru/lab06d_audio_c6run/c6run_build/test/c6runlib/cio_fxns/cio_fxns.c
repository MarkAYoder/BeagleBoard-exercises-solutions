/*
 * cio_fxns.c
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
#include <stdint.h>
#include <string.h>

#include <limits.h>
#include <float.h>

#include "cio_fxns.h"

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

char *fileName = NULL;

/************************************************************
* Global Function Definitions                               *
************************************************************/

void cio_fxns_printf(int arg1,int arg2,int arg3)
{
  printf("Arg1 = %d, Arg2 = %d, Arg3 = %d\n",arg1, arg2, arg3);
  printf("Sum = %d\n",arg1 + arg2 + arg3);
}
  
void cio_fxns_scanf( void )
{
  if (fileName == NULL)
  {
    fileName = malloc(256);
  }

  printf("Enter a file name: ");
  scanf("%s", fileName);
}
  
void cio_fxns_create_file( void )
{
  FILE *fid;
  if (fileName == NULL)
  {
    fileName = "cio_fxns_test.txt";
  }

  printf("Creating file %s\n",fileName);
  fid = fopen(fileName,"ab");
  fclose(fid);
}

void cio_fxns_write_file( void )
{
  FILE *fid;
  char *string = "C6Run test output.";
  fid = fopen(fileName,"wb");

  printf("Writing file %s\n",fileName);
  fwrite(string,sizeof(char),strlen(string),fid);
  fclose(fid);
}
  
void cio_fxns_read_file( void )
{
  FILE *fid;
  char buffer[256];
  size_t bytes_read;
  fid = fopen(fileName,"rb");
  
  printf("Reading file %s\n",fileName);
  bytes_read = fread(buffer, sizeof(char), 256, fid);
  printf("Read %d bytes from file.\n",bytes_read);
  buffer[bytes_read] = 0; // NULL terminate
  
  printf("String read: %s\n",buffer);
  
  fclose(fid);
}


/***********************************************************
* Local Function Definitions                               *
***********************************************************/


/***********************************************************
* End file                                                 *
***********************************************************/
