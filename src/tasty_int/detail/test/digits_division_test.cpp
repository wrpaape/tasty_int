#include "tasty_int/detail/digits_division.hpp"

#include <cmath>

#include <type_traits>
#include <utility>

#include "gtest/gtest.h"

#include "tasty_int/detail/digits_addition.hpp"
#include "tasty_int/detail/digits_multiplication.hpp"
#include "tasty_int/detail/conversions/digits_from_integral.hpp"
#include "tasty_int/detail/conversions/digits_from_floating_point.hpp"
#include "tasty_int_test/logarithmic_range.hpp"


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
using tasty_int::detail::conversions::digits_from_integral;
using tasty_int::detail::conversions::digits_from_floating_point;


std::vector<digit_type>
digit_base_power(std::vector<digit_type>::size_type exponent)
{
    std::vector<digit_type> power(exponent + 1);
    power.back() = 1;
    return power;
}

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

const std::vector<std::vector<digit_type>> SAMPLE_DIVIDENDS = {
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
    { 0, 0, 0, 1 },
    { 1, 2, 3, 4, 5, 6, 7, 8, 9, 8, 7, 6, 5, 4, 3, 2, 1 },
    { DIGIT_TYPE_MAX, DIGIT_TYPE_MAX, DIGIT_TYPE_MAX },
    std::vector<digit_type>(100, 6),
    { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 },
    digit_base_power(99),
    std::vector<digit_type>(7, 19),
    std::vector<digit_type>(250, DIGIT_TYPE_MAX)
};


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
    ::testing::ValuesIn(SAMPLE_DIVIDENDS)
);


struct DigitsDivisionArbitraryValuesTestParam
{
    std::vector<digit_type> dividend;
    std::vector<digit_type> divisor;
    DigitsDivisionResult    expected_result;
}; // DigitsDivisionArbitraryValuesTestParam

class DigitsDivisionArbitraryValuesTest
    : public ::testing::TestWithParam<DigitsDivisionArbitraryValuesTestParam>
{}; // class DigitsDivisionArbitraryValuesTest

TEST_P(DigitsDivisionArbitraryValuesTest, DigitsDividedByArbitraryDigitsValue)
{
    auto dividend        = GetParam().dividend;
    auto divisor         = GetParam().divisor;
    auto expected_result = GetParam().expected_result;

    test_division(dividend, divisor, expected_result);
}

INSTANTIATE_TEST_SUITE_P(
    DigitsDivisionTest,
    DigitsDivisionArbitraryValuesTest,
    ::testing::ValuesIn(
        std::vector<DigitsDivisionArbitraryValuesTestParam> {
            {
                .dividend        = { 0 },
                .divisor         = { 1 },
                .expected_result = {
                    .quotient  = { 0 },
                    .remainder = { 0 }
                }
            },
            {
                .dividend        = { 1,              DIGIT_TYPE_MAX },
                .divisor         = { DIGIT_TYPE_MAX, 1 },
                .expected_result = {
                    .quotient  = { DIGIT_TYPE_MAX / 2 },
                    .remainder = { DIGIT_BASE / 2, 1 }
                }
            },
            {
                .dividend        = { 0 },
                .divisor         = std::vector<digit_type>(20, DIGIT_TYPE_MAX),
                .expected_result = {
                    .quotient  = { 0 },
                    .remainder = { 0 }
                }
            },
            {
                .dividend        = {
                    1,   2,  3,  4,  5,
                    6,   7,  8,  9, 10,
                    11, 12, 13, 14, 15,
                    16, 17, 18, 19, 20,
                    21, 22, 23, 24, 25
                },
                .divisor         = {
                    15, 14, 13, 12, 11,
                    10,  9,  8,  7,  6,
                     5,  4,  3,  2,  1
                },
                .expected_result = {
                    .quotient  = {
                        0, 0, 0, 0, 0, 0, 0, 0, 0, DIGIT_TYPE_MAX - 25, 24
                    },
                    .remainder = {
                        1, 2, 3, 4, 5, 6, 7, 8, 9, 400
                    }
                }
            },
            {
                .dividend        = std::vector<digit_type>(999, DIGIT_TYPE_MAX),
                .divisor         = std::vector<digit_type>(777, DIGIT_TYPE_MAX),
                .expected_result =  {
                    .quotient  = digit_base_power(222),
                    .remainder = std::vector<digit_type>(222, DIGIT_TYPE_MAX)
                }
            },
            {
                .dividend        = digit_base_power(333) + std::uintmax_t(1),
                .divisor         = digit_base_power(150),
                .expected_result = {
                    .quotient  = digit_base_power(183),
                    .remainder = { 1 }
                }
            },
            {
                .dividend        = digit_base_power(999) + std::uintmax_t(12),
                .divisor         = digit_base_power(2),
                .expected_result = {
                    .quotient  = digit_base_power(997),
                    .remainder = { 12 }
                }
            },
            {
                .dividend        = std::vector<digit_type>(254, DIGIT_TYPE_MAX),
                .divisor         = std::vector<digit_type>(62,  DIGIT_TYPE_MAX),
                .expected_result = {
                    .quotient  = digit_base_power(192)
                               + digit_base_power(130)
                               + digit_base_power( 68)
                               + digit_base_power(  6),
                    .remainder = std::vector<digit_type>(6, DIGIT_TYPE_MAX)
                }
            },
            {
                .dividend        = digit_base_power(1022),
                .divisor         = digit_base_power(126),
                .expected_result = {
                    .quotient  = digit_base_power(896),
                    .remainder = { 0 }
                }
            }
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

TEST(DivideNormalized3n2nSplitTest, EqualValue)
{
    std::vector<digit_type> dividend = {
        0, 0, digit_type(1) << (DIGIT_TYPE_BITS - 1)
    };
    std::vector<digit_type> divisor = dividend;

    DigitsDivisionResult expected_result = {
        .quotient = { 1 }, .remainder = { 0 }
    };

    auto result = divide_normalized_3n_2n_split(dividend, divisor);

    expect_equal(expected_result, result);
}

TEST(DivideNormalized3n2nSplitTest, UnevenSplits)
{
    std::vector<digit_type> dividend = {
        0, 0, DIGIT_TYPE_MAX - 1, DIGIT_TYPE_MAX, DIGIT_TYPE_MAX
    };
    std::vector<digit_type> divisor = {
        0, DIGIT_TYPE_MAX, DIGIT_TYPE_MAX, DIGIT_TYPE_MAX
    };

    DigitsDivisionResult expected_result = {
        .quotient  = { DIGIT_TYPE_MAX },
        .remainder = { 0, DIGIT_TYPE_MAX, DIGIT_TYPE_MAX - 1, DIGIT_TYPE_MAX }
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

TEST(DivideNormalized2n1nSplitTest, EqualValue)
{
    std::vector<digit_type> dividend = {
        0, 0, 0, digit_type(1) << (DIGIT_TYPE_BITS - 1)
    };
    std::vector<digit_type> divisor = dividend;

    DigitsDivisionResult expected_result = {
        .quotient = { 1 }, .remainder = { 0 }
    };

    auto result = divide_normalized_2n_1n_split(dividend, divisor);

    expect_equal(expected_result, result);
}


class DigitsAndIntegralDivisionTest
    : public ::testing::TestWithParam<
      std::tuple<std::vector<digit_type>, std::uintmax_t>
    >
{}; // class DigitsAndIntegralDivisionTest

TEST_P(DigitsAndIntegralDivisionTest,
       DigitsDividedByIntegralIsConsistentWithDigitsDividedByDigits)
{
    std::vector<digit_type> dividend = std::get<0>(GetParam());
    std::uintmax_t divisor           = std::get<1>(GetParam());
    auto expected_result             = divide(dividend,
                                              digits_from_integral(divisor));

    test_division(dividend, divisor, expected_result);
}

INSTANTIATE_TEST_SUITE_P(
    DigitsDivisionTest,
    DigitsAndIntegralDivisionTest,
    ::testing::Combine(
        ::testing::ValuesIn(SAMPLE_DIVIDENDS),
        tasty_int_test::logarithmic_range<std::uintmax_t>(
            1, std::numeric_limits<std::uintmax_t>::max(), 3
        )
    )
);


class DigitsAndFloatingPointDivisionTest
    : public ::testing::TestWithParam<
      std::tuple<std::vector<digit_type>, long double>
    >
{}; // class DigitsAndFloatingPointDivisionTest

TEST_P(DigitsAndFloatingPointDivisionTest,
       DigitsDividedByFloatingPointIsConsistentWithDigitsDividedByDigits)
{
    std::vector<digit_type> dividend = std::get<0>(GetParam());
    long double divisor              = std::get<1>(GetParam());
    auto expected_result             = divide(dividend,
                                              digits_from_floating_point(divisor));

    test_division(dividend, divisor, expected_result);
}

INSTANTIATE_TEST_SUITE_P(
    DigitsDivisionTest,
    DigitsAndFloatingPointDivisionTest,
    ::testing::Combine(
        ::testing::ValuesIn(SAMPLE_DIVIDENDS),
        ::testing::Values(
            1.0L,
            2.0L,
            10.0L,
            std::pow(DIGIT_BASE, 200.0L),
            1.0e20L,
            42.0e100L,
            77.0e300L,
            std::numeric_limits<long double>::max()
        )
    )
);

} // namespace
