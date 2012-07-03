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

/* ======================================================================= */

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>

#include "mem_cpy.h"

void copy_int32_to_int8(int8_t *restrict dst, int32_t *restrict src, int32_t elements)
{
  int32_t i;

  for(i = 0; i < elements; i++)
  {
    dst[i] = (int8_t) (src[i] & 0xFF);
  }
}

void copy_int32_to_int16(int16_t *restrict dst, int32_t *restrict src, int32_t elements)
{
  int32_t i;
  int32_t dat_out;
  int8_t *char_dst = (int8_t *)dst; // For non-aligned memory.

  for(i = 0; i < elements; i++)
  {
    dat_out = src[i];
    *char_dst++ = (int8_t) (dat_out & 0xFF);
    *char_dst++ = (int8_t) ((dat_out >> 8) & 0xFF);
  }
}

void copy_int32_to_int32(int32_t *restrict dst, int32_t *restrict src, int32_t elements)
{
  memcpy(dst, src, elements * sizeof(int32_t));
}

void copy_int32_to_uint8(uint8_t *restrict dst, int32_t *restrict src, int32_t elements)
{
  copy_int32_to_int8( (int8_t *)dst, src, elements);
}

void copy_int32_to_uint16(uint16_t *restrict dst, int32_t *restrict src, int32_t elements)
{
  copy_int32_to_int16( (int16_t *)dst, src, elements);
}

void copy_int32_to_uint32(uint32_t *restrict dst, int32_t *restrict src, int32_t elements)
{
  memcpy(dst, src, elements * sizeof(uint32_t));
}


/* ----------------------------------------------------------------------- */
/*            Copyright (c) 2007 Texas Instruments, Incorporated.          */
/*                           All Rights Reserved.                          */
/* ======================================================================= */


