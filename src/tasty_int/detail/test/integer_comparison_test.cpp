#include "tasty_int/detail/integer.hpp"

#include <vector>

#include "gtest/gtest.h"

#include "tasty_int/detail/test/comparison_test_common.hpp"
#include "tasty_int/detail/test/integer_test_common.hpp"


namespace {

using tasty_int::detail::digit_type;
using tasty_int::detail::DIGIT_TYPE_MAX;
using tasty_int::detail::Integer;
using tasty_int::detail::Sign;


class EqualityTest : public ::testing::TestWithParam<Integer>
{}; // class EqualityTest

TEST_P(EqualityTest, ThisEqualToThis)
{
    const Integer &integer = GetParam();

    comparison_test_common::expect_equal(integer, integer);
}

TEST_P(EqualityTest, LhsEqualToRhsCopy)
{
    const Integer &lhs = GetParam();
    auto rhs           = lhs;

    comparison_test_common::expect_equal(lhs, rhs);
}

INSTANTIATE_TEST_SUITE_P(
    IntegerComparisonTest,
    EqualityTest,
    ::testing::ValuesIn(
        std::vector<Integer> {
            { Sign::ZERO,     { 0 } },
            { Sign::POSITIVE, { 1 } },
            { Sign::POSITIVE, { 0, 1 } },
            { Sign::POSITIVE, { 0, 0, 1 } },
            { Sign::POSITIVE, { 0, 1, 1 } },
            { Sign::POSITIVE, { 1, 1, 1 } },
            { Sign::NEGATIVE, { 1 } },
            { Sign::NEGATIVE, { 0, 1 } },
            { Sign::NEGATIVE, { 0, 0, 1 } },
            { Sign::NEGATIVE, { 0, 1, 1 } },
            { Sign::NEGATIVE, { 1, 1, 1 } }
        }
    )
);


struct UnequalDigitsTestParam
{
    std::vector<digit_type> lesser;
    std::vector<digit_type> greater;
}; // struct UnequalDigitsTestParam

std::ostream &
operator<<(std::ostream                 &output,
           const UnequalDigitsTestParam &test_param)
{
    return output
        << "{ lesser="  << ::testing::PrintToString(test_param.lesser)
        << ", greater=" << ::testing::PrintToString(test_param.greater) << " }";
}

class UnequalDigitsInequalityTest
    : public ::testing::TestWithParam<UnequalDigitsTestParam>
{}; // class UnequalDigitsInequalityTest

TEST_P(UnequalDigitsInequalityTest,
       LesserPositiveLhsIsLessThanGreaterPositiveRhs)
{
    Integer lesser  = { .sign = Sign::POSITIVE, .digits = GetParam().lesser  };
    Integer greater = { .sign = Sign::POSITIVE, .digits = GetParam().greater };

    comparison_test_common::expect_unequal(lesser, greater);
}

TEST_P(UnequalDigitsInequalityTest,
       GreaterNegativeLhsIsLessThanLesserNegativeRhs)
{
    Integer lesser  = { .sign = Sign::NEGATIVE, .digits = GetParam().greater };
    Integer greater = { .sign = Sign::NEGATIVE, .digits = GetParam().lesser  };

    comparison_test_common::expect_unequal(lesser, greater);
}

TEST_P(UnequalDigitsInequalityTest,
       LesserNegativeLhsIsLessThanGreaterPositiveRhs)
{
    Integer lesser  = { .sign = Sign::NEGATIVE, .digits = GetParam().lesser };
    Integer greater = { .sign = Sign::POSITIVE, .digits = GetParam().greater};

    comparison_test_common::expect_unequal(lesser, greater);
}

TEST_P(UnequalDigitsInequalityTest,
       GreaterNegativeLhsIsLessThanLesserPositiveRhs)
{
    Integer lesser  = { .sign = Sign::NEGATIVE, .digits = GetParam().greater };
    Integer greater = { .sign = Sign::POSITIVE, .digits = GetParam().lesser  };

    comparison_test_common::expect_unequal(lesser, greater);
}

INSTANTIATE_TEST_SUITE_P(
    IntegerComparisonTest,
    UnequalDigitsInequalityTest,
    ::testing::ValuesIn(
        std::vector<UnequalDigitsTestParam> {
            { .lesser = { 0 },              .greater = { 1 } },
            { .lesser = { 1 },              .greater = { 0, 1 } },
            { .lesser = { DIGIT_TYPE_MAX }, .greater = { 0, 1 } },
            { .lesser = { 1, 1, 1 },        .greater = { 1, 1, 2 } },
            { .lesser = { 1, 1, 1 },        .greater = { 1, 2, 1 } },
            { .lesser = { 1, 1, 1 },        .greater = { 2, 1, 1 } }
        }
    )
);


class EqualDigitsInequalityTest
    : public ::testing::TestWithParam<std::vector<digit_type>>
{}; // class EqualDigitsInequalityTest

TEST_P(EqualDigitsInequalityTest, NegativeLhsIsLessThanPositiveRhs)
{
    Integer lesser  = { .sign = Sign::NEGATIVE, .digits = GetParam() };
    Integer greater = { .sign = Sign::POSITIVE, .digits = GetParam() };

    comparison_test_common::expect_unequal(lesser, greater);
}

INSTANTIATE_TEST_SUITE_P(
    IntegerComparisonTest,
    EqualDigitsInequalityTest,
    ::testing::ValuesIn(
        std::vector<std::vector<digit_type>> {
            { 1 },
            { 0, 1 },
            { 0, 0, 1 },
            { 0, 1, 1 },
            { 1, 1, 1 }
        }
    )
);

} // namespace
