#include "tasty_int/detail/digits_bitwise.hpp"

#include "gtest/gtest.h"

#include "tasty_int/detail/digit_from_nonnegative_value.hpp"


namespace {

using tasty_int::detail::multiply_digit_base;
using tasty_int::detail::multiply_digit_base_power_in_place;
using tasty_int::detail::MultiplierExponents;
using tasty_int::detail::multiply_powers;
using tasty_int::detail::digit_type;
using tasty_int::detail::DIGIT_TYPE_MAX;
using tasty_int::detail::digit_from_nonnegative_value;


TEST(MultiplyDigitBaseTest, SingleDigit)
{
    std::vector<digit_type> multiplicand    = { 1 };
    std::vector<digit_type> expected_result = { 0, 1 };

    auto result = multiply_digit_base(multiplicand);

    EXPECT_EQ(expected_result, result);
}

TEST(MultiplyDigitBaseTest, MutlipleDigits)
{
    std::vector<digit_type> multiplicand    = { 1, 2, 3, 4 };
    std::vector<digit_type> expected_result = { 0, 1, 2, 3, 4 };

    auto result = multiply_digit_base(multiplicand);

    EXPECT_EQ(expected_result, result);
}

TEST(MultiplyDigitBasePowerTest, ZeroWithZeroExponent)
{
    std::vector<digit_type> multiplicand = { 0 };
    std::vector<digit_type>::size_type ZERO = 0;
    std::vector<digit_type> expected_result = multiplicand;

    multiply_digit_base_power_in_place(ZERO, multiplicand);

    EXPECT_EQ(expected_result, multiplicand);
}

TEST(MultiplyDigitBasePowerTest, ZeroWithNonzeroExponent)
{
    std::vector<digit_type> multiplicand = { 0 };
    std::vector<digit_type>::size_type exponent = 7;
    std::vector<digit_type> expected_result = multiplicand;

    multiply_digit_base_power_in_place(exponent, multiplicand);

    EXPECT_EQ(expected_result, multiplicand);
}

TEST(MultiplyDigitBasePowerTest, NonzeroWithZeroExponent)
{
    std::vector<digit_type> multiplicand = { 1, 2, 3 };
    std::vector<digit_type>::size_type ZERO = 0;
    std::vector<digit_type> expected_result = multiplicand;

    multiply_digit_base_power_in_place(ZERO, multiplicand);

    EXPECT_EQ(expected_result, multiplicand);
}

TEST(MultiplyDigitBasePowerTest, NonzeroWithNonzeroExponent)
{
    std::vector<digit_type> multiplicand = { 1, 2, 3 };
    std::vector<digit_type>::size_type exponent = 5;
    std::vector<digit_type> expected_result = { 0, 0, 0, 0, 0, 1, 2, 3 };

    multiply_digit_base_power_in_place(exponent, multiplicand);

    EXPECT_EQ(expected_result, multiplicand);
}

TEST(MultiplyPowersTest, NoExponents)
{
    std::vector<digit_type> multiplicand    = { DIGIT_TYPE_MAX };
    MultiplierExponents exponents           = { .digit_base = 0, .two = 0 };
    std::vector<digit_type> expected_result = multiplicand;

    auto result = multiply_powers(multiplicand, exponents);

    EXPECT_EQ(expected_result, result);
}

TEST(MultiplyPowersTest, OnlyDigitBaseExponent)
{
    std::vector<digit_type> multiplicand = { DIGIT_TYPE_MAX, DIGIT_TYPE_MAX };
    MultiplierExponents exponents        = { .digit_base = 3, .two = 0 };
    std::vector<digit_type> expected_result = {
        0, 0, 0, DIGIT_TYPE_MAX, DIGIT_TYPE_MAX
    };

    auto result = multiply_powers(multiplicand, exponents);

    EXPECT_EQ(expected_result, result);
}

TEST(MultiplyPowersTest, OnlyTwoExponentNoOverlap)
{
    std::vector<digit_type> multiplicand    = { 0, 1, 2 };
    MultiplierExponents exponents           = { .digit_base = 0, .two = 5 };
    std::vector<digit_type> expected_result = { 0, 1 << 5, 2 << 5 };

    auto result = multiply_powers(multiplicand, exponents);

    EXPECT_EQ(expected_result, result);
}

TEST(MultiplyPowersTest, OnlyTwoExponentWithOverlap)
{
    std::vector<digit_type> multiplicand = {
        DIGIT_TYPE_MAX / 2, DIGIT_TYPE_MAX / 4, 0b010101, 1
    };
    MultiplierExponents exponents = { .digit_base  = 0, .two = 4 };
    std::vector<digit_type> expected_result = { 
        DIGIT_TYPE_MAX ^ 0b1111, // 4 lsb zeros
        DIGIT_TYPE_MAX ^ 0b1000, // 1 zero at bit position 3
        0b0101010011,
        1 << 4
    };

    auto result = multiply_powers(multiplicand, exponents);

    EXPECT_EQ(expected_result, result);
}

TEST(MultiplyPowersTest, DigitBaseAndTwoExponentsNoOverlap)
{
    std::vector<digit_type> multiplicand    = { 1, 2, 3, 4 };
    MultiplierExponents exponents           = { .digit_base  = 4, .two = 7 };
    std::vector<digit_type> expected_result = {
        0, 0, 0, 0, 1 << 7, 2 << 7, 3 << 7, 4 << 7
    };

    auto result = multiply_powers(multiplicand, exponents);

    EXPECT_EQ(expected_result, result);
}

TEST(MultiplyPowersTest, DigitBaseAndTwoExponentsWithOverlap)
{
    std::vector<digit_type> multiplicand = {
        DIGIT_TYPE_MAX >> 1,
        DIGIT_TYPE_MAX >> 2,
        0,
        DIGIT_TYPE_MAX >> 3,
        DIGIT_TYPE_MAX >> 4
    };
    MultiplierExponents exponents = { .digit_base = 2, .two = 5 };
    std::vector<digit_type> expected_result = {
        0,
        0,
        digit_from_nonnegative_value(DIGIT_TYPE_MAX << 5),
        digit_from_nonnegative_value((DIGIT_TYPE_MAX << 5) | 0b1111),
        0b111,
        digit_from_nonnegative_value(DIGIT_TYPE_MAX << 5),
        digit_from_nonnegative_value((DIGIT_TYPE_MAX << 5) |   0b11),
        1
    };

    auto result = multiply_powers(multiplicand, exponents);

    EXPECT_EQ(expected_result, result);
}

} // namespace
