#include "tasty_int/detail/digit_type.hpp"

#include <cmath>

#include <limits>
#include <type_traits>

#include "gtest/gtest.h"


namespace {

using tasty_int::detail::DIGIT_BASE;
using tasty_int::detail::DIGIT_TYPE_BITS;
using tasty_int::detail::DIGIT_TYPE_MAX;
using tasty_int::detail::DIGITS_PER_DIGIT_ACCUMULATOR;
using tasty_int::detail::digit_accumulator_type;
using tasty_int::detail::signed_digit_accumulator_type;
using tasty_int::detail::digit_type;


TEST(DigitTypeTest, DigitTypeIsIntegral)
{
    EXPECT_TRUE(std::is_integral_v<digit_type>);
}

TEST(DigitTypeTest, DigitTypeIsUnsigned)
{
    EXPECT_TRUE(std::is_unsigned_v<digit_type>);
}

TEST(DigitTypeTest, DigitAccumulatorTypeIsIntegral)
{
    EXPECT_TRUE(std::is_integral_v<digit_accumulator_type>);
}

TEST(DigitTypeTest, DigitAccumulatorTypeIsUnsigned)
{
    EXPECT_TRUE(std::is_unsigned_v<digit_accumulator_type>);
}

TEST(DigitTypeTest, SignedDigitAccumulatorTypeIsIntegral)
{
    EXPECT_TRUE(
        std::is_integral_v<signed_digit_accumulator_type>
    );
}

TEST(DigitTypeTest, SignedDigitAccumulatorTypeIsSigned)
{
    EXPECT_TRUE(
        std::is_signed_v<signed_digit_accumulator_type>
    );
}

TEST(DigitTypeTest, DigitAccumulatorTypesAreSameSize)
{
    EXPECT_EQ(sizeof(digit_accumulator_type),
              sizeof(signed_digit_accumulator_type));
}

TEST(DigitTypeTest, DigitTypeBitsIsLessThanOrEqualToDigitTypeNumericLimit)
{
    EXPECT_LE(DIGIT_TYPE_BITS, std::numeric_limits<digit_type>::digits);
}

TEST(DigitTypeTest,
     DigitTypeBitsEqualsDigitAccumulatorBitsDividedByDigitsPerAccumulator)
{
    EXPECT_EQ(
        std::numeric_limits<digit_accumulator_type>::digits /
        DIGITS_PER_DIGIT_ACCUMULATOR,
        DIGIT_TYPE_BITS
    );
}

TEST(DigitTypeTest, DigitTypeMaxCanBeHeldInDigitType)
{
    EXPECT_LE(DIGIT_TYPE_MAX,
              std::numeric_limits<digit_type>::max());
}

auto SQUARE_ROOT_OF_DIGIT_ACCUMLATOR_TYPE_MAX =
    static_cast<digit_accumulator_type>(
        std::ceil(
            std::sqrt(
                std::numeric_limits<digit_accumulator_type>::max()
            )
        )
    );

TEST(DigitTypeTest,
     DigitTypeMaxIsLessThanTheSquareRootOfDigitAccumulatorTypeMax)
{
    EXPECT_LE(DIGIT_TYPE_MAX,
              SQUARE_ROOT_OF_DIGIT_ACCUMLATOR_TYPE_MAX);
}

TEST(DigitTypeTest, DigitTypeMaxIsRoughlyTheSquareRootOfDigitAccumulatorTypeMax)
{
    EXPECT_NEAR(SQUARE_ROOT_OF_DIGIT_ACCUMLATOR_TYPE_MAX,
                static_cast<double>(DIGIT_TYPE_MAX),
                1.0);
}

TEST(DigitTypeTest, DigitBaseIsOneGreaterThanDigitTypeMax)
{
    EXPECT_EQ(DIGIT_BASE, DIGIT_TYPE_MAX + 1);
}

} // namespace
