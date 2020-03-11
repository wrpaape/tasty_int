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

using DigitsAndDigitsInequalityTestParam = std::pair<
    std::vector<digit_type>,
    std::vector<digit_type>
>;

class DigitsAndDigitsInequalityTest
    : public ::testing::TestWithParam<DigitsAndDigitsInequalityTestParam>
{}; // class DigitsAndDigitsInequalityTest

TEST_P(DigitsAndDigitsInequalityTest, LhsLessThanRhs)
{
    const std::vector<digit_type> &lesser  = GetParam().first;
    const std::vector<digit_type> &greater = GetParam().second;

    comparison_test_common::expect_unequal(lesser, greater);
}

INSTANTIATE_TEST_SUITE_P(
    DigitsComparisonTest,
    DigitsAndDigitsInequalityTest,
    ::testing::ValuesIn(
        std::vector<DigitsAndDigitsInequalityTestParam> {
            { { 0 },              /* < */ { 1 } },
            { { 1 },              /* < */ { 0, 1 } },
            { { DIGIT_TYPE_MAX }, /* < */ { 0, 1 } },
            { { 1, 1, 1 },        /* < */ { 1, 1, 2 } },
            { { 1, 1, 1 },        /* < */ { 1, 2, 1 } },
            { { 1, 1, 1 },        /* < */ { 2, 1, 1 } }
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

using DigitsAndIntegralInequalityTestParam = std::pair<
    std::vector<digit_type>,
    std::uintmax_t
>;

class DigitsLessThanIntegralTest
    : public ::testing::TestWithParam<DigitsAndIntegralInequalityTestParam>
{}; // class DigitsLessThanIntegralTest

TEST_P(DigitsLessThanIntegralTest, LhsLessThanRhs)
{
    const std::vector<digit_type> &lesser  = GetParam().first;
    std::uintmax_t                 greater = GetParam().second;

    comparison_test_common::expect_unequal(lesser, greater);
}

INSTANTIATE_TEST_SUITE_P(
    DigitsComparisonTest,
    DigitsLessThanIntegralTest,
    ::testing::ValuesIn(
        std::vector<DigitsAndIntegralInequalityTestParam> {
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

class IntegralLessThanDigitsTest
    : public ::testing::TestWithParam<DigitsAndIntegralInequalityTestParam>
{}; // class IntegralLessThanDigitsTest

TEST_P(IntegralLessThanDigitsTest, LhsLessThanRhs)
{
    std::uintmax_t                 lesser  = GetParam().second;
    const std::vector<digit_type> &greater = GetParam().first;

    comparison_test_common::expect_unequal(lesser, greater);
}

INSTANTIATE_TEST_SUITE_P(
    DigitsComparisonTest,
    IntegralLessThanDigitsTest,
    ::testing::ValuesIn(
        std::vector<DigitsAndIntegralInequalityTestParam> {
            { { 1 },    /* > */ 0  },
            { { 2 },    /* > */ 1  },
            { { 0, 1 }, /* > */ DIGIT_TYPE_MAX },
            { { 1, 1 }, /* > */ DIGIT_BASE  },
            {
                { 0, 0, 1 },
                std::numeric_limits<std::uintmax_t>::max()
            },
            {
                { DIGIT_TYPE_MAX, DIGIT_TYPE_MAX },
                std::numeric_limits<std::uintmax_t>::max() - 1
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

using DigitsAndFloatingPointInequalityTestParam = std::pair<
    std::vector<digit_type>,
    long double   
>;

class DigitsLessThanFloatingPointTest
    : public ::testing::TestWithParam<DigitsAndFloatingPointInequalityTestParam>
{}; // class DigitsLessThanFloatingPointTest

TEST_P(DigitsLessThanFloatingPointTest, LhsLessThanRhs)
{
    const std::vector<digit_type> &lesser  = GetParam().first;
    long double                    greater = GetParam().second;

    comparison_test_common::expect_unequal(lesser, greater);
}

INSTANTIATE_TEST_SUITE_P(
    DigitsComparisonTest,
    DigitsLessThanFloatingPointTest,
    ::testing::ValuesIn(
        std::vector<DigitsAndFloatingPointInequalityTestParam> {
            { { 0 },              /* < */ 1.0L  },
            { { 0 },              /* < */ 1.5L  },
            { { 1 },              /* < */ 2.1L  },
            { { DIGIT_TYPE_MAX }, /* < */ DIGIT_BASE },
            { { 0, 1 },           /* < */ DIGIT_BASE + 1.1L  },
            {
                digits_from_floating_point(1.0e19L), /* < */ 1.1e20L
            },
            {
                digits_from_floating_point(1.0e20L), /* < */ 1.00000001e20L
            },
            {   { DIGIT_TYPE_MAX },
                std::numeric_limits<long double>::max()
            }
        }
    )
);

class FloatingPointLessThanDigitsTest
    : public ::testing::TestWithParam<DigitsAndFloatingPointInequalityTestParam>
{}; // class FloatingPointLessThanDigitsTest

TEST_P(FloatingPointLessThanDigitsTest, LhsLessThanRhs)
{
    long double                    lesser  = GetParam().second;
    const std::vector<digit_type> &greater = GetParam().first;

    comparison_test_common::expect_unequal(lesser, greater);
}

INSTANTIATE_TEST_SUITE_P(
    DigitsComparisonTest,
    FloatingPointLessThanDigitsTest,
    ::testing::ValuesIn(
        std::vector<DigitsAndFloatingPointInequalityTestParam> {
            { { 1 },       /* > */ 0.0L  },
            { { 1 },       /* > */ 0.9L  },
            { { 2 },       /* > */ 1.9L  },
            { { 0, 1 },    /* > */ DIGIT_TYPE_MAX  },
            { { 0, 1 },    /* > */ DIGIT_BASE - 0.1L  },
            { { 1, 1 },    /* > */ DIGIT_BASE },
            { { 0, 0, 1 }, /* > */ 1.1L },
            {
                digits_from_floating_point(1.1e20L), /* > */ 1.0e20L
            },
            {
                digits_from_floating_point(1.00000001e20L), /* > */ 1.0e20L
            }
        }
    )
);

} // namespace
