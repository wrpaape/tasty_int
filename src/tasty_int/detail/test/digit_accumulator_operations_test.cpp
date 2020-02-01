#include "tasty_int/detail/digit_type.hpp"

#include <limits>

#include "gtest/gtest.h"

#include "tasty_int_test/logarithmic_range.hpp"


namespace {

using tasty_int::detail::DIGIT_BASE;
using tasty_int::detail::DIGIT_TYPE_BITS;
using tasty_int::detail::DIGIT_TYPE_MAX;
using tasty_int::detail::digit_accumulator_type;


class DigitAccumulatorOperationsTest
    : public ::testing::TestWithParam<digit_accumulator_type>
{}; // class DigitAccumulatorOperationsTest

TEST_P(DigitAccumulatorOperationsTest,
       AndByDigitTypeMaxSameAsModuloByDigitBase)
{
    EXPECT_EQ(GetParam() % DIGIT_BASE,
              GetParam() & DIGIT_TYPE_MAX);
}

TEST_P(DigitAccumulatorOperationsTest,
       LeftShiftByDigitTypeBitsSameAsMultiplyByDigitBase)
{
    EXPECT_EQ(GetParam() *  DIGIT_BASE,
              GetParam() << DIGIT_TYPE_BITS);
}

TEST_P(DigitAccumulatorOperationsTest,
       RightShiftByDigitTypeBitsSameAsDivideByDigitBase)
{
    EXPECT_EQ(GetParam() /  DIGIT_BASE,
              GetParam() >> DIGIT_TYPE_BITS);
}

INSTANTIATE_TEST_SUITE_P(
    DigitAccumulatorOperationsTest,
    DigitAccumulatorOperationsTest,
    tasty_int_test::logarithmic_range<digit_accumulator_type>(
        0, std::numeric_limits<digit_accumulator_type>::max(), 2
    )
);

} // namespace
