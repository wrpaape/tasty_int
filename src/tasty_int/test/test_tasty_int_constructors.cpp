#include "gtest/gtest.h"           // TEST
#include "tasty_int/tasty_int.hpp" // TastyInt
#include <limits>                  // std::numeric_limits



#define TEST_INTEGRAL(TYPE)                                                 \
TEST(Integral, unsigned_ ## TYPE)                                           \
{                                                                           \
    const unsigned TYPE zero = static_cast<unsigned TYPE>(0);               \
    const unsigned TYPE max  = std::numeric_limits<unsigned TYPE>::max();   \
    const unsigned TYPE mid  = max / static_cast<unsigned TYPE>(2);         \
    EXPECT_EQ(zero, TastyInt(zero).to_number<unsigned TYPE>());             \
    EXPECT_EQ(mid,  TastyInt(mid).to_number<unsigned TYPE>());              \
    EXPECT_EQ(max,  TastyInt(max).to_number<unsigned TYPE>());              \
}                                                                           \
TEST(Integral, signed_ ## TYPE)                                             \
{                                                                           \
    const signed TYPE zero = static_cast<signed TYPE>(0);                   \
    const signed TYPE min  = std::numeric_limits<signed TYPE>::min();       \
    const signed TYPE max  = std::numeric_limits<signed TYPE>::max();       \
    EXPECT_EQ(zero, TastyInt(zero).to_number<signed TYPE>());               \
    EXPECT_EQ(min,  TastyInt(min).to_number<signed TYPE>());                \
    EXPECT_EQ(max,  TastyInt(max).to_number<signed TYPE>());                \
}

TEST_INTEGRAL(char)
TEST_INTEGRAL(short)
TEST_INTEGRAL(int)
TEST_INTEGRAL(long)


#define TEST_FLOATING_POINT(TYPE, NAME)                                     \
TEST(FloatingPoint, NAME)                                                   \
{                                                                           \
    const TYPE begin = static_cast<TYPE>(-1000.0);                          \
    const TYPE end   = static_cast<TYPE>(10000.0);                          \
    const TYPE step  = static_cast<TYPE>((end - begin) / 3);                \
    for (TYPE x = begin; x < end; x += step)                                \
        EXPECT_EQ(static_cast<long>(x),                                     \
                  static_cast<long>(TastyInt(x).to_number<TYPE>()));        \
}

TEST_FLOATING_POINT(float,       float)
TEST_FLOATING_POINT(double,      double)
TEST_FLOATING_POINT(long double, long_double)
