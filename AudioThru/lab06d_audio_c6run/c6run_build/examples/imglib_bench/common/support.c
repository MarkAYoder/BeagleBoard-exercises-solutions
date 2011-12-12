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
/*      The header file hooks "srand()" to call srand32() when COMM_FLOW    */
/*      is set.  It also hooks "memcmp()" to call mem_compare() when        */
/*      INTERACTIVE_DEBUG is set.                                           */
/* ------------------------------------------------------------------------ */
/*            Copyright (c) 2008 Texas Instruments, Incorporated.           */
/*                           All Rights Reserved.                           */
/* ======================================================================== */

#ifdef COMM_FLOW

#include <stdio.h>    /* For fprintf() */
#include <limits.h>   /* For xxx_MAX   */
#include <stdlib.h>   /* For exit()    */
#include "support.h"

#ifdef _TMS320C6X
# define INLINE inline
# include <c6x.h>
# define lmo(x)   _lmbd(1,x)
# define SHRU(x,y) (((unsigned)(x)) >> (y))
#else
# define INLINE 
# define SHRU(x,y) (((x) & 32) ? 0 : (((unsigned)(x)) >> (y)))

/* ======================================================================== */
/*  LMO -- Return left-most 1.                                              */
/* ======================================================================== */
unsigned lmo(unsigned num)
{
    unsigned a;
    int l=31;

    if (!num) return 32;

    a=num&0xFFFF0000; if (a) { l-=16; num=a; }
    a=num&0xFF00FF00; if (a) { l-= 8; num=a; }
    a=num&0xF0F0F0F0; if (a) { l-= 4; num=a; }
    a=num&0xCCCCCCCC; if (a) { l-= 2; num=a; }
    a=num&0xAAAAAAAA; if (a) { l-= 1; }

    return l;
}
#endif

#ifdef _TMS320C6X
# pragma DATA_ALIGN(__r_buf, 128);
#endif

static unsigned __r_buf[128], __r_ptr = 0;

/* ======================================================================== */
/*  RAND32   -- Generates a pseudo-random number using a state array.       */
/* ======================================================================== */
static INLINE unsigned Rand32(void)
{
    unsigned p, p1, p2;

    /* -------------------------------------------------------------------- */
    /*  Lagged Fibonacci Sequence Random Number Generator.                  */
    /*                                                                      */
    /*  This random number generator comes from Knuth vol 2., 3rd Ed,       */
    /*  p27-29.  The algorithm should produce a sequence whose most         */
    /*  significant bits have a period of 2**31 * (2**127 - 1) and whose    */
    /*  least significant bits have a period of 2**127 - 1.  Not bad.       */
    /*  The lags of 30 and 127 come from Table 1 on p29.                    */
    /* -------------------------------------------------------------------- */

    p  = __r_ptr++ & 127;
    p1 = (p -  30) & 127;
    p2 = (p - 127) & 127;

    return (__r_buf[p] = __r_buf[p1] + __r_buf[p2]);
}
unsigned rand32(void)
{
    return Rand32();
}

/* ======================================================================== */
/*  SRAND32  -- Initializes a random number generator state array.          */
/* ======================================================================== */
void srand32(unsigned seed)
{
    unsigned s = seed ^ 0x2A3A4A5A, s1, acc = 0;
    int i, j;

#ifdef srand
# undef srand
    /* -------------------------------------------------------------------- */
    /*  Call the standard-library's srand(), since we hooked it w/a macro.  */
    /* -------------------------------------------------------------------- */
    srand(seed);
#endif

    /* -------------------------------------------------------------------- */
    /*  This initializer uses the user-provided seed to drive a linear-     */
    /*  feedback-shift-register (LFSR) random number generator to produce   */
    /*  the initial random number buffer for the lagged-Fibonacci           */
    /*  generator that rand32() uses.  This code uses the CRC32 polynomial  */
    /*  x^32+x^26+x^23+x^22+x^16+x^12+x^11+x^10+x^8+x^7+x^5+x^4+x^2+x+1     */
    /*  for the LFSR, since it generates a maximal-length sequence.         */
    /*                                                                      */
    /*  The user-provided seed is salted with my favorite magic constant,   */
    /*  0x2A3A4A5A, to provide the initial LSFR setting.  If that comes     */
    /*  up zero, then the salt is removed, giving an initial LSFR value of  */
    /*  0x2A3A4A5A.                                                         */
    /*                                                                      */
    /*  The LFSR is run for 43 iterations between buffer writes.  43 is     */
    /*  relatively prime to 2**32 - 1, and so all 2**32 - 1 unique seeds    */
    /*  will produce unique LFSR sequences to be written to the lagged-     */
    /*  Fibonacci generator buffer.  It is also a large enough number of    */
    /*  iters to ensure that the 32 bits in the LSFR seed are "new" bits.   */
    /*                                                                      */
    /*  The output of the LFSR is added to the initial seed and loop count  */
    /*  for a touch of added randomness, but I doubt that it significantly  */
    /*  impacts its randomness, either positively or negatively.  LFSR's    */
    /*  are already pretty good random number generators.  :-)              */
    /* -------------------------------------------------------------------- */

    if (!s) 
        s = 0x2A3A4A5A;

    for (i = 0; i < 127; i++)
    {
        for (j = 0; j <= 42; j++)
        {
            s1 = s >> 31 ? 0x4C11DB7 : 0;
            s  = (s << 1) ^ s1;
        }

        acc |= __r_buf[i] = seed + s + i;
    }

    /* -------------------------------------------------------------------- */
    /*  Note:  We should have at least one non-zero bit in each bit         */
    /*  position across all of the bits in the random number buffer.  We    */
    /*  ensure this by ORing all of the buffer entries together, and        */
    /*  then ORing the inverse of this accumulation into buf[0].  Usually,  */
    /*  this accumulation is all 1s, which means that no additional bits    */
    /*  will be set in buf[0].  (It's only _really_ necessary to ensure     */
    /*  that bit 0 has at least one 1 in it, but I make sure that all bits  */
    /*  have at least one 1.)                                               */
    /* -------------------------------------------------------------------- */
    __r_buf[0] |= ~acc;

    /* -------------------------------------------------------------------- */
    /*  Set the buffer pointer so that the first random number is           */
    /*  generated from buf[0], is stored in buf[127].  This is necessary    */
    /*  since we do not initialize buf[127] here.                           */
    /* -------------------------------------------------------------------- */
    __r_ptr = 127;
}


/* ======================================================================== */
/*  RANDOMIZE_ARRAY  -- Fills an array with random data.                    */
/* ======================================================================== */
void randomize_array
(
    void *inp_data,         /* Pointer to input data.       */
    int   num_data,         /* Number of elements.          */
    int   el_size,          /* Element size (1,2,4).        */
    Long  l_bound,          /* Lower bound.                 */
    Long  u_bound           /* Upper bound.                 */
)
{
    int i, rshift;
    Long rand0, range;
    char  *c_ptr = (char  *)inp_data;
    short *s_ptr = (short *)inp_data;
    int   *i_ptr = (int   *)inp_data;

    /* -------------------------------------------------------------------- */
    /*  Error checking.                                                     */
    /* -------------------------------------------------------------------- */
    if (el_size != 1 && el_size != 2 && el_size != 4)
    {
        fprintf(stderr, "randomize_array: Invalid element size %d\n", el_size);
        exit(1);
    }
    
    if ((el_size - 1) & (unsigned)inp_data)
    {
        fprintf(stderr, "randomize_array: Array alignment does not match "
                        "element size.\n>> inp_data = %.8X  el_size = %d <<\n",
                        (unsigned)inp_data, el_size);
        exit(1);
    }

    if (l_bound > u_bound)
    {
        fprintf(stderr, "randomize_array: Lower bound is larger than upper "
                        "bound.\n");
        exit(1);
    }

    /* -------------------------------------------------------------------- */
    /*  Find right-shift amount which best bounds our random number range.  */
    /* -------------------------------------------------------------------- */
    range  = u_bound - l_bound;
    rshift = (range <= UINT_MAX) ? lmo((unsigned)range) : 0;

    /* -------------------------------------------------------------------- */
    /*  Pick "num_data" random numbers.                                     */
    /* -------------------------------------------------------------------- */
    for (i = 0; i < num_data; i += rand0 <= u_bound)
    {
        rand0 = SHRU(Rand32(), rshift) + l_bound;
        if (el_size == 1) c_ptr[i] = rand0;
        if (el_size == 2) s_ptr[i] = rand0;
        if (el_size == 4) i_ptr[i] = rand0;
    }
}

/* ======================================================================== */
/*  RANDOMIZE_FLOAT_ARRAY -- Fills an array of float w/ random data.        */
/* ======================================================================== */
void randomize_float_array(float *inp_data, int num_data)
{
    const float MYFLT_MAX = 1E+10; 
    float r1;
    int r2 = (short)rand();
    unsigned int r4 = 0xFFFFFFFF;
    int i, r3;
    float u_bound = MYFLT_MAX;

    for (i=0; i < num_data; i++)
    {
        r2 = 69069 * r2 + 1;
        r3 = r2 % r4;
        /* at this point, 0.0 <= r1 <= 1.0 */
        r1 = (float)((float)r3/(float)r4);
        r1 = (float)(u_bound*(r1 - 0.5)); 

        inp_data[i] = r1;
    }
}

#ifdef WITH_INTERRUPTS
/* ======================================================================== */
/*  INIT_INTERRUPTS -- Initializes the ISTP, clears our counts, and sets    */
/*                     the GIE, NMIE and IER bits to receive interrupts.    */
/* ======================================================================== */
void init_interrupts(void)
{
    unsigned old_csr;

    /* -------------------------------------------------------------------- */
    /*  First, force interrupts off, in case they were already on.          */
    /* -------------------------------------------------------------------- */
    old_csr = CSR;
    CSR = (old_csr & ~1U);

    /* -------------------------------------------------------------------- */
    /*  Zero our interrupt counts for INT_4 through INT_F.                  */
    /* -------------------------------------------------------------------- */
    _int_4_cnt = 0;
    _int_5_cnt = 0;
    _int_6_cnt = 0;
    _int_7_cnt = 0;
    _int_8_cnt = 0;
    _int_9_cnt = 0;
    _int_A_cnt = 0;
    _int_B_cnt = 0;
    _int_C_cnt = 0;
    _int_D_cnt = 0;
    _int_E_cnt = 0;
    _int_F_cnt = 0;

    /* -------------------------------------------------------------------- */
    /*  Set our Interrupt Service Table Base to point to our ISRs.          */
    /* -------------------------------------------------------------------- */
    ISTP = (unsigned)_int_0;

    /* -------------------------------------------------------------------- */
    /*  Enable all interrupts in IER, including NMIE.                       */
    /* -------------------------------------------------------------------- */
    IER = 0xFFF2;

    /* -------------------------------------------------------------------- */
    /*  Now, clear all bits in IFR --> no pending interrupts.               */
    /* -------------------------------------------------------------------- */
    ICR = ~0U;

    /* -------------------------------------------------------------------- */
    /*  Finally, throw the switch -- GIE is enabled, interrupts are on.     */
    /* -------------------------------------------------------------------- */
    CSR = old_csr | 1;

#ifdef INTERACTIVE_DEBUG
    /* -------------------------------------------------------------------- */
    /*  If we're in interactive mode, register "show_interrupts" to run     */
    /*  at program exit.                                                    */
    /* -------------------------------------------------------------------- */
    atexit(show_interrupts);
#endif
}


#ifdef INTERACTIVE_DEBUG
/* ======================================================================== */
/*  SHOW_INTERRUPTS -- Show the currently accumulated number of interrupts. */
/* ======================================================================== */
void show_interrupts(void)
{
    unsigned old_csr;

    /* -------------------------------------------------------------------- */
    /*  First, force interrupts off, so our values are stable.              */
    /* -------------------------------------------------------------------- */
    old_csr = CSR;
    CSR = (old_csr & 0xFFFFFFFE);

    printf("=========================\n");
    printf("   Interrupt Summary:\n");
    printf("-------------------------\n");
    printf(" INT 4 Count:  %9d\n",_int_4_cnt);
    printf(" INT 5 Count:  %9d\n",_int_5_cnt);
    printf(" INT 6 Count:  %9d\n",_int_6_cnt);
    printf(" INT 7 Count:  %9d\n",_int_7_cnt);
    printf(" INT 8 Count:  %9d\n",_int_8_cnt);
    printf(" INT 9 Count:  %9d\n",_int_9_cnt);
    printf(" INT A Count:  %9d\n",_int_A_cnt);
    printf(" INT B Count:  %9d\n",_int_B_cnt);
    printf(" INT C Count:  %9d\n",_int_C_cnt);
    printf(" INT D Count:  %9d\n",_int_D_cnt);
    printf(" INT E Count:  %9d\n",_int_E_cnt);
    printf(" INT F Count:  %9d\n",_int_F_cnt);
    printf("=========================\n");

    /* -------------------------------------------------------------------- */
    /*  Restore our interruptibility state.                                 */
    /* -------------------------------------------------------------------- */
    CSR = old_csr;
}
#endif /* INTERACTIVE_DEBUG */

/* ======================================================================== */
/*  The Interrupt Service Table....                                         */
/* ======================================================================== */

asm("isr     .macro          _n");
asm("");
asm("        .global __int_:_n:");
asm("        .global __int_:_n:_cnt");
asm("__int_:_n:");
asm("        .bss    __int_:_n:_cnt,4,4");
asm("        STW     A0,     *SP--               ; Spill A0 to stack");
asm("        LDW     *DP(__int_:_n:_cnt),    A0  ; Load exec count");
asm("        B       IRP                         ; Start returning to caller");
asm("        LDW     *++SP,  A0                  ; Load spill value into A0");
asm("        NOP                                 ; Wait...");
asm("        NOP                                 ; Wait...");
asm("        ADD     1,      A0,     A0          ; Increment exec count");
asm("        STW     A0,     *DP(__int_:_n:_cnt) ; Store exec count");
asm("        ; === Spill value is loaded here");
asm("        ; === Branch to IRP occurs here");
asm("");
asm("        .endm");
asm("");
asm("        .sect   \".vectors\"");
asm("        .align  1024");
asm("        isr     0");
asm("        isr     1");
asm("        isr     2");
asm("        isr     3");
asm("        isr     4");
asm("        isr     5");
asm("        isr     6");
asm("        isr     7");
asm("        isr     8");
asm("        isr     9");
asm("        isr     A");
asm("        isr     B");
asm("        isr     C");
asm("        isr     D");
asm("        isr     E");
asm("        isr     F");
asm("");
asm("        .sect   \".text\"");

#endif /* WITH_INTERRUPTS */

#ifdef INTERACTIVE_DEBUG

#ifdef memcmp
# undef memcmp
#endif

#include <string.h>
/* ======================================================================== */
/*  MEM_COMPARE -- Compare two memory images and output a detailed dump if  */
/*                 the images differ.                                       */
/* ======================================================================== */
int mem_compare(void *r1, char *n1, void *r2, char *n2, int len)
{
    unsigned char *c1, *c2;
    int i, j, k, total, skip;
    unsigned addr;
    char buf[80];
    const char hex[16] = "0123456789ABCDEF";

    /* -------------------------------------------------------------------- */
    /*  Do a simple memcmp.  If it succeeds, return "OK".                   */
    /* -------------------------------------------------------------------- */
    if (memcmp(r1, r2, len) == 0)
        return 0;

    /* -------------------------------------------------------------------- */
    /*  The memcmp failed, so dump out a nicely formatted table which       */
    /*  shows both arrays, and notes where they differ.                     */
    /* -------------------------------------------------------------------- */
    printf("\n\nERROR:  Arrays '%s' and '%s' do not match.\n", n1, n2);

    printf("           %-32s  %-32s\n", n1, n2);
#ifdef _BIG_ENDIAN
    printf("Address     0   1   2   3   4   5   6   7"
                  "     0   1   2   3   4   5   6   7\n");
#else
    printf("Address     7   6   5   4   3   2   1   0"
                  "     7   6   5   4   3   2   1   0\n");
#endif
    printf("========   =============================="
                  "    ==============================\n");

    /* -------------------------------------------------------------------- */
    /*  Generate char ptrs to the arrays.                                   */
    /* -------------------------------------------------------------------- */
    c1 = (unsigned char *)r1;
    c2 = (unsigned char *)r2;

    /* -------------------------------------------------------------------- */
    /*  The output dump is aligned on 8-byte boundaries.  Handle arrays     */
    /*  which start on other boundaries by backing up the pointers a bit.   */
    /*  We'll output whitespace for the entries which are outside our       */
    /*  array.                                                              */
    /* -------------------------------------------------------------------- */
    addr  = (unsigned)&c1[0];
    skip  = addr & 7;
    addr -= skip;
    c1   -= skip;
    c2   -= skip;
    total = len + skip;

    /* -------------------------------------------------------------------- */
    /*  Initialize our line buffer to all blanks.  We'll fill in fields w/  */
    /*  hex characters and asterisks (to denote differences) as needed.     */
    /* -------------------------------------------------------------------- */
    memset(buf, ' ', sizeof(buf));
    buf[ 8] = ':';
    buf[ 9] = ' ';
    buf[10] = ' ';
    buf[76] = '\n';

    /* -------------------------------------------------------------------- */
    /*  Generate the output table.  Each line contains 8 bytes from each    */
    /*  array, plus the address of the first array corresponding to the     */
    /*  elements shown.  Asterisks are shown in the first array to          */
    /*  illustrate differences between it and the second array.             */
    /* -------------------------------------------------------------------- */
    for (i = 0; i < total; i += 8)
    {
        /* ---------------------------------------------------------------- */
        /*  "Render" the bytes within a line.                               */
        /* ---------------------------------------------------------------- */
        k = total - i;
        k = k > 8 ? 8 : k;

        for (j = skip; j < k; j++)
        {
            int val1 = c1[i + j], val2 = c2[i + j];
            int v1d1, v1d0, v2d1, v2d0;

            v1d1 = hex[0xF & (val1 >> 4)];
            v1d0 = hex[0xF &  val1      ];
            v2d1 = hex[0xF & (val2 >> 4)];
            v2d0 = hex[0xF &  val2      ];

#ifdef _BIG_ENDIAN
            buf[11 + 4*j] = v1d1;
            buf[12 + 4*j] = v1d0;
            buf[13 + 4*j] = val1 == val2 ? ' ' : '*';
            buf[45 + 4*j] = v2d1;
            buf[46 + 4*j] = v2d0;
#else
            buf[39 - 4*j] = v1d1;
            buf[40 - 4*j] = v1d0;
            buf[41 - 4*j] = val1 == val2 ? ' ' : '*';
            buf[73 - 4*j] = v2d1;
            buf[74 - 4*j] = v2d0;
#endif
        }


        /* ---------------------------------------------------------------- */
        /*  If this line did not contain 8 bytes from the array because we  */
        /*  are at one end or the other, blank out the unused bytes.        */
        /* ---------------------------------------------------------------- */
#ifdef _BIG_ENDIAN
        if (skip > 0)
        {
            memset(buf + 11, ' ', 4*skip);
            memset(buf + 45, ' ', 4*skip);
        }
        if (k < 8) 
        {
            memset(buf + 11 + 4*k, ' ', 32 - 4*k);
            memset(buf + 45 + 4*k, ' ', 32 - 4*k);
        }
#else
        if (skip > 0)
        {
            memset(buf + 42 - 4*skip, ' ', 4*skip);
            memset(buf + 76 - 4*skip, ' ', 4*skip);
        }
        if (k < 8) 
        {
            memset(buf + 11, ' ', 32 - 4*k);
            memset(buf + 45, ' ', 32 - 4*k);
        }
#endif

        /* ---------------------------------------------------------------- */
        /*  Update the address field on the line.                           */
        /* ---------------------------------------------------------------- */
        buf[ 0] = hex[0xF & (addr >> 28)];
        buf[ 1] = hex[0xF & (addr >> 24)];
        buf[ 2] = hex[0xF & (addr >> 20)];
        buf[ 3] = hex[0xF & (addr >> 16)];
        buf[ 4] = hex[0xF & (addr >> 12)];
        buf[ 5] = hex[0xF & (addr >>  8)];
        buf[ 6] = hex[0xF & (addr >>  4)];
        buf[ 7] = hex[0xF & (addr      )];

        /* ---------------------------------------------------------------- */
        /*  Shuttle the line buffer to stdout for the user to see.          */
        /* ---------------------------------------------------------------- */
        fwrite(buf, 1, 77, stdout);
        addr += 8;

        skip = 0;
    }

    printf("\nResult failure ('%s' vs. '%s')\n", n1, n2);
    
    /* -------------------------------------------------------------------- */
    /*  Since we're running in "interactive debugging" mode, exit now       */
    /*  rather than continuing to compare the other arrays.                 */
    /* -------------------------------------------------------------------- */
    /*exit(1);*/

    return -1;
}
#endif /* INTERACTIVE_DEBUG */

#else

/* ======================================================================== */
/*  Fix the following warning:  "At end of source: warning: a translation   */
/*  unit must contain at least one declaration"                             */
/* ======================================================================== */
void __unused__(void) { }

#endif /* COMM_FLOW */
/* ======================================================================== */
/*  End of file:  support.c                                                 */
/* ------------------------------------------------------------------------ */
/*            Copyright (c) 2008 Texas Instruments, Incorporated.           */
/*                           All Rights Reserved.                           */
/* ======================================================================== */


