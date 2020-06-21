#include "tasty_int/tasty_int.hpp"

#include <type_traits>

#include "gtest/gtest.h"

#include "tasty_int_test/arithmetic_types.hpp"
#include "tasty_int_test/check_integer_result.hpp"
#include "tasty_int_test/sample_arithmetic.hpp"
#include "tasty_int_test/signed_arithmetic_types.hpp"


namespace {

using tasty_int::TastyInt;
using tasty_int_test::check_integer_result;
using tasty_int_test::SampleArithmetic;



template<tasty_int::TastyIntOperand DifferenceType,
         tasty_int::TastyIntOperand MinuendType>
void
check_subtract_in_place_result(const DifferenceType &expected_difference,
                               const MinuendType    &result,
                               const MinuendType    &minuend)
{
    EXPECT_EQ(&minuend, &result)
        << "-= did not return reference to minuend";

    check_integer_result(expected_difference, minuend, "-=");
}

template<tasty_int::TastyIntOperand LhsType,
         tasty_int::TastyIntOperand RhsType,
         tasty_int::TastyIntOperand DifferenceType>
void
run_test_subtract_in_place(LhsType              &&lhs,
                           const RhsType         &rhs,
                           const DifferenceType  &expected_difference)
{
    const auto &result = (lhs -= rhs);

    check_subtract_in_place_result(expected_difference, lhs, result);
}

template<tasty_int::TastyIntOperand LhsType,
         tasty_int::TastyIntOperand RhsType,
         tasty_int::TastyIntOperand DifferenceType>
void
test_subtract_in_place(const LhsType        &lhs,
                       const RhsType        &rhs,
                       const DifferenceType &expected_difference)
{
    run_test_subtract_in_place(TastyInt(lhs),
                               rhs,
                               expected_difference);
    run_test_subtract_in_place(LhsType(lhs),
                               TastyInt(rhs),
                               LhsType(expected_difference));
}

template<tasty_int::TastyIntOperand LhsType,
         tasty_int::TastyIntOperand RhsType,
         tasty_int::TastyIntOperand DifferenceType>
void
test_subtract(const LhsType        &lhs,
              const RhsType        &rhs,
              const DifferenceType &expected_difference)
{
    EXPECT_EQ(expected_difference, TastyInt(lhs) - rhs          );
    EXPECT_EQ(expected_difference, lhs           - TastyInt(rhs));
}

template<tasty_int::TastyIntOperand LhsType,
         tasty_int::TastyIntOperand RhsType,
         tasty_int::TastyIntOperand DifferenceType>
void
test_subtraction(const LhsType        &lhs,
                 const RhsType        &rhs,
                 const DifferenceType &expected_difference)
{
    test_subtract_in_place(lhs, rhs, expected_difference);

    test_subtract(lhs, rhs, expected_difference);
}

template<tasty_int::Arithmetic ArithmeticType>
void
test_subtraction(ArithmeticType lhs,
                 ArithmeticType rhs)
{
    auto expected_difference = lhs - rhs;

    test_subtraction(lhs, rhs, expected_difference);
}


template<tasty_int::Arithmetic ArithmeticType>
class TastyIntAndArithmeticTypeSubtractionTest : public ::testing::Test
{}; // class TastyIntAndArithmeticTypeSubtractionTest

TYPED_TEST_SUITE(TastyIntAndArithmeticTypeSubtractionTest,
                 tasty_int_test::ArithmeticTypes);

TYPED_TEST(TastyIntAndArithmeticTypeSubtractionTest, ZeroAndZero)
{
    test_subtraction(SampleArithmetic<TypeParam>::ZERO,
                     SampleArithmetic<TypeParam>::ZERO);
}

TYPED_TEST(TastyIntAndArithmeticTypeSubtractionTest, OneAndOne)
{
    test_subtraction(SampleArithmetic<TypeParam>::ONE,
                     SampleArithmetic<TypeParam>::ONE);
}

TYPED_TEST(TastyIntAndArithmeticTypeSubtractionTest, MinimumAndMinimum)
{
    test_subtraction(SampleArithmetic<TypeParam>::MINIMUM,
                     SampleArithmetic<TypeParam>::MINIMUM);
}

TYPED_TEST(TastyIntAndArithmeticTypeSubtractionTest,
           LowerQuartileAndLowerQuartile)
{
    test_subtraction(SampleArithmetic<TypeParam>::LOWER_QUARTILE,
                     SampleArithmetic<TypeParam>::LOWER_QUARTILE);
}

TYPED_TEST(TastyIntAndArithmeticTypeSubtractionTest,
           UpperQuartileAndUpperQuartile)
{
    test_subtraction(SampleArithmetic<TypeParam>::UPPER_QUARTILE,
                     SampleArithmetic<TypeParam>::UPPER_QUARTILE);
}

TYPED_TEST(TastyIntAndArithmeticTypeSubtractionTest, MaximumAndMaximum)
{
    test_subtraction(SampleArithmetic<TypeParam>::MAXIMUM,
                     SampleArithmetic<TypeParam>::MAXIMUM);
}

TYPED_TEST(TastyIntAndArithmeticTypeSubtractionTest, MaximumAndUpperQuartile)
{
    test_subtraction(SampleArithmetic<TypeParam>::MAXIMUM,
                     SampleArithmetic<TypeParam>::UPPER_QUARTILE);
}

TYPED_TEST(TastyIntAndArithmeticTypeSubtractionTest, MaximumAndMedian)
{
    test_subtraction(SampleArithmetic<TypeParam>::MAXIMUM,
                     SampleArithmetic<TypeParam>::MEDIAN);
}

TYPED_TEST(TastyIntAndArithmeticTypeSubtractionTest, UpperQuartileAndMedian)
{
    test_subtraction(SampleArithmetic<TypeParam>::UPPER_QUARTILE,
                     SampleArithmetic<TypeParam>::MEDIAN);
}

TYPED_TEST(TastyIntAndArithmeticTypeSubtractionTest, UpperQuartileAndLowerQuartile)
{
    test_subtraction(SampleArithmetic<TypeParam>::UPPER_QUARTILE,
                     SampleArithmetic<TypeParam>::LOWER_QUARTILE);
}

TYPED_TEST(TastyIntAndArithmeticTypeSubtractionTest, MedianAndLowerQuartile)
{
    test_subtraction(SampleArithmetic<TypeParam>::MEDIAN,
                     SampleArithmetic<TypeParam>::LOWER_QUARTILE);
}

TYPED_TEST(TastyIntAndArithmeticTypeSubtractionTest, LowerQuartileAndMinimum)
{
    test_subtraction(SampleArithmetic<TypeParam>::LOWER_QUARTILE,
                     SampleArithmetic<TypeParam>::MINIMUM);
}


template<typename SignedArithmeticType>
    requires std::is_signed_v<SignedArithmeticType>
class TastyIntAndSignedArithmeticTypeSubtractionTest : public ::testing::Test
{}; // class TastyIntAndArithmeticTypeSubtractionTest

TYPED_TEST_SUITE(TastyIntAndSignedArithmeticTypeSubtractionTest,
                 tasty_int_test::SignedArithmeticTypes);

TYPED_TEST(TastyIntAndSignedArithmeticTypeSubtractionTest, ZeroAndOne)
{
    test_subtraction(SampleArithmetic<TypeParam>::ZERO,
                     SampleArithmetic<TypeParam>::ONE);
}

TYPED_TEST(TastyIntAndSignedArithmeticTypeSubtractionTest, ZeroAndLowerQuartile)
{
    test_subtraction(SampleArithmetic<TypeParam>::ZERO,
                     SampleArithmetic<TypeParam>::LOWER_QUARTILE);
}

TYPED_TEST(TastyIntAndSignedArithmeticTypeSubtractionTest, ZeroAndMedian)
{
    test_subtraction(SampleArithmetic<TypeParam>::ZERO,
                     SampleArithmetic<TypeParam>::MEDIAN);
}

TYPED_TEST(TastyIntAndSignedArithmeticTypeSubtractionTest, ZeroAndUpperQuartile)
{
    test_subtraction(SampleArithmetic<TypeParam>::ZERO,
                     SampleArithmetic<TypeParam>::UPPER_QUARTILE);
}

TYPED_TEST(TastyIntAndSignedArithmeticTypeSubtractionTest,
           MinimumAndLowerQuartile)
{
    test_subtraction(SampleArithmetic<TypeParam>::MINIMUM,
                     SampleArithmetic<TypeParam>::LOWER_QUARTILE);
}

TYPED_TEST(TastyIntAndSignedArithmeticTypeSubtractionTest,
           MinimumAndMedian)
{
    test_subtraction(SampleArithmetic<TypeParam>::MINIMUM,
                     SampleArithmetic<TypeParam>::MEDIAN);
}

TYPED_TEST(TastyIntAndSignedArithmeticTypeSubtractionTest,
           LowerQuartileAndMedian)
{
    test_subtraction(SampleArithmetic<TypeParam>::LOWER_QUARTILE,
                     SampleArithmetic<TypeParam>::MEDIAN);
}

TYPED_TEST(TastyIntAndSignedArithmeticTypeSubtractionTest,
           LowerQuartileAndUpperQuartile)
{
    test_subtraction(SampleArithmetic<TypeParam>::LOWER_QUARTILE,
                     SampleArithmetic<TypeParam>::UPPER_QUARTILE);
}

TYPED_TEST(TastyIntAndSignedArithmeticTypeSubtractionTest,
           MedianAndUpperQuartile)
{
    test_subtraction(SampleArithmetic<TypeParam>::MEDIAN,
                     SampleArithmetic<TypeParam>::UPPER_QUARTILE);
}

TYPED_TEST(TastyIntAndSignedArithmeticTypeSubtractionTest,
           UpperQuartileAndMaximum)
{
    test_subtraction(SampleArithmetic<TypeParam>::UPPER_QUARTILE,
                     SampleArithmetic<TypeParam>::MAXIMUM);
}


TEST(TastyIntAndTastyIntSubtractionTest, ZeroAndZero)
{
    test_subtraction(
        TastyInt(0),
        TastyInt(0),
        TastyInt(0)
    );
}

TEST(TastyIntAndTastyIntSubtractionTest, ZeroAndPositive)
{
    test_subtraction(
        TastyInt(                                              0 ),
        TastyInt("+111111111111111111111111111111111111111111111"),
        TastyInt("-111111111111111111111111111111111111111111111")
    );
}

TEST(TastyIntAndTastyIntSubtractionTest, ZeroAndNegative)
{
    test_subtraction(
        TastyInt(                                              0 ),
        TastyInt("-222222222222222222222222222222222222222222222"),
        TastyInt("+222222222222222222222222222222222222222222222")
    );
}

TEST(TastyIntAndTastyIntSubtractionTest, PositiveAndZero)
{
    test_subtraction(
        TastyInt("+3333333333333333333333333333333333333333333333333333333333"),
        TastyInt(                                                           0 ),
        TastyInt("+3333333333333333333333333333333333333333333333333333333333")
    );
}

TEST(TastyIntAndTastyIntSubtractionTest, PositiveAndSmallerPositive)
{
    test_subtraction(
        TastyInt("+4444444444444444444444444444444444"),
        TastyInt("+3333333333333333333333333333333333"),
        TastyInt("+1111111111111111111111111111111111")
    );
}

TEST(TastyIntAndTastyIntSubtractionTest, PositiveAndLargerPositive)
{
    test_subtraction(
        TastyInt("+5555555555555555555555555555555555"),
        TastyInt("+6666666666666666666666666666666666"),
        TastyInt("-1111111111111111111111111111111111")
    );
}

TEST(TastyIntAndTastyIntSubtractionTest, PositiveAndSmallerNegative)
{
    test_subtraction(
        TastyInt( "+7777777777777777777777777777777777"),
        TastyInt( "-5555555555555555555555555555555555"),
        TastyInt("+13333333333333333333333333333333332")
    );
}

TEST(TastyIntAndTastyIntSubtractionTest, PositiveAndLargerNegative)
{
    test_subtraction(
        TastyInt( "+8888888888888888888888888888888888"),
        TastyInt( "-9999999999999999999999999999999999"),
        TastyInt("+18888888888888888888888888888888887")
    );
}

TEST(TastyIntAndTastyIntSubtractionTest, NegativeAndSmallerPositive)
{
    test_subtraction(
        TastyInt("-123123123123123123123123123123123"),
        TastyInt("+111111111111111111111111111111111"),
        TastyInt("-234234234234234234234234234234234")
    );
}

TEST(TastyIntAndTastyIntSubtractionTest, NegativeAndLargerPositive)
{
    test_subtraction(
        TastyInt( "-321321321321321321321321321321321321"),
        TastyInt( "+987987987987987987987987987987987987"),
        TastyInt("-1309309309309309309309309309309309308")
    );
}

TEST(TastyIntAndTastyIntSubtractionTest, NegativeAndSmallerNegative)
{
    test_subtraction(
        TastyInt("-78787878787878787878787878787878787878787878787878787878"),
        TastyInt("-34343434343434343434343434343434343434343434343434343434"),
        TastyInt("-44444444444444444444444444444444444444444444444444444444")
    );
}

TEST(TastyIntAndTastyIntSubtractionTest, NegativeAndLargerNegative)
{
    test_subtraction(
        TastyInt("-45454545454545454545454545454545"),
        TastyInt("-56565656565656565656565656565656"),
        TastyInt("+11111111111111111111111111111111")
    );
}

} // namespace
