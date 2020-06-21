#include "tasty_int/tasty_int.hpp"

#include <limits>

#include "gtest/gtest.h"

#include "tasty_int_test/arithmetic_types.hpp"
#include "tasty_int_test/check_integer_result.hpp"
#include "tasty_int_test/sample_arithmetic.hpp"


namespace {

using tasty_int::TastyInt;
using tasty_int_test::check_integer_result;
using tasty_int_test::SampleArithmetic;


template<tasty_int::TastyIntOperand SumType,
         tasty_int::TastyIntOperand AugendType>
void
check_add_in_place_result(const SumType    &expected_sum,
                          const AugendType &result,
                          const AugendType &augend)
{
    EXPECT_EQ(&augend, &result)
        << "+= did not return reference to augend";

    check_integer_result(expected_sum, augend, "+=");
}

template<tasty_int::TastyIntOperand LhsType,
         tasty_int::TastyIntOperand RhsType,
         tasty_int::TastyIntOperand SumType>
void
run_test_add_in_place(LhsType       &&lhs,
                      const RhsType  &rhs,
                      const SumType  &expected_sum)
{
    const auto &result = (lhs += rhs);

    check_add_in_place_result(expected_sum, lhs, result);
}

template<tasty_int::TastyIntOperand LhsType,
         tasty_int::TastyIntOperand RhsType,
         tasty_int::TastyIntOperand SumType>
void
test_add_in_place(const LhsType &lhs,
                  const RhsType &rhs,
                  const SumType &expected_sum)
{
    run_test_add_in_place(TastyInt(lhs), rhs,           expected_sum);
    run_test_add_in_place(LhsType(lhs),  TastyInt(rhs), LhsType(expected_sum));
}

template<tasty_int::TastyIntOperand LhsType,
         tasty_int::TastyIntOperand RhsType,
         tasty_int::TastyIntOperand SumType>
void
test_add(const LhsType &lhs,
         const RhsType &rhs,
         const SumType &expected_sum)
{
    EXPECT_EQ(expected_sum, TastyInt(lhs) + rhs          );
    EXPECT_EQ(expected_sum, lhs           + TastyInt(rhs));
}

template<tasty_int::TastyIntOperand LhsType,
         tasty_int::TastyIntOperand RhsType,
         tasty_int::TastyIntOperand SumType>
void
test_addition(const LhsType &lhs,
              const RhsType &rhs,
              const SumType &expected_sum)
{
    test_add_in_place(lhs, rhs, expected_sum);
    test_add_in_place(rhs, lhs, expected_sum);

    test_add(lhs, rhs, expected_sum);
    test_add(rhs, lhs, expected_sum);
}


template<tasty_int::Arithmetic ArithmeticType>
class TastyIntAndArithmeticTypeAdditionTest : public ::testing::Test
{
protected:
    static void
    test_addition(ArithmeticType lhs,
                  ArithmeticType rhs)
    {
        auto expected_sum = tasty_int::detail::prepare_operand(lhs) + rhs;

        ::test_addition(lhs, rhs, expected_sum);
    }
}; // class TastyIntAndArithmeticTypeAdditionTest

TYPED_TEST_SUITE(TastyIntAndArithmeticTypeAdditionTest,
                 tasty_int_test::ArithmeticTypes);

TYPED_TEST(TastyIntAndArithmeticTypeAdditionTest, LowerQuartileAndLowerQuartile)
{
    TestFixture::test_addition(SampleArithmetic<TypeParam>::LOWER_QUARTILE,
                               SampleArithmetic<TypeParam>::LOWER_QUARTILE);
}

TYPED_TEST(TastyIntAndArithmeticTypeAdditionTest, MedianAndMedian)
{
    TestFixture::test_addition(SampleArithmetic<TypeParam>::MEDIAN,
                               SampleArithmetic<TypeParam>::MEDIAN);
}

TYPED_TEST(TastyIntAndArithmeticTypeAdditionTest, LowerQuartileAndUpperQuartile)
{
    TestFixture::test_addition(SampleArithmetic<TypeParam>::LOWER_QUARTILE,
                               SampleArithmetic<TypeParam>::UPPER_QUARTILE);
}

TYPED_TEST(TastyIntAndArithmeticTypeAdditionTest, ZeroAndOne)
{
    TestFixture::test_addition(SampleArithmetic<TypeParam>::ZERO,
                               SampleArithmetic<TypeParam>::ONE);
}

TYPED_TEST(TastyIntAndArithmeticTypeAdditionTest, ZeroAndMinimum)
{
    TestFixture::test_addition(SampleArithmetic<TypeParam>::ZERO,
                               SampleArithmetic<TypeParam>::MINIMUM);
}

TYPED_TEST(TastyIntAndArithmeticTypeAdditionTest, ZeroAndLowerQuartile)
{
    TestFixture::test_addition(SampleArithmetic<TypeParam>::ZERO,
                               SampleArithmetic<TypeParam>::LOWER_QUARTILE);
}

TYPED_TEST(TastyIntAndArithmeticTypeAdditionTest, ZeroAndMedian)
{
    TestFixture::test_addition(SampleArithmetic<TypeParam>::ZERO,
                               SampleArithmetic<TypeParam>::MEDIAN);
}

TYPED_TEST(TastyIntAndArithmeticTypeAdditionTest, ZeroAndUpperQuartile)
{
    TestFixture::test_addition(SampleArithmetic<TypeParam>::ZERO,
                               SampleArithmetic<TypeParam>::UPPER_QUARTILE);
}

TYPED_TEST(TastyIntAndArithmeticTypeAdditionTest, ZeroAndMaximum)
{
    TestFixture::test_addition(SampleArithmetic<TypeParam>::ZERO,
                               SampleArithmetic<TypeParam>::MAXIMUM);
}


TEST(TastyIntAndTastyIntAdditionTest, ZeroAndZero)
{
    test_addition(
        TastyInt(0),
        TastyInt(0),
        TastyInt(0)
    );
}

TEST(TastyIntAndTastyIntAdditionTest, PositiveAndPositive)
{
    test_addition(
        TastyInt("+7878787878787878787878787878787878787878787878787878787878"),
        TastyInt("+2121212121212121212121212121212121212121212121212121212121"),
        TastyInt("+9999999999999999999999999999999999999999999999999999999999")
    );
}

TEST(TastyIntAndTastyIntAdditionTest, NegativeAndNegative)
{
    test_addition(
        TastyInt("-246802468024680246802468024680246802468024680"),
        TastyInt("-135797531135797531135797531135797531135797531"),
        TastyInt("-382599999160477777938265555816044333603822211")
    );
}

TEST(TastyIntAndTastyIntAdditionTest, PositiveAndZero)
{
    test_addition(
        TastyInt("+3333333333333333333333333333333333333333333333333333333333"),
        TastyInt(                                                           0 ),
        TastyInt("+3333333333333333333333333333333333333333333333333333333333")
    );
}

TEST(TastyIntAndTastyIntAdditionTest, NegativeAndZero)
{
    test_addition(
        TastyInt("-1111111111111111111111111111111111111111111111111111111111"),
        TastyInt(                                                           0 ),
        TastyInt("-1111111111111111111111111111111111111111111111111111111111")
    );
}

TEST(TastyIntAndTastyIntAdditionTest, LargerPositiveAndSmallerNegative)
{
    test_addition(
        TastyInt("+9999999999999999999999999999999999999999999999999999999999"),
        TastyInt(                   "-333333333333333333333333333333333333333"),
        TastyInt("+9999999999999999999666666666666666666666666666666666666666")
    );
}

TEST(TastyIntAndTastyIntAdditionTest, SmallerPositiveAndLargerNegative)
{
    test_addition(
        TastyInt(           "+77777777777777777777777777777777777777777777777"),
        TastyInt("-8888888888888888888888888888888888888888888888888888888888"),
        TastyInt("-8888888888811111111111111111111111111111111111111111111111")
    );
}

} // namespace
