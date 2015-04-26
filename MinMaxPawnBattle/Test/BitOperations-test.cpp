#include "UnitTest++.h"
#include "BitOperations.hpp"

TEST(LeastSignificant1BitTest)
{
    CHECK(LS1B(0) == 0);
    CHECK(LS1B(1) == 1);
    CHECK(LS1B(2) == 2);
    CHECK(LS1B(32) == 32);
    CHECK(LS1B(37008) == 16);    
    CHECK(LS1B(-8935000923214708672) == 64);
}

TEST(LeastSignificant1BitResetTest)
{
    CHECK(LS1BReset(0) == 0);
    CHECK(LS1BReset(1) == 0);
    CHECK(LS1BReset(3) == 2);
    CHECK(LS1BReset(10) == 8);
    CHECK(LS1BReset(37008) == 36992);
    CHECK(LS1BReset(-8935000923214708672) == -8935000923214708736);
}


TEST(BitScanTest)
{
    // bitScan(0) will crash
    CHECK(bitScan(1) == 0);
    CHECK(bitScan(4) == 2);
    CHECK(bitScan(32) == 5);
    CHECK(bitScan(4096) == 12);
    CHECK(bitScan(140737488355328) == 47);
    CHECK(bitScan((0 - 9223372036854775808)) == 63);
}