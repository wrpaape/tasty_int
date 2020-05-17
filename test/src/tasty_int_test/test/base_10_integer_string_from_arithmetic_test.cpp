#include "tasty_int_test/base_10_integer_string_from_arithmetic.hpp"

#include <string>
#include <type_traits>

#include "gtest/gtest.h"

#include "tasty_int_test/arithmetic_types.hpp"
#include "tasty_int_test/sample_arithmetic.hpp"


namespace {

using tasty_int_test::base_10_integer_string_from_arithmetic;

template<typename ArithmeticType>
concept Arithmetic = std::is_arithmetic_v<ArithmeticType>;


template<Arithmetic ArithmeticType>
class Base10IntegerStringFromArithmeticTest : public ::testing::Test
{
protected:
    static void
    test_value_is_convertible(ArithmeticType value);

    static std::string
    make_expected_base_10_integer_string(ArithmeticType value);

    static std::string
    to_string(ArithmeticType value);
}; // class Base10IntegerStringFromArithmeticTest

template<Arithmetic ArithmeticType>
void
Base10IntegerStringFromArithmeticTest<ArithmeticType>::test_value_is_convertible(
    ArithmeticType value
)
{
    EXPECT_EQ(make_expected_base_10_integer_string(value),
              base_10_integer_string_from_arithmetic(value));
}

template<Arithmetic ArithmeticType>
std::string
Base10IntegerStringFromArithmeticTest<ArithmeticType>::make_expected_base_10_integer_string(
    ArithmeticType value
)
{
    auto base_10_string = to_string(value);
    auto decimal_point  = base_10_string.find('.');

    return base_10_string.substr(0, decimal_point);
}

template<Arithmetic ArithmeticType>
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
    TestFixture::test_value_is_convertible(
        tasty_int_test::SampleArithmetic<TypeParam>::MINIMUM
    );
}

TYPED_TEST(Base10IntegerStringFromArithmeticTest, LowerQuartileValue)
{
    TestFixture::test_value_is_convertible(
        tasty_int_test::SampleArithmetic<TypeParam>::LOWER_QUARTILE
    );
}

TYPED_TEST(Base10IntegerStringFromArithmeticTest, MedianValue)
{
    TestFixture::test_value_is_convertible(
        tasty_int_test::SampleArithmetic<TypeParam>::MEDIAN
    );
}

TYPED_TEST(Base10IntegerStringFromArithmeticTest, UpperQuartileValue)
{
    TestFixture::test_value_is_convertible(
        tasty_int_test::SampleArithmetic<TypeParam>::UPPER_QUARTILE
    );
}

TYPED_TEST(Base10IntegerStringFromArithmeticTest, MaximumValue)
{
    TestFixture::test_value_is_convertible(
        tasty_int_test::SampleArithmetic<TypeParam>::MAXIMUM
    );
}

TYPED_TEST(Base10IntegerStringFromArithmeticTest, Zero)
{
    TestFixture::test_value_is_convertible(
        tasty_int_test::SampleArithmetic<TypeParam>::ZERO
    );
}

TYPED_TEST(Base10IntegerStringFromArithmeticTest, One)
{
    TestFixture::test_value_is_convertible(
        tasty_int_test::SampleArithmetic<TypeParam>::ONE
    );
}

} // namespace
