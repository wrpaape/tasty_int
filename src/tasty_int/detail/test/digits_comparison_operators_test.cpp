#include "tasty_int/detail/digits_comparison_operators.hpp"

#include "gtest/gtest.h"

#include "tasty_int/detail/test/comparison_test_common.hpp"


namespace {

using tasty_int::detail::digit_type;
using tasty_int::detail::DIGIT_TYPE_MAX;
using tasty_int::detail::operator==;
using tasty_int::detail::operator!=;
using tasty_int::detail::operator<;
using tasty_int::detail::operator>;
using tasty_int::detail::operator<=;
using tasty_int::detail::operator>=;


class EqualityTest : public ::testing::TestWithParam<std::vector<digit_type>>
{}; // class EqualityTest

TEST_P(EqualityTest, ThisEqualToThis)
{
    const std::vector<digit_type> &digits = GetParam();

    comparison_test_common::expect_equal(digits, digits);
}

TEST_P(EqualityTest, LhsEqualToRhsCopy)
{
    const std::vector<digit_type> &lhs = GetParam();
    auto rhs                           = lhs;

    comparison_test_common::expect_equal(lhs, rhs);
}

INSTANTIATE_TEST_SUITE_P(
    DigitsComparisonTest,
    EqualityTest,
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


using InequalityTestParam = std::pair<
    std::vector<digit_type>,
    std::vector<digit_type>
>;

class InequalityTest : public ::testing::TestWithParam<InequalityTestParam>
{}; // class InequalityTest

TEST_P(InequalityTest, LhsLessThanRhs)
{
    const std::vector<digit_type> &lesser  = GetParam().first;
    const std::vector<digit_type> &greater = GetParam().second;

    comparison_test_common::expect_unequal(lesser, greater);
}

INSTANTIATE_TEST_SUITE_P(
    DigitsComparisonTest,
    InequalityTest,
    ::testing::ValuesIn(
        std::vector<InequalityTestParam> {
            { { 0 },              /* < */ { 1 } },
            { { 1 },              /* < */ { 0, 1 } },
            { { DIGIT_TYPE_MAX }, /* < */ { 0, 1 } },
            { { 1, 1, 1 },        /* < */ { 1, 1, 2 } },
            { { 1, 1, 1 },        /* < */ { 1, 2, 1 } },
            { { 1, 1, 1 },        /* < */ { 2, 1, 1 } }
        }
    )
);

} // namespace
