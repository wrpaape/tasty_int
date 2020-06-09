#include "tasty_int/detail/sign.hpp"

#include "gtest/gtest.h"

#include "tasty_int/detail/test/sign_test_common.hpp"


namespace {

using tasty_int::detail::Sign;


TEST(SignTest, UnaryMinusFlipsPositiveToNegative)
{
    EXPECT_EQ(Sign::NEGATIVE, -Sign::POSITIVE);
}

TEST(SignTest, UnaryMinusFlipsNegativeToPositive)
{
    EXPECT_EQ(Sign::POSITIVE, -Sign::NEGATIVE);
}

TEST(SignTest, UnaryMinusFlipsZeroToZero)
{
    EXPECT_EQ(Sign::ZERO, -Sign::ZERO);
}


void
check_multiply_in_place_result(Sign  expected_result,
                               Sign &multiplicand,
                               Sign &result)
{
    EXPECT_EQ(&multiplicand, &result)
        << "*= did not return reference to multiplicand";

    EXPECT_EQ(expected_result, multiplicand)
        << "*= did not produce the expected result";

}

void
test_multiply_in_place(Sign multiplicand,
                       Sign multiplier,
                       Sign expected_result)
{
    auto &&result = multiplicand *= multiplier;

    check_multiply_in_place_result(expected_result, multiplicand, result);
}

void
test_multiply(Sign lhs,
              Sign rhs,
              Sign expected_result)
{
    auto result = lhs * rhs;

    EXPECT_EQ(expected_result, result)
        << "* did not produce the expected result";
}

void
test_multiplication(Sign multiplicand,
                    Sign multiplier,
                    Sign expected_result)
{
    test_multiply_in_place(multiplicand, multiplier, expected_result);

    test_multiply(multiplicand, multiplier, expected_result);
}

TEST(SignTest, MultiplyZeroAndZero)
{
    test_multiplication(Sign::ZERO, Sign::ZERO, Sign::ZERO);
}

TEST(SignTest, MultiplyZeroAndPositive)
{
    test_multiplication(Sign::ZERO, Sign::POSITIVE, Sign::ZERO);
}

TEST(SignTest, MultiplyZeroAndNegative)
{
    test_multiplication(Sign::ZERO, Sign::NEGATIVE, Sign::ZERO);
}

TEST(SignTest, MultiplyPositiveAndZero)
{
    test_multiplication(Sign::POSITIVE, Sign::ZERO, Sign::ZERO);
}

TEST(SignTest, MultiplyPositiveAndPositive)
{
    test_multiplication(Sign::POSITIVE, Sign::POSITIVE, Sign::POSITIVE);
}

TEST(SignTest, MultiplyPositiveAndNegative)
{
    test_multiplication(Sign::POSITIVE, Sign::NEGATIVE, Sign::NEGATIVE);
}

TEST(SignTest, MultiplyNegativeAndZero)
{
    test_multiplication(Sign::NEGATIVE, Sign::ZERO, Sign::ZERO);
}

TEST(SignTest, MultiplyNegativeAndPositive)
{
    test_multiplication(Sign::NEGATIVE, Sign::POSITIVE, Sign::NEGATIVE);
}

TEST(SignTest, MultiplyNegativeAndNegative)
{
    test_multiplication(Sign::NEGATIVE, Sign::NEGATIVE, Sign::POSITIVE);
}

} // namespace
