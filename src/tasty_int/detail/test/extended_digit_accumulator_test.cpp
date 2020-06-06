#include "tasty_int/detail/extended_digit_accumulator.hpp"

#include <limits>
#include <utility>

#include "gtest/gtest.h"

#include "tasty_int/detail/test/comparison_test_common.hpp"
#include "tasty_int_test/comparison_tests.hpp"


namespace {

using tasty_int::detail::ExtendedDigitAccumulator;
using tasty_int::detail::IntegralDigitsView;
using tasty_int::detail::digit_accumulator_type;
using tasty_int::detail::digit_type;
using tasty_int::detail::DIGIT_TYPE_BITS;
using tasty_int::detail::DIGIT_BASE;
using tasty_int::detail::DIGIT_TYPE_MAX;
using comparison_test_common::InequalityTestParam;


std::ostream &
operator<<(std::ostream       &output,
           IntegralDigitsView  view)
{
    return output << view.value();
}

std::ostream &
operator<<(std::ostream             &output,
           ExtendedDigitAccumulator  accumulator)
{
    return output << "{ " << accumulator.low_digit()
                  << ", " << accumulator.middle_digit()
                  << ", " << accumulator.high_digit()
                  << " }"
                    "/{ " << accumulator.front()
                  << ", " << accumulator.back()
                  << " }";
}


TEST(ExtendedDigitAccumulatorTest, DigitAccesors)
{
    ExtendedDigitAccumulator accumulator = {{
        1 | (digit_accumulator_type(2) << DIGIT_TYPE_BITS), 3
    }};

    EXPECT_EQ(1, accumulator.low_digit());
    EXPECT_EQ(2, accumulator.middle_digit());
    EXPECT_EQ(3, accumulator.high_digit());
}

TEST(ExtendedDigitAccumulatorTest, DigitsSizeOfZeroIsOne)
{
    ExtendedDigitAccumulator accumulator = {{ 0 }};

    EXPECT_EQ(1, accumulator.digits_size());
}

TEST(ExtendedDigitAccumulatorTest, DigitsSizeOfNonzeroDigitIsOne)
{
    ExtendedDigitAccumulator accumulator = {{ DIGIT_TYPE_MAX }};

    EXPECT_EQ(1, accumulator.digits_size());
}

TEST(ExtendedDigitAccumulatorTest, DigitsSizeOfTwoDigitsIsTwo)
{
    ExtendedDigitAccumulator accumulator = {{ DIGIT_BASE }};

    EXPECT_EQ(2, accumulator.digits_size());
}

TEST(ExtendedDigitAccumulatorTest, DigitsSizeOfThreeDigitsIsThree)
{
    ExtendedDigitAccumulator accumulator = {{
        std::numeric_limits<digit_accumulator_type>::max(), 1
    }};

    EXPECT_EQ(3, accumulator.digits_size());
}

TEST(ExtendedDigitAccumulatorTest, MultiplyDigitsBaseForZero)
{
    ExtendedDigitAccumulator accumulator = {{ 0 }};

    accumulator.multiply_digit_base();

    EXPECT_EQ(1, accumulator.digits_size());
    EXPECT_EQ(0, accumulator.front());
}

TEST(ExtendedDigitAccumulatorTest, MultiplyDigitsBaseForNonzeroDigit)
{
    ExtendedDigitAccumulator accumulator = {{ 7 }};

    accumulator.multiply_digit_base();

    EXPECT_EQ(2, accumulator.digits_size());
    EXPECT_EQ(0, accumulator.low_digit());
    EXPECT_EQ(7, accumulator.middle_digit());
}

TEST(ExtendedDigitAccumulatorTest, MultiplyDigitsBaseForTwoDigits)
{
    ExtendedDigitAccumulator accumulator = {{ DIGIT_BASE }};

    accumulator.multiply_digit_base_accumulate(0);

    EXPECT_EQ(3, accumulator.digits_size());
    EXPECT_EQ(0, accumulator.low_digit());
    EXPECT_EQ(0, accumulator.middle_digit());
    EXPECT_EQ(1, accumulator.high_digit());
}

TEST(ExtendedDigitAccumulatorTest, MultiplyDigitsBaseAccumulateForZero)
{
    ExtendedDigitAccumulator accumulator = {{ 0 }};

    accumulator.multiply_digit_base_accumulate(11);

    EXPECT_EQ( 1, accumulator.digits_size());
    EXPECT_EQ(11, accumulator.low_digit());
}

TEST(ExtendedDigitAccumulatorTest, MultiplyDigitsBaseAccumulateForNonzeroDigit)
{
    ExtendedDigitAccumulator accumulator = {{ 9 }};

    accumulator.multiply_digit_base_accumulate(13);

    EXPECT_EQ( 2, accumulator.digits_size());
    EXPECT_EQ(13, accumulator.low_digit());
    EXPECT_EQ( 9, accumulator.middle_digit());
}

TEST(ExtendedDigitAccumulatorTest, MultiplyDigitsBaseAccumulateForTwoDigits)
{
    ExtendedDigitAccumulator accumulator = {
        { std::numeric_limits<digit_accumulator_type>::max() }
    };

    accumulator.multiply_digit_base_accumulate(3);

    EXPECT_EQ(             3, accumulator.digits_size());
    EXPECT_EQ(             3, accumulator.low_digit());
    EXPECT_EQ(DIGIT_TYPE_MAX, accumulator.middle_digit());
    EXPECT_EQ(DIGIT_TYPE_MAX, accumulator.high_digit());
}


class ExtendedDigitAccumulatorEqualityTest
    : public ::testing::TestWithParam<ExtendedDigitAccumulator>
{}; // class ExtendedDigitAccumulatorEqualityTest

TEST_P(ExtendedDigitAccumulatorEqualityTest, TestEquality)
{
    auto lhs = GetParam();
    auto rhs = lhs;

    tasty_int_test::expect_equal(lhs, rhs);
}

INSTANTIATE_TEST_SUITE_P(
    ExtendedDigitAccumulatorTest,
    ExtendedDigitAccumulatorEqualityTest,
    ::testing::ValuesIn(
        std::vector<ExtendedDigitAccumulator> {
            {{ 0 }},
            {{ 1 }},
            {{ DIGIT_TYPE_MAX }},
            {{ DIGIT_BASE }},
            {{ DIGIT_BASE >> (DIGIT_TYPE_BITS - 1) }},
            {{ std::numeric_limits<digit_accumulator_type>::max() }},
            {{ 0, 1 }},
            {{ 1, 1 }},
            {{ DIGIT_TYPE_MAX, 1 }},
            {{ std::numeric_limits<digit_accumulator_type>::max(), 1 }},
            {{ 0, DIGIT_TYPE_MAX }},
            {{ 1, DIGIT_TYPE_MAX }},
            {{ DIGIT_TYPE_MAX, DIGIT_TYPE_MAX }},
            {{
                std::numeric_limits<digit_accumulator_type>::max(),
                DIGIT_TYPE_MAX
            }}
        }
    )
);

using ExtendedDigitAccumulatorInequalityTestParam =
    InequalityTestParam<ExtendedDigitAccumulator, ExtendedDigitAccumulator>;

class ExtendedDigitAccumulatorInequalityTest
    : public ::testing::TestWithParam<
          ExtendedDigitAccumulatorInequalityTestParam
      >
{}; // class ExtendedDigitAccumulatorInequalityTest

TEST_P(ExtendedDigitAccumulatorInequalityTest, TestInequality)
{
    auto smaller = GetParam().smaller;
    auto larger  = GetParam().larger;

    tasty_int_test::expect_unequal(smaller, larger);
}

INSTANTIATE_TEST_SUITE_P(
    ExtendedDigitAccumulatorTest,
    ExtendedDigitAccumulatorInequalityTest,
    ::testing::ValuesIn(
        std::vector<ExtendedDigitAccumulatorInequalityTestParam> {
            { .smaller = {{ 0 }},          .larger = {{ 1 }} },
            { .smaller = {{ 0 }},          .larger = {{ DIGIT_BASE }} },
            { .smaller = {{ 0 }},          .larger = {{ 0, 1 }} },
            { .smaller = {{ 1 }},          .larger = {{ 2 }} },
            { .smaller = {{ 1 }},          .larger = {{ DIGIT_BASE }} },
            { .smaller = {{ 1 }},          .larger = {{ 0, 1 }} },
            { .smaller = {{ DIGIT_BASE }}, .larger = {{ DIGIT_BASE * 2 }} },
            { .smaller = {{ DIGIT_BASE }}, .larger = {{ 0, 1 }} },
            { .smaller = {{ 0, 1 }},       .larger = {{ 1, 1 }} },
            { .smaller = {{ 0, 1 }},       .larger = {{ 0, 2 }} },
            { .smaller = {{ 1, 1 }},       .larger = {{ 0, 2 }} }
        }
    )
);


struct ExtendedDigitAccumulatorMultiplicationTestParam
{
    IntegralDigitsView       multiplicand;
    digit_type               multiplier;
    ExtendedDigitAccumulator expected_result;
}; // struct ExtendedDigitAccumulatorMultiplicationTestParam

std::ostream &
operator<<(std::ostream                                          &output,
           const ExtendedDigitAccumulatorMultiplicationTestParam &test_param)
{
    return output << "{ multiplicand="    << test_param.multiplicand
                  << ", multiplier="      << test_param.multiplier
                  << ", expected_result=" << test_param.expected_result
                  << " }";
}

class ExtendedDigitAccumulatorMultiplicationTest
    : public ::testing::TestWithParam< 
          ExtendedDigitAccumulatorMultiplicationTestParam
      >
{}; // class ExtendedDigitAccumulatorMultiplicationTest

TEST_P(ExtendedDigitAccumulatorMultiplicationTest, TestMultiply)
{
    auto multiplicand    = GetParam().multiplicand;
    auto multiplier      = GetParam().multiplier;
    auto expected_result = GetParam().expected_result;

    EXPECT_EQ(expected_result, multiplicand * multiplier);
    EXPECT_EQ(expected_result, multiplier * multiplicand);
}

INSTANTIATE_TEST_SUITE_P(
    ExtendedDigitAccumulatorTest,
    ExtendedDigitAccumulatorMultiplicationTest,
    ::testing::ValuesIn(
        std::vector<ExtendedDigitAccumulatorMultiplicationTestParam> {
            {
                .multiplicand    = 0,
                .multiplier      = 0,
                .expected_result = {{ 0 }}
            },
            {
                .multiplicand    = 0,
                .multiplier      = DIGIT_TYPE_MAX,
                .expected_result = {{ 0 }}
            },
            {
                .multiplicand    = std::numeric_limits<std::uintmax_t>::max(),
                .multiplier      = 0,
                .expected_result = {{ 0 }}
            },
            {
                .multiplicand    = 1,
                .multiplier      = 1,
                .expected_result = {{ 1 }}
            },
            {
                .multiplicand    = 7,
                .multiplier      = 3,
                .expected_result = {{ 21 }}
            },
            {
                .multiplicand    = DIGIT_TYPE_MAX,
                .multiplier      = 1,
                .expected_result = {{ DIGIT_TYPE_MAX }}
            },
            {
                .multiplicand    = DIGIT_TYPE_MAX,
                .multiplier      = DIGIT_TYPE_MAX,
                .expected_result = {{ DIGIT_TYPE_MAX * DIGIT_TYPE_MAX }}
            },
            {
                .multiplicand    = DIGIT_BASE * (DIGIT_BASE / 2),
                .multiplier      = 2,
                .expected_result = {{ 0, 1 }}
            },
            {
                .multiplicand    = DIGIT_BASE * (DIGIT_BASE / 2) + 1,
                .multiplier      = 4,
                .expected_result = {{ 4, 2 }}
            },
            {
                .multiplicand    = std::numeric_limits<std::uintmax_t>::max(),
                .multiplier      = DIGIT_TYPE_MAX,
                .expected_result = {{
                    1 + (DIGIT_TYPE_MAX << DIGIT_TYPE_BITS), DIGIT_TYPE_MAX - 1
                }}
            }
        }
    )
);


TEST(ExtendedDigitAccumulatorSubtractionTest, MinusEqualsReturnsReferenceToLhs)
{
    ExtendedDigitAccumulator lhs = {{ 0 }};
    IntegralDigitsView       rhs = 0;

    EXPECT_EQ(&lhs, &(lhs -= rhs));
}

template<typename MinuendType>
struct ExtendedDigitAccumulatorSubtractionTestParam
{
    ExtendedDigitAccumulator subtrahend;
    MinuendType              minuend;
    ExtendedDigitAccumulator expected_result;
}; // struct ExtendedDigitAccumulatorSubtractionTestParam

template<typename MinuendType>
std::ostream &
operator<<(
    std::ostream                                                    &output,
    const ExtendedDigitAccumulatorSubtractionTestParam<MinuendType> &test_param
)
{
    return output << "{ subtrahend="      << test_param.subtrahend
                  << ", minuend="         << test_param.minuend
                  << ", expected_result=" << test_param.expected_result
                  << " }";
}

class ExtendedDigitAccumulatorAndExtendedDigitAccumulatorSubtractionTest
    : public ::testing::TestWithParam< 
          ExtendedDigitAccumulatorSubtractionTestParam<ExtendedDigitAccumulator>
      >
{}; // class ExtendedDigitAccumulatorAndExtendedDigitAccumulatorSubtractionTest

TEST_P(ExtendedDigitAccumulatorAndExtendedDigitAccumulatorSubtractionTest,
       TestMinusEquals)
{
    auto subtrahend      = GetParam().subtrahend;
    auto minuend         = GetParam().minuend;
    auto expected_result = GetParam().expected_result;

    subtrahend -= minuend;

    EXPECT_EQ(expected_result, subtrahend);
}

INSTANTIATE_TEST_SUITE_P(
    ExtendedDigitAccumulatorTest,
    ExtendedDigitAccumulatorAndExtendedDigitAccumulatorSubtractionTest,
    ::testing::ValuesIn(
        std::vector<
            ExtendedDigitAccumulatorSubtractionTestParam<
                ExtendedDigitAccumulator
            >
        > {
            {
                .subtrahend      = {{ 0 }},
                .minuend         = {{ 0 }},
                .expected_result = {{ 0 }}
            },
            {
                .subtrahend      = {{ 1 }},
                .minuend         = {{ 1 }},
                .expected_result = {{ 0 }}
            },
            {
                .subtrahend      = {{ 1 }},
                .minuend         = {{ 0 }},
                .expected_result = {{ 1 }}
            },
            {
                .subtrahend      = {{ 2 }},
                .minuend         = {{ 1 }},
                .expected_result = {{ 1 }}
            },
            {
                .subtrahend      = {{ DIGIT_TYPE_MAX + 1 }},
                .minuend         = {{ DIGIT_TYPE_MAX }},
                .expected_result = {{ 1 }}
            },
            {
                .subtrahend      = {{
                    std::numeric_limits<std::uintmax_t>::max()
                }},
                .minuend         = {{ DIGIT_TYPE_MAX }},
                .expected_result = {{ DIGIT_TYPE_MAX << DIGIT_TYPE_BITS }}
            },
            {
                .subtrahend      = {{ 0, 1 }},
                .minuend         = {{ 1 }},
                .expected_result = {{
                    std::numeric_limits<std::uintmax_t>::max()
                }}
            },
            {
                .subtrahend      = {{ 0, 1 }},
                .minuend         = {{
                    std::numeric_limits<std::uintmax_t>::max()
                }},
                .expected_result = {{ 1 }}
            },
            {
                .subtrahend      = {{
                    std::numeric_limits<std::uintmax_t>::max(),
                    DIGIT_TYPE_MAX
                }},
                .minuend         = {{
                    std::numeric_limits<std::uintmax_t>::max()
                }},
                .expected_result = {{ 0, DIGIT_TYPE_MAX }}
            },
            {
                .subtrahend      = {{ 1, 1 }},
                .minuend         = {{ 0, 1 }},
                .expected_result = {{ 1 }}
            },
            {
                .subtrahend      = {{ 1, DIGIT_TYPE_MAX }},
                .minuend         = {{ DIGIT_TYPE_MAX, 1 }},
                .expected_result = {{
                    std::numeric_limits<std::uintmax_t>::max() - DIGIT_TYPE_MAX
                        + 2,
                    DIGIT_TYPE_MAX - 2
                }}
            },
            {
                .subtrahend      = {{
                    std::numeric_limits<std::uintmax_t>::max(),
                    DIGIT_TYPE_MAX
                }},
                .minuend         = {{
                    std::numeric_limits<std::uintmax_t>::max(),
                    DIGIT_TYPE_MAX
                }},
                .expected_result = {{ 0 }}
            }
        }
    )
);

class ExtendedDigitAccumulatorAndIntegralDigitsViewSubtractionTest
    : public ::testing::TestWithParam< 
          ExtendedDigitAccumulatorSubtractionTestParam<IntegralDigitsView>
      >
{}; // class ExtendedDigitAccumulatorAndIntegralDigitsViewSubtractionTest

TEST_P(ExtendedDigitAccumulatorAndIntegralDigitsViewSubtractionTest,
       TestMinusEquals)
{
    auto subtrahend      = GetParam().subtrahend;
    auto minuend         = GetParam().minuend;
    auto expected_result = GetParam().expected_result;

    subtrahend -= minuend;

    EXPECT_EQ(expected_result, subtrahend);
}

INSTANTIATE_TEST_SUITE_P(
    ExtendedDigitAccumulatorTest,
    ExtendedDigitAccumulatorAndIntegralDigitsViewSubtractionTest,
    ::testing::ValuesIn(
        std::vector<
            ExtendedDigitAccumulatorSubtractionTestParam<IntegralDigitsView>
        > {
            {
                .subtrahend      = {{ 0 }},
                .minuend         =    0,
                .expected_result = {{ 0 }}
            },
            {
                .subtrahend      = {{ 1 }},
                .minuend         =    1,
                .expected_result = {{ 0 }}
            },
            {
                .subtrahend      = {{ 1 }},
                .minuend         =    0,
                .expected_result = {{ 1 }}
            },
            {
                .subtrahend      = {{ 2 }},
                .minuend         =    1,
                .expected_result = {{ 1 }}
            },
            {
                .subtrahend      = {{ DIGIT_TYPE_MAX + 1 }},
                .minuend         = DIGIT_TYPE_MAX,
                .expected_result = {{ 1 }}
            },
            {
                .subtrahend      = {{
                    std::numeric_limits<std::uintmax_t>::max()
                }},
                .minuend         = DIGIT_TYPE_MAX,
                .expected_result = {{ DIGIT_TYPE_MAX << DIGIT_TYPE_BITS }}
            },
            {
                .subtrahend      = {{ 0, 1 }},
                .minuend         = 1,
                .expected_result = {{
                    std::numeric_limits<std::uintmax_t>::max()
                }}
            },
            {
                .subtrahend      = {{ 0, 1 }},
                .minuend         = std::numeric_limits<std::uintmax_t>::max(),
                .expected_result = {{ 1 }}
            },
            {
                .subtrahend      = {{
                    std::numeric_limits<std::uintmax_t>::max(),
                    DIGIT_TYPE_MAX
                }},
                .minuend         = std::numeric_limits<std::uintmax_t>::max(),
                .expected_result = {{ 0, DIGIT_TYPE_MAX }}
            }
        }
    )
);


constexpr digit_accumulator_type
top_bits(unsigned int num_bits)
{
    auto bit_shift =
        std::numeric_limits<digit_accumulator_type>::digits - num_bits;

    return std::numeric_limits<digit_accumulator_type>::max() << bit_shift;
}

TEST(ExtendedDigitAccumulatorTest, RightShiftReturnsReferenceToLhs)
{
    ExtendedDigitAccumulator accumulator = {{ 43 }};

    EXPECT_EQ(&accumulator, &(accumulator >>= 10));
}

TEST(ExtendedDigitAccumulatorTest, RightShiftZeroWithZeroBitOffset)
{
    ExtendedDigitAccumulator accumulator     = {{ 0 }};
    ExtendedDigitAccumulator expected_result = accumulator;

    accumulator >>= 0;

    EXPECT_EQ(expected_result, accumulator);
}

TEST(ExtendedDigitAccumulatorTest, RightShiftNonzeroWithZeroBitOffset)
{
    ExtendedDigitAccumulator accumulator     = {{ 1, 2 }};
    ExtendedDigitAccumulator expected_result = accumulator;

    accumulator >>= 0;

    EXPECT_EQ(expected_result, accumulator);
}

TEST(ExtendedDigitAccumulatorTest, RightShiftZeroWithNonzeroBitOffset)
{
    ExtendedDigitAccumulator accumulator     = {{ 0 }};
    ExtendedDigitAccumulator expected_result = accumulator;

    accumulator >>= (DIGIT_TYPE_BITS - 1);

    EXPECT_EQ(expected_result, accumulator);
}

TEST(ExtendedDigitAccumulatorTest,
     RightShiftNonzeroWithNonzeroBitOffsetNoOverlap)
{
    ExtendedDigitAccumulator accumulator     = {{ 16, 32 }};
    ExtendedDigitAccumulator expected_result = {{  2,  4 }};

    accumulator >>= 3;

    EXPECT_EQ(expected_result, accumulator);
}

TEST(ExtendedDigitAccumulatorTest,
     RightShiftNonzeroWithNonzeroBitOffsetWithOneBitOverlap)
{
    ExtendedDigitAccumulator accumulator     = {{ 16, 1 | 32 }};
    ExtendedDigitAccumulator expected_result = {{  8 | top_bits(1), 16 }};

    accumulator >>= 1;

    EXPECT_EQ(expected_result, accumulator);
}

TEST(ExtendedDigitAccumulatorTest,
     RightShiftNonzeroWithNonzeroBitOffsetWithMultipleBitsOverlap)
{
    ExtendedDigitAccumulator accumulator = {{
        std::numeric_limits<std::uintmax_t>::max() ^ top_bits(3),
        DIGIT_TYPE_MAX
    }};
    ExtendedDigitAccumulator expected_result = {{
        std::numeric_limits<std::uintmax_t>::max() ^ (top_bits(3) >> 5),
        DIGIT_TYPE_MAX >> 5

    }};

    accumulator >>= 5;

    EXPECT_EQ(expected_result, accumulator);
}

} // namespace
