/* ======================================================================= */
/*  TEXAS INSTRUMENTS, INC.                                                */
/*                                                                         */
/*  DSPLIB  DSP Signal Processing Library                                  */
/*                                                                         */
/*  This library contains proprietary intellectual property of Texas       */
/*  Instruments, Inc.  The library and its source code are protected by    */
/*  various copyrights, and portions may also be protected by patents or   */
/*  other legal protections.                                               */
/*                                                                         */
/*  This software is licensed for use with Texas Instruments TMS320        */
/*  family DSPs.  This license was provided to you prior to installing     */
/*  the software.  You may review this license by consulting the file      */
/*  TI_license.PDF which accompanies the files in this library.            */
/*                                                                         */
/* ----------------------------------------------------------------------- */
/*                                                                         */
/* DSP_iir.c -- IIR Filter                                                 */
/*              Optimized C Implementation (w/ Intrinsics)                 */
/*                                                                         */
/* Rev 0.0.1                                                               */
/*                                                                         */
/*  Usage                                                                  */
/*     This routine is C-callable and can be called as:                    */
/*                                                                         */
/*     void DSP_iir (                                                      */
/*         short                 Input,                                    */
/*         const short *restrict ptr_Coefs,                                */
/*         int                   nCoefs,                                   */
/*         short       *restrict ptr_State                                 */
/*     )                                                                   */
/*                                                                         */
/*  DESCRIPTION                                                            */
/*      This function implements an IIR filter, with a number of biquad    */
/*      stages given by nCoefs / 4. It accepts a single sample of          */
/*      input and returns a single sample of output. Coefficients are      */
/*      expected to be in the range [-2.0, 2.0) with Q14 precision.        */
/*                                                                         */
/* ----------------------------------------------------------------------- */
/*            Copyright (c) 2007 Texas Instruments, Incorporated.          */
/*                           All Rights Reserved.                          */
/* ======================================================================= */
#pragma CODE_SECTION(DSP_iir, ".text:intrinsic");

#include "DSP_iir.h"

short DSP_iir (
    short                 Input, 
    const short *restrict Coefs, 
    int                   nCoefs, 
    short       *restrict State 
) 
{
    int j, x, t_0, t_1, p_0, p_1, p_2, p_3;

    int s_32, s_10;

    long long c_7654, c_3210;
    long long s_3210;

    /* -------------------------------------------------------------------- */
    /*  Initialize our starting state.                                      */
    /* -------------------------------------------------------------------- */
    x = Input;

    /* -------------------------------------------------------------------- */
    /*  Inform the compiler about various alignments, etc.                  */
    /* -------------------------------------------------------------------- */
    _nassert((int)Coefs % 8 == 0);
    _nassert((int)State % 8 == 0);
    _nassert((int)nCoefs % 4 == 0);
    _nassert((int)nCoefs >= 4);

    /* -------------------------------------------------------------------- */
    /*  Iterate over the biquads, processing two per iteration.             */
    /* -------------------------------------------------------------------- */
    for (j = 0; j < nCoefs; j += 8) {
        s_3210 = _amem8(&State[j]);
        c_3210 = _amem8_const(&Coefs[j]);
        c_7654 = _amem8_const(&Coefs[j + 4]);

        s_10 = _loll(s_3210);
        s_32 = _hill(s_3210);

        p_0 = _dotp2(_hill(c_3210), s_10);
        p_1 = _dotp2(_loll(c_3210), s_10);

        p_2 = _dotp2(_hill(c_7654), s_32);
        p_3 = _dotp2(_loll(c_7654), s_32);

        t_0 = x + (p_0 >> 14);
        x += ((p_0 + p_1) >> 14);

        t_1 = x + (p_2 >> 14);
        x += ((p_2 + p_3) >> 14);

        if (j < nCoefs - 4)
            _mem8(&State[j]) = _itoll(_pack2(s_32, t_1), _pack2(s_10, t_0));
        else
            State[j] = _pack2(s_10, t_0);
    }
    return x;
}

/* ======================================================================= */
/*  End of file:  DSP_iir.c                                                */
/* ----------------------------------------------------------------------- */
/*            Copyright (c) 2007 Texas Instruments, Incorporated.          */
/*                           All Rights Reserved.                          */
/* ======================================================================= */

