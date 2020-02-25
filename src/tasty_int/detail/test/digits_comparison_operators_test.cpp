#include "tasty_int/detail/digits_comparison_operators.hpp"

#include "gtest/gtest.h"


namespace {

using tasty_int::detail::digit_type;
using tasty_int::detail::DIGIT_TYPE_MAX;
using tasty_int::detail::operator==;
using tasty_int::detail::operator!=;
using tasty_int::detail::operator<;
using tasty_int::detail::operator>;
using tasty_int::detail::operator<=;
using tasty_int::detail::operator>=;


using DigitsComparisonTestParam = std::pair<
    std::vector<digit_type>,
    std::vector<digit_type>
>;

class DigitsComparisonTest
    : public ::testing::TestWithParam<DigitsComparisonTestParam>
{}; // class DigitsComparisonTest


class EqualityTest : public DigitsComparisonTest
{
protected:
    static void
    expect_equal(const std::vector<digit_type> &lhs,
                 const std::vector<digit_type> &rhs);
}; // class EqualityTest

void
EqualityTest::expect_equal(const std::vector<digit_type> &lhs,
                           const std::vector<digit_type> &rhs)
{
    EXPECT_TRUE(lhs == rhs);

    EXPECT_FALSE(lhs != rhs);

    EXPECT_FALSE(lhs < rhs);

    EXPECT_FALSE(lhs > rhs);

    EXPECT_TRUE(lhs <= rhs);

    EXPECT_TRUE(lhs >= rhs);
}

TEST_P(EqualityTest, LhsEqualToRhs)
{
    const std::vector<digit_type> &lhs = GetParam().first;
    const std::vector<digit_type> &rhs = GetParam().second;

    expect_equal(lhs, rhs);
}

INSTANTIATE_TEST_SUITE_P(
    DigitsComparisonTest,
    EqualityTest,
    ::testing::ValuesIn(
        std::vector<DigitsComparisonTestParam> {
            { { 0 },       /* == */ { 0 } },
            { { 1 },       /* == */ { 1 } },
            { { 0, 1 },    /* == */ { 0, 1 } },
            { { 0, 0, 1 }, /* == */ { 0, 0, 1 } },
            { { 0, 1, 1 }, /* == */ { 0, 1, 1 } },
            { { 1, 1, 1 }, /* == */ { 1, 1, 1 } }
        }
    )
);


class InequalityTest : public DigitsComparisonTest
{
protected:
    static void
    expect_less(const std::vector<digit_type> &lesser,
                const std::vector<digit_type> &greater);

}; // class InequalityTest

void
InequalityTest::expect_less(const std::vector<digit_type> &lesser,
                            const std::vector<digit_type> &greater)
{
    EXPECT_FALSE(lesser == greater);

    EXPECT_TRUE(lesser != greater);

    EXPECT_TRUE(lesser < greater);

    EXPECT_FALSE(lesser > greater);

    EXPECT_TRUE(lesser <= greater);

    EXPECT_FALSE(lesser >= greater);
}

TEST_P(InequalityTest, LhsLessThanRhs)
{
    const std::vector<digit_type> &lesser  = GetParam().first;
    const std::vector<digit_type> &greater = GetParam().second;

    expect_less(lesser, greater);
}

INSTANTIATE_TEST_SUITE_P(
    DigitsComparisonTest,
    InequalityTest,
    ::testing::ValuesIn(
        std::vector<DigitsComparisonTestParam> {
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
