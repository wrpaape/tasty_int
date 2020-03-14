#include "tasty_int/detail/digits_comparison.hpp"

#include <limits>

#include "gtest/gtest.h"

#include "tasty_int/detail/conversions/digits_from_integral.hpp"
#include "tasty_int/detail/conversions/digits_from_floating_point.hpp"
#include "tasty_int/detail/test/comparison_test_common.hpp"
#include "tasty_int_test/logarithmic_range.hpp"


namespace {

using tasty_int::detail::operator==;
using tasty_int::detail::operator!=;
using tasty_int::detail::operator<;
using tasty_int::detail::operator>;
using tasty_int::detail::operator<=;
using tasty_int::detail::operator>=;
using tasty_int::detail::digit_type;
using tasty_int::detail::DIGIT_TYPE_MAX;
using tasty_int::detail::DIGIT_BASE;
using tasty_int::detail::conversions::digits_from_integral;
using tasty_int::detail::conversions::digits_from_floating_point;
using comparison_test_common::InequalityTestParam;


class DigitsAndDigitsEqualityTest
    : public ::testing::TestWithParam<std::vector<digit_type>>
{}; // class DigitsAndDigitsEqualityTest

TEST_P(DigitsAndDigitsEqualityTest, ThisEqualToThis)
{
    const std::vector<digit_type> &digits = GetParam();

    comparison_test_common::expect_equal(digits, digits);
}

TEST_P(DigitsAndDigitsEqualityTest, LhsEqualToRhsCopy)
{
    const std::vector<digit_type> &lhs = GetParam();
    auto rhs                           = lhs;

    comparison_test_common::expect_equal(lhs, rhs);
}

INSTANTIATE_TEST_SUITE_P(
    DigitsComparisonTest,
    DigitsAndDigitsEqualityTest,
    ::testing::ValuesIn(
        std::vector<std::vector<digit_type>> {
            { { 0 } },
            { { 1 } },
            { { 0, 1 } },
            { { 0, 0, 1 } },
            { { 0, 1, 1 } },
            { { 1, 1, 1 } }
        }
    )
);

using DigitsAndDigitsInequalityTestParam = InequalityTestParam<
    std::vector<digit_type>,
    std::vector<digit_type>
>;

class DigitsAndDigitsInequalityTest
    : public ::testing::TestWithParam<DigitsAndDigitsInequalityTestParam>
{}; // class DigitsAndDigitsInequalityTest

TEST_P(DigitsAndDigitsInequalityTest, LhsLessThanRhs)
{
    const std::vector<digit_type> &lesser  = GetParam().smaller;
    const std::vector<digit_type> &greater = GetParam().larger;

    comparison_test_common::expect_unequal(lesser, greater);
}

INSTANTIATE_TEST_SUITE_P(
    DigitsComparisonTest,
    DigitsAndDigitsInequalityTest,
    ::testing::ValuesIn(
        std::vector<DigitsAndDigitsInequalityTestParam> {
            { .smaller = { 0 },              .larger = { 1 } },
            { .smaller = { 1 },              .larger = { 0, 1 } },
            { .smaller = { DIGIT_TYPE_MAX }, .larger = { 0, 1 } },
            { .smaller = { 1, 1, 1 },        .larger = { 1, 1, 2 } },
            { .smaller = { 1, 1, 1 },        .larger = { 1, 2, 1 } },
            { .smaller = { 1, 1, 1 },        .larger = { 2, 1, 1 } }
        }
    )
);


class DigitsAndIntegralEqualityTest
    : public ::testing::TestWithParam<std::uintmax_t>
{}; // class DigitsAndIntegralEqualityTest

TEST_P(DigitsAndIntegralEqualityTest, LhsEqualToRhs)
{
    std::uintmax_t value           = GetParam();
    std::vector<digit_type> digits = digits_from_integral(value);

    comparison_test_common::expect_equal(digits, value);
}

INSTANTIATE_TEST_SUITE_P(
    DigitsComparisonTest,
    DigitsAndIntegralEqualityTest,
    tasty_int_test::logarithmic_range<std::uintmax_t>(
        0, std::numeric_limits<std::uintmax_t>::max(), 2
    )
);

using DigitsSmallerThanIntegralTestParam = InequalityTestParam<
    std::vector<digit_type>,
    std::uintmax_t
>;

class DigitsLessThanIntegralTest
    : public ::testing::TestWithParam<DigitsSmallerThanIntegralTestParam>
{}; // class DigitsLessThanIntegralTest

TEST_P(DigitsLessThanIntegralTest, LhsLessThanRhs)
{
    const std::vector<digit_type> &lesser  = GetParam().smaller;
    std::uintmax_t                 greater = GetParam().larger;

    comparison_test_common::expect_unequal(lesser, greater);
}

INSTANTIATE_TEST_SUITE_P(
    DigitsComparisonTest,
    DigitsLessThanIntegralTest,
    ::testing::ValuesIn(
        std::vector<DigitsSmallerThanIntegralTestParam> {
            { { 0 },              /* < */ 1  },
            { { 1 },              /* < */ 2  },
            { { DIGIT_TYPE_MAX }, /* < */ DIGIT_BASE },
            { { 0, 1 },           /* < */ DIGIT_BASE + 1  },
            {
                { 0, DIGIT_TYPE_MAX },
                std::numeric_limits<std::uintmax_t>::max()
            },
            {
                { DIGIT_TYPE_MAX - 1, DIGIT_TYPE_MAX },
                std::numeric_limits<std::uintmax_t>::max()
            }
        }
    )
);

using IntegralSmallerThanDigitsTestParam = InequalityTestParam<
    std::uintmax_t,
    std::vector<digit_type>
>;

class IntegralLessThanDigitsTest
    : public ::testing::TestWithParam<IntegralSmallerThanDigitsTestParam>
{}; // class IntegralLessThanDigitsTest

TEST_P(IntegralLessThanDigitsTest, LhsLessThanRhs)
{
    std::uintmax_t                 lesser  = GetParam().smaller;
    const std::vector<digit_type> &greater = GetParam().larger;

    comparison_test_common::expect_unequal(lesser, greater);
}

INSTANTIATE_TEST_SUITE_P(
    DigitsComparisonTest,
    IntegralLessThanDigitsTest,
    ::testing::ValuesIn(
        std::vector<IntegralSmallerThanDigitsTestParam> {
            { .smaller = 0,              .larger = { 1 } },
            { .smaller = 1,              .larger = { 2 } },
            { .smaller = DIGIT_TYPE_MAX, .larger = { 0, 1 } },
            { .smaller = DIGIT_BASE,     .larger = { 1, 1 } },
            {
                .smaller = std::numeric_limits<std::uintmax_t>::max(),
                .larger  = { 0, 0, 1 }
            },
            {
                .smaller = std::numeric_limits<std::uintmax_t>::max() - 1,
                .larger  = { DIGIT_TYPE_MAX, DIGIT_TYPE_MAX }
            }
        }
    )
);


class DigitsAndFloatingPointEqualityTest
    : public ::testing::TestWithParam<long double>
{}; // class DigitsAndFloatingPointEqualityTest

TEST_P(DigitsAndFloatingPointEqualityTest, LhsEqualToRhs)
{
    long double value              = GetParam();
    std::vector<digit_type> digits = digits_from_floating_point(value);

    comparison_test_common::expect_equal(digits, value);
}

INSTANTIATE_TEST_SUITE_P(
    DigitsComparisonTest,
    DigitsAndFloatingPointEqualityTest,
    tasty_int_test::logarithmic_range<long double>(
        0.0L, std::numeric_limits<long double>::max(), 1.0e20L
    )
);

using DigitsSmallerThanFloatingPointTestParam = InequalityTestParam<
    std::vector<digit_type>,
    long double   
>;

class DigitsLessThanFloatingPointTest
    : public ::testing::TestWithParam<DigitsSmallerThanFloatingPointTestParam>
{}; // class DigitsLessThanFloatingPointTest

TEST_P(DigitsLessThanFloatingPointTest, LhsLessThanRhs)
{
    const std::vector<digit_type> &lesser  = GetParam().smaller;
    long double                    greater = GetParam().larger;

    comparison_test_common::expect_unequal(lesser, greater);
}

INSTANTIATE_TEST_SUITE_P(
    DigitsComparisonTest,
    DigitsLessThanFloatingPointTest,
    ::testing::ValuesIn(
        std::vector<DigitsSmallerThanFloatingPointTestParam> {
            { .smaller = { 0 },              .larger = 1.0L  },
            { .smaller = { 0 },              .larger = 1.5L  },
            { .smaller = { 1 },              .larger = 2.1L  },
            { .smaller = { DIGIT_TYPE_MAX }, .larger = DIGIT_BASE },
            { .smaller = { 0, 1 },           .larger = DIGIT_BASE + 1.1L },
            {
                .smaller = digits_from_floating_point(1.0e19L),
                .larger  = 1.1e20L
            },
            {
                .smaller = digits_from_floating_point(1.0e20L),
                .larger  =  1.00000001e20L
            },
            {
                .smaller = { DIGIT_TYPE_MAX },
                .larger  = std::numeric_limits<long double>::max()
            }
        }
    )
);

using FloatingPointSmallerThanDigitsTestParam = InequalityTestParam<
    long double,
    std::vector<digit_type>
>;

class FloatingPointLessThanDigitsTest
    : public ::testing::TestWithParam<FloatingPointSmallerThanDigitsTestParam>
{}; // class FloatingPointLessThanDigitsTest

TEST_P(FloatingPointLessThanDigitsTest, LhsLessThanRhs)
{
    long double                    lesser  = GetParam().smaller;
    const std::vector<digit_type> &greater = GetParam().larger;

    comparison_test_common::expect_unequal(lesser, greater);
}

INSTANTIATE_TEST_SUITE_P(
    DigitsComparisonTest,
    FloatingPointLessThanDigitsTest,
    ::testing::ValuesIn(
        std::vector<FloatingPointSmallerThanDigitsTestParam> {
            { .smaller = 0.0L,              .larger = { 1 } },
            { .smaller = 0.9L,              .larger = { 1 } },
            { .smaller = 1.9L,              .larger = { 2 } },
            { .smaller = DIGIT_TYPE_MAX,    .larger = { 0, 1 } },
            { .smaller = DIGIT_BASE - 0.1L, .larger = { 0, 1 } },
            { .smaller = DIGIT_BASE,        .larger = { 1, 1 } },
            { .smaller = 1.1L,              .larger = { 0, 0, 1 } },
            {
                .smaller = 1.0e20L,
                .larger  = digits_from_floating_point(1.1e20L)
            },
            {
                .smaller = 1.0e20L,
                .larger = digits_from_floating_point(1.00000001e20L)
            }
        }
    )
);

} // namespace
