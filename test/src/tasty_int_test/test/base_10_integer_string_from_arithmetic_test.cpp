#include "tasty_int_test/base_10_integer_string_from_arithmetic.hpp"

#include <string>
#include <type_traits>

#include "gtest/gtest.h"

#include "tasty_int_test/arithmetic_types.hpp"


namespace {

using tasty_int_test::base_10_integer_string_from_arithmetic;


template<typename ArithmeticType>
    requires std::is_arithmetic_v<ArithmeticType>
class Base10IntegerStringFromArithmeticTest : public ::testing::Test
{
protected:
    static constexpr auto ZERO    = static_cast<ArithmeticType>(0);
    static constexpr auto MINIMUM =
        std::numeric_limits<ArithmeticType>::lowest();
    static constexpr auto MAXIMUM = std::numeric_limits<ArithmeticType>::max();

    static constexpr ArithmeticType
    get_middle(ArithmeticType lower_bound,
               ArithmeticType upper_bound)
    {
        // promote to long double to avoid overflow
        auto range = static_cast<long double>(upper_bound)
                   - static_cast<long double>(lower_bound);
        return lower_bound + static_cast<ArithmeticType>(range / 2.0L);
    }

    static constexpr auto MEDIAN = std::is_signed_v<ArithmeticType>
                                 ? ZERO // avoid overflow for long double
                                 : get_middle(MINIMUM, MAXIMUM);
    static constexpr auto LOWER_QUARTILE = get_middle(MINIMUM, MEDIAN);
    static constexpr auto UPPER_QUARTILE = get_middle(MEDIAN,  MAXIMUM);

    static void
    test_value_is_convertible(ArithmeticType value);

    static std::string
    make_expected_base_10_integer_string(ArithmeticType value);

    static std::string
    to_string(ArithmeticType value);
}; // class LogarithmicRangeValuesTest

template<typename ArithmeticType>
void
Base10IntegerStringFromArithmeticTest<ArithmeticType>::test_value_is_convertible(
    ArithmeticType value
)
{
    EXPECT_EQ(make_expected_base_10_integer_string(value),
              base_10_integer_string_from_arithmetic(value));
}

template<typename ArithmeticType>
std::string
Base10IntegerStringFromArithmeticTest<ArithmeticType>::make_expected_base_10_integer_string(
    ArithmeticType value
)
{
    auto base_10_string = to_string(value);
    auto decimal_point  = base_10_string.find('.');

    return base_10_string.substr(0, decimal_point);
}

template<typename ArithmeticType>
std::string
Base10IntegerStringFromArithmeticTest<ArithmeticType>::to_string(
    ArithmeticType value
)
{
    if constexpr (std::is_integral_v<ArithmeticType>) {
        if constexpr (std::is_signed_v<ArithmeticType>) {
            return std::to_string(static_cast<long long>(value));
        } else {
            return std::to_string(static_cast<unsigned long long>(value));
        }
    } else {
        return std::to_string(static_cast<long double>(value));
    }
}

TYPED_TEST_SUITE(Base10IntegerStringFromArithmeticTest,
                 tasty_int_test::ArithmeticTypes);

TYPED_TEST(Base10IntegerStringFromArithmeticTest, MinimumValue)
{
    TestFixture::test_value_is_convertible(TestFixture::MINIMUM);
}

TYPED_TEST(Base10IntegerStringFromArithmeticTest, LowerQuartileValue)
{
    TestFixture::test_value_is_convertible(TestFixture::LOWER_QUARTILE);
}

TYPED_TEST(Base10IntegerStringFromArithmeticTest, Zero)
{
    TestFixture::test_value_is_convertible(TestFixture::ZERO);
}

TYPED_TEST(Base10IntegerStringFromArithmeticTest, MedianValue)
{
    TestFixture::test_value_is_convertible(TestFixture::MEDIAN);
}

TYPED_TEST(Base10IntegerStringFromArithmeticTest, UpperQuartileValue)
{
    TestFixture::test_value_is_convertible(TestFixture::UPPER_QUARTILE);
}

TYPED_TEST(Base10IntegerStringFromArithmeticTest, MaximumValue)
{
    TestFixture::test_value_is_convertible(TestFixture::MAXIMUM);
}

} // namespace
