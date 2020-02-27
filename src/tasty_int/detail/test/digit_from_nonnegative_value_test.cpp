#include "tasty_int/detail/digit_from_nonnegative_value.hpp"

#include <cmath>

#include <limits>
#include <type_traits>

#include "gtest/gtest.h"

#include "tasty_int_test/floating_point_types.hpp"
#include "tasty_int_test/integral_types.hpp"
#include "tasty_int_test/logarithmic_range_values.hpp"


namespace {

using tasty_int::detail::DIGIT_BASE;
using tasty_int::detail::digit_from_nonnegative_value;


template<typename IntegralType>
    requires std::is_integral_v<IntegralType>
class DigitFromNonNegativeIntegralTest : public ::testing::Test
{
protected:
    static const std::vector<IntegralType> TEST_VALUES;
}; // class DigitFromNonNegativeIntegralTest

template<typename IntegralType>
    requires std::is_integral_v<IntegralType>
const std::vector<IntegralType>
DigitFromNonNegativeIntegralTest<IntegralType>::TEST_VALUES =
    tasty_int_test::logarithmic_range_values<IntegralType>(
        0, std::numeric_limits<IntegralType>::max(), 2
    );

template<>
const std::vector<bool> DigitFromNonNegativeIntegralTest<bool>::TEST_VALUES =
    { false, true };
    
TYPED_TEST_SUITE(DigitFromNonNegativeIntegralTest,
                 tasty_int_test::IntegralTypes);

TYPED_TEST(DigitFromNonNegativeIntegralTest,
           DigitFromNonNegativeIntegralEqualsModuloDigitBase)
{
    for (TypeParam value : TestFixture::TEST_VALUES)
        EXPECT_EQ(value % DIGIT_BASE, digit_from_nonnegative_value(value));
}


template<typename FloatingPointType>
    requires std::is_floating_point_v<FloatingPointType>
class DigitFromNonNegativeFloatingPointTest : public ::testing::Test
{
protected:
    static std::vector<FloatingPointType> test_values();
}; // class DigitFromNonNegativeFloatingPointTest

template<typename FloatingPointType>
    requires std::is_floating_point_v<FloatingPointType>
std::vector<FloatingPointType>
DigitFromNonNegativeFloatingPointTest<FloatingPointType>::test_values()
{
    auto values = tasty_int_test::logarithmic_range_values<FloatingPointType>(
            0.0, std::numeric_limits<uintmax_t>::max() - 1, 2.0
        );

    auto uinteger_max_to_floating_point_max =
        tasty_int_test::logarithmic_range_values<FloatingPointType>(
            std::numeric_limits<uintmax_t>::max(),
            std::numeric_limits<FloatingPointType>::max(),
            2.0
        );

    values.insert(values.end(),
                  uinteger_max_to_floating_point_max.begin(),
                  uinteger_max_to_floating_point_max.end());

    return values;
}

TYPED_TEST_SUITE(DigitFromNonNegativeFloatingPointTest,
                 tasty_int_test::FloatingPointTypes);

TYPED_TEST(DigitFromNonNegativeFloatingPointTest,
           DigitFromNonNegativeFloatingPointEqualsFmodDigitBase)
{
    for (TypeParam value : TestFixture::test_values())
        EXPECT_EQ(std::fmod(value, DIGIT_BASE),
                  digit_from_nonnegative_value(value));
}

} // namespace
