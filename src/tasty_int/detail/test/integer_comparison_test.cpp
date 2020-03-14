#include "tasty_int/detail/integer.hpp"

#include <vector>
#include <limits>

#include "gtest/gtest.h"

#include "tasty_int/detail/sign_from_digits.hpp"
#include "tasty_int/detail/conversions/digits_from_integral.hpp"
#include "tasty_int/detail/conversions/integer_from_signed_integral.hpp"
#include "tasty_int/detail/conversions/integer_from_unsigned_integral.hpp"
#include "tasty_int/detail/test/comparison_test_common.hpp"
#include "tasty_int/detail/test/integer_test_common.hpp"
#include "tasty_int_test/logarithmic_range.hpp"


namespace {

using tasty_int::detail::digit_type;
using tasty_int::detail::DIGIT_TYPE_MAX;
using tasty_int::detail::DIGIT_BASE;
using tasty_int::detail::Integer;
using tasty_int::detail::Sign;
using tasty_int::detail::sign_from_digits;
using tasty_int::detail::conversions::digits_from_integral;
using tasty_int::detail::conversions::integer_from_signed_integral;
using tasty_int::detail::conversions::integer_from_unsigned_integral;
using comparison_test_common::InequalityTestParam;


class IntegerAndIntegerEqualityTest : public ::testing::TestWithParam<Integer>
{}; // class IntegerAndIntegerEqualityTest

TEST_P(IntegerAndIntegerEqualityTest, ThisEqualToThis)
{
    const Integer &integer = GetParam();

    comparison_test_common::expect_equal(integer, integer);
}

TEST_P(IntegerAndIntegerEqualityTest, LhsEqualToRhsCopy)
{
    const Integer &lhs = GetParam();
    auto rhs           = lhs;

    comparison_test_common::expect_equal(lhs, rhs);
}

INSTANTIATE_TEST_SUITE_P(
    IntegerComparisonTest,
    IntegerAndIntegerEqualityTest,
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

using UnequalDigitsTestParam = InequalityTestParam<
    std::vector<digit_type>, std::vector<digit_type>
>;

class IntegerAndIntegerUnequalDigitsInequalityTest
    : public ::testing::TestWithParam<UnequalDigitsTestParam>
{}; // class IntegerAndIntegerUnequalDigitsInequalityTest

TEST_P(IntegerAndIntegerUnequalDigitsInequalityTest,
       SmallerPositiveLhsIsLessThanLargerPositiveRhs)
{
    Integer lesser  = { .sign = Sign::POSITIVE, .digits = GetParam().smaller };
    Integer greater = { .sign = Sign::POSITIVE, .digits = GetParam().larger  };

    comparison_test_common::expect_unequal(lesser, greater);
}

TEST_P(IntegerAndIntegerUnequalDigitsInequalityTest,
       LargerNegativeLhsIsLessThanSmallerNonpositiveRhs)
{
    Integer lesser  = { .sign = Sign::NEGATIVE, .digits = GetParam().larger  };
    Integer greater = {
        .sign   = sign_from_digits(GetParam().smaller,
                                   Sign::NEGATIVE),
        .digits = GetParam().smaller
    };

    comparison_test_common::expect_unequal(lesser, greater);
}

TEST_P(IntegerAndIntegerUnequalDigitsInequalityTest,
       SmallerNonpositiveLhsIsLessThanLargerPositiveRhs)
{
    Integer lesser = {
        .sign   = sign_from_digits(GetParam().smaller,
                                   Sign::NEGATIVE),
        .digits = GetParam().smaller
    };
    Integer greater = { .sign = Sign::POSITIVE, .digits = GetParam().larger  };

    comparison_test_common::expect_unequal(lesser, greater);
}

TEST_P(IntegerAndIntegerUnequalDigitsInequalityTest,
       LargerNegativeLhsIsLessThanSmallerNonnegativeRhs)
{
    Integer lesser  = { .sign = Sign::NEGATIVE, .digits = GetParam().larger  };
    Integer greater = {
        .sign   = sign_from_digits(GetParam().smaller,
                                   Sign::POSITIVE),
        .digits = GetParam().smaller
    };

    comparison_test_common::expect_unequal(lesser, greater);
}

INSTANTIATE_TEST_SUITE_P(
    IntegerComparisonTest,
    IntegerAndIntegerUnequalDigitsInequalityTest,
    ::testing::ValuesIn(
        std::vector<UnequalDigitsTestParam> {
            { .smaller = { 0 },              .larger = { 1 } },
            { .smaller = { 1 },              .larger = { 0, 1 } },
            { .smaller = { DIGIT_TYPE_MAX }, .larger = { 0, 1 } },
            { .smaller = { 1, 1, 1 },        .larger = { 1, 1, 2 } },
            { .smaller = { 1, 1, 1 },        .larger = { 1, 2, 1 } },
            { .smaller = { 1, 1, 1 },        .larger = { 2, 1, 1 } }
        }
    )
);

class IntegerAndIntegerEqualDigitsInequalityTest
    : public ::testing::TestWithParam<std::vector<digit_type>>
{}; // class IntegerAndIntegerEqualDigitsInequalityTest

TEST_P(IntegerAndIntegerEqualDigitsInequalityTest,
       NegativeLhsIsLessThanPositiveRhs)
{
    Integer lesser  = { .sign = Sign::NEGATIVE, .digits = GetParam() };
    Integer greater = { .sign = Sign::POSITIVE, .digits = GetParam() };

    comparison_test_common::expect_unequal(lesser, greater);
}

INSTANTIATE_TEST_SUITE_P(
    IntegerComparisonTest,
    IntegerAndIntegerEqualDigitsInequalityTest,
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


TEST(DigitsSameAsUnsignedIntegralTest, ZeroEqualToZero)
{
    std::uintmax_t lhs = 0;
    Integer        rhs = { .sign = Sign::ZERO, .digits = { 0 } };

    comparison_test_common::expect_equal(lhs, rhs);
}

class DigitsSameAsUnsignedIntegralTest
    : public ::testing::TestWithParam<std::uintmax_t>
{}; // class DigitsSameAsUnsignedIntegralTest

TEST_P(DigitsSameAsUnsignedIntegralTest,
       UnsignedIntegralEqualToPositiveInteger)
{
    std::uintmax_t lhs = GetParam();
    Integer        rhs = integer_from_unsigned_integral(lhs);

    comparison_test_common::expect_equal(lhs, rhs);
}

TEST_P(DigitsSameAsUnsignedIntegralTest,
       NegativeIntegerLessThanUnsignedIntegral)
{
    std::uintmax_t greater = GetParam();
    Integer        lesser  = {
        .sign   = Sign::NEGATIVE,
        .digits = digits_from_integral(greater)
    };

    comparison_test_common::expect_unequal(lesser, greater);
}

INSTANTIATE_TEST_SUITE_P(
    IntegerComparisonTest,
    DigitsSameAsUnsignedIntegralTest,
    tasty_int_test::logarithmic_range<std::uintmax_t>(
        1, std::numeric_limits<std::uintmax_t>::max(), 2
    )
);

using DigitsSmallerThanUnsignedIntegralTestParam = InequalityTestParam<
    std::vector<digit_type>, std::uintmax_t
>;

class DigitsSmallerThanUnsignedIntegralTest
    : public ::testing::TestWithParam<
          DigitsSmallerThanUnsignedIntegralTestParam
      >
{}; // class DigitsSmallerThanUnsignedIntegralTest

TEST_P(DigitsSmallerThanUnsignedIntegralTest,
       SmallerNonnegativeLhsIsLessThanLargerPositiveRhs)
{
    Integer lesser         = {
        .sign   = sign_from_digits(GetParam().smaller,
                                   Sign::POSITIVE),
        .digits = GetParam().smaller
    };
    std::uintmax_t greater = GetParam().larger;

    comparison_test_common::expect_unequal(lesser, greater);
}

TEST_P(DigitsSmallerThanUnsignedIntegralTest,
       SmallerNonpositiveLhsIsLessThanLargerPositiveRhs)
{
    Integer lesser         = {
        .sign   = sign_from_digits(GetParam().smaller,
                                   Sign::NEGATIVE),
        .digits = GetParam().smaller
    };
    std::uintmax_t greater = GetParam().larger;

    comparison_test_common::expect_unequal(lesser, greater);
}

INSTANTIATE_TEST_SUITE_P(
    IntegerComparisonTest,
    DigitsSmallerThanUnsignedIntegralTest,
    ::testing::ValuesIn(
        std::vector<DigitsSmallerThanUnsignedIntegralTestParam> {
            { .smaller = { 0 },              .larger = 1 },
            { .smaller = { 1 },              .larger = DIGIT_BASE },
            { .smaller = { DIGIT_TYPE_MAX }, .larger = DIGIT_BASE },
            {
                .smaller = { 0, 1 },
                .larger  = std::numeric_limits<std::uintmax_t>::max()
            },
            {
                .smaller = { DIGIT_TYPE_MAX - 1, DIGIT_TYPE_MAX },
                .larger  = std::numeric_limits<std::uintmax_t>::max()
            }
        }
    )
);

using UnsignedIntegralSmallerThanDigitsTestParam = InequalityTestParam<
    std::uintmax_t, std::vector<digit_type>
>;

class UnsignedIntegralSmallerThanDigitsTest
    : public ::testing::TestWithParam<UnsignedIntegralSmallerThanDigitsTestParam>
{}; // class UnsignedIntegralSmallerThanDigitsTest

TEST_P(UnsignedIntegralSmallerThanDigitsTest,
       SmallerPositiveLhsIsLessThanLargerPositiveRhs)
{
    std::uintmax_t lesser = GetParam().smaller;
    Integer greater = { .sign = Sign::POSITIVE, .digits = GetParam().larger };

    comparison_test_common::expect_unequal(lesser, greater);
}

TEST_P(UnsignedIntegralSmallerThanDigitsTest,
       LargerNegativeLhsIsLessThanSmallerPositiveRhs)
{
    Integer lesser = { .sign = Sign::NEGATIVE, .digits = GetParam().larger };
    std::uintmax_t greater = GetParam().smaller;

    comparison_test_common::expect_unequal(lesser, greater);
}

INSTANTIATE_TEST_SUITE_P(
    IntegerComparisonTest,
    UnsignedIntegralSmallerThanDigitsTest,
    ::testing::ValuesIn(
        std::vector<UnsignedIntegralSmallerThanDigitsTestParam> {
            { .smaller = 0,              .larger = { 1 } },
            { .smaller = 1,              .larger = { 0, 1 } },
            { .smaller = DIGIT_TYPE_MAX, .larger = { 0, 1 } },
            {
                .smaller = std::numeric_limits<std::uintmax_t>::max(),
                .larger  = { 0, 0, 1 }
            }
        }
    )
);


TEST(DigitsSameAsSignedIntegralTest, ZeroEqualToZero)
{
    std::intmax_t lhs = 0;
    Integer       rhs = { .sign = Sign::ZERO, .digits = { 0 } };

    comparison_test_common::expect_equal(lhs, rhs);
}

class DigitsSameAsPositiveSignedIntegralTest
    : public ::testing::TestWithParam<std::intmax_t>
{}; // class DigitsSameAsPositiveSignedIntegralTest

TEST_P(DigitsSameAsPositiveSignedIntegralTest,
       PositiveSignedIntegralEqualToPositiveInteger)
{
    std::intmax_t lhs = GetParam();
    Integer       rhs = integer_from_signed_integral(lhs);

    comparison_test_common::expect_equal(lhs, rhs);
}

TEST_P(DigitsSameAsPositiveSignedIntegralTest,
       NegativeIntegerLessThanPositiveSignedIntegral)
{
    std::intmax_t  greater = GetParam();
    Integer        lesser  = {
        .sign   = Sign::NEGATIVE,
        .digits = digits_from_integral(greater)
    };

    comparison_test_common::expect_unequal(lesser, greater);
}

INSTANTIATE_TEST_SUITE_P(
    IntegerComparisonTest,
    DigitsSameAsPositiveSignedIntegralTest,
    tasty_int_test::logarithmic_range<std::intmax_t>(
        1, std::numeric_limits<std::intmax_t>::max(), 2
    )
);

class DigitsSameAsNegativeSignedIntegralTest
    : public ::testing::TestWithParam<std::intmax_t>
{}; // class DigitsSameAsNegativeSignedIntegralTest

TEST_P(DigitsSameAsNegativeSignedIntegralTest,
       NegativeSignedIntegralEqualToNegativeInteger)
{
    std::intmax_t lhs = GetParam();
    Integer       rhs = integer_from_signed_integral(lhs);

    comparison_test_common::expect_equal(lhs, rhs);
}

TEST_P(DigitsSameAsNegativeSignedIntegralTest,
       NegativeSignedIntegralLessThanPositiveInteger)
{
    std::intmax_t  lesser  = GetParam();
    Integer        greater = {
        .sign   = Sign::POSITIVE,
        .digits = digits_from_integral(-lesser)
    };

    comparison_test_common::expect_unequal(lesser, greater);
}

INSTANTIATE_TEST_SUITE_P(
    IntegerComparisonTest,
    DigitsSameAsNegativeSignedIntegralTest,
    tasty_int_test::logarithmic_range<std::intmax_t>(
        -1, std::numeric_limits<std::intmax_t>::lowest(), 2
    )
);

using DigitsSmallerThanPositiveSignedIntegralTestParam = InequalityTestParam<
    std::vector<digit_type>, std::intmax_t
>;

class DigitsSmallerThanPositiveSignedIntegralTest
    : public ::testing::TestWithParam<
          DigitsSmallerThanPositiveSignedIntegralTestParam
      >
{}; // class DigitsSmallerThanPositiveSignedIntegralTest

TEST_P(DigitsSmallerThanPositiveSignedIntegralTest,
       SmallerNonnegativeLhsIsLessThanLargerPositiveRhs)
{
    Integer lesser        = {
        .sign   = sign_from_digits(GetParam().smaller,
                                   Sign::POSITIVE),
        .digits = GetParam().smaller
    };
    std::intmax_t greater = GetParam().larger;

    comparison_test_common::expect_unequal(lesser, greater);
}

TEST_P(DigitsSmallerThanPositiveSignedIntegralTest,
       SmallerNonpositiveLhsIsLessThanLargerPositiveRhs)
{
    Integer lesser         = {
        .sign   = sign_from_digits(GetParam().smaller,
                                   Sign::NEGATIVE),
        .digits = GetParam().smaller
    };
    std::intmax_t greater = GetParam().larger;

    comparison_test_common::expect_unequal(lesser, greater);
}

INSTANTIATE_TEST_SUITE_P(
    IntegerComparisonTest,
    DigitsSmallerThanPositiveSignedIntegralTest,
    ::testing::ValuesIn(
        std::vector<DigitsSmallerThanPositiveSignedIntegralTestParam> {
            { .smaller = { 0 },              .larger = 1 },
            { .smaller = { 1 },              .larger = DIGIT_BASE },
            { .smaller = { DIGIT_TYPE_MAX }, .larger = DIGIT_BASE },
            {
                .smaller = { 0, 1 },
                .larger  = std::numeric_limits<std::intmax_t>::max()
            },
            {
                .smaller = { DIGIT_TYPE_MAX, 1 },
                .larger  = std::numeric_limits<std::intmax_t>::max()
            }
        }
    )
);

using DigitsSmallerThanNegativeSignedIntegralTestParam = InequalityTestParam<
    std::vector<digit_type>, std::intmax_t
>;

class DigitsSmallerThanNegativeSignedIntegralTest
    : public ::testing::TestWithParam<
          DigitsSmallerThanNegativeSignedIntegralTestParam
      >
{}; // class DigitsSmallerThanNegativeSignedIntegralTest

TEST_P(DigitsSmallerThanNegativeSignedIntegralTest,
       LargerNegativeLhsIsLessThanSmallerNonpositiveRhs)
{
    std::intmax_t lesser = GetParam().larger;
    Integer greater      = {
        .sign   = sign_from_digits(GetParam().smaller,
                                   Sign::NEGATIVE),
        .digits = GetParam().smaller
    };

    comparison_test_common::expect_unequal(lesser, greater);
}

TEST_P(DigitsSmallerThanNegativeSignedIntegralTest,
       LargerNegativeLhsIsLessThanSmallerNonnegativeRhs)
{
    std::intmax_t lesser = GetParam().larger;
    Integer greater      = {
        .sign   = sign_from_digits(GetParam().smaller,
                                   Sign::POSITIVE),
        .digits = GetParam().smaller
    };

    comparison_test_common::expect_unequal(lesser, greater);
}

INSTANTIATE_TEST_SUITE_P(
    IntegerComparisonTest,
    DigitsSmallerThanNegativeSignedIntegralTest,
    ::testing::ValuesIn(
        std::vector<DigitsSmallerThanNegativeSignedIntegralTestParam> {
            { .smaller = { 0 }, .larger = -1 },
            {
                .smaller = { 1 },
                .larger  = -static_cast<std::intmax_t>(DIGIT_BASE)
            },
            {
                .smaller = { DIGIT_TYPE_MAX },
                .larger  = -static_cast<std::intmax_t>(DIGIT_BASE)
            },
            {
                .smaller = { 0, 1 },
                .larger  = std::numeric_limits<std::intmax_t>::lowest()
            },
            {
                .smaller = { DIGIT_TYPE_MAX, 1 },
                .larger  = std::numeric_limits<std::intmax_t>::lowest()
            }
        }
    )
);

using PositiveSignedIntegralSmallerThanDigitsTestParam = InequalityTestParam<
    std::intmax_t, std::vector<digit_type>
>;

class PositiveSignedIntegralSmallerThanDigitsTest
    : public ::testing::TestWithParam<
          PositiveSignedIntegralSmallerThanDigitsTestParam
      >
{}; // class PositiveSigSmallerThantegralLessThanDigitsTest

TEST_P(PositiveSignedIntegralSmallerThanDigitsTest,
       SmallerNonnegativeLhsIsLessThanLargerPositiveRhs)
{
    std::intmax_t lesser = GetParam().smaller;
    Integer greater = { .sign = Sign::POSITIVE, .digits = GetParam().larger };

    comparison_test_common::expect_unequal(lesser, greater);
}

TEST_P(PositiveSignedIntegralSmallerThanDigitsTest,
       LargerNegativeLhsIsLessThanSmallerNonnegativeRhs)
{
    Integer lesser = { .sign = Sign::NEGATIVE, .digits = GetParam().larger };
    std::intmax_t greater = GetParam().smaller;

    comparison_test_common::expect_unequal(lesser, greater);
}

INSTANTIATE_TEST_SUITE_P(
    IntegerComparisonTest,
    PositiveSignedIntegralSmallerThanDigitsTest,
    ::testing::ValuesIn(
        std::vector<PositiveSignedIntegralSmallerThanDigitsTestParam> {
            { .smaller = 0,              .larger = { 1 } },
            { .smaller = 1,              .larger = { 0, 1 } },
            { .smaller = DIGIT_TYPE_MAX, .larger = { 0, 1 } },
            {
                .smaller = std::numeric_limits<std::intmax_t>::max(),
                .larger  = { DIGIT_TYPE_MAX, DIGIT_TYPE_MAX }
            },
            {
                .smaller = std::numeric_limits<std::intmax_t>::max(),
                .larger  = { 0, 0, 1 }
            }
        }
    )
);

using NegativeSignedIntegralSmallerThanDigitsTestParam = InequalityTestParam<
    std::intmax_t, std::vector<digit_type> 
>;

class NegativeSignedIntegralSmallerThanDigitsTest
    : public ::testing::TestWithParam<
          NegativeSignedIntegralSmallerThanDigitsTestParam
      >
{}; // class NegativeSignedIntegralSmallerThanDigitsTest

TEST_P(NegativeSignedIntegralSmallerThanDigitsTest,
       LargerNegativeLhsIsLessThanSmallerNonpositiveRhs)
{
    Integer lesser       = {
        .sign   = Sign::NEGATIVE,
        .digits = GetParam().larger
    };
    std::intmax_t greater = GetParam().smaller;

    comparison_test_common::expect_unequal(lesser, greater);
}

TEST_P(NegativeSignedIntegralSmallerThanDigitsTest,
       SmallerNonpositiveLhsIsLessThanLargerPositiveRhs)
{
    std::intmax_t lesser = GetParam().smaller;
    Integer greater      = {
        .sign   = Sign::POSITIVE,
        .digits = GetParam().larger
    };

    comparison_test_common::expect_unequal(lesser, greater);
}

INSTANTIATE_TEST_SUITE_P(
    IntegerComparisonTest,
    NegativeSignedIntegralSmallerThanDigitsTest,
    ::testing::ValuesIn(
        std::vector<NegativeSignedIntegralSmallerThanDigitsTestParam> {
            { .smaller = 0, .larger = { 1 } },
            {
                .smaller = -1,
                .larger  = { DIGIT_TYPE_MAX }
            },
            {
                .smaller = -static_cast<std::intmax_t>(DIGIT_TYPE_MAX),
                .larger  = { 0, 1 }
            },
            {
                .smaller = -static_cast<std::intmax_t>(DIGIT_BASE),
                .larger  = { 1 , 1 }
            },
            {
                .smaller = std::numeric_limits<std::intmax_t>::lowest(),
                .larger  = { 0, 0, 1 }
            }
        }
    )
);

} // namespace
