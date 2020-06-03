#include "tasty_int/detail/integer.hpp"

#include "gtest/gtest.h"

#include "tasty_int/detail/conversions/integer_from_string.hpp"
#include "tasty_int/detail/test/integer_test_common.hpp"

namespace {

using tasty_int::detail::Integer;
using tasty_int::detail::Sign;
using tasty_int::detail::conversions::integer_from_string;


TEST(IntegerMultiplicationTest, TODO)
{
    SUCCEED();
}

// TEST(DigitsAndFloatingPointMultiplicationTest, SingleDigitTimesFraction)
// {
//     std::vector<digit_type> digit           = { 10 };
//     long double floating_point              = 0.2;
//     std::vector<digit_type> expected_result = { 5 };

//     test_multiplication(digit, floating_point, expected_result);
// }

// TEST(DigitsAndFloatingPointMultiplicationTest, MultipleDigitsTimesFraction)
// {
//     std::vector<digit_type> digits          = { DIGIT_TYPE_MAX, DIGIT_TYPE_MAX };
//     long double floating_point              = 1.0L / DIGIT_BASE;;
//     std::vector<digit_type> expected_result = { DIGIT_TYPE_MAX };

//     test_multiplication(digits, floating_point, expected_result);
// }

} // namespace
