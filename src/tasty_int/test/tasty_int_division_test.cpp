#include "tasty_int/tasty_int.hpp"

#include <cmath>

#include <type_traits>

#include "gtest/gtest.h"

#include "tasty_int_test/arithmetic_types.hpp"
#include "tasty_int_test/non_boolean_arithmetic_types.hpp"
#include "tasty_int_test/check_integer_result.hpp"
#include "tasty_int_test/sample_arithmetic.hpp"


namespace {

using tasty_int::TastyInt;
using tasty_int::TastyIntDivisionResult;
using tasty_int_test::check_integer_result;
using tasty_int_test::SampleArithmetic;


template<typename DividendType,
         typename DivisorType,
         typename QuotientType>
void
run_test_divide_in_place(const DividendType &lhs,
                         const DivisorType  &rhs,
                         const QuotientType &expected_quotient)
{
    auto dividend = lhs;

    auto &&quotient = (dividend /= rhs);

    EXPECT_EQ(&dividend, &quotient)
        << "/= did not return reference to dividend";

    check_integer_result(expected_quotient, dividend, "/=");
}

template<typename DividendType,
         typename DivisorType,
         typename QuotientType>
void
test_divide_in_place(const DividendType &dividend,
                     const DivisorType  &divisor,
                     const QuotientType &expected_quotient)
{
    run_test_divide_in_place(TastyInt(dividend),
                             divisor,
                             expected_quotient);
    run_test_divide_in_place(dividend,
                             TastyInt(divisor),
                             expected_quotient);
}

template<typename DividendType,
         typename DivisorType,
         typename QuotientType>
void
run_test_divide(const DividendType &dividend,
                const DivisorType  &divisor,
                const QuotientType &expected_quotient)
{
    auto &&quotient = dividend / divisor;

    check_integer_result(expected_quotient, quotient, "/");
}

template<typename DividendType,
         typename DivisorType,
         typename QuotientType>
void
test_divide(const DividendType &dividend,
            const DivisorType  &divisor,
            const QuotientType &expected_quotient)
{
    run_test_divide(TastyInt(dividend), divisor,           expected_quotient);
    run_test_divide(          dividend, TastyInt(divisor), expected_quotient);
}

template<typename DividendType,
         typename DivisorType,
         typename RemainderType>
void
run_test_modulo_in_place(const DividendType  &lhs,
                         const DivisorType   &rhs,
                         const RemainderType &expected_remainder)
{
    auto dividend = lhs;

    auto &&remainder = (dividend %= rhs);

    EXPECT_EQ(&dividend, &remainder)
        << "%= did not return reference to dividend";

    check_integer_result(expected_remainder, dividend, "%=");
}

template<typename DividendType,
         typename DivisorType,
         typename RemainderType>
void
test_modulo_in_place(const DividendType  &dividend,
                     const DivisorType   &divisor,
                     const RemainderType &expected_remainder)
{
    run_test_modulo_in_place(TastyInt(dividend),
                             divisor,
                             expected_remainder);
    run_test_modulo_in_place(dividend,
                             TastyInt(divisor),
                             expected_remainder);
}

template<typename DividendType,
         typename DivisorType,
         typename RemainderType>
void
run_test_modulo(const DividendType  &dividend,
                const DivisorType   &divisor,
                const RemainderType &expected_remainder)
{
    auto &&remainder = dividend % divisor;

    check_integer_result(expected_remainder, remainder, "%");
}

template<typename DividendType,
         typename DivisorType,
         typename RemainderType>
void
test_modulo(const DividendType  &dividend,
            const DivisorType   &divisor,
            const RemainderType &expected_remainder)
{
    run_test_modulo(TastyInt(dividend), divisor,           expected_remainder);
    run_test_modulo(dividend,           TastyInt(divisor), expected_remainder);
}

template<typename DividendType,
         typename DivisorType,
         typename TastyIntDivisionResultType>
void
run_test_div(const DividendType               &dividend,
             const DivisorType                &divisor,
             const TastyIntDivisionResultType &expected_result)
{
    auto &&result = tasty_int::div(dividend, divisor);

    check_integer_result(expected_result.quotient,
                         result.quotient,
                         "div (quotient)");
    check_integer_result(expected_result.remainder,
                         result.remainder,
                         "div (remainder)");
}

template<typename DividendType,
         typename DivisorType,
         typename TastyIntDivisionResultType>
void
test_div(const DividendType               &dividend,
         const DivisorType                &divisor,
         const TastyIntDivisionResultType &expected_result)
{
    run_test_div(TastyInt(dividend), divisor,           expected_result);
    run_test_div(dividend,           TastyInt(divisor), expected_result);
}

template<typename DividendType,
         typename DivisorType>
void
test_division(const DividendType                         &dividend,
              const DivisorType                          &divisor,
              const TastyIntDivisionResult<DividendType> &expected_result)
{
    test_divide_in_place(dividend, divisor, expected_result.quotient);
    test_divide(         dividend, divisor, expected_result.quotient);
    test_modulo_in_place(dividend, divisor, expected_result.remainder);
    test_modulo(         dividend, divisor, expected_result.remainder);
    test_div(            dividend, divisor, expected_result);
}


template<tasty_int::Arithmetic ArithmeticType>
class TastyIntAndArithmeticTypeDivisionTest : public ::testing::Test
{
protected:
    static void
    test_division(ArithmeticType lhs,
                  ArithmeticType rhs)
    {
        auto promoted_lhs = tasty_int::prepare_operand(lhs);

        auto expected_quotient = static_cast<ArithmeticType>(
             promoted_lhs / rhs
        );

        ArithmeticType expected_remainder;
        if constexpr (std::is_floating_point_v<ArithmeticType>)
            expected_remainder = static_cast<ArithmeticType>(
                std::fmod(promoted_lhs, rhs)
            );
        else
            expected_remainder = static_cast<ArithmeticType>(
                promoted_lhs % rhs
            );

        TastyIntDivisionResult<ArithmeticType> expected_result = {
            .quotient  = expected_quotient,
            .remainder = expected_remainder
        };

        ::test_division(lhs, rhs, expected_result);
    }
}; // class TastyIntAndArithmeticTypeDivisionTest

TYPED_TEST_SUITE(TastyIntAndArithmeticTypeDivisionTest,
                 tasty_int_test::ArithmeticTypes);

TYPED_TEST(TastyIntAndArithmeticTypeDivisionTest, OneAndOne)
{
    TestFixture::test_division(SampleArithmetic<TypeParam>::ONE,
                               SampleArithmetic<TypeParam>::ONE);
}

TYPED_TEST(TastyIntAndArithmeticTypeDivisionTest, MinimumAndOne)
{
    TestFixture::test_division(SampleArithmetic<TypeParam>::MINIMUM,
                               SampleArithmetic<TypeParam>::ONE);
}

TYPED_TEST(TastyIntAndArithmeticTypeDivisionTest, LowerQuartileAndOne)
{
    TestFixture::test_division(SampleArithmetic<TypeParam>::LOWER_QUARTILE,
                  SampleArithmetic<TypeParam>::ONE);
}

TYPED_TEST(TastyIntAndArithmeticTypeDivisionTest, UpperQuartileAndOne)
{
    TestFixture::test_division(SampleArithmetic<TypeParam>::UPPER_QUARTILE,
                  SampleArithmetic<TypeParam>::ONE);
}

TYPED_TEST(TastyIntAndArithmeticTypeDivisionTest, MaximumAndOne)
{
    TestFixture::test_division(SampleArithmetic<TypeParam>::MAXIMUM,
                  SampleArithmetic<TypeParam>::ONE);
}


template<tasty_int::Arithmetic NonBooleanArithmeticType>
    requires (!std::is_same_v<NonBooleanArithmeticType, bool>)
class TastyIntAndNonBooleanArithmeticTypeDivisionTest
    : public TastyIntAndArithmeticTypeDivisionTest<NonBooleanArithmeticType>
{}; // class TastyIntAndNonBooleanArithmeticTypeDivisionTest

TYPED_TEST_SUITE(TastyIntAndNonBooleanArithmeticTypeDivisionTest,
                 tasty_int_test::NonBooleanArithmeticTypes);

TYPED_TEST(TastyIntAndNonBooleanArithmeticTypeDivisionTest, ZeroAndOne)
{
    TestFixture::test_division(SampleArithmetic<TypeParam>::ZERO,
                               SampleArithmetic<TypeParam>::ONE);
}

TYPED_TEST(TastyIntAndNonBooleanArithmeticTypeDivisionTest, ZeroAndLowerQuartile)
{
    TestFixture::test_division(SampleArithmetic<TypeParam>::ZERO,
                               SampleArithmetic<TypeParam>::LOWER_QUARTILE);
}

TYPED_TEST(TastyIntAndNonBooleanArithmeticTypeDivisionTest, ZeroAndUpperQuartile)
{
    TestFixture::test_division(SampleArithmetic<TypeParam>::ZERO,
                               SampleArithmetic<TypeParam>::UPPER_QUARTILE);
}

TYPED_TEST(TastyIntAndNonBooleanArithmeticTypeDivisionTest, ZeroAndMaximum)
{
    TestFixture::test_division(SampleArithmetic<TypeParam>::ZERO,
                               SampleArithmetic<TypeParam>::MAXIMUM);
}

TYPED_TEST(TastyIntAndNonBooleanArithmeticTypeDivisionTest,
           MaximumAndUpperQuartile)
{
    TestFixture::test_division(SampleArithmetic<TypeParam>::MAXIMUM,
                               SampleArithmetic<TypeParam>::UPPER_QUARTILE);
}

TYPED_TEST(TastyIntAndNonBooleanArithmeticTypeDivisionTest,
           UpperQuartileAndMaximum)
{
    TestFixture::test_division(SampleArithmetic<TypeParam>::UPPER_QUARTILE,
                               SampleArithmetic<TypeParam>::MAXIMUM);
}

TYPED_TEST(TastyIntAndNonBooleanArithmeticTypeDivisionTest,
           UpperQuartileAndLowerQuartile)
{
    TestFixture::test_division(SampleArithmetic<TypeParam>::UPPER_QUARTILE,
                               SampleArithmetic<TypeParam>::LOWER_QUARTILE);
}

TYPED_TEST(TastyIntAndNonBooleanArithmeticTypeDivisionTest,
           LowerQuartileAndUpperQuartile)
{
    TestFixture::test_division(SampleArithmetic<TypeParam>::LOWER_QUARTILE,
                               SampleArithmetic<TypeParam>::UPPER_QUARTILE);
}

TYPED_TEST(TastyIntAndNonBooleanArithmeticTypeDivisionTest,
           MedianAndLowerQuartile)
{
    TestFixture::test_division(SampleArithmetic<TypeParam>::MEDIAN,
                               SampleArithmetic<TypeParam>::LOWER_QUARTILE);
}

TYPED_TEST(TastyIntAndNonBooleanArithmeticTypeDivisionTest,
           MinimumAndLowerQuartile)
{
    TestFixture::test_division(SampleArithmetic<TypeParam>::MINIMUM,
                               SampleArithmetic<TypeParam>::LOWER_QUARTILE);
}

TYPED_TEST(TastyIntAndNonBooleanArithmeticTypeDivisionTest,
           MedianAndUpperQuartile)
{
    TestFixture::test_division(SampleArithmetic<TypeParam>::MEDIAN,
                               SampleArithmetic<TypeParam>::UPPER_QUARTILE);
}

TEST(TastyIntAndTastyIntDivisionTest, ZeroAndPositive)
{
    test_division(
        TastyInt(                                              0 ),
        TastyInt("+111111111111111111111111111111111111111111111"),
        {
            .quotient  = TastyInt(0),
            .remainder = TastyInt(0)
        }
    );
}

TEST(TastyIntAndTastyIntDivisionTest, ZeroAndNegative)
{
    test_division(
        TastyInt(                                              0 ),
        TastyInt("-111111111111111111111111111111111111111111111"),
        {
            .quotient  = TastyInt(0),
            .remainder = TastyInt(0)
        }
    );
}

TEST(TastyIntAndTastyIntDivisionTest, PositiveAndSmallerPositive)
{
    test_division(
        TastyInt("+4444444444444444444444444444444444"),
        TastyInt(                 "+33333333333333333"),
        {
            .quotient  = TastyInt("+133333333333333334"),
            .remainder = TastyInt("+22222222222222222")
        }
    );
}

TEST(TastyIntAndTastyIntDivisionTest, PositiveAndLargerPositive)
{
    test_division(
        TastyInt(                 "+55555555555555555"),
        TastyInt("+6666666666666666666666666666666666"),
        {
            .quotient  = TastyInt("0"),
            .remainder = TastyInt("+55555555555555555")
        }
    );
}

TEST(TastyIntAndTastyIntDivisionTest, PositiveAndSmallerNegative)
{
    test_division(
        TastyInt("+7777777777777777777777777777777777"),
        TastyInt(                            "-555555"),
        {
            .quotient  = TastyInt("-14000014000014000014000014000"),
            .remainder = TastyInt("+7777")
        }
    );
}

TEST(TastyIntAndTastyIntDivisionTest, PositiveAndLargerNegative)
{
    test_division(
        TastyInt(          "+555555555555555555555555"),
        TastyInt("+7777777777777777777777777777777777"),
        {
            .quotient  = TastyInt(0),
            .remainder = TastyInt("+555555555555555555555555")
        }
    );
}

TEST(TastyIntAndTastyIntDivisionTest, NegativeAndSmallerPositive)
{
    test_division(
        TastyInt("-123123123123123123123123123123123"),
        TastyInt("+111111111111111111111111111111111"),
        {
            .quotient  = TastyInt(-1),
            .remainder = TastyInt("-12012012012012012012012012012012")
        }
    );
}

TEST(TastyIntAndTastyIntDivisionTest, NegativeAndLargerPositive)
{
    test_division(
        TastyInt("-321321321321321321321321321321321321"),
        TastyInt("+987987987987987987987987987987987987"),
        {
            .quotient  = TastyInt(0),
            .remainder = TastyInt("-321321321321321321321321321321321321")
        }
    );
}

TEST(TastyIntAndTastyIntDivisionTest, NegativeAndSmallerNegative)
{
    test_division(
        TastyInt("-78787878787878787878787878787878787878787878787878787878"),
        TastyInt(                "-3434343434343434343434343434343434343434"),
        {
            .quotient  = TastyInt("+22941176470588235"),
            .remainder = TastyInt("-1010101010101010101010108888888888888888")
        }
    );
}

TEST(TastyIntAndTastyIntDivisionTest, NegativeAndLargerNegative)
{
    test_division(
        TastyInt("-45454545454545454545454545454545"),
        TastyInt("-56565656565656565656565656565656"),
        {
            .quotient  = TastyInt(0),
            .remainder = TastyInt("-45454545454545454545454545454545")
        }
    );
}

} // namespace
