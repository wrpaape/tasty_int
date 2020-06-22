#include "tasty_int/detail/absolute_value_from_arithmetic.hpp"

#include <cmath>

#include <type_traits>

#include "gtest/gtest.h"

#include "tasty_int_test/sample_arithmetic.hpp"
#include "tasty_int_test/unsigned_arithmetic_types.hpp"
#include "tasty_int_test/signed_integral_types.hpp"
#include "tasty_int_test/floating_point_types.hpp"
#include "tasty_int_test/expect_approx.hpp"


namespace {

using tasty_int::detail::absolute_value_from_arithmetic;
using tasty_int_test::SampleArithmetic;

template<tasty_int::UnsignedIntegral UnsignedIntegralType>
class AbsoluteValueFromUnsignedIntegralTest : public ::testing::Test
{}; // class AbsoluteValueFromUnsignedIntegralTest

TYPED_TEST_SUITE(AbsoluteValueFromUnsignedIntegralTest,
                 tasty_int_test::UnsignedArithmeticTypes);

TYPED_TEST(AbsoluteValueFromUnsignedIntegralTest, DoesNotChangeValue)
{
    for (TypeParam value : SampleArithmetic<TypeParam>::VALUES) {
        auto absolute_value = absolute_value_from_arithmetic(value);

        static_assert(std::is_same_v<TypeParam, decltype(absolute_value)>);

        EXPECT_EQ(value, absolute_value);
    }
}


template<tasty_int::SignedIntegral SignedIntegralType>
class AbsoluteValueFromSignedIntegralTest : public ::testing::Test
{}; // class AbsoluteValueFromSignedIntegralTest

TYPED_TEST_SUITE(AbsoluteValueFromSignedIntegralTest,
                 tasty_int_test::SignedIntegralTypes);

TYPED_TEST(AbsoluteValueFromSignedIntegralTest,
           TypeIsUnsignedAndValueIsNegatedIfNegative)
{
    for (TypeParam value : SampleArithmetic<TypeParam>::VALUES) {
        auto absolute_value = absolute_value_from_arithmetic(value);

        static_assert(std::is_same_v<
            std::make_unsigned_t<TypeParam>, decltype(absolute_value)
        >);

        if (value < TypeParam(0))
            EXPECT_EQ(value, TypeParam(-absolute_value));
        else
            EXPECT_EQ(value, absolute_value);
    }
}


template<tasty_int::FloatingPoint FloatingPointType>
class AbsoluteValueFromFloatingPointTest : public ::testing::Test
{}; // class AbsoluteValueFromFloatingPointTest

TYPED_TEST_SUITE(AbsoluteValueFromFloatingPointTest,
                 tasty_int_test::FloatingPointTypes);

TYPED_TEST(AbsoluteValueFromFloatingPointTest,
           TypeIsUnsignedAndValueIsNegatedIfNegative)
{
    for (TypeParam value : SampleArithmetic<TypeParam>::VALUES) {
        auto absolute_value = absolute_value_from_arithmetic(value);

        static_assert(std::is_same_v<TypeParam, decltype(absolute_value)>);

        EXPECT_APPROX(std::abs(value), absolute_value);
    }
}

} // namespace
