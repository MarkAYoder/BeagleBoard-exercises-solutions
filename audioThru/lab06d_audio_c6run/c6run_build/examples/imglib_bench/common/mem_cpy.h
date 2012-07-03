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

#include <stdint.h>

void copy_int32_to_int8(int8_t *restrict dst, int32_t *restrict src, int32_t elements);
void copy_int32_to_int16(int16_t *restrict dst, int32_t *restrict src, int32_t elements);
void copy_int32_to_int32(int32_t *restrict dst, int32_t *restrict src, int32_t elements);

void copy_int32_to_uint8(uint8_t *restrict dst, int32_t *restrict src, int32_t elements);
void copy_int32_to_uint16(uint16_t *restrict dst, int32_t *restrict src, int32_t elements);
void copy_int32_to_uint32(uint32_t *restrict dst, int32_t *restrict src, int32_t elements);


/* ----------------------------------------------------------------------- */
/*            Copyright (c) 2007 Texas Instruments, Incorporated.          */
/*                           All Rights Reserved.                          */
/* ======================================================================= */
