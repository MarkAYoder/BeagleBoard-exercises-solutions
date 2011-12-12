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

#include "IMG_conv_3x3_i8_c8s.h"
#include "IMG_conv_3x3_i8_c8s_c.h"


/************************************************************
* Explicit External Declarations                            *
************************************************************/

/* Declare the golden input and output data buffers created in Matlab. */
extern int in_data[]; /* Standard input data array. */
extern unsigned char out_data[]; /* Standard output data array. */
extern int testcases; /* number of test-cases */


/************************************************************
* Local Macro Declarations                                  *
************************************************************/

#define M_SIZE 3
#define O_N 32
#define N (M_SIZE * O_N)
#define C_N (M_SIZE * M_SIZE)
#define PAD 64
#define SIZE (N + 2*PAD)
#define C_SIZE (C_N + 2*PAD)
#define O_SIZE (O_N + 2*PAD)

#define ITER_CNT (1000)


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

uint8_t input_1[SIZE];
int8_t mask[C_SIZE];
uint8_t output[O_SIZE], ref_output[O_SIZE];


/************************************************************
* Global Function Definitions                               *
************************************************************/

int main()
{
  timestamp_t t_start, t_stop, t_overhead, t_c;
  int32_t count, i;
  int32_t in_size, out_size, m_size;
  int32_t width;
  int32_t shift;
  int16_t align_in, align_mask, align_out;
  uint8_t *src_ptr_1;
  int8_t *mask_ptr;
  uint8_t *output_ptr, *ref_output_ptr;

  int32_t *inp = &in_data[0];
  uint8_t *outp = &out_data[0];

  // Compute the overhead of calling clock twice to get timing info.
  t_start    = get_timestamp();
  t_overhead = 0;
  for (i=0; i<ITER_CNT; i++);
  {
    t_start    = get_timestamp();
    t_stop     = get_timestamp();
    t_overhead += (t_stop - t_start);
  }
  t_overhead = t_overhead / ITER_CNT;

  /* Read test parameters. */
  m_size      = *inp++;
  align_in    = *inp++;
  align_mask  = *inp++;
  align_out   = *inp++;

  if(m_size != M_SIZE)
  {
    printf("Incorrect data file: for mask size %d\n", m_size);
    return(0);
  }

  src_ptr_1 =      (uint8_t *)( (uint32_t)&input_1[PAD]  + align_in );
  mask_ptr =       (int8_t *)( (uint32_t)&mask[PAD]     + align_mask);
  output_ptr  =    (uint8_t *)( (uint32_t)&output[PAD]   + align_out);
  ref_output_ptr = (uint8_t *)( (uint32_t)&ref_output[PAD] + align_out);

  for(count = 0; count < testcases; count++)
  {
    /* Read test-case params. */
    width = *inp++;
    shift = *inp++;
    in_size  = *inp++;
    out_size = *inp++;

    /* Checking sanity of generated driver. */
    if( N < in_size )
    {
      printf("source or dst array size is less than test-case (ID %d) size\n", count);
      exit(1);
    }

    /* Prepare output arrays */
    memset(input_1, 0, sizeof(input_1));
    memset(output, 0, sizeof(output[0]) * O_SIZE);
    memset(ref_output, 0, sizeof(ref_output[0]) * O_SIZE);

    /* Copy input and ref output to respective buffers */
    copy_int32_to_uint8(src_ptr_1, inp, in_size);   // copy input
    inp += in_size;
    copy_int32_to_int8(mask_ptr, inp, C_N);     // copy mask
    inp += C_N;
    memcpy(ref_output_ptr, outp, out_size * sizeof(outp[0]));
    outp += out_size;

    // Run the testcase
    printf("IMG_conv_3x3_i8_c8s, Test %2d, width=%d, %d calls: \n" , count, width, ITER_CNT);

#ifdef _C6RUN_IN_USE_
    // Call once to get in instruction cache
    IMG_conv_3x3_i8_c8s (src_ptr_1, output_ptr, width, mask_ptr, shift);

    t_start = get_timestamp();
    for (i = 0; i<ITER_CNT; i++)
    {
      IMG_conv_3x3_i8_c8s (src_ptr_1, output_ptr, width, mask_ptr, shift);
    }
    t_stop = get_timestamp();

    t_c = t_stop - t_start - t_overhead;

    if( memcmp(output, ref_output, O_SIZE * sizeof(ref_output[0])) )
    {
      printf("\tResult failure: output - intrinsics: case # %d\n", count);
      exit(1);
    }


    printf("\tIntrinsic C Time = %llu us\n", t_c);

    memset(output, 0, sizeof(output[0]) * O_SIZE);
#endif
    
    // Call once to get in instruction cache
    IMG_conv_3x3_i8_c8s_cn (src_ptr_1, output_ptr, width, width, mask_ptr, shift);

    t_start = get_timestamp();
    for (i = 0; i<ITER_CNT; i++)
    {
      IMG_conv_3x3_i8_c8s_cn (src_ptr_1, output_ptr, width, width, mask_ptr, shift);
    }
    t_stop = get_timestamp();

    t_c = t_stop - t_start - t_overhead;

    if( memcmp(output, ref_output, O_SIZE * sizeof(ref_output[0])) )
    {
      printf("\tResult failure: output - natural c: case # %d\n", count);
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


