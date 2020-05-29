#include "tasty_int/detail/digits_bitwise.hpp"

#include "gtest/gtest.h"

#include "tasty_int/detail/digit_from_nonnegative_value.hpp"


namespace {

using tasty_int::detail::multiply_digit_base;
using tasty_int::detail::DigitsShiftOffset;
using tasty_int::detail::operator<<;
using tasty_int::detail::operator<<=;
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

TEST(ShiftLeftInPlaceTest, ReturnsReferenceToDigits)
{
    std::vector<digit_type> digits = { 1, 2, 3 };

    EXPECT_EQ(&digits, &(digits <<= 11));
}

TEST(ShiftLeftInPlaceTest, ZeroWithZeroDigitOffset)
{
    std::vector<digit_type> digits          = { 0 };
    std::vector<digit_type>::size_type ZERO = 0;
    std::vector<digit_type> expected_result = digits;

    digits <<= ZERO;

    EXPECT_EQ(expected_result, digits);
}

TEST(ShiftLeftInPlaceTest, ZeroWithNonzeroDigitOffset)
{
    std::vector<digit_type> digits                  = { 0 };
    std::vector<digit_type>::size_type digit_offset = 7;
    std::vector<digit_type> expected_result         = digits;

    digits <<= digit_offset;

    EXPECT_EQ(expected_result, digits);
}

TEST(ShiftLeftInPlaceTest, NonzeroWithZeroDigitOffset)
{
    std::vector<digit_type> digits          = { 1, 2, 3 };
    std::vector<digit_type>::size_type ZERO = 0;
    std::vector<digit_type> expected_result = digits;

    digits <<= ZERO;

    EXPECT_EQ(expected_result, digits);
}

TEST(ShiftLeftInPlaceTest, NonzeroWithNonzeroDigitOffset)
{
    std::vector<digit_type> digits                  = { 1, 2, 3 };
    std::vector<digit_type>::size_type digit_offset = 5;
    std::vector<digit_type> expected_result = { 0, 0, 0, 0, 0, 1, 2, 3 };

    digits <<= digit_offset;

    EXPECT_EQ(expected_result, digits);
}

TEST(ShiftLeftTest, Zero)
{
    std::vector<digit_type> digits          = { 0 };
    DigitsShiftOffset offset                = { .digits = 7, .bits = 11 };
    std::vector<digit_type> expected_result = digits;

    auto result = digits << offset;

    EXPECT_EQ(expected_result, result);
}

TEST(ShiftLeftTest, NoOffset)
{
    std::vector<digit_type> digits          = { DIGIT_TYPE_MAX };
    DigitsShiftOffset offset                = { .digits = 0, .bits = 0 };
    std::vector<digit_type> expected_result = digits;

    auto result = digits << offset;

    EXPECT_EQ(expected_result, result);
}

TEST(ShiftLeftTest, DigitsOffset)
{
    std::vector<digit_type> digits = { DIGIT_TYPE_MAX, DIGIT_TYPE_MAX };
    DigitsShiftOffset offset       = { .digits = 3, .bits = 0 };
    std::vector<digit_type> expected_result = {
        0, 0, 0, DIGIT_TYPE_MAX, DIGIT_TYPE_MAX
    };

    auto result = digits << offset;

    EXPECT_EQ(expected_result, result);
}

TEST(ShiftLeftTest, BitsOffsetWithoutOverlap)
{
    std::vector<digit_type> digits          = { 0, 1, 2 };
    DigitsShiftOffset offset                = { .digits = 0, .bits = 5 };
    std::vector<digit_type> expected_result = { 0, 1 << 5, 2 << 5 };

    auto result = digits << offset;

    EXPECT_EQ(expected_result, result);
}

TEST(ShiftLeftTest, BitsOffsetWithOverlap)
{
    std::vector<digit_type> digits = {
        DIGIT_TYPE_MAX / 2, DIGIT_TYPE_MAX / 4, 0b010101, 1
    };
    DigitsShiftOffset offset = { .digits  = 0, .bits = 4 };
    std::vector<digit_type> expected_result = { 
        DIGIT_TYPE_MAX ^ 0b1111, // 4 lsb zeros
        DIGIT_TYPE_MAX ^ 0b1000, // 1 zero at bit position 3
        0b0101010011,
        1 << 4
    };

    auto result = digits << offset;

    EXPECT_EQ(expected_result, result);
}

TEST(ShiftLeftTest, DigitsAndBitsOffsetWithoutOverlap)
{
    std::vector<digit_type> digits = { 1, 2, 3, 4 };
    DigitsShiftOffset offset       = { .digits  = 4, .bits = 7 };
    std::vector<digit_type> expected_result = {
        0, 0, 0, 0, 1 << 7, 2 << 7, 3 << 7, 4 << 7
    };

    auto result = digits << offset;

    EXPECT_EQ(expected_result, result);
}

TEST(ShiftLeftTest, DigitsAndBitsOffsetWithOverlap)
{
    std::vector<digit_type> digits = {
        DIGIT_TYPE_MAX >> 1,
        DIGIT_TYPE_MAX >> 2,
        0,
        DIGIT_TYPE_MAX >> 3,
        DIGIT_TYPE_MAX >> 4
    };
    DigitsShiftOffset offset = { .digits = 2, .bits = 5 };
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

    auto result = digits << offset;

    EXPECT_EQ(expected_result, result);
}

} // namespace
