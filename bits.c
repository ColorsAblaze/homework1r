/* WARNING: Do not include any other libraries here,
 * otherwise you will get an error while running test.py
 * You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.
 *
 * Using printf will interfere with our script capturing the execution results.
 * At this point, you can only test correctness with ./btest.
 * After confirming everything is correct in ./btest, remove the printf
 * and run the complete tests with test.py.
 */

 /*
 * bitAnd - x & y using only ~ and |
 * Example: bitAnd(4, 5) = 4
 * Legal ops: ~ |
 * Max ops: 7
 * Difficulty: 1
 */
// #include<assert.h>
int bitAnd(int x, int y) {
    return ~((~x)|(~y));
}

/*
 * bitXor - x ^ y using only ~ and &
 *   Example: bitXor(4, 5) = 1
 *   Legal ops: ~ &
 *   Max ops: 7
 *   Difficulty: 1
 */
int bitXor(int x, int y) {
    return (~((~x)&(~y)))&(~(x&y));// OR-AND
}

/*
 * samesign - Determines if two integers have the same sign.
 *   0 is not positive, nor negative
 *   Example: samesign(0, 1) = 0, samesign(0, 0) = 1
 *            samesign(-4, -5) = 1, samesign(-4, 5) = 0
 *   Legal ops: >> << ! ^ && if else &
 *   Max ops: 12
 *   Difficulty: 2
 *
 * Parameters:
 *   x - The first integer.
 *   y - The second integer.
 *
 * Returns:
 *   1 if x and y have the same sign , 0 otherwise.
 */
int samesign(int x, int y) {
    if ((!x) && (!y)) return 1;
    if (!x) return 0;
    if (!y) return 0;
    return !((x>>31)^(y>>31));
}

/*
 * logtwo - Calculate the base-2 logarithm of a positive integer using bit
 *   shifting. (Think about bitCount)
 *   Note: You may assume that v > 0
 *   Example: logtwo(32) = 5
 *   Legal ops: > < >> << |
 *   Max ops: 25
 *   Difficulty: 4
 */
int logtwo(int x) {
    int b16 = ((x>>16)>0)<<4; x=x>>b16;
    int b8 = ((x>>8)>0)<<3; x=x>>b8;
    int b4 = ((x>>4)>0)<<2; x=x>>b4;
    int b2 = ((x>>2)>0)<<1; x=x>>b2;
    int b1 = ((x>>1)>0); x=x>>b1;
    // int b0 = x;
    return b16|b8|b4|b4|b2|b1;

}

/*
 *  byteSwap - swaps the nth byte and the mth byte
 *    Examples: byteSwap(0x12345678, 1, 3) = 0x56341278
 *              byteSwap(0xDEADBEEF, 0, 2) = 0xDEEFBEAD
 *    Note: You may assume that 0 <= n <= 3, 0 <= m <= 3
 *    Legal ops: ! ~ & ^ | + << >>
 *    Max ops: 17
 *    Difficulty: 2
 */
int byteSwap(int x, int n, int m) {
    int nn = n<<3, mm = m<<3;
    int t1 = (x>>mm)&0xff;
    int t2 = (x>>nn)&0xff;
    // assert(t2==0x80);
    //右移可能会补1，神笔c语言
    x &= ~(0xff<<mm);
    x &= ~(0xff<<nn);//消除归零
    x |= t1<<nn;
    x |= t2<<mm;
    return x;
}

/*
 * reverse - Reverse the bit order of a 32-bit unsigned integer.
 *   Example: reverse(0xFFFF0000) = 0x0000FFFF reverse(0x80000000)=0x1 reverse(0xA0000000)=0x5
 *   Note: You may assume that an unsigned integer is 32 bits long.
 *   Legal ops: << | & - + >> for while ! ~ (You can define unsigned in this function)
 *   Max ops: 30
 *   Difficulty: 3
 */
unsigned reverse(unsigned v) {
    unsigned u=0;
    for(unsigned i=1; i; i<<=1)
    {
        u <<=1; u |=(v&1); v >>=1;
    }
    return u;
}

/*
 * logicalShift - shift x to the right by n, using a logical shift
 *   Examples: logicalShift(0x87654321,4) = 0x08765432
 *   Note: You can assume that 0 <= n <= 31
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Difficulty: 3
 */
int logicalShift(int x, int n) {
    int p = (x>>31);//p<<31=负数-2147483648，正数0
    return (x>>n)^((p<<31)>>n)^((p&1)<<(31+(1+~n)));
}

/*
 * leftBitCount - returns count of number of consective 1's in left-hand (most) end of word.
 *   Examples: leftBitCount(-1) = 32, leftBitCount(0xFFF0F0F0) = 12,
 *             leftBitCount(0xFE00FF0F) = 7
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 50
 *   Difficulty: 4
 */
int leftBitCount(int x) {
    int a16 = (((x>>16)&0xFFFF)+1)>>16;
    a16<<=4;
    x <<= a16;
    int a8 = (((x>>24)&0xFF)+1)>>8;
    a8<<=3;
    x <<= a8;
    int a4 = (((x>>28)&0xF)+1)>>4;
    a4<<=2;
    x <<= a4;
    int a2 = (((x>>30)&0x3)+1)>>2;
    a2<<=1;
    x <<= a2;
    int a1 = (x>>31)&0x1;//p=0 or 1, (p+1)>>1=p
    x <<= a1;
    int a0=(x>>31)&0x1;
    return a0+a1+a2+a4+a8+a16;
}

/*
 * float_i2f - Return bit-level equivalent of expression (float) x
 *   Result is returned as unsigned int, but it is to be interpreted as
 *   the bit-level representation of a single-precision floating point values.
 *   Legal ops: if else while for & | ~ + - >> << < > ! ==
 *   Max ops: 30
 *   Difficulty: 4
 */
unsigned float_i2f(int x) {
    unsigned ux = x;                     
    unsigned sign = ux & 0x80000000;     
    unsigned absX = ux;
    if (x < 0) absX = ~ux + 1;           
    if (absX == 0) return 0;             

    int e = 31;
    while (!(absX >> e)) e = e - 1;

    unsigned exp = (e + 127) << 23;

    unsigned temp = absX << (31 - e);

    unsigned frac   = (temp >> 8) & 0x7FFFFF;
    unsigned round  = (temp >> 7) & 1;
    unsigned sticky = temp & 0x7F;

    if (round) {
        if (sticky | (frac & 1)) {
            frac = frac + 1;
            if (frac == 0x800000) {    
                frac = 0;
                exp = exp + (1 << 23);
            }
        }
    }

    return sign | exp | frac;
}

/*
 * floatScale2 - Return bit-level equivalent of expression 2*f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   When argument is NaN, return argument
 *   Legal ops: & >> << | if > < >= <= ! ~ else + ==
 *   Max ops: 30
 *   Difficulty: 4
 */
unsigned floatScale2(unsigned uf) {
    unsigned sign = uf & 0x80000000;
    unsigned exp = (uf >> 23) & 0xFF;
    unsigned frac = uf & 0x7FFFFF;

    // 无穷大或 NaN，直接返回
    if (exp == 0xFF) return uf;

    if (exp == 0) {
        if (frac == 0) return uf;          
        frac = frac << 1;                  
        if (frac & 0x800000) {             
            exp = 1;
            frac = frac & 0x7FFFFF;
        }
        return sign | (exp << 23) | frac;
    } else {
        // 规格化数，指数加 1
        exp = exp + 1;
        if (exp == 0xFF) {
            frac = 0;                      
        }
        return sign | (exp << 23) | frac;
    }
}

/*
 * float64_f2i - Convert a 64-bit IEEE 754 floating-point number to a 32-bit signed integer.
 *   The conversion rounds towards zero.
 *   Note: Assumes IEEE 754 representation and standard two's complement integer format.
 *   Parameters:
 *     uf1 - The lower 32 bits of the 64-bit floating-point number.
 *     uf2 - The higher 32 bits of the 64-bit floating-point number.
 *   Returns:
 *     The converted integer value, or 0x80000000 on overflow, or 0 on underflow.
 *   Legal ops: >> << | & ~ ! + - > < >= <= if else
 *   Max ops: 60
 *   Difficulty: 3
 */
int float64_f2i(unsigned uf1, unsigned uf2) {
    unsigned sign = uf2 >> 31;
    unsigned exp = (uf2 >> 20) & 0x7FF;
    unsigned frac_high = uf2 & 0xFFFFF;
    unsigned frac_low = uf1;

    if (!(exp - 0x7FF)) return 0x80000000;
    // 非规格化数或 0：太小，返回 0
    if (!exp) return 0;

    int E = exp - 1023;               
    if (E < 0) return 0;              
    if (E > 30) return 0x80000000;    

    unsigned hi = (1 << 20) | frac_high;   
    unsigned lo = frac_low;                

    int shift = 52 - E;                    
    unsigned result;

    if (shift >= 32) {
        result = hi >> (shift - 32);       
    } else {
        result = (hi << (32 - shift)) | (lo >> shift);
    }

    if (sign) {
        return ~result + 1;                
    } else {
        return result;
    }
}

/*
 * floatPower2 - Return bit-level equivalent of the expression 2.0^x
 *   (2.0 raised to the power x) for any 32-bit integer x.
 *
 *   The unsigned value that is returned should have the identical bit
 *   representation as the single-precision floating-point number 2.0^x.
 *   If the result is too small to be represented as a denorm, return
 *   0. If too large, return +INF.
 *
 *   Legal ops: < > <= >= << >> + - & | ~ ! if else &&
 *   Max ops: 30
 *   Difficulty: 4
 */
unsigned floatPower2(int x) {
    if (x > 127) {
        return 0x7F800000;                 
    } else if (x >= -126) {
        unsigned exp = x + 127;
        return exp << 23;
    } else if (x >= -149) {
        unsigned frac = 1 << (x + 149);
        return frac;
    } else {
        return 0;                          
    }
}
