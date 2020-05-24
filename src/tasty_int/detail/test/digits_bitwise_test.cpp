#include "tasty_int/detail/digits_bitwise.hpp"

#include "gtest/gtest.h"

#include "tasty_int/detail/digit_from_nonnegative_value.hpp"


namespace {

using tasty_int::detail::DigitsShiftOffset;
using tasty_int::detail::count_leading_zero_bits_from_digit;
using tasty_int::detail::operator<<;
using tasty_int::detail::operator<<=;
using tasty_int::detail::digit_type;
using tasty_int::detail::DIGIT_TYPE_MAX;
using tasty_int::detail::DIGIT_TYPE_BITS;
using tasty_int::detail::digit_from_nonnegative_value;


class CountLeadingZeroBitsFromDigitTest : public ::testing::TestWithParam<int>
{
public:
    static constexpr int MAX_EXPONENT = DIGIT_TYPE_BITS - 1;
}; // class CountLeadingZeroBitsFromDigitTest

TEST_P(CountLeadingZeroBitsFromDigitTest, DenseBitPatternTest)
{
    auto shift          = GetParam();
    auto value          = DIGIT_TYPE_MAX >> shift;
    auto expected_count = shift;

    EXPECT_EQ(expected_count, count_leading_zero_bits_from_digit(value));
}

TEST_P(CountLeadingZeroBitsFromDigitTest, SingleBitTest)
{
    auto shift          = GetParam();
    auto value          = digit_type(1) << shift;
    auto expected_count = MAX_EXPONENT - shift;

    EXPECT_EQ(expected_count, count_leading_zero_bits_from_digit(value));
}

INSTANTIATE_TEST_SUITE_P(
    CountLeadingZeroBitsFromDigitTest,
    CountLeadingZeroBitsFromDigitTest,
    ::testing::Range(0, CountLeadingZeroBitsFromDigitTest::MAX_EXPONENT)
);

TEST(LeftShiftDigitOffsetInPlaceTest, ReturnsReferenceToDigits)
{
    std::vector<digit_type> digits = { 1, 2, 3 };

    EXPECT_EQ(&digits, &(digits <<= 11));
}

TEST(LeftShiftDigitOffsetInPlaceTest, ZeroWithZeroDigitOffset)
{
    std::vector<digit_type> digits          = { 0 };
    std::vector<digit_type>::size_type ZERO = 0;
    std::vector<digit_type> expected_result = digits;

    digits <<= ZERO;

    EXPECT_EQ(expected_result, digits);
}

TEST(LeftShiftDigitOffsetInPlaceTest, ZeroWithNonzeroDigitOffset)
{
    std::vector<digit_type> digits                  = { 0 };
    std::vector<digit_type>::size_type digit_offset = 7;
    std::vector<digit_type> expected_result         = digits;

    digits <<= digit_offset;

    EXPECT_EQ(expected_result, digits);
}

TEST(LeftShiftDigitOffsetInPlaceTest, NonzeroWithZeroDigitOffset)
{
    std::vector<digit_type> digits          = { 1, 2, 3 };
    std::vector<digit_type>::size_type ZERO = 0;
    std::vector<digit_type> expected_result = digits;

    digits <<= ZERO;

    EXPECT_EQ(expected_result, digits);
}

TEST(LeftShiftDigitOffsetInPlaceTest, NonzeroWithNonzeroDigitOffset)
{
    std::vector<digit_type> digits                  = { 1, 2, 3 };
    std::vector<digit_type>::size_type digit_offset = 5;
    std::vector<digit_type> expected_result = { 0, 0, 0, 0, 0, 1, 2, 3 };

    digits <<= digit_offset;

    EXPECT_EQ(expected_result, digits);
}

TEST(LeftShiftDigitsShiftOffsetInPlaceTest, Zero)
{
    std::vector<digit_type> digits          = { 0 };
    DigitsShiftOffset offset                = { .digits = 7, .bits = 11 };
    std::vector<digit_type> expected_result = digits;

    auto result = digits << offset;

    EXPECT_EQ(expected_result, result);
}

TEST(LeftShiftDigitsShiftOffsetInPlaceTest, NoOffset)
{
    std::vector<digit_type> digits          = { DIGIT_TYPE_MAX };
    DigitsShiftOffset offset                = { .digits = 0, .bits = 0 };
    std::vector<digit_type> expected_result = digits;

    auto result = digits << offset;

    EXPECT_EQ(expected_result, result);
}

TEST(LeftShiftDigitsShiftOffsetInPlaceTest, DigitsOffset)
{
    std::vector<digit_type> digits = { DIGIT_TYPE_MAX, DIGIT_TYPE_MAX };
    DigitsShiftOffset offset       = { .digits = 3, .bits = 0 };
    std::vector<digit_type> expected_result = {
        0, 0, 0, DIGIT_TYPE_MAX, DIGIT_TYPE_MAX
    };

    auto result = digits << offset;

    EXPECT_EQ(expected_result, result);
}

TEST(LeftShiftDigitsShiftOffsetInPlaceTest, BitsOffsetNoOverlap)
{
    std::vector<digit_type> digits          = { 0, 1, 2 };
    DigitsShiftOffset offset                = { .digits = 0, .bits = 5 };
    std::vector<digit_type> expected_result = { 0, 1 << 5, 2 << 5 };

    auto result = digits << offset;

    EXPECT_EQ(expected_result, result);
}

TEST(LeftShiftDigitsShiftOffsetInPlaceTest, BitsOffsetWithOverlap)
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

TEST(LeftShiftDigitsShiftOffsetInPlaceTest, DigitsAndBitsOffsetNoOverlap)
{
    std::vector<digit_type> digits = { 1, 2, 3, 4 };
    DigitsShiftOffset offset       = { .digits  = 4, .bits = 7 };
    std::vector<digit_type> expected_result = {
        0, 0, 0, 0, 1 << 7, 2 << 7, 3 << 7, 4 << 7
    };

    auto result = digits << offset;

    EXPECT_EQ(expected_result, result);
}

TEST(LeftShiftDigitsShiftOffsetInPlaceTest, DigitsAndBitsOffsetWithOverlap)
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

TEST(RightShiftDigitsShiftOffsetInPlaceTest, ReturnsReferenceToDigits)
{
    std::vector<digit_type> digits = { 1, 2, 3 };
    DigitsShiftOffset offset       = { .digits = 1, .bits = 3 };

    EXPECT_EQ(&digits, &(digits >>= offset));
}

TEST(RightShiftDigitsShiftOffsetInPlaceTest, Zero)
{
    std::vector<digit_type> digits          = { 0 };
    DigitsShiftOffset offset                = { .digits = 33, .bits = 1 };
    std::vector<digit_type> expected_result = digits;

    digits >>= offset;

    EXPECT_EQ(expected_result, digits);
}

TEST(RightShiftDigitsShiftOffsetInPlaceTest, NoOffset)
{
    std::vector<digit_type> digits          = { DIGIT_TYPE_MAX };
    DigitsShiftOffset offset                = { .digits = 0, .bits = 0 };
    std::vector<digit_type> expected_result = digits;

    digits >>= offset;

    EXPECT_EQ(expected_result, digits);
}

TEST(RightShiftDigitsShiftOffsetInPlaceTest, DigitsOffsetWithUnderflow)
{
    std::vector<digit_type> digits          = { 1, 2, 3, 4, 5 };
    DigitsShiftOffset offset                = { .digits = 5, .bits = 0 };
    std::vector<digit_type> expected_result = { 0 };

    digits >>= offset;

    EXPECT_EQ(expected_result, digits);
}

TEST(RightShiftDigitsShiftOffsetInPlaceTest, DigitsOffset)
{
    std::vector<digit_type> digits          = { 1, 2, 3, 4, 5 };
    DigitsShiftOffset offset                = { .digits = 2, .bits = 0 };
    std::vector<digit_type> expected_result = { 3, 4, 5 };

    digits >>= offset;

    EXPECT_EQ(expected_result, digits);
}

TEST(RightShiftDigitsShiftOffsetInPlaceTest, BitsOffsetWithUnderflow)
{
    std::vector<digit_type> digits = { 7 };
    DigitsShiftOffset offset       = { .digits = 0, .bits = DIGIT_TYPE_BITS };
    std::vector<digit_type> expected_result = { 0 };

    digits >>= offset;

    EXPECT_EQ(expected_result, digits);
}

TEST(RightShiftDigitsShiftOffsetInPlaceTest, BitsOffsetToZero)
{
    std::vector<digit_type> digits = { DIGIT_TYPE_MAX };
    DigitsShiftOffset offset       = { .digits = 0, .bits = DIGIT_TYPE_BITS };
    std::vector<digit_type> expected_result = { 0 };

    digits >>= offset;

    EXPECT_EQ(expected_result, digits);
}

TEST(RightShiftDigitsShiftOffsetInPlaceTest, BitsOffsetNoOverlap)
{
    std::vector<digit_type> digits = { 2, 2, 2, 2, 2 };
    DigitsShiftOffset offset       = { .digits = 0, .bits = 1 };
    std::vector<digit_type> expected_result = { 1, 1, 1, 1, 1 };

    digits >>= offset;

    EXPECT_EQ(expected_result, digits);
}

TEST(RightShiftDigitsShiftOffsetInPlaceTest, BitsOffsetWithOverlap)
{
    std::vector<digit_type> digits = { 1, DIGIT_TYPE_MAX, 2 };
    DigitsShiftOffset offset       = { .digits = 0, .bits = 5 };
    std::vector<digit_type> expected_result = {
        digit_from_nonnegative_value(
            DIGIT_TYPE_MAX << (DIGIT_TYPE_BITS - 5)
        ),
        digit_from_nonnegative_value(
            (DIGIT_TYPE_MAX >> 5) | (2 << (DIGIT_TYPE_BITS - 5))
        )
    };

    digits >>= offset;

    EXPECT_EQ(expected_result, digits);
}

TEST(RightShiftDigitsShiftOffsetInPlaceTest, DigitsAndBitsOffsetNoOverlap)
{
    std::vector<digit_type> digits          = { 1, 2, 4, 8, 16 };
    DigitsShiftOffset offset                = { .digits = 2, .bits = 2 };
    std::vector<digit_type> expected_result = { 1, 2, 4 };

    digits >>= offset;

    EXPECT_EQ(expected_result, digits);
}

TEST(RightShiftDigitsShiftOffsetInPlaceTest, DigitsAndBitsOffsetWithOverlap)
{
    std::vector<digit_type> digits = { 0, DIGIT_TYPE_MAX, 16, DIGIT_TYPE_MAX };
    DigitsShiftOffset offset       = { .digits = 2, .bits = 3 };
    std::vector<digit_type> expected_result = {
        digit_from_nonnegative_value(
            (16 >> 3) | (DIGIT_TYPE_MAX << (DIGIT_TYPE_BITS - 3))
        ),
        digit_from_nonnegative_value(
            DIGIT_TYPE_MAX >> 3
        )
    };

    digits >>= offset;

    EXPECT_EQ(expected_result, digits);
}

TEST(RightShiftDigitsShiftOffsetInPlaceTest, DigitsAndBitsOffsetToZero)
{
    std::vector<digit_type> digits = { 0, 1 };
    DigitsShiftOffset offset       = { .digits = 1, .bits = 1 };
    std::vector<digit_type> expected_result = { 0 };

    digits >>= offset;

    EXPECT_EQ(expected_result, digits);
}

} // namespace
