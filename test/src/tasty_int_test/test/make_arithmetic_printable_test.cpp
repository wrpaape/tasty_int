#include "tasty_int_test/make_arithmetic_printable.hpp"

#include <cstdint>

#include <limits>
#include <sstream>
#include <type_traits>

#include "gtest/gtest.h"

#include "tasty_int_test/floating_point_types.hpp"
#include "tasty_int_test/integral_types.hpp"


namespace {

template<typename MaxPrecisionType, typename ArithmeticType>
static void
test_value(ArithmeticType value)
    requires std::is_arithmetic_v<MaxPrecisionType>
          && std::is_arithmetic_v<ArithmeticType>
{
    std::ostringstream expected;
    expected << static_cast<MaxPrecisionType>(value);

    std::ostringstream actual;
    actual << tasty_int_test::make_arithmetic_printable(value);

    EXPECT_EQ(expected.str(), actual.str());
}


template<typename FloatingPointType>
    requires std::is_floating_point_v<FloatingPointType>
class MakeArithmeticPrintableFloatingPointTest
    : public ::testing::Test
{
protected:
    static void
    test_floating_point_value(FloatingPointType value)
    {
        test_value<long double>(value);
    }
}; // class MakeArithmeticPrintableFloatingPointTest

TYPED_TEST_SUITE(MakeArithmeticPrintableFloatingPointTest,
                 tasty_int_test::FloatingPointTypes);

TYPED_TEST(MakeArithmeticPrintableFloatingPointTest, MinimumValueIsPreserved)
{
    auto min_value = std::numeric_limits<TypeParam>::lowest();

    TestFixture::test_floating_point_value(min_value);
}

TYPED_TEST(MakeArithmeticPrintableFloatingPointTest, MaximumValueIsPreserved)
{
    auto max_value = std::numeric_limits<TypeParam>::max();

    TestFixture::test_floating_point_value(max_value);
}


template<typename IntegralType>
    requires std::is_integral_v<IntegralType>
class MakeArithmeticPrintableIntegralTest
    : public ::testing::Test
{}; // class MakeArithmeticPrintableIntegralTest

TYPED_TEST_SUITE(MakeArithmeticPrintableIntegralTest,
                 tasty_int_test::IntegralTypes);

TYPED_TEST(MakeArithmeticPrintableIntegralTest, MinimumValueIsPreserved)
{
    auto min_value = std::numeric_limits<TypeParam>::lowest();

    test_value<std::intmax_t>(min_value);
}

TYPED_TEST(MakeArithmeticPrintableIntegralTest, MaximumValueIsPreserved)
{
    auto max_value = std::numeric_limits<TypeParam>::max();

    test_value<std::uintmax_t>(max_value);
}

} // namespace
