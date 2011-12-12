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

#include "IMG_boundary_8.h"
#include "IMG_boundary_8_c.h"


/************************************************************
* Explicit External Declarations                            *
************************************************************/

/* Declare the golden input and output data buffers created in Matlab. */
extern int32_t in_data[]; /* Standard input data array. */
extern int32_t out_data[]; /* Standard output data array. */
extern int32_t testcases; /* number of test-cases */


/************************************************************
* Local Macro Declarations                                  *
************************************************************/

#define N 400
#define PAD 64
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

uint8_t input_1[SIZE];
int32_t coord[SIZE], ref_coord[SIZE];
int32_t grey[SIZE], ref_grey[SIZE];


/************************************************************
* Global Function Definitions                               *
************************************************************/

int32_t main()
{
  timestamp_t t_start, t_stop, t_overhead, t_c;
  int32_t count,i;
  int32_t in_size, out_size;
  int32_t rows, cols;
  int16_t align_in, align_out;
  uint8_t *src_ptr_1;
  int32_t *coord_ptr, *ref_coord_ptr;
  int32_t *grey_ptr, *ref_grey_ptr;

  int32_t *inp = &in_data[0];
  int32_t *outp = &out_data[0];

  // Compute the overhead of calling clock twice to get timing info.
  t_start    = get_timestamp();
  t_overhead = 0;
  for (i=0; i<1000; i++);
  {
    t_start    = get_timestamp();
    t_stop     = get_timestamp();
    t_overhead += (t_stop - t_start);
  }
  t_overhead = t_overhead / 1000;

  align_in  = *inp++;
  align_out = *inp++;

  src_ptr_1 =     (uint8_t*)( (uint32_t)&input_1[PAD]  + align_in );
  coord_ptr =     (int32_t *)( (uint32_t)&coord[PAD] + align_out);
  ref_coord_ptr = (int32_t *)( (uint32_t)&ref_coord[PAD] + align_out);
  grey_ptr  =     (int32_t *)( (uint32_t)&grey[PAD] + align_out);
  ref_grey_ptr =  (int32_t *)( (uint32_t)&ref_grey[PAD] + align_out);

  for(count = 0; count < testcases; count++)
  {
    /* Read test-case params. */
    rows = *inp++;
    cols = *inp++;
    in_size  = *inp++;
    out_size = *inp++;

    /* Checking sanity of generated driver. */
    if( N < in_size )
    {
      printf("source or dst array size is less than test-case (ID %d) size\n", count);
      exit(1);
    }

    /* Prepare output arrays */
    memset(coord, 0, sizeof(coord[0]) * SIZE);
    memset(grey,  0, sizeof(grey[0])  * SIZE);
    memset(ref_coord, 0, sizeof(ref_coord[0]) * SIZE);
    memset(ref_grey,  0, sizeof(ref_grey[0]) * SIZE);

    /* Copy input and ref output to respective buffers */
    copy_int32_to_uint8(src_ptr_1, inp, in_size);
    inp += in_size;
    copy_int32_to_int32(ref_coord_ptr, outp, out_size);
    outp += out_size;
    copy_int32_to_int32(ref_grey_ptr, outp, out_size);
    outp += out_size;

    // Run the testcase
    printf("IMG_boundary_8(), Test %2d, %4dW x %4dH, 1000 calls: \n" , count, cols, rows);

#ifdef _C6RUN_IN_USE_
    // Call once to get in instruction cache
    IMG_boundary_8 (src_ptr_1, rows, cols, coord_ptr, grey_ptr );

    t_start = get_timestamp();
    for (i = 0; i<1000; i++)
    {
      IMG_boundary_8 (src_ptr_1, rows, cols, coord_ptr, grey_ptr );
    }
    t_stop = get_timestamp();

    t_c = t_stop - t_start - t_overhead;

    if( memcmp(coord, ref_coord, SIZE * sizeof(ref_coord[0])) )
    {
      printf("\tResult failure: coord - intrinsics: case # %d\n", count);
      exit(1);
    }

    if( memcmp(grey, ref_grey, SIZE * sizeof(ref_grey[0])) )
    {
      printf("\tResult failure: grey - intrinsics: case # %d\n", count);
      exit(1);
    }

    printf("\tIntrinsic C Time = %llu us\n", t_c);

    memset(coord, 0, sizeof(coord[0]) * SIZE);
    memset(grey,  0, sizeof(grey[0])  * SIZE);
#endif
    
    // Call once to get in instruction cache
    IMG_boundary_8_cn(src_ptr_1, rows, cols, coord_ptr, grey_ptr );

    t_start = get_timestamp();
    for (i = 0; i<1000; i++)
    {
      IMG_boundary_8_cn(src_ptr_1, rows, cols, coord_ptr, grey_ptr );
    }
    t_stop = get_timestamp();

    t_c = t_stop - t_start - t_overhead;

    if( memcmp(coord, ref_coord, SIZE * sizeof(ref_coord[0])) )
    {
      printf("\tResult failure: coord - natural c: case # %d\n", count);
      exit(1);
    }

    if( memcmp(grey, ref_grey, SIZE * sizeof(ref_grey[0])) )
    {
      printf("\tResult failure: grey - natural c: case # %d\n", count);
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


