#include "tasty_int_test/logarithmic_range_values.hpp"

#include <sstream>

#include "gtest/gtest.h"


namespace {

template<typename T>
auto
make_printable(T value)
    requires std::is_arithmetic_v<T>
{
    return +value; // promote to int if char
}

template<typename T>
class LogarithmicRangeValuesTest : public ::testing::Test
{
}; // class LogarithmicRangeValuesTest

TYPED_TEST_SUITE_P(LogarithmicRangeValuesTest);

TYPED_TEST_P(LogarithmicRangeValuesTest, ThrowsIfMinIsGreaterThanMax)
{
    TypeParam min(1);
    TypeParam max(0);
    TypeParam step(2);

    try {
        (void) tasty_int_test::logarithmic_range_values<TypeParam>(
            min, max, step
        );
        FAIL() << "did not throw expected std::invalid_argument";

    } catch (const std::invalid_argument &exception) {
        std::ostringstream expected_message;
        expected_message <<
                "tasty_int_test::logarithmic_range_values - min ("
             << make_printable(min) << ") > max (" << make_printable(max)
             << ").";
        EXPECT_EQ(expected_message.str(), exception.what());
    }
}

TYPED_TEST_P(LogarithmicRangeValuesTest, ThrowsIfStepIsLessThanOne)
{
    TypeParam min(0);
    TypeParam max(1);
    TypeParam step(0);

    try {
        (void) tasty_int_test::logarithmic_range_values<TypeParam>(
            min, max, step
        );
        FAIL() << "did not throw expected std::invalid_argument";

    } catch (const std::invalid_argument &exception) {
        std::ostringstream expected_message;
        expected_message <<
            "tasty_int_test::logarithmic_range_values - step ("
            << make_printable(step) << ") <= 1.";
        EXPECT_EQ(expected_message.str(), exception.what());
    }
}

TYPED_TEST_P(LogarithmicRangeValuesTest, ThrowsIfStepIsEqualToOne)
{
    TypeParam min(0);
    TypeParam max(1);
    TypeParam step(1);

    try {
        (void) tasty_int_test::logarithmic_range_values<TypeParam>(
            min, max, step
        );
        FAIL() << "did not throw expected std::invalid_argument";

    } catch (const std::invalid_argument &exception) {
        std::ostringstream expected_message;
        expected_message <<
            "tasty_int_test::logarithmic_range_values - step ("
            << make_printable(step) << ") <= 1.";
        EXPECT_EQ(expected_message.str(), exception.what());
    }
}

TYPED_TEST_P(LogarithmicRangeValuesTest, SingleValueIfMinEqualsMax)
{
    TypeParam min(0);
    TypeParam max(min);
    TypeParam step(2);

    std::vector<TypeParam> expected_values = { min };
    EXPECT_EQ(
        expected_values,
        tasty_int_test::logarithmic_range_values<TypeParam>(
            min, max, step
        )
    );
}

TYPED_TEST_P(LogarithmicRangeValuesTest, NoIntermediateValuesIfStepEqualToRange)
{
    TypeParam min(0);
    TypeParam max(10);
    TypeParam step(max - min);

    std::vector<TypeParam> expected_values = { min, max };
    EXPECT_EQ(
        expected_values,
        tasty_int_test::logarithmic_range_values<TypeParam>(
            min, max, step
        )
    );
}

TYPED_TEST_P(LogarithmicRangeValuesTest,
             NoIntermediateValuesIfStepGreaterThanRange)
{
    TypeParam min(0);
    TypeParam max(10);
    TypeParam step(max + 1 - min);

    std::vector<TypeParam> expected_values = { min, max };
    EXPECT_EQ(
        expected_values,
        tasty_int_test::logarithmic_range_values<TypeParam>(
            min, max, step
        )
    );
}

TYPED_TEST_P(LogarithmicRangeValuesTest,
             IntermediateValuesIfStepLessThanRange)
{
    TypeParam min(-10);
    TypeParam max(100);
    TypeParam step(2);

    std::vector<TypeParam> expected_values = {
        min,
        static_cast<TypeParam>(min + step),
        static_cast<TypeParam>(min + step * step),
        static_cast<TypeParam>(min + step * step * step),
        static_cast<TypeParam>(min + step * step * step * step),
        static_cast<TypeParam>(min + step * step * step * step * step),
        max
    };
    EXPECT_EQ(
        expected_values,
        tasty_int_test::logarithmic_range_values<TypeParam>(
            min, max, step
        )
    );
}

REGISTER_TYPED_TEST_SUITE_P(
    LogarithmicRangeValuesTest,
    ThrowsIfMinIsGreaterThanMax,
    ThrowsIfStepIsLessThanOne,
    ThrowsIfStepIsEqualToOne,
    SingleValueIfMinEqualsMax,
    NoIntermediateValuesIfStepEqualToRange,
    NoIntermediateValuesIfStepGreaterThanRange,
    IntermediateValuesIfStepLessThanRange
);

using LogarithmicRangeValuesTestTypes = ::testing::Types<
    float, double, long double,
    char, short, int, long, long long
>;

INSTANTIATE_TYPED_TEST_SUITE_P(LogarithmicRangeValuesTest,
                               LogarithmicRangeValuesTest,
                               LogarithmicRangeValuesTestTypes);

} // namespace
