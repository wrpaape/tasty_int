#include "tasty_int_test/floating_point_integral_limits.hpp"

#include <tuple>

#include "gtest/gtest.h"

#include "tasty_int_test/floating_point_types.hpp"
#include "tasty_int_test/integral_types.hpp"
#include "tasty_int_test/combine_types.hpp"


namespace {

using tasty_int_test::FloatingPointIntegralLimits;
using TestTypes = tasty_int_test::CombineTypes<
    tasty_int_test::FloatingPointTypes, 
    tasty_int_test::IntegralTypes
>;


template<typename T>
class FloatingPointIntegralLimitsTest : public ::testing::Test
{}; // class FloatingPointIntegralLimitsTest

TYPED_TEST_SUITE(FloatingPointIntegralLimitsTest, TestTypes);

TYPED_TEST(FloatingPointIntegralLimitsTest, MinimumIsLessThanMaximum)
{
    using FloatingPointType = std::tuple_element_t<0, TypeParam>;
    using IntegralType      = std::tuple_element_t<1, TypeParam>;
    using Limits            =
        FloatingPointIntegralLimits<FloatingPointType, IntegralType>;

    EXPECT_LE(Limits::minimum(), Limits::maximum());
}

TYPED_TEST(FloatingPointIntegralLimitsTest, MinimumIsCovertible)
{
    using FloatingPointType = std::tuple_element_t<0, TypeParam>;
    using IntegralType      = std::tuple_element_t<1, TypeParam>;

    auto integral =
        FloatingPointIntegralLimits<FloatingPointType, IntegralType>::minimum();
    static_assert(std::is_same_v<IntegralType, decltype(integral)>);
    auto floating_point = static_cast<FloatingPointType>(integral);
    auto converted      = static_cast<IntegralType>(floating_point);

    EXPECT_EQ(integral, converted);
}

TYPED_TEST(FloatingPointIntegralLimitsTest, MaximumIsCovertible)
{
    using FloatingPointType = std::tuple_element_t<0, TypeParam>;
    using IntegralType      = std::tuple_element_t<1, TypeParam>;

    auto integral =
        FloatingPointIntegralLimits<FloatingPointType, IntegralType>::maximum();
    static_assert(std::is_same_v<IntegralType, decltype(integral)>);
    auto floating_point = static_cast<FloatingPointType>(integral);
    auto converted      = static_cast<IntegralType>(floating_point);

    EXPECT_EQ(integral, converted);
}

} // namespace
