#include "tasty_int/detail/digit_type.hpp"

#include <limits>
#include <type_traits>
#include <cmath>

#include "gtest/gtest.h"


namespace {

TEST(DigitTypeTest, DigitTypeIsIntegral)
{
    EXPECT_TRUE(std::is_integral_v<tasty_int::detail::digit_type>);
}

TEST(DigitTypeTest, DigitTypeIsUnsigned)
{
    EXPECT_TRUE(std::is_unsigned_v<tasty_int::detail::digit_type>);
}

TEST(DigitTypeTest, DigitAccumulatorTypeIsIntegral)
{
    EXPECT_TRUE(std::is_integral_v<tasty_int::detail::digit_accumulator_type>);
}

TEST(DigitTypeTest, DigitAccumulatorTypeIsUnsigned)
{
    EXPECT_TRUE(std::is_unsigned_v<tasty_int::detail::digit_accumulator_type>);
}

TEST(DigitTypeTest, SignedDigitAccumulatorTypeIsIntegral)
{
    EXPECT_TRUE(
        std::is_integral_v<tasty_int::detail::signed_digit_accumulator_type>
    );
}

TEST(DigitTypeTest, SignedDigitAccumulatorTypeIsSigned)
{
    EXPECT_TRUE(
        std::is_signed_v<tasty_int::detail::signed_digit_accumulator_type>
    );
}

TEST(DigitTypeTest, DigitAccumulatorTypesAreSameSize)
{
    EXPECT_EQ(sizeof(tasty_int::detail::digit_accumulator_type),
              sizeof(tasty_int::detail::signed_digit_accumulator_type));
}

TEST(DigitTypeTest, DigitTypeBitsIsLessThanOrEqualToDigitTypeNumericLimit)
{
    EXPECT_LE(tasty_int::detail::DIGIT_TYPE_BITS,
              std::numeric_limits<tasty_int::detail::digit_type>::digits);
}

TEST(DigitTypeTest, DigitTypeBitsIsOneHalfofDigitAccumulatorTypeNumericLimit)
{
    EXPECT_EQ(
        std::numeric_limits<
            tasty_int::detail::digit_accumulator_type
        >::digits / 2,
        tasty_int::detail::DIGIT_TYPE_BITS
    );
}

TEST(DigitTypeTest, DigitTypeMaxCanBeHeldInDigitType)
{
    EXPECT_LE(tasty_int::detail::DIGIT_TYPE_MAX,
              std::numeric_limits<tasty_int::detail::digit_type>::max());
}

auto SQUARE_ROOT_OF_DIGIT_ACCUMLATOR_TYPE_MAX =
    static_cast<tasty_int::detail::digit_accumulator_type>(
        std::ceil(
            std::sqrt(
                std::numeric_limits<
                    tasty_int::detail::digit_accumulator_type
                >::max()
            )
        )
    );

TEST(DigitTypeTest,
     DigitTypeMaxIsLessThanTheSquareRootOfDigitAccumulatorTypeMax)
{
    EXPECT_LE(tasty_int::detail::DIGIT_TYPE_MAX,
              SQUARE_ROOT_OF_DIGIT_ACCUMLATOR_TYPE_MAX);
}

TEST(DigitTypeTest, DigitTypeMaxIsRoughlyTheSquareRootOfDigitAccumulatorTypeMax)
{
    EXPECT_NEAR(SQUARE_ROOT_OF_DIGIT_ACCUMLATOR_TYPE_MAX,
                tasty_int::detail::DIGIT_TYPE_MAX,
                1);
}

} // namespace
