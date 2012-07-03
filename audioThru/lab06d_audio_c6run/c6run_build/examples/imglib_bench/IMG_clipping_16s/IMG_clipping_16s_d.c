/* ======================================================================== */
/*  TEXAS INSTRUMENTS, INC.                                                 */
/*                                                                          */
/*  IMGLIB-2  DSP Image/Video Processing Library                            */
/*                                                                          */
/*      Release:        Revision 2.0.1                                      */
/*      Snapshot date:  6-May-2008                                          */
/*                                                                          */
/*  This library contains proprietary intellectual property of Texas        */
/*  Instruments, Inc.  The library and its source code are protected by     */
/*  various copyrights, and portions may also be protected by patents or    */
/*  other legal protections.                                                */
/*                                                                          */
/*  This software is licensed for use with Texas Instruments TMS320         */
/*  family DSPs.  This license was provided to you prior to installing      */
/*  the software.  You may review this license by consulting the file       */
/*  TI_license.PDF which accompanies the files in this library.             */
/* ------------------------------------------------------------------------ */
/*          Copyright (C) 2008 Texas Instruments, Incorporated.             */
/*                          All Rights Reserved.                            */
/* ======================================================================== */

/* Copyright 2008, Texas Instruments, Inc.  All rights reserved. */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#if defined(_TMS320C6X)
#elif defined(__GNUC__)
  #include <sys/time.h>
#endif

#include "mem_cpy.h"
#include "support.h"

#include "IMG_clipping_16s.h"
#include "IMG_clipping_16s_c.h"


/************************************************************
* Explicit External Declarations                            *
************************************************************/

/* Declare the golden input and output data buffers created in Matlab. */
extern int32_t in_data[]; /* Standard input data array. */
extern int16_t out_data[]; /* Standard output data array. */
extern int32_t testcases; /* number of test-cases */


/************************************************************
* Local Macro Declarations                                  *
************************************************************/

#define N 56
#define PAD 32
#define SIZE (N + 2*PAD)


/************************************************************
* Local Typedef Declarations                                *
************************************************************/

typedef unsigned long long timestamp_t;


/************************************************************
* Local Function Declarations                               *
************************************************************/

static timestamp_t get_timestamp( void );


/************************************************************
* Local Variable Definitions                                *
************************************************************/


/************************************************************
* Global Variable Definitions                               *
************************************************************/

int16_t input[SIZE];
int16_t output[SIZE], ref_output[SIZE];


/************************************************************
* Global Function Definitions                               *
************************************************************/

int main()
{
  timestamp_t t_start, t_stop, t_overhead, t_c;
  int32_t count,i;
  int32_t in_size, out_size;
  int32_t cols, rows;
  int32_t thresh_max, thresh_min;
  int16_t align_in, align_out;
  int16_t *src_ptr;
  int16_t *output_ptr, *ref_output_ptr;

  int32_t *inp = &in_data[0];
  int16_t *outp = &out_data[0];

  // Compute the overhead of calling clock twice to get timing info.
  t_start    = get_timestamp();
  t_overhead = 0;  
  for (i=0; i<1000; i++);
  {
    t_start    = get_timestamp();
    t_stop     = get_timestamp();
    t_overhead += (t_stop - t_start);
  }
  
  printf("Timing overhead = %llu us.\n", t_overhead);
  
  t_overhead = t_overhead / 1000;
  
  printf("Timing overhead = %llu us.\n", t_overhead);

  /* Read test parameters. */
  align_in    = *inp++;
  align_out   = *inp++;

  src_ptr =        (int16_t *)( (uint32_t)&input[PAD]  + align_in );
  output_ptr  =    (int16_t *)( (uint32_t)&output[PAD] + align_out);
  ref_output_ptr = (int16_t *)( (uint32_t)&ref_output[PAD] + align_out);

  for (count = 0; count < testcases; count++)
  {
    /* Read test-case params. */
    cols = *inp++;
    rows = *inp++;
    thresh_max = *inp++;
    thresh_min = *inp++;
    in_size  = *inp++;
    out_size = in_size;  // input and output size is the same.

    /* Checking sanity of generated driver. */
    if( N < in_size )
    {
      printf("source or dst array size is less than test-case (ID %d) size\n", count);
      exit(1);
    }

    /* Prepare output arrays */
    memset(input, 0, sizeof(input));
    memset(output, 0, sizeof(output[0]) * SIZE);
    memset(ref_output, 0, sizeof(ref_output[0]) * SIZE);

    /* Copy input and ref output to respective buffers */
    copy_int32_to_int16(src_ptr, inp, in_size);   // copy input
    inp += in_size;
    memcpy(ref_output_ptr, outp, out_size * sizeof(outp[0]));
    outp += out_size;

    // Run the testcase
    printf("IMG_clipping_16s(), Test %2d, %4dW x %4dH, 1000 calls: \n" , count, cols, rows);
    
#ifdef _C6RUN_IN_USE_
    // Call once to get in instruction cache
    IMG_clipping_16s (src_ptr, rows, cols, output_ptr, thresh_max, thresh_min);

    t_start = get_timestamp();
    for (i = 0; i<1000; i++)
    {
      IMG_clipping_16s (src_ptr, rows, cols, output_ptr, thresh_max, thresh_min);
    }
    t_stop = get_timestamp();

    t_c = t_stop - t_start - t_overhead;

    if( memcmp(output, ref_output, SIZE * sizeof(ref_output[0])) )
    {
      printf("\tResult failure: output - intrinsics\n");
      exit(1);
    }
    
    printf("\tIntrinsic C Time = %llu us\n", t_c);
    
    memset(output, 0, sizeof(output[0]) * SIZE);
#endif
    
    // Call once to get in instruction cache
    IMG_clipping_16s_cn (src_ptr, rows, cols, output_ptr, thresh_max, thresh_min);

    t_start = get_timestamp();
    for (i = 0; i<1000; i++)
    {
      IMG_clipping_16s_cn (src_ptr, rows, cols, output_ptr, thresh_max, thresh_min);
    }
    t_stop = get_timestamp();

    t_c = t_stop - t_start - t_overhead;

    if( memcmp(output, ref_output, SIZE * sizeof(ref_output[0])) )
    {
      printf("\tResult failure: output - natural c\n");
      exit(1);
    }

    printf("\tNatural C Time = %llu us\n", t_c);
  }

  printf("\nSuccess. Test suite (%d cases) passed.\n", testcases);

  return 0;
}


/***********************************************************
* Local Function Definitions                               *
***********************************************************/

static timestamp_t get_timestamp( void )
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


/***********************************************************
* End file                                                 *
***********************************************************/


