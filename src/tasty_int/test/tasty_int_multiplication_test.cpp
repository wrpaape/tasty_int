#include "tasty_int/tasty_int.hpp"

#include <cmath>

#include <limits>

#include "gtest/gtest.h"
#include "tasty_int_test/arithmetic_types.hpp"
#include "tasty_int_test/check_integer_result.hpp"
#include "tasty_int_test/sample_arithmetic.hpp"


namespace {

using tasty_int::TastyInt;
using tasty_int_test::check_integer_result;
using tasty_int_test::SampleArithmetic;


template<tasty_int::TastyIntOperand ProductType,
         tasty_int::TastyIntOperand MultiplicandType>
void
check_multiply_in_place_result(const ProductType      &expected_product,
                               const MultiplicandType &result,
                               const MultiplicandType &multiplicand)
{
    EXPECT_EQ(&multiplicand, &result)
        << "+= did not return reference to multiplicand";

    check_integer_result(expected_product, multiplicand, "+=");
}

/// @todo: TODO: apply tasty_int::TastyIntOperand constraint
template<typename LhsType,
         typename RhsType,
         typename ProductType>
void
run_test_multiply_in_place(LhsType           &&lhs,
                           const RhsType      &rhs,
                           const ProductType  &expected_product)
{
    const auto &result = (lhs *= rhs);

    check_multiply_in_place_result(expected_product, lhs, result);
}

/// @todo: TODO: apply tasty_int::TastyIntOperand constraint
template<typename LhsType,
         typename RhsType,
         typename ProductType>
void
test_multiply_in_place(const LhsType     &lhs,
                       const RhsType     &rhs,
                       const ProductType &expected_product)
{
    run_test_multiply_in_place(TastyInt(lhs),
                               rhs,
                               expected_product);
    run_test_multiply_in_place(LhsType(lhs),
                               TastyInt(rhs),
                               LhsType(expected_product));
}

template<tasty_int::TastyIntOperand LhsType,
         tasty_int::TastyIntOperand RhsType,
         tasty_int::TastyIntOperand ProductType>
void
test_multiply(const LhsType     &lhs,
              const RhsType     &rhs,
              const ProductType &expected_product)
{
    EXPECT_EQ(expected_product, TastyInt(lhs) * rhs          );
    EXPECT_EQ(expected_product, lhs           * TastyInt(rhs));
}

template<tasty_int::TastyIntOperand LhsType,
         tasty_int::TastyIntOperand RhsType,
         tasty_int::TastyIntOperand ProductType>
void
test_multiplication(const LhsType     &lhs,
                    const RhsType     &rhs,
                    const ProductType &expected_product)
{
    test_multiply_in_place(lhs, rhs, expected_product);
    test_multiply_in_place(rhs, lhs, expected_product);

    test_multiply(lhs, rhs, expected_product);
    test_multiply(rhs, lhs, expected_product);
}


template<tasty_int::Arithmetic ArithmeticType>
class TastyIntAndArithmeticTypeMultiplicationTest : public ::testing::Test
{
protected:
    static void
    test_multiplication(ArithmeticType lhs,
                        ArithmeticType rhs)
    {
        auto expected_product = tasty_int::detail::prepare_operand(lhs) * rhs;

        ::test_multiplication(lhs, rhs, expected_product);
    }
}; // class TastyIntAndArithmeticTypeMultiplicationTest

TYPED_TEST_SUITE(TastyIntAndArithmeticTypeMultiplicationTest,
                 tasty_int_test::ArithmeticTypes);

TYPED_TEST(TastyIntAndArithmeticTypeMultiplicationTest, ZeroAndOne)
{
    TestFixture::test_multiplication(SampleArithmetic<TypeParam>::ZERO,
                                     SampleArithmetic<TypeParam>::ONE);
}

TYPED_TEST(TastyIntAndArithmeticTypeMultiplicationTest, ZeroAndMinimum)
{
    TestFixture::test_multiplication(SampleArithmetic<TypeParam>::ZERO,
                                     SampleArithmetic<TypeParam>::MINIMUM);
}

TYPED_TEST(TastyIntAndArithmeticTypeMultiplicationTest, ZeroAndLowerQuartile)
{
    TestFixture::test_multiplication(
        SampleArithmetic<TypeParam>::ZERO,
        SampleArithmetic<TypeParam>::LOWER_QUARTILE
    );
}

TYPED_TEST(TastyIntAndArithmeticTypeMultiplicationTest, ZeroAndMedian)
{
    TestFixture::test_multiplication(SampleArithmetic<TypeParam>::ZERO,
                                     SampleArithmetic<TypeParam>::MEDIAN);
}

TYPED_TEST(TastyIntAndArithmeticTypeMultiplicationTest, ZeroAndUpperQuartile)
{
    TestFixture::test_multiplication(SampleArithmetic<TypeParam>::ZERO,
                                     SampleArithmetic<TypeParam>::UPPER_QUARTILE);
}

TYPED_TEST(TastyIntAndArithmeticTypeMultiplicationTest, ZeroAndMaximum)
{
    TestFixture::test_multiplication(SampleArithmetic<TypeParam>::ZERO,
                                     SampleArithmetic<TypeParam>::MAXIMUM);
}

TYPED_TEST(TastyIntAndArithmeticTypeMultiplicationTest, OneAndMinimum)
{
    TestFixture::test_multiplication(SampleArithmetic<TypeParam>::ONE,
                                     SampleArithmetic<TypeParam>::MINIMUM);
}

TYPED_TEST(TastyIntAndArithmeticTypeMultiplicationTest, OneAndLowerQuartile)
{
    TestFixture::test_multiplication(
        SampleArithmetic<TypeParam>::ONE,
        SampleArithmetic<TypeParam>::LOWER_QUARTILE
    );
}

TYPED_TEST(TastyIntAndArithmeticTypeMultiplicationTest, OneAndMedian)
{
    TestFixture::test_multiplication(SampleArithmetic<TypeParam>::ONE,
                                     SampleArithmetic<TypeParam>::MEDIAN);
}

TYPED_TEST(TastyIntAndArithmeticTypeMultiplicationTest, OneAndUpperQuartile)
{
    TestFixture::test_multiplication(
        SampleArithmetic<TypeParam>::ONE,
        SampleArithmetic<TypeParam>::UPPER_QUARTILE
    );
}

TYPED_TEST(TastyIntAndArithmeticTypeMultiplicationTest, OneAndMaximum)
{
    TestFixture::test_multiplication(SampleArithmetic<TypeParam>::ZERO,
                                     SampleArithmetic<TypeParam>::MAXIMUM);
}


TEST(TastyIntAndTastyIntMultiplicationTest, ZeroAndZero)
{
    test_multiplication(
        TastyInt(0),
        TastyInt(0),
        TastyInt(0)
    );
}

TEST(TastyIntAndTastyIntMultiplicationTest, ZeroAndPositive)
{
    test_multiplication(
        TastyInt(                                                           0 ),
        TastyInt("+3333333333333333333333333333333333333333333333333333333333"),
        TastyInt(                                                           0 )
    );
}

TEST(TastyIntAndTastyIntMultiplicationTest, ZeroAndNegative)
{
    test_multiplication(
        TastyInt(                                                           0 ),
        TastyInt("-1111111111111111111111111111111111111111111111111111111111"),
        TastyInt(                                                           0 )
    );
}

TEST(TastyIntAndTastyIntMultiplicationTest, PositiveAndPositive)
{
    test_multiplication(
        TastyInt("+787878787878787878787878787878787878787878787878787878787878"),
        TastyInt("+212121212121212121212121212121212121212121212121212121212121"),
        TastyInt("+167125803489439853076216712580348943985307621671258034894398196510560146923783287419651056014692378328741965105601469238")
    );
}

TEST(TastyIntAndTastyIntMultiplicationTest, PositiveAndNegative)
{
    test_multiplication(
        TastyInt("+9999999999999999999999999999999999999999999999999999999999"),
        TastyInt(                   "-333333333333333333333333333333333333333"),
        TastyInt("-3333333333333333333333333333333333333329999999999999999999666666666666666666666666666666666666667")
    );
}

TEST(TastyIntAndTastyIntMultiplicationTest, NegativeAndNegative)
{
    test_multiplication(
        TastyInt("-246802468024680246802468024680246802468024680"),
        TastyInt("-135797531135797531135797531135797531135797531"),
        TastyInt("+33515165835973190416218992874243573120046031077595945275137920694892118236867537991065080")
    );
}

} // namespace
