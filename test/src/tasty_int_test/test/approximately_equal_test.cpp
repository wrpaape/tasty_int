#include "tasty_int_test/approximately_equal.hpp"

#include <cmath>

#include <limits>
#include <type_traits>

#include "gtest/gtest.h"

#include "tasty_int_test/floating_point_types.hpp"
#include "tasty_int_test/sample_arithmetic.hpp"


namespace {

using tasty_int_test::approximately_equal;
using tasty_int_test::SampleArithmetic;


template<typename FloatingPointType>
    requires std::is_floating_point_v<FloatingPointType>
class ApproximatelyEqualTest : public ::testing::Test
{}; // class ApproximatelyEqualTest

TYPED_TEST_SUITE(ApproximatelyEqualTest,
                 tasty_int_test::FloatingPointTypes);

TYPED_TEST(ApproximatelyEqualTest,
           PointOnePlusPointTwoApproximatelyEqualsPoint3)
{
    TypeParam lhs(0.1);
    TypeParam rhs(0.2);
    auto sum = lhs + rhs;
    TypeParam expected_result(0.3);

    EXPECT_TRUE(approximately_equal(sum, expected_result))
        << "    LHS: " << sum
        << "    RHS: " << expected_result;
}

TYPED_TEST(ApproximatelyEqualTest,
           PointOnePlusPointTwoDoesApproximatelyEqualPoint4)
{
    TypeParam lhs(0.1);
    TypeParam rhs(0.2);
    auto sum = lhs + rhs;
    TypeParam unexpected_result(0.4);

    EXPECT_FALSE(approximately_equal(sum, unexpected_result))
        << "    LHS: " << sum
        << "    RHS: " << unexpected_result;
}

template<typename FloatingPointType>
    requires std::is_floating_point_v<FloatingPointType>
void
expect_value_approximately_equals_self(FloatingPointType value)
{
    EXPECT_TRUE(approximately_equal(value, value))
        << "    LHS: " << value
        << "    RHS: " << value;
}

TYPED_TEST(ApproximatelyEqualTest, ValueApproximatelyEqualsItself)
{
    for (auto value : SampleArithmetic<TypeParam>::VALUES)
        expect_value_approximately_equals_self(value);

    expect_value_approximately_equals_self(
        std::numeric_limits<TypeParam>::min()
    );
}

template<typename FloatingPointType>
    requires std::is_floating_point_v<FloatingPointType>
void
expect_value_approximately_equals_adjacent_values(FloatingPointType value)
{

    auto prev_value =
        std::nextafter(value, std::numeric_limits<FloatingPointType>::lowest());
    EXPECT_TRUE(approximately_equal(value, prev_value))
        << "    LHS: " << value
        << "    RHS: " << prev_value;

    auto next_value =
        std::nextafter(value, std::numeric_limits<FloatingPointType>::max());
    EXPECT_TRUE(approximately_equal(value, next_value))
        << "    LHS: " << value
        << "    RHS: " << next_value;
}

TYPED_TEST(ApproximatelyEqualTest, AdjacentValuesAreApproximatelyEqual)
{
    for (auto value : SampleArithmetic<TypeParam>::VALUES)
        expect_value_approximately_equals_adjacent_values(value);

    expect_value_approximately_equals_adjacent_values(
        std::numeric_limits<TypeParam>::min()
    );
}

template<typename FloatingPointType>
    requires std::is_floating_point_v<FloatingPointType>
void
expect_value_approximately_equals_demotion_cast(FloatingPointType value)
{
    auto demoted_value = static_cast<float>(value);
    EXPECT_TRUE(approximately_equal(value, demoted_value))
        << "    LHS: " << value
        << "    RHS: " << demoted_value;
}

TYPED_TEST(ApproximatelyEqualTest, DemotionCastIsApproximatelyEqual)
{
    for (TypeParam value : SampleArithmetic<float>::VALUES)
        expect_value_approximately_equals_demotion_cast(value);

    expect_value_approximately_equals_demotion_cast(
        std::numeric_limits<TypeParam>::min()
    );
}

TYPED_TEST(ApproximatelyEqualTest, PositiveInfinitiesAreApproximatelyEqual)
{
    constexpr auto POSITIVE_INFINITY =
        +std::numeric_limits<TypeParam>::infinity();

    EXPECT_TRUE(approximately_equal(POSITIVE_INFINITY, POSITIVE_INFINITY));
}

TYPED_TEST(ApproximatelyEqualTest, NegativeInfinitiesAreApproximatelyEqual)
{
    constexpr auto NEGATIVE_INFINITY =
        -std::numeric_limits<TypeParam>::infinity();

    EXPECT_TRUE(approximately_equal(NEGATIVE_INFINITY, NEGATIVE_INFINITY));
}

TYPED_TEST(ApproximatelyEqualTest,
           OppositeSignInfinitiesAreNotApproximatelyEqual)
{
    constexpr auto POSITIVE_INFINITY =
        +std::numeric_limits<TypeParam>::infinity();
    constexpr auto NEGATIVE_INFINITY =
        -std::numeric_limits<TypeParam>::infinity();

    EXPECT_FALSE(approximately_equal(NEGATIVE_INFINITY, POSITIVE_INFINITY));
    EXPECT_FALSE(approximately_equal(POSITIVE_INFINITY, NEGATIVE_INFINITY));
}

} // namespace
