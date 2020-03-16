#include "tasty_int/detail/digits_subtraction.hpp"

#include <cmath>

#include "gtest/gtest.h"

#include "tasty_int/detail/conversions/digits_from_integral.hpp"
#include "tasty_int/detail/conversions/digits_from_floating_point.hpp"
#include "tasty_int/detail/integer.hpp"
#include "tasty_int/detail/sign_from_digits.hpp"
#include "tasty_int/detail/test/integer_test_common.hpp"
#include "tasty_int_test/nonnegative_arithmetic_values.hpp"


namespace {

using tasty_int::detail::subtract;
using tasty_int::detail::subtract_in_place;
using tasty_int::detail::digit_type;
using tasty_int::detail::Integer;
using tasty_int::detail::Sign;
using tasty_int::detail::conversions::digits_from_integral;
using tasty_int::detail::conversions::digits_from_floating_point;
using tasty_int_test::NONNEGATIVE_ARITHMETIC_VALUES;


template<typename SubtrahendType>
Integer
subtract_from_digits(const std::vector<digit_type> &minuend,
                     SubtrahendType                 subtrahend)
{
    auto result_digits = minuend;

    Sign result_sign = subtract_in_place(subtrahend, result_digits);

    Integer result = { .sign = result_sign, .digits = result_digits };

    return result;
}

template<typename MinuendType>
Integer
subtract_from_arithmetic(MinuendType                    minuend,
                         const std::vector<digit_type> &subtrahend)
    requires std::is_arithmetic_v<MinuendType>
{
    auto [result_sign, result_digits] = subtract(minuend, subtrahend);

    Integer result = { .sign = result_sign, .digits = result_digits };

    return result;
}


template<typename ArithmeticType>
    requires std::is_arithmetic_v<ArithmeticType>
class DigitsSubtractionIntegrationTest
    : public ::testing::TestWithParam<
          std::tuple<ArithmeticType, ArithmeticType>
      >
{
public:
    static auto
    make_test_params()
    {
        return ::testing::Combine(
            ::testing::ValuesIn(NONNEGATIVE_ARITHMETIC_VALUES<ArithmeticType>),
            ::testing::ValuesIn(NONNEGATIVE_ARITHMETIC_VALUES<ArithmeticType>)
        );
    }
}; // class DigitsSubtractionIntegrationTest


class DigitsSubtractionIntegralIntegrationTest
    : public DigitsSubtractionIntegrationTest<std::uintmax_t>
{}; // class DigitsSubtractionIntegralIntegrationTest

TEST_P(DigitsSubtractionIntegralIntegrationTest,
       DigitsMinusIntegralIsConsistentWithDigitsMinusDigits)
{
    std::uintmax_t lhs = std::get<0>(GetParam());
    std::uintmax_t rhs = std::get<1>(GetParam());
    auto lhs_digits = digits_from_integral(lhs);
    auto rhs_digits = digits_from_integral(rhs);
    Integer expected_result = subtract_from_digits(lhs_digits, rhs_digits);

    Integer actual_result = subtract_from_digits(lhs_digits, rhs);

    EXPECT_EQ(expected_result, actual_result);
}

TEST_P(DigitsSubtractionIntegralIntegrationTest,
       IntegralMinusDigitsIsConsistentWithDigitsMinusDigits)
{
    std::uintmax_t lhs = std::get<0>(GetParam());
    std::uintmax_t rhs = std::get<1>(GetParam());
    auto lhs_digits = digits_from_integral(lhs);
    auto rhs_digits = digits_from_integral(rhs);
    Integer expected_result = subtract_from_digits(lhs_digits, rhs_digits);

    Integer actual_result = subtract_from_arithmetic(lhs, rhs_digits);

    EXPECT_EQ(expected_result, actual_result);
}

INSTANTIATE_TEST_SUITE_P(
    DigitsSubtractionIntegrationTest,
    DigitsSubtractionIntegralIntegrationTest,
    DigitsSubtractionIntegralIntegrationTest::make_test_params()
);


class DigitsSubtractionFloatingPointIntegrationTest
    : public DigitsSubtractionIntegrationTest<long double>
{}; // class DigitsSubtractionFloatingPointIntegrationTest

TEST_P(DigitsSubtractionFloatingPointIntegrationTest,
       DigitsMinusTruncFloatingPointIsConsistentWithDigitsMinusDigits)
{
    long double lhs = std::trunc(std::get<0>(GetParam()));
    long double rhs = std::trunc(std::get<1>(GetParam()));
    auto lhs_digits = digits_from_floating_point(lhs);
    auto rhs_digits = digits_from_floating_point(rhs);
    Integer expected_result = subtract_from_digits(lhs_digits, rhs_digits);

    Integer actual_result = subtract_from_digits(lhs_digits, rhs);

    EXPECT_EQ(expected_result, actual_result);
}

TEST_P(DigitsSubtractionFloatingPointIntegrationTest,
       TruncFloatingPointMinusDigitsIsConsistentWithDigitsMinusDigits)
{
    long double lhs = std::trunc(std::get<0>(GetParam()));
    long double rhs = std::trunc(std::get<1>(GetParam()));
    auto lhs_digits = digits_from_floating_point(lhs);
    auto rhs_digits = digits_from_floating_point(rhs);
    Integer expected_result = subtract_from_digits(lhs_digits, rhs_digits);

    Integer actual_result = subtract_from_arithmetic(lhs, rhs_digits);

    EXPECT_EQ(expected_result, actual_result);
}

INSTANTIATE_TEST_SUITE_P(
    DigitsSubtractionIntegrationTest,
    DigitsSubtractionFloatingPointIntegrationTest,
    DigitsSubtractionFloatingPointIntegrationTest::make_test_params()
);

} // namespace
