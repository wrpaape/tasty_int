#include "tasty_int/detail/digits_comparison.hpp"

#include <array>
#include <limits>

#include "gtest/gtest.h"

#include "tasty_int/detail/conversions/digits_from_integral.hpp"
#include "tasty_int/detail/conversions/digits_from_floating_point.hpp"
#include "tasty_int/detail/test/comparison_test_common.hpp"
#include "tasty_int_test/logarithmic_range.hpp"
#include "tasty_int_test/comparison_tests.hpp"


namespace {

using tasty_int::detail::operator==;
using tasty_int::detail::operator!=;
using tasty_int::detail::operator<;
using tasty_int::detail::operator>;
using tasty_int::detail::operator<=;
using tasty_int::detail::operator>=;
using tasty_int::detail::less_than;
using tasty_int::detail::digit_type;
using tasty_int::detail::DIGIT_TYPE_MAX;
using tasty_int::detail::DIGIT_BASE;
using tasty_int::detail::conversions::digits_from_integral;
using tasty_int::detail::conversions::digits_from_floating_point;
using comparison_test_common::InequalityTestParam;

/**
 * The point of this wrapper is to expose the comparison operator overloads for
 * `std::vector<digit_type>` that are declared in the `tasty_int::detail`
 * namespace to the test routines `expect_equal` and `expect_unequal,` which
 * are declared in the `tasty_int_test` namespace.  The `using
 * tasty_int::detail::operator` declarations in this namespace are essential.
 */
class WrappedDigits : public std::vector<digit_type>
{
public:
    using std::vector<digit_type>::vector;

    WrappedDigits(std::vector<digit_type>&& base)
        : std::vector<digit_type>(std::move(base))
    {}
}; // class WrappedDigits


class DigitsAndDigitsEqualityTest : public ::testing::TestWithParam<WrappedDigits>
{}; // class DigitsAndDigitsEqualityTest

TEST_P(DigitsAndDigitsEqualityTest, ThisEqualToThis)
{
    const WrappedDigits &digits = GetParam();

    tasty_int_test::expect_equal(digits, digits);
}

TEST_P(DigitsAndDigitsEqualityTest, LhsEqualToRhsCopy)
{
    const WrappedDigits &lhs = GetParam();
    auto rhs                 = lhs;

    tasty_int_test::expect_equal(lhs, rhs);
}

INSTANTIATE_TEST_SUITE_P(
    DigitsComparisonTest,
    DigitsAndDigitsEqualityTest,
    ::testing::ValuesIn(
        std::vector<WrappedDigits> {
            { 0 },
            { 1 },
            { 0, 1 },
            { 0, 0, 1 },
            { 0, 1, 1 },
            { 1, 1, 1 }
        }
    )
);

using DigitsAndDigitsInequalityTestParam =
    InequalityTestParam<WrappedDigits, WrappedDigits>;

class DigitsAndDigitsInequalityTest
    : public ::testing::TestWithParam<DigitsAndDigitsInequalityTestParam>
{}; // class DigitsAndDigitsInequalityTest

TEST_P(DigitsAndDigitsInequalityTest, LhsLessThanRhs)
{
    const WrappedDigits &lesser  = GetParam().smaller;
    const WrappedDigits &greater = GetParam().larger;

    tasty_int_test::expect_unequal(lesser, greater);
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
    std::uintmax_t value = GetParam();
    WrappedDigits digits = digits_from_integral(value);

    tasty_int_test::expect_equal(digits, value);
}

INSTANTIATE_TEST_SUITE_P(
    DigitsComparisonTest,
    DigitsAndIntegralEqualityTest,
    tasty_int_test::logarithmic_range<std::uintmax_t>(
        0, std::numeric_limits<std::uintmax_t>::max(), 2
    )
);

using DigitsSmallerThanIntegralTestParam =
    InequalityTestParam<WrappedDigits, std::uintmax_t>;

class DigitsLessThanIntegralTest
    : public ::testing::TestWithParam<DigitsSmallerThanIntegralTestParam>
{}; // class DigitsLessThanIntegralTest

TEST_P(DigitsLessThanIntegralTest, LhsLessThanRhs)
{
    const WrappedDigits &lesser  = GetParam().smaller;
    std::uintmax_t       greater = GetParam().larger;

    tasty_int_test::expect_unequal(lesser, greater);
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

using IntegralSmallerThanDigitsTestParam =
    InequalityTestParam<std::uintmax_t, WrappedDigits>;

class IntegralLessThanDigitsTest
    : public ::testing::TestWithParam<IntegralSmallerThanDigitsTestParam>
{}; // class IntegralLessThanDigitsTest

TEST_P(IntegralLessThanDigitsTest, LhsLessThanRhs)
{
    std::uintmax_t       lesser  = GetParam().smaller;
    const WrappedDigits &greater = GetParam().larger;

    tasty_int_test::expect_unequal(lesser, greater);
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
    long double value    = GetParam();
    WrappedDigits digits = digits_from_floating_point(value);

    tasty_int_test::expect_equal(digits, value);
}

INSTANTIATE_TEST_SUITE_P(
    DigitsComparisonTest,
    DigitsAndFloatingPointEqualityTest,
    tasty_int_test::logarithmic_range<long double>(
        0.0L, std::numeric_limits<long double>::max(), 1.0e20L
    )
);

using DigitsSmallerThanFloatingPointTestParam =
    InequalityTestParam<WrappedDigits, long double>;

class DigitsLessThanFloatingPointTest
    : public ::testing::TestWithParam<DigitsSmallerThanFloatingPointTestParam>
{}; // class DigitsLessThanFloatingPointTest

TEST_P(DigitsLessThanFloatingPointTest, LhsLessThanRhs)
{
    const WrappedDigits &lesser  = GetParam().smaller;
    long double          greater = GetParam().larger;

    tasty_int_test::expect_unequal(lesser, greater);
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

using FloatingPointSmallerThanDigitsTestParam =
    InequalityTestParam<long double, WrappedDigits>;

class FloatingPointLessThanDigitsTest
    : public ::testing::TestWithParam<FloatingPointSmallerThanDigitsTestParam>
{}; // class FloatingPointLessThanDigitsTest

TEST_P(FloatingPointLessThanDigitsTest, LhsLessThanRhs)
{
    long double          lesser  = GetParam().smaller;
    const WrappedDigits &greater = GetParam().larger;

    tasty_int_test::expect_unequal(lesser, greater);
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



struct DigitsSequenceTestParam
{
    std::vector<digit_type>             digits;
    std::vector<digit_type>::size_type  begin_offset;
    std::vector<digit_type>::size_type  end_offset;
}; // struct DigitsSequenceTestParam

std::ostream &
operator<<(std::ostream                  &output,
           const DigitsSequenceTestParam &test_param)
{
    return output << "{ digits=" << ::testing::PrintToString(test_param.digits)
                  << ", begin_offset=" << test_param.begin_offset
                  << ", end_offset=" << test_param.end_offset
                  << " }";
}

struct DigitsSequenceComparisonTestParam
{
    DigitsSequenceTestParam lhs;
    DigitsSequenceTestParam rhs;
}; // struct DigitsSequenceComparisonTestParam

std::ostream &
operator<<(std::ostream                            &output,
           const DigitsSequenceComparisonTestParam &test_param)
{
    return output << "{ lhs=" << test_param.lhs
                  << ", rhs=" << test_param.rhs
                  << " }";
}

std::array<std::vector<digit_type>::const_iterator, 4>
unpack(const DigitsSequenceComparisonTestParam& test_param)
{
    auto&& [ lhs, rhs ] = test_param;

    auto lhs_begin = lhs.digits.begin() + lhs.begin_offset;
    auto lhs_end   = lhs.digits.begin() + lhs.end_offset;
    auto rhs_begin = rhs.digits.begin() + rhs.begin_offset;
    auto rhs_end   = rhs.digits.begin() + rhs.end_offset;

    return { lhs_begin, lhs_end, rhs_begin, rhs_end };
}

class DigitsSequenceLessThanInequalityTest
    : public ::testing::TestWithParam<DigitsSequenceComparisonTestParam>
{
protected:
    static void
    expect_unequal(std::vector<digit_type>::const_iterator lhs_begin,
                   std::vector<digit_type>::const_iterator lhs_end,
                   std::vector<digit_type>::const_iterator rhs_begin,
                   std::vector<digit_type>::const_iterator rhs_end)
    {
        EXPECT_TRUE(less_than(lhs_begin, lhs_end,
                              rhs_begin, rhs_end));

        EXPECT_FALSE(less_than(rhs_begin, rhs_end,
                               lhs_begin, lhs_end));
    }
}; // class DigitsSequenceLessThanInequalityTest

TEST_P(DigitsSequenceLessThanInequalityTest, LhsLessThanRhs)
{
    auto [lhs_begin, lhs_end, rhs_begin, rhs_end] = unpack(GetParam());

    expect_unequal(lhs_begin, lhs_end,
                   rhs_begin, rhs_end);
}

INSTANTIATE_TEST_SUITE_P(
    DigitsComparisonTest,
    DigitsSequenceLessThanInequalityTest,
    ::testing::ValuesIn(
        std::vector<DigitsSequenceComparisonTestParam> {
            { 
                .lhs = { {},    0, 0 },
                .rhs = { { 0 }, 0, 1 }
            },
            { 
                .lhs = { { 1, 2, 3 },    0, 3 },
                .rhs = { { 1, 2, 3, 4 }, 0, 4 }
            },
            { 
                .lhs = { { 1, 2, 3 },    0, 3 },
                .rhs = { { 1, 2, 3, 4 }, 1, 4 }
            },
            { 
                .lhs = { { 1, 2, 3, 4 }, 0, 2 },
                .rhs = { { 1, 2, 3 },    1, 3 }
            },
            { 
                .lhs = { { 1, 2, 3, 4 }, 2, 4 },
                .rhs = { { 1, 2, 3 },    0, 3 }
            },
            { 
                .lhs = { { 1, 2, 3, 4 }, 4, 4 },
                .rhs = { { 1, 2, 3 },    0, 1 }
            }
        }
    )
);

class DigitsSequenceLessThanEqualityTest
    : public ::testing::TestWithParam<DigitsSequenceComparisonTestParam>
{}; // class DigitsSequenceLessThanEqualityTest

TEST_P(DigitsSequenceLessThanEqualityTest, LhsEqualToRhs)
{
    auto [lhs_begin, lhs_end, rhs_begin, rhs_end] = unpack(GetParam());

    EXPECT_FALSE(less_than(lhs_begin, lhs_end,
                           rhs_begin, rhs_end));
}

INSTANTIATE_TEST_SUITE_P(
    DigitsComparisonTest,
    DigitsSequenceLessThanEqualityTest,
    ::testing::ValuesIn(
        std::vector<DigitsSequenceComparisonTestParam> {
            { 
                .lhs = { {}, 0, 0 },
                .rhs = { {}, 0, 0 }
            },
            { 
                .lhs = { { 1, 2, 3 },    0, 3 },
                .rhs = { { 1, 2, 3, 4 }, 0, 3 }
            },
            { 
                .lhs = { { 2, 3, 1 },    0, 2 },
                .rhs = { { 0, 2, 3, 7 }, 1, 3 }
            },
            { 
                .lhs = { { 1, 2, 3, 4 }, 3, 4 },
                .rhs = { { 1, 4, 3 },    1, 2 }
            }
        }
    )
);

} // namespace
