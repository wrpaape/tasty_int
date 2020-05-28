#include "tasty_int/detail/digits_division.hpp"

#include <type_traits>
#include <utility>

#include "gtest/gtest.h"

#include "tasty_int/detail/digits_addition.hpp"
#include "tasty_int/detail/digits_multiplication.hpp"


namespace {

using tasty_int::detail::divide;
using tasty_int::detail::divide_in_place;
using tasty_int::detail::divide_normalized_3n_2n_split;
using tasty_int::detail::divide_normalized_2n_1n_split;
using tasty_int::detail::DigitsDivisionResult;
using tasty_int::detail::digit_type;
using tasty_int::detail::DIGIT_TYPE_MAX;
using tasty_int::detail::DIGIT_TYPE_BITS;
using tasty_int::detail::DIGIT_BASE;
using tasty_int::detail::operator+;
using tasty_int::detail::operator*;


void
expect_equal(const DigitsDivisionResult    &expected_result,
             const std::vector<digit_type> &quotient,
             const std::vector<digit_type> &remainder)
{
    EXPECT_EQ(expected_result.quotient, quotient);

    EXPECT_EQ(expected_result.remainder, remainder);
}

void
expect_equal(const DigitsDivisionResult &expected_result,
             const DigitsDivisionResult &actual_result)
{
    expect_equal(expected_result,
                 actual_result.quotient,
                 actual_result.remainder);
}


template<typename DivisorType>
void
test_divide_in_place(const std::vector<digit_type> &dividend,
                     const DivisorType             &divisor,
                     const DigitsDivisionResult    &expected_result)
{
    std::vector<digit_type> result_digits = dividend;

    auto remainder = divide_in_place(divisor, result_digits);

    expect_equal(expected_result, result_digits, remainder);
}

template<typename DividendType, typename DivisorType>
void
test_divide(const DividendType         &dividend,
            const DivisorType          &divisor,
            const DigitsDivisionResult &expected_result)
{
    auto result = divide(dividend, divisor);

    expect_equal(expected_result, result);
}

template<typename DividendType, typename DivisorType>
void
test_division(const DividendType         &dividend,
              const DivisorType          &divisor,
              const DigitsDivisionResult &expected_result)
{
    if constexpr (std::is_same_v<DividendType, std::vector<digit_type>>)
        test_divide_in_place(dividend, divisor, expected_result);

    test_divide(dividend, divisor, expected_result);
}


class DigitsDivisionIdentitiesTest
    : public ::testing::TestWithParam<std::vector<digit_type>>
{}; // class DigitsDivisionIdentitiesTest

TEST_P(DigitsDivisionIdentitiesTest, DigitsDividedByIdenticalDigitsValue)
{
    std::vector<digit_type> dividend = GetParam();
    std::vector<digit_type> divisor  = dividend;
    DigitsDivisionResult expected_result = {
        .quotient = { 1 }, .remainder = { 0 }
    };

    test_division(dividend, divisor, expected_result);
}

TEST_P(DigitsDivisionIdentitiesTest, DigitsSquaredDividedByOriginalDigitsValue)
{
    std::vector<digit_type> divisor  = GetParam();
    std::vector<digit_type> dividend = divisor * divisor;
    DigitsDivisionResult expected_result = {
        .quotient = divisor, .remainder = { 0 }
    };

    test_division(dividend, divisor, expected_result);
}

TEST_P(DigitsDivisionIdentitiesTest, DigitsDividedByGreaterDigitsValue)
{
    std::vector<digit_type> dividend = GetParam();
    std::vector<digit_type> divisor  = dividend + std::uintmax_t(1);
    DigitsDivisionResult expected_result = {
        .quotient = { 0 }, .remainder = dividend
    };

    test_division(dividend, divisor, expected_result);
}

INSTANTIATE_TEST_SUITE_P(
    DigitsDivisionTest,
    DigitsDivisionIdentitiesTest,
    ::testing::ValuesIn(
        std::vector<std::vector<digit_type>> {
            { 1 },
            { 2 },
            { DIGIT_TYPE_MAX },
            { 0, 1 },
            { 1, 1 },
            { 2, 1 },
            { 0, DIGIT_TYPE_MAX },
            { 1, DIGIT_TYPE_MAX },
            { 2, DIGIT_TYPE_MAX },
            { DIGIT_TYPE_MAX, 1 },
            { DIGIT_TYPE_MAX, 2 },
            { DIGIT_TYPE_MAX, DIGIT_TYPE_MAX },
            { 0, 0, 1 },
            { 1, 2, 3, 4, 5, 6, 7, 8, 9, 8, 7, 6, 5, 4, 3, 2, 1 },
            { DIGIT_TYPE_MAX , DIGIT_TYPE_MAX, DIGIT_TYPE_MAX },
        }
    )
);


TEST(DivideNormalized3n2nSplitTest, DividendHighEqualToDivisorHighTest)
{
    std::vector<digit_type> dividend = {
        0, 0, DIGIT_TYPE_MAX
    };
    std::vector<digit_type> divisor = {
        DIGIT_TYPE_MAX, DIGIT_TYPE_MAX
    };
    DigitsDivisionResult expected_result = {
        .quotient = { DIGIT_TYPE_MAX }, .remainder = { DIGIT_TYPE_MAX }
    };

    auto result = divide_normalized_3n_2n_split(dividend, divisor);

    expect_equal(expected_result, result);
}

TEST(DivideNormalized3n2nSplitTest, DividendHighGreaterThanDivisorHighTest)
{
    std::vector<digit_type> dividend = {
        DIGIT_TYPE_MAX, DIGIT_TYPE_MAX,
        DIGIT_TYPE_MAX, DIGIT_TYPE_MAX,
        0,              (DIGIT_BASE / 2) + 1
    };
    std::vector<digit_type> divisor = {
        0, 0, 1, (DIGIT_BASE / 2) + 1
    };
    DigitsDivisionResult expected_result = {
        .quotient  = { DIGIT_TYPE_MAX, DIGIT_TYPE_MAX },
        .remainder = { DIGIT_TYPE_MAX, DIGIT_TYPE_MAX, 0, (DIGIT_BASE / 2) + 1 }
    };

    auto result = divide_normalized_3n_2n_split(dividend, divisor);

    expect_equal(expected_result, result);
}

TEST(DivideNormalized2n1nSplitTest, FourDigitDiviend)
{
    std::vector<digit_type> dividend = {
        0, 0, 0, 1
    };
    std::vector<digit_type> divisor = {
        0, digit_type(1) << (DIGIT_TYPE_BITS - 1)
    };
    DigitsDivisionResult expected_result = {
        .quotient = { 0, 2 }, .remainder = { 0 }
    };

    auto result = divide_normalized_2n_1n_split(dividend, divisor);

    expect_equal(expected_result, result);
}

TEST(DivideNormalized2n1nSplitTest, SixDigitDiviend)
{
    std::vector<digit_type> dividend = {
        1, DIGIT_TYPE_MAX,
        2, DIGIT_TYPE_MAX,
        3, DIGIT_TYPE_MAX
    };
    std::vector<digit_type> divisor = {
        4, 0, DIGIT_TYPE_MAX
    };
    DigitsDivisionResult expected_result = {
        .quotient  = { DIGIT_TYPE_MAX, 3, 0, 1 },
        .remainder = { 5, DIGIT_TYPE_MAX - 16, 1 }
    };

    auto result = divide_normalized_2n_1n_split(dividend, divisor);

    expect_equal(expected_result, result);
}

} // namespace
