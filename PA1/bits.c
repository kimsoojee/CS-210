/*
 * CS:APP Data Lab 
 * 
 * <Please put your name and userid here>
 * 
 * bits.c - Source file with your solutions to the Lab.
 *          This is the file you will hand in to your instructor.
 *
 * WARNING: Do not include the <stdio.h> header; it confuses the dlc
 * compiler. You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.  
 */

#if 0
/*
 * Instructions to Students:
 *
 * STEP 1: Read the following instructions carefully.
 */

You will provide your solution to the Data Lab by
editing the collection of functions in this source file.

INTEGER CODING RULES:
 
  Replace the "return" statement in each function with one
  or more lines of C code that implements the function. Your code 
  must conform to the following style:
 
  int Funct(arg1, arg2, ...) {
      /* brief description of how your implementation works */
      int var1 = Expr1;
      ...
      int varM = ExprM;

      varJ = ExprJ;
      ...
      varN = ExprN;
      return ExprR;
  }

  Each "Expr" is an expression using ONLY the following:
  1. Integer constants 0 through 255 (0xFF), inclusive. You are
      not allowed to use big constants such as 0xffffffff.
  2. Function arguments and local variables (no global variables).
  3. Unary integer operations ! ~
  4. Binary integer operations & ^ | + << >>
    
  Some of the problems restrict the set of allowed operators even further.
  Each "Expr" may consist of multiple operators. You are not restricted to
  one operator per line.

  You are expressly forbidden to:
  1. Use any control constructs such as if, do, while, for, switch, etc.
  2. Define or use any macros.
  3. Define any additional functions in this file.
  4. Call any functions.
  5. Use any other operations, such as &&, ||, -, or ?:
  6. Use any form of casting.
  7. Use any data type other than int.  This implies that you
     cannot use arrays, structs, or unions.

 
  You may assume that your machine:
  1. Uses 2s complement, 32-bit representations of integers.
  2. Performs right shifts arithmetically.
  3. Has unpredictable behavior when shifting an integer by more
     than the word size.

EXAMPLES OF ACCEPTABLE CODING STYLE:
  /*
   * pow2plus1 - returns 2^x + 1, where 0 <= x <= 31
   */
  int pow2plus1(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     return (1 << x) + 1;
  }

  /*
   * pow2plus4 - returns 2^x + 4, where 0 <= x <= 31
   */
  int pow2plus4(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     int result = (1 << x);
     result += 4;
     return result;
  }

FLOATING POINT CODING RULES

For the problems that require you to implent floating-point operations,
the coding rules are less strict.  You are allowed to use looping and
conditional control.  You are allowed to use both ints and unsigneds.
You can use arbitrary integer and unsigned constants.

You are expressly forbidden to:
  1. Define or use any macros.
  2. Define any additional functions in this file.
  3. Call any functions.
  4. Use any form of casting.
  5. Use any data type other than int or unsigned.  This means that you
     cannot use arrays, structs, or unions.
  6. Use any floating point data types, operations, or constants.


NOTES:
  1. Use the dlc (data lab checker) compiler (described in the handout) to 
     check the legality of your solutions.
  2. Each function has a maximum number of operators (! ~ & ^ | + << >>)
     that you are allowed to use for your implementation of the function. 
     The max operator count is checked by dlc. Note that '=' is not 
     counted; you may use as many of these as you want without penalty.
  3. Use the btest test harness to check your functions for correctness.
  4. Use the BDD checker to formally verify your functions
  5. The maximum number of ops for each function is given in the
     header comment for each function. If there are any inconsistencies 
     between the maximum ops in the writeup and in this file, consider
     this file the authoritative source.

/*
 * STEP 2: Modify the following functions according the coding rules.
 * 
 *   IMPORTANT. TO AVOID GRADING SURPRISES:
 *   1. Use the dlc compiler to check that your solutions conform
 *      to the coding rules.
 *   2. Use the BDD checker to formally verify that your solutions produce 
 *      the correct answers.
 */


#endif
/* Copyright (C) 1991-2015 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, see
   <http://www.gnu.org/licenses/>.  */
/* This header is separate from features.h so that the compiler can
   include it implicitly at the start of every compilation.  It must
   not itself include <features.h> or any other header that includes
   <features.h> because the implicit include comes before any feature
   test macros that may be defined in a source file before it first
   explicitly includes a system header.  GCC knows the name of this
   header in order to preinclude it.  */
/* glibc's intent is to support the IEC 559 math functionality, real
   and complex.  If the GCC (4.9 and later) predefined macros
   specifying compiler intent are available, use them to determine
   whether the overall intent is to support these features; otherwise,
   presume an older compiler has intent to support these features and
   define these macros by default.  */
/* wchar_t uses Unicode 7.0.0.  Version 7.0 of the Unicode Standard is
   synchronized with ISO/IEC 10646:2012, plus Amendments 1 (published
   on April, 2013) and 2 (not yet published as of February, 2015).
   Additionally, it includes the accelerated publication of U+20BD
   RUBLE SIGN.  Therefore Unicode 7.0.0 is between 10646:2012 and
   10646:2014, and so we use the date ISO/IEC 10646:2012 Amd.1 was
   published.  */
/* We do not support C11 <threads.h>.  */
/* 
 * absVal - absolute value of x
 *   Example: absVal(-1) = 1.
 *   You may assume -TMax <= x <= TMax
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 10
 *   Rating: 4
 */
int absVal(int x) {
    int xsign, negx;
    xsign = x >> 31;
    /*remove sign*/
    negx = x ^ xsign;
    return negx + (1 + ~xsign);

}
/* 
 * isGreater - if x > y  then return 1, else return 0 
 *   Example: isGreater(4,5) = 0, isGreater(5,4) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */
int isGreater(int x, int y) {
    int xsign, ysign, xy_subtract, eq_sign, dif_sign;
    /* neg = 1, pos = 0 */
    xsign = !!(x >> 31);
    ysign = !!(y >> 31);
    
    xy_subtract = ((x + ~y) >> 31) & 1;
    
    /* xy_subtract = 0, x > y | xy_subtract = 1, x < y */
    eq_sign = (!(xsign ^ ysign) & !(xy_subtract));
    
    /* x = pos & y = neg */
    dif_sign = (xsign ^ ysign) & !(xsign);
    
    return (eq_sign | dif_sign);
}
/* 
 * subOK - Determine if can compute x-y without overflow
 *   Example: subOK(0x80000000,0x80000000) = 1,
 *            subOK(0x80000000,0x70000000) = 0, 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 3
 */
int subOK(int x, int y) {
    int result, result_sign, xsign, xysign;
    result = (x + (~y + 1));
    result_sign = !!(result >> 31);
    
    /* pos = 0, neg = 1 */
    xsign = !!(x >> 31);
    
    /* same sign = 0, different sign = 1 */
    xysign = (xsign) ^ !(y >> 31);
    
    /* overflow -> same x,y sign & different result sign */
    return !((xsign^result_sign) & (!xysign));
}

/*
 * bitNor - x^y using only ~ and &
 *   Example: bitXor(4, 5) = 1
 *   Legal ops: ~ &
 *   Max ops: 14
 *   Rating: 1
 */
int bitNor(int x, int y) {
    /* Demorgan's law*/
    return (~x & ~y);
}
/*
 * bitParity - returns 1 if x contains an odd number of 0's
 *   Examples: bitParity(5) = 0, bitParity(7) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 4
 */
int bitParity(int x) {
    int F = 0xFF | (0xFF<<8);
    /* compare [0,15] & [16,31] */
    x = ((x) ^ (x>> 16)) & F;
    /* compare [0,7] & [8,15] */
    x = ((x) ^ (x >> 8)) & 0xff;
    /* compare [0,3] & [4,7] */
    x = ((x) ^ (x >> 4)) & 0xf;
    /*compare [0,1] & [2,3] */
    x = ((x) ^ (x >> 2)) & 0x3;
    /* check num of zero if even or odd*/
    x = ((x) ^ (x >> 1)) & 0x1;

    return x;
}
/*
 * divpwr2 - Compute x/(2^n), for 0 <= n <= 30
 *  Round toward zero
 *   Examples: divpwr2(15,1) = 7, divpwr2(-33,4) = -2
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 2
 */
int divpwr2(int x, int n) {
    
    int xsign, xadd;
    /* (x >> n) + 1 if x < 0 */
    xsign = x >> 31;
    xadd = ((!!xsign) << n) + xsign;
    return (x + xadd) >> n;
}
/* 
 * rotateRight - Rotate x to the right by n
 *   Can assume that 0 <= n <= 31
 *   Examples: rotateRight(0x87654321,4) = 0x18765432
 *   Legal ops: ~ & ^ | + << >> !
 *   Max ops: 25
 *   Rating: 3 
 */
int rotateRight(int x, int n) {

    int F, shiftByn, num, front, convertF,back;
    F = ~(~0 << n);
    shiftByn = (x >> n);
    /* num = 32-n */
    num = 31 & (~n+1);
    front = (F & x) << num;
    /* make front to F */
    convertF = (F << num) | shiftByn;
    /* make front to zero */
    back = (F << num) ^ convertF;
    return front | back;
    
    
}
/* 
 * conditional - same as x ? y : z 
 *   Example: conditional(2,4,5) = 4
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 16
 *   Rating: 3
 */
int conditional(int x, int y, int z) {
    int x_check, printy, printz;
    /* if x != 0, 0xFFFFFFFF
       if x = 0, 0x00000000 */
    x_check = !x + (~0);
    printy = x_check & y;
    printz = ~(x_check) & z;
    return printy | printz;
}
/* 
 * float_abs - Return bit-level equivalent of absolute value of f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representations of
 *   single-precision floating point values.
 *   When argument is NaN, return argument..
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 10
 *   Rating: 2
 */
unsigned float_abs(unsigned uf) {
    unsigned normal, Nan, limit;
    normal = 0x7FFFFFFF;
    Nan = 0x7F800001;
    limit = normal & uf;
    
    /* if limit < nan, return limit */
    if (((limit) + (~Nan + 1)) >> 31)
        return limit;
    return uf;
}
/* 
 * float_i2f - Return bit-level equivalent of expression (float) x
 *   Result is returned as unsigned int, but
 *   it is to be interpreted as the bit-level representation of a
 *   single-precision floating point values.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned float_i2f(int x) {
    unsigned sign, exp, n, frac;
    sign = x & 0x80000000 ;
    exp = 31 + 127;
    n = 0;
    
    if (!x)
        return 0;
    
    if (sign)
        x = (~x+1);
    
    while (!(x & 0x80000000)) {
        exp = exp + (~1 +1);
        x = x << 1;
    }
    exp = exp << 23;
    
    /*  -127 < x < 128 */
    if ((x & 0xFF) > 128 | (x & 0x000001FF) == 0x180)
        n = 1;
    
    frac = ((x & 0x7FFFFFFF) >> 8 ) + n;
    
    return sign + exp + frac;
    
}
/*
 * float_half - Return bit-level equivalent of expression 0.5*f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   When argument is NaN, return argument
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned float_half(unsigned uf) {
    
    unsigned sign, exp, frac, n;
    sign = uf & 0x80000000;
    exp = uf & 0x7F800000;
    frac = (uf & (0x7FFFFFFF >> 8));
    n = !((uf & 0x3) ^ 3); //round
    
    /* infinity or NaN */
    if (exp == 0x7F800000)
        return uf;
    
    /* Denormalized, +1 */
    if (!exp) {
        return sign + ((frac >> 1) + n); //exp = 0
    }
    
    if (exp == (0x80000000 >> 8)) {
        frac = (frac >> 1) + (0x80000000 >> 9) + n;
        return sign + frac; //exp = 0
    }
    
    exp = (((exp >> 23) + ~1 + 1) << 23);
    return sign + exp + frac;
   
    
    
}
