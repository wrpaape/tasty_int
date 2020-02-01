#include "tasty_int_test/logarithmic_range_values.hpp"

#include <sstream>
#include <type_traits>

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
    requires std::is_arithmetic_v<T>
class LogarithmicRangeValuesTest : public ::testing::Test
{
}; // class LogarithmicRangeValuesTest

TYPED_TEST_SUITE_P(LogarithmicRangeValuesTest);

TYPED_TEST_P(LogarithmicRangeValuesTest, ThrowsIfScaleIsLessThanOne)
{
    TypeParam first(0);
    TypeParam last(1);
    TypeParam scale(0);

    try {
        (void) tasty_int_test::logarithmic_range_values<TypeParam>(
            first, last, scale
        );
        FAIL() << "did not throw expected std::invalid_argument";

    } catch (const std::invalid_argument &exception) {
        std::ostringstream expected_message;
        expected_message <<
            "tasty_int_test::logarithmic_range_values - scale ("
            << make_printable(scale) << ") <= 1.";
        EXPECT_EQ(expected_message.str(), exception.what());
    }
}

TYPED_TEST_P(LogarithmicRangeValuesTest, ThrowsIfScaleIsEqualToOne)
{
    TypeParam first(0);
    TypeParam last(1);
    TypeParam scale(1);

    try {
        (void) tasty_int_test::logarithmic_range_values<TypeParam>(
            first, last, scale
        );
        FAIL() << "did not throw expected std::invalid_argument";

    } catch (const std::invalid_argument &exception) {
        std::ostringstream expected_message;
        expected_message <<
            "tasty_int_test::logarithmic_range_values - scale ("
            << make_printable(scale) << ") <= 1.";
        EXPECT_EQ(expected_message.str(), exception.what());
    }
}

TYPED_TEST_P(LogarithmicRangeValuesTest, SingleValueIfFirstEqualsLast)
{
    TypeParam first(0);
    TypeParam last(first);
    TypeParam scale(2);

    std::vector<TypeParam> expected_values = { first };
    EXPECT_EQ(
        expected_values,
        tasty_int_test::logarithmic_range_values<TypeParam>(
            first, last, scale
        )
    );
}

TYPED_TEST_P(LogarithmicRangeValuesTest,
             NoAscendingIntermediateValuesIfScaleEqualToAbsDelta)
{
    TypeParam first(0);
    TypeParam last(10);
    TypeParam scale(last - first);

    std::vector<TypeParam> expected_values = { first, last };
    EXPECT_EQ(
        expected_values,
        tasty_int_test::logarithmic_range_values<TypeParam>(
            first, last, scale
        )
    );
}

TYPED_TEST_P(LogarithmicRangeValuesTest,
             NoDescendingIntermediateValuesIfScaleEqualToAbsDelta)
{
    TypeParam first(0);
    TypeParam last(-10);
    TypeParam scale(first - last);

    std::vector<TypeParam> expected_values = { first, last };
    EXPECT_EQ(
        expected_values,
        tasty_int_test::logarithmic_range_values<TypeParam>(
            first, last, scale
        )
    );
}

TYPED_TEST_P(LogarithmicRangeValuesTest,
             NoAscendingIntermediateValuesIfScaleGreaterThanAbsDelta)
{
    TypeParam first(0);
    TypeParam last(10);
    TypeParam scale(last + 1 - first);

    std::vector<TypeParam> expected_values = { first, last };
    EXPECT_EQ(
        expected_values,
        tasty_int_test::logarithmic_range_values<TypeParam>(
            first, last, scale
        )
    );
}

TYPED_TEST_P(LogarithmicRangeValuesTest,
             NoDescendingIntermediateValuesIfScaleGreaterThanAbsDelta)
{
    TypeParam first(0);
    TypeParam last(-10);
    TypeParam scale(first + 1 - last);

    std::vector<TypeParam> expected_values = { first, last };
    EXPECT_EQ(
        expected_values,
        tasty_int_test::logarithmic_range_values<TypeParam>(
            first, last, scale
        )
    );
}

TYPED_TEST_P(LogarithmicRangeValuesTest,
             AscendingIntermediateValuesIfScaleLessThanAbsDelta)
{
    TypeParam first(-10);
    TypeParam last(100);
    TypeParam scale(2);

    std::vector<TypeParam> expected_values = {
        first,
        static_cast<TypeParam>(first + scale),
        static_cast<TypeParam>(first + scale * scale),
        static_cast<TypeParam>(first + scale * scale * scale),
        static_cast<TypeParam>(first + scale * scale * scale * scale),
        static_cast<TypeParam>(first + scale * scale * scale * scale * scale),
        last
    };
    EXPECT_EQ(
        expected_values,
        tasty_int_test::logarithmic_range_values<TypeParam>(
            first, last, scale
        )
    );
}

TYPED_TEST_P(LogarithmicRangeValuesTest,
             DescendingIntermediateValuesIfScaleLessThanAbsDelta)
{
    TypeParam first(+10);
    TypeParam last(-100);
    TypeParam scale(2);

    std::vector<TypeParam> expected_values = {
        first,
        static_cast<TypeParam>(first - scale),
        static_cast<TypeParam>(first - scale * scale),
        static_cast<TypeParam>(first - scale * scale * scale),
        static_cast<TypeParam>(first - scale * scale * scale * scale),
        static_cast<TypeParam>(first - scale * scale * scale * scale * scale),
        last
    };
    EXPECT_EQ(
        expected_values,
        tasty_int_test::logarithmic_range_values<TypeParam>(
            first, last, scale
        )
    );
}

REGISTER_TYPED_TEST_SUITE_P(
    LogarithmicRangeValuesTest,
    ThrowsIfScaleIsLessThanOne,
    ThrowsIfScaleIsEqualToOne,
    SingleValueIfFirstEqualsLast,
    NoAscendingIntermediateValuesIfScaleEqualToAbsDelta,
    NoDescendingIntermediateValuesIfScaleEqualToAbsDelta,
    NoAscendingIntermediateValuesIfScaleGreaterThanAbsDelta,
    NoDescendingIntermediateValuesIfScaleGreaterThanAbsDelta,
    AscendingIntermediateValuesIfScaleLessThanAbsDelta,
    DescendingIntermediateValuesIfScaleLessThanAbsDelta
);

using LogarithmicRangeValuesTestTypes = ::testing::Types<
    float, double, long double,
    signed char, signed short, signed int, signed long, signed long long
>;

INSTANTIATE_TYPED_TEST_SUITE_P(LogarithmicRangeValuesTest,
                               LogarithmicRangeValuesTest,
                               LogarithmicRangeValuesTestTypes);

} // namespace
