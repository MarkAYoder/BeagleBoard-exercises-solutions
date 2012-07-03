/*
 * enum_args.c
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
#include <stdbool.h>
#include <string.h>

#include <inttypes.h>
#include <limits.h>
#include <float.h>

#include "enum_args.h"

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

static char *LOCAL_colorStringLookup( enum ColorEnum color );
static char *LOCAL_vehicleStringLookup( enum VehicleEnum vehicle );
static char *LOCAL_flagsStringConstruct( DummyFlags flags );


/************************************************************
* Local Variable Definitions                                *
************************************************************/

static char LOCAL_charBuffer[256];

/************************************************************
* Global Variable Definitions                               *
************************************************************/


/************************************************************
* Global Function Definitions                               *
************************************************************/

void enum_args_print( enum ColorEnum color, enum VehicleEnum vehicle)
{
  printf("I love to drive my shiny %s %s.\n",
    LOCAL_colorStringLookup(color),
    LOCAL_vehicleStringLookup(vehicle) );
}

void enum_args_print2( DummyFlags flags )
{
  printf("The flags variable represents %s.\n",LOCAL_flagsStringConstruct(flags));
}

enum ColorEnum enum_args_return( void )
{
  return BLUE;
}

DummyFlags enum_args_return2( void )
{
  return DUMMY_FLAG1;
}


/***********************************************************
* Local Function Definitions                               *
***********************************************************/

static char *LOCAL_colorStringLookup( enum ColorEnum color )
{
  const char *colorStrings[11] = 
  {
    "red",
    "blue",
    "green",
    "burnt sienna",
    "maroon",
    "gray",
    "white",
    "black",
    "brown",
    "yellow",
    "orange"
  };
  
  return ((char *)colorStrings[((int)color)]);
}

static char *LOCAL_vehicleStringLookup( enum VehicleEnum vehicle )
{
  const char *vehicleStrings[4] = 
  {
    "motorcycle",
    "car",
    "bus",
    "tank"
  };
  
  return ((char *)vehicleStrings[((int)vehicle)]);
}

static char *LOCAL_flagsStringConstruct( DummyFlags flags )
{
  bool start = true;
  char *buffPtr = LOCAL_charBuffer;
  int i = 0;
  
  const DummyFlags flagArray[4] = 
  {
    DUMMY_FLAG1,
    DUMMY_FLAG2,
    DUMMY_FLAG3,
    DUMMY_FLAG4  
  };
  
  const char *flagStrings[4] = 
  {
    "DUMMY_FLAG1",
    "DUMMY_FLAG2",
    "DUMMY_FLAG3",
    "DUMMY_FLAG4"
  };
  
  for (i=0; i<4; i++)
  {
    if (flags & flagArray[i])
    {
      if (!start)
      {
        strcpy(buffPtr," | ");
        buffPtr+=3;
      }
      else
      {  
        start = false;
      }
      strcpy(buffPtr,flagStrings[i]);
      buffPtr+=strlen(flagStrings[i]);
    }
  }
  
  return LOCAL_charBuffer;
}

/***********************************************************
* End file                                                 *
***********************************************************/
