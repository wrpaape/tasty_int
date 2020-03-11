#include "tasty_int/detail/floating_point_digits_iterator.hpp"

#include <cmath>
#include <cstddef>

#include <iterator>
#include <limits>
#include <type_traits>

#include "gtest/gtest.h"

#include "tasty_int/detail/digit_from_nonnegative_value.hpp"
#include "tasty_int_test/logarithmic_range.hpp"


namespace {

using tasty_int::detail::FloatingPointDigitsIterator;
using tasty_int::detail::digit_from_nonnegative_value;
using tasty_int::detail::DIGIT_BASE;
using tasty_int::detail::digit_type;


class FloatingPointDigitsIteratorTest
    : public ::testing::TestWithParam<long double>
{
protected:
    static long double
    different_by_at_least_one(long double value);
}; // class FloatingPointDigitsIteratorTest

long double
FloatingPointDigitsIteratorTest::different_by_at_least_one(long double value)
{
    long double step            = (value / 2.0L) + 1.0L;
    long double sign            = (value > 1.0L) ? -1.0L : +1.0L;
    long double different_value = value + (step * sign);

    return different_value;
}

TEST_P(FloatingPointDigitsIteratorTest, IteratorCategoryEqualToInputIteratorTag)
{
    bool expected = std::is_same_v<
        std::input_iterator_tag, FloatingPointDigitsIterator::iterator_category
    >;
    EXPECT_TRUE(expected);
}

TEST_P(FloatingPointDigitsIteratorTest, ValueTypeEqualToDigitType)
{
    bool expected = std::is_same_v<
        digit_type, FloatingPointDigitsIterator::value_type
    >;
    EXPECT_TRUE(expected);
}

TEST_P(FloatingPointDigitsIteratorTest, ReferenceEqualToDigitType)
{
    bool expected = std::is_same_v<
        digit_type, FloatingPointDigitsIterator::reference
    >;
    EXPECT_TRUE(expected);
}

TEST_P(FloatingPointDigitsIteratorTest, PointerEqualToPointerToDigitType)
{
    bool expected = std::is_same_v<
        digit_type *, FloatingPointDigitsIterator::pointer
    >;
    EXPECT_TRUE(expected);
}

TEST_P(FloatingPointDigitsIteratorTest, DifferenceTypeEqualToPtrDiffT)
{
    bool expected = std::is_same_v<
        std::ptrdiff_t, FloatingPointDigitsIterator::difference_type
    >;
    EXPECT_TRUE(expected);
}

TEST_P(FloatingPointDigitsIteratorTest, DeferenceOperatorReturnsNextDigit)
{
    long double value = GetParam();
    FloatingPointDigitsIterator iter(value);

    EXPECT_EQ(digit_from_nonnegative_value(value), *iter);
}

TEST_P(FloatingPointDigitsIteratorTest, PreIncrementAdvances)
{
    long double value = GetParam();
    FloatingPointDigitsIterator iter(value);

    ++iter;

    EXPECT_EQ(digit_from_nonnegative_value(value / DIGIT_BASE), *iter);
}

TEST_P(FloatingPointDigitsIteratorTest, PreIncrementReturnsReferenceToSelf)
{
    long double value = GetParam();
    FloatingPointDigitsIterator iter(value);
    const FloatingPointDigitsIterator* iter_instance = &iter;

    EXPECT_EQ(iter_instance, &++iter);
}

TEST_P(FloatingPointDigitsIteratorTest, PostIncrementAdvances)
{
    long double value = GetParam();
    FloatingPointDigitsIterator iter(value);

    iter++;

    EXPECT_EQ(digit_from_nonnegative_value(value / DIGIT_BASE), *iter);
}

TEST_P(FloatingPointDigitsIteratorTest, PostIncrementReturnsCopyOfOriginalValue)
{
    long double value = GetParam();
    FloatingPointDigitsIterator iter(value);
    FloatingPointDigitsIterator original_iter = iter;

    EXPECT_EQ(original_iter, iter++);
}

TEST_P(FloatingPointDigitsIteratorTest,
       IteratorsToTheSameDigitsSequenceAreEqual)
{
    long double value             = GetParam();
    long double same_digits_value = std::floor(value);
    FloatingPointDigitsIterator iter(value);
    FloatingPointDigitsIterator same_digits_iter(same_digits_value);

    EXPECT_TRUE(iter == same_digits_iter);
}

TEST_P(FloatingPointDigitsIteratorTest,
       IteratorsToTheSameDigitsSequenceAreNotUnequal)
{
    long double value             = GetParam();
    long double same_digits_value = std::floor(value);
    FloatingPointDigitsIterator iter(value);
    FloatingPointDigitsIterator same_digits_iter(same_digits_value);

    EXPECT_FALSE(iter != same_digits_iter);
}

TEST_P(FloatingPointDigitsIteratorTest,
       IteratorsToDifferentDigitsSequencesAreNotEqual)
{
    long double value                  = GetParam();
    long double different_digits_value = different_by_at_least_one(value);
    FloatingPointDigitsIterator iter(value);
    FloatingPointDigitsIterator different_digits_iter(different_digits_value);

    EXPECT_FALSE(iter == different_digits_iter);
}

TEST_P(FloatingPointDigitsIteratorTest,
       IteratorsToDifferentDigitsSequenceAreUnequal)
{
    long double value                  = GetParam();
    long double different_digits_value = different_by_at_least_one(value);
    FloatingPointDigitsIterator iter(value);
    FloatingPointDigitsIterator different_digits_iter(different_digits_value);

    EXPECT_TRUE(iter != different_digits_iter);
}

TEST_P(FloatingPointDigitsIteratorTest,
       RemainingValueInitiallyEqualsOriginalValue)
{
    long double value = GetParam();
    FloatingPointDigitsIterator iter(value);

    EXPECT_EQ(value, iter.remaining_value());
}

TEST_P(FloatingPointDigitsIteratorTest,
       RemainingValueAfterIncrementEqualsOriginalValueDividedbyDigitBase)
{
    long double value = GetParam();
    FloatingPointDigitsIterator iter(value);

    ++iter;

    EXPECT_EQ(value / DIGIT_BASE, iter.remaining_value());
}

TEST_P(FloatingPointDigitsIteratorTest, PreIncrementTraversal)
{
    long double value = GetParam();
    FloatingPointDigitsIterator iter(value);
    do {
        digit_type expected_digit = digit_from_nonnegative_value(value);
        value /= DIGIT_BASE;

        ASSERT_EQ(expected_digit, *iter);

        ++iter;

    } while (value >= 1.0L);
}

TEST_P(FloatingPointDigitsIteratorTest, PostIncrementTraversal)
{
    long double value = GetParam();
    FloatingPointDigitsIterator iter(value);
    do {
        digit_type expected_digit = digit_from_nonnegative_value(value);
        value /= DIGIT_BASE;

        ASSERT_EQ(expected_digit, *iter);

        iter++;

    } while (value >= 1.0L);
}

INSTANTIATE_TEST_SUITE_P(
    FloatingPointDigitsIteratorTest,
    FloatingPointDigitsIteratorTest,
    tasty_int_test::logarithmic_range<long double>(
        0.0L, std::numeric_limits<long double>::max(), 1.0e20
    )
);

} // namespace
