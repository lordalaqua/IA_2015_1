#ifndef BitOperations_h__
#define BitOperations_h__
#include <cassert>

typedef unsigned long long int uint64;

/*
    Least Significant 1 Bit (LS1B)
    Returns a 64 bit integer where only the least significant
    bit with value 1 in the input has value 1. Ex: LS1B(10) == 2;
*/
inline uint64 LS1B(uint64 bb)
{
    return bb & (0 - bb);
}

/*
    Reset Least Significant 1 Bit
    Returns a 64 bit integer where the least significant 1
    bit is subtracted from the value of the input.
*/
inline uint64 LS1BReset(uint64 bb)
{
    return bb & (bb - 1);
}

/* Index for bitScan function */
const int BITSCAN_INDEX[64] = {
    0, 47, 1, 56, 48, 27, 2, 60,
    57, 49, 41, 37, 28, 16, 3, 61,
    54, 58, 35, 52, 50, 42, 21, 44,
    38, 32, 29, 23, 17, 11, 4, 62,
    46, 55, 26, 59, 40, 36, 15, 53,
    34, 51, 20, 43, 31, 22, 10, 45,
    25, 39, 14, 33, 19, 30, 9, 24,
    13, 18, 8, 12, 7, 6, 5, 63
};

/*
    Bit Scan
    Given an input where only one bit in the 64-bit integer has value 1,
    return the index in [0,63] which indicates which bit is 1.
*/
inline int bitScan(uint64 bb)
{
    /* Adapted from:
    "https://chessprogramming.wikispaces.com/BitScan#Bitscan forward-De Bruijn Multiplication-With separated LS1B"*/
    const uint64 debruijn64 = 0x03f79d71b4cb0a89;
    assert(bb != 0);
    return BITSCAN_INDEX[((bb ^ (bb - 1)) * debruijn64) >> 58];
}

#endif // BitOperations_h__
