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
/* ======================================================================== */
/*                                                                          */
/*  TEXAS INSTRUMENTS, INC.                                                 */
/*                                                                          */
/*  NAME                                                                    */
/*      support -- Support routines for benchmark flow.                     */
/*                                                                          */
/*  USAGE                                                                   */
/*      For char, short and int data, use:                                  */
/*                                                                          */
/*          randomize_array(data, len, el_size, l_bound, u_bound);          */
/*                                                                          */
/*      For float data, use:                                                */
/*                                                                          */
/*          randomize_float_array(data, len);                               */
/*                                                                          */
/*      To enable interrupts in a driver file:                              */
/*                                                                          */
/*      #ifdef COMM_FLOW                                                    */
/*          init_interrupts();                                              */
/*      #endif                                                              */
/*                                                                          */
/*  DESCRIPTION                                                             */
/*      RAND32                -- Return 32-bit random integers.             */
/*      SRAND32               -- Seeds rand32() random number generator.    */
/*      RANDOMIZE_ARRAY       -- Fills an integer array w/ random data.     */
/*      RANDOMIZE_FLOAT_ARRAY -- Fills an array of float w/ random data.    */
/*      MEM_COMPARE           -- memcmp() plus memory dump for debug.       */
/*      INIT_INTERRUPTS       -- Enables interrupts.                        */
/*      SHOW_INTERRUPTS       -- Shows interrupt occurance tallies.         */
/*                                                                          */
/*  NOTES                                                                   */
/*      These routines are compiled only if COMM_FLOW is set.  Also,        */
/*      the following macros control whether certain sets of functions      */
/*      are built:                                                          */
/*                                                                          */
/*         WITH_INTERRUPTS   -- init_interrupts, show_interrupts            */
/*         INTERACTIVE_DEBUG -- mem_compare, show_interrupts                */
/*                                                                          */
/*      In the case of the interrupt routines, empty macros are provided    */
/*      for "init_interrupts" and "show_interrupts" if COMM_FLOW is         */
/*      defined and WITH_INTERRUPTS is not.                                 */
/*                                                                          */
/*      This header file hooks "srand()" to call srand32() when COMM_FLOW   */
/*      is set.  It also hooks "memcmp()" to call mem_compare() when        */
/*      INTERACTIVE_DEBUG is set.                                           */
/* ------------------------------------------------------------------------ */
/*            Copyright (c) 2008 Texas Instruments, Incorporated.           */
/*                           All Rights Reserved.                           */
/* ======================================================================== */

#if defined(COMM_FLOW) && !defined(_SUPPORT_H_)
#define _SUPPORT_H_ 1

#ifdef _TMS320C6X
typedef long Long;
#define INLINE inline
#else
typedef long long Long; /* This type must be larger than 32 bits. */
#endif

/* ======================================================================== */
/*  RAND32  -- Return 32-bit random integers.                               */
/*  SRAND32 -- Seed the rand32() random number generator.                   */
/* ======================================================================== */
unsigned rand32(void);
void srand32(unsigned seed);

#define rand     rand32         /* Hook rand() for transparency.  */
#define srand(x) srand32(x)     /* Hook srand() for transparency. */

/* ======================================================================== */
/*  RANDOMIZE_ARRAY       -- Fills an array of char w/ random data.         */
/* ======================================================================== */
void randomize_array
(
    void *inp_data,         /* Pointer to input data.       */
    int   num_data,         /* Number of elements.          */
    int   el_size,          /* Element size (1,2,4)         */
    Long  l_bound,          /* Lower bound.                 */
    Long  u_bound           /* Upper bound.                 */
);

#define randomize_char_array(i,n,s,l,u)   randomize_array(i,n,1,l,u)
#define randomize_short_array(i,n,s,l,u)  randomize_array(i,n,2,l,u)
#define randomize_int_array(i,n,s,l,u)    randomize_array(i,n,4,l,u)

/* ======================================================================== */
/*  RANDOMIZE_FLOAT_ARRAY -- Fills an array of float w/ random data.        */
/* ======================================================================== */
void randomize_float_array(float *inp_data, int num_data);

#ifdef WITH_INTERRUPTS
/* ======================================================================== */
/*  INIT_INTERRUPTS -- Initializes the ISTP, clears our counts, and sets    */
/*                     the GIE, NMIE and IER bits to receive interrupts.    */
/* ======================================================================== */
void init_interrupts(void);

#ifdef INTERACTIVE_DEBUG
/* ======================================================================== */
/*  SHOW_INTERRUPTS -- Show the currently accumulated number of interrupts. */
/* ======================================================================== */
void show_interrupts(void);
#else
#define show_interrupts()
#endif /*INTERACTIVE_DEBUG*/

/* ======================================================================== */
/*  Interrupt routines and variables.                                       */
/* ======================================================================== */
extern void _int_0(void), _int_8(void);
extern void _int_1(void), _int_9(void);
extern void _int_2(void), _int_A(void);
extern void _int_3(void), _int_B(void);
extern void _int_4(void), _int_C(void);
extern void _int_5(void), _int_D(void);
extern void _int_6(void), _int_E(void);
extern void _int_7(void), _int_F(void);

extern volatile int _int_0_cnt, _int_8_cnt;
extern volatile int _int_1_cnt, _int_9_cnt;
extern volatile int _int_2_cnt, _int_A_cnt;
extern volatile int _int_3_cnt, _int_B_cnt;
extern volatile int _int_4_cnt, _int_C_cnt;
extern volatile int _int_5_cnt, _int_D_cnt;
extern volatile int _int_6_cnt, _int_E_cnt;
extern volatile int _int_7_cnt, _int_F_cnt;

#else

#define init_interrupts()
#define show_interrupts()

#endif /* WITH_INTERRUPTS */


#ifdef INTERACTIVE_DEBUG

/* ======================================================================== */
/*  MEM_COMPARE -- Compare two memory images and output a detailed dump if  */
/*                 the images differ.                                       */
/* ======================================================================== */
int mem_compare(void *r1, char *n1, void *r2, char *n2, int len);

/* ======================================================================== */
/*  Redefine memcmp() to call mem_compare() for better debug output.        */
/* ======================================================================== */
#define memcmp(x,y,z) mem_compare(x, #x, y, #y, z)

#endif /* INTERACTIVE_DEBUG */

#endif /* defined(COMM_FLOW) && !defined(_SUPPORT_H_) */
/* ======================================================================== */
/*  End of file:  support.h                                                 */
/* ------------------------------------------------------------------------ */
/*            Copyright (c) 2008 Texas Instruments, Incorporated.           */
/*                           All Rights Reserved.                           */
/* ======================================================================== */
