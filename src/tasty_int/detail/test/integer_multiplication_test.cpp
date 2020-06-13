#include "tasty_int/detail/integer_multiplication.hpp"

#include <type_traits>

#include "gtest/gtest.h"

#include "tasty_int/detail/conversions/integer_from_string.hpp"
#include "tasty_int/detail/test/integer_test_common.hpp"


namespace {

using tasty_int::detail::Integer;
using tasty_int::detail::Sign;
using tasty_int::detail::conversions::integer_from_string;


const Integer ZERO_INTEGER = { .sign = Sign::ZERO, .digits = { 0 } };

void
check_multiply_in_place_result(const Integer &expected_result,
                               const Integer &multiplicand,
                               const Integer &result)
{
    EXPECT_EQ(&multiplicand, &result)
        << "*= did not return reference to multiplicand";

    EXPECT_EQ(expected_result, multiplicand)
        << "*= did not produce the expected result";
}

template<typename RhsType>
void
test_multiply_in_place(const Integer &lhs,
                       const RhsType &rhs,
                       const Integer &expected_result)
{
    Integer multiplicand = lhs;

    const Integer &result = (multiplicand *= rhs);

    check_multiply_in_place_result(expected_result, multiplicand, result);
}

template<typename LhsType, typename RhsType>
void
test_multiply(const LhsType &lhs,
              const RhsType &rhs,
              const Integer &expected_result)
{
    const Integer result = lhs * rhs;

    EXPECT_EQ(expected_result, result)
        << "* did not produce the expected result";
}

template<typename Multiplier2Type>
void
test_multiplication(const Integer         &multiplier1,
                    const Multiplier2Type &multiplier2,
                    const Integer         &expected_result)
{
    test_multiply_in_place(multiplier1, multiplier2, expected_result);

    if constexpr (std::is_same_v<Multiplier2Type, Integer>)
        test_multiply_in_place(multiplier2, multiplier1, expected_result);

    test_multiply(multiplier1, multiplier2, expected_result);

    test_multiply(multiplier2, multiplier1, expected_result);
}


TEST(IntegerMultiplicationTest, ZeroIntegerAndZeroInteger)
{
    test_multiplication(ZERO_INTEGER, ZERO_INTEGER, ZERO_INTEGER);
}

TEST(IntegerMultiplicationTest, ZeroIntegerAndPositiveInteger)
{
    Integer multiplier1     = ZERO_INTEGER;
    Integer multiplier2     = integer_from_string("+111111111111111111", 10);
    Integer expected_result = ZERO_INTEGER;

    test_multiplication(multiplier1, multiplier2, expected_result);
}

TEST(IntegerMultiplicationTest, ZeroIntegerAndNegativeInteger)
{
    Integer multiplier1     = ZERO_INTEGER;
    Integer multiplier2     = integer_from_string("-222222222222222222", 10);
    Integer expected_result = ZERO_INTEGER;

    test_multiplication(multiplier1, multiplier2, expected_result);
}

TEST(IntegerMultiplicationTest, PositiveIntegerAndPositiveInteger)
{
    Integer multiplier1 = integer_from_string("+24680246802468024680", 10);
    Integer multiplier2 = integer_from_string("+13579135791357913579", 10);
    Integer expected_result =
        integer_from_string("+335136422694940256528933958626279129720", 10);

    test_multiplication(multiplier1, multiplier2, expected_result);
}

TEST(IntegerMultiplicationTest, PositiveIntegerAndNegativeInteger)
{
    Integer multiplier1 = integer_from_string("+1111111111111111111111111", 10);
    Integer multiplier2 = integer_from_string("-2222222222222222222222222", 10);
    Integer expected_result = integer_from_string(
        "-2469135802469135802469135308641975308641975308642",
        10
    );

    test_multiplication(multiplier1, multiplier2, expected_result);
}

TEST(IntegerMultiplicationTest, NegativeIntegerAndNegativeInteger)
{
    Integer multiplier1 = integer_from_string("-3333333333333333333333333", 10);
    Integer multiplier2 = integer_from_string("-4444444444444444444444444", 10);
    Integer expected_result = integer_from_string(
        "+14814814814814814814814811851851851851851851851852",
        10
    );

    test_multiplication(multiplier1, multiplier2, expected_result);
}


TEST(IntegerMultiplicationTest, ZeroIntegerAndZeroUnsignedIntegral)
{
    Integer        multiplier1 = ZERO_INTEGER;
    std::uintmax_t multiplier2 = 0;
    Integer expected_result    = ZERO_INTEGER;

    test_multiplication(multiplier1, multiplier2, expected_result);
}

TEST(IntegerMultiplicationTest, ZeroIntegerAndPositiveUnsignedIntegral)
{
    Integer        multiplier1 = ZERO_INTEGER;
    std::uintmax_t multiplier2 = +911;
    Integer expected_result    = ZERO_INTEGER;

    test_multiplication(multiplier1, multiplier2, expected_result);
}

TEST(IntegerMultiplicationTest, PositiveIntegerAndZeroUnsignedIntegral)
{
    Integer        multiplier1 = integer_from_string("+777777777777777777", 10);
    std::uintmax_t multiplier2 = 0;
    Integer expected_result    = ZERO_INTEGER;

    test_multiplication(multiplier1, multiplier2, expected_result);
}

TEST(IntegerMultiplicationTest, PositiveIntegerAndPositiveUnsignedIntegral)
{
    Integer        multiplier1 = integer_from_string("+888888888888888888", 10);
    std::uintmax_t multiplier2 = +9999;
    Integer expected_result    =
        integer_from_string("+8887999999999999991112", 10);

    test_multiplication(multiplier1, multiplier2, expected_result);
}

TEST(IntegerMultiplicationTest, NegativeIntegerAndZeroUnsignedIntegral)
{
    Integer        multiplier1 = integer_from_string("-999999999999999999", 10);
    std::uintmax_t multiplier2 = 0;
    Integer expected_result    = ZERO_INTEGER;

    test_multiplication(multiplier1, multiplier2, expected_result);
}

TEST(IntegerMultiplicationTest, NegativeIntegerAndPositiveUnsignedIntegral)
{
    Integer        multiplier1 = integer_from_string("-121212121212121212", 10);
    std::uintmax_t multiplier2 = +6666;
    Integer expected_result    =
        integer_from_string("-807999999999999999192", 10);

    test_multiplication(multiplier1, multiplier2, expected_result);
}


TEST(IntegerMultiplicationTest, ZeroIntegerAndZeroSignedIntegral)
{
    Integer       multiplier1 = ZERO_INTEGER;
    std::intmax_t multiplier2 = 0;
    Integer expected_result   = ZERO_INTEGER;

    test_multiplication(multiplier1, multiplier2, expected_result);
}

TEST(IntegerMultiplicationTest, ZeroIntegerAndPositiveSignedIntegral)
{
    Integer       multiplier1 = ZERO_INTEGER;
    std::intmax_t multiplier2 = +311;
    Integer expected_result   = ZERO_INTEGER;

    test_multiplication(multiplier1, multiplier2, expected_result);
}

TEST(IntegerMultiplicationTest, ZeroIntegerAndNegativeSignedIntegral)
{
    Integer       multiplier1 = ZERO_INTEGER;
    std::intmax_t multiplier2 = -411;
    Integer expected_result   = ZERO_INTEGER;

    test_multiplication(multiplier1, multiplier2, expected_result);
}

TEST(IntegerMultiplicationTest, PositiveIntegerAndZeroSignedIntegral)
{
    Integer       multiplier1 = integer_from_string("+232323232323232323", 10);
    std::intmax_t multiplier2 = 0;
    Integer expected_result   = ZERO_INTEGER;

    test_multiplication(multiplier1, multiplier2, expected_result);
}

TEST(IntegerMultiplicationTest, PositiveIntegerAndPositiveSignedIntegral)
{
    Integer       multiplier1 = integer_from_string("+343434343434343434", 10);
    std::intmax_t multiplier2 = +10000;
    Integer expected_result   =
        integer_from_string("+3434343434343434340000", 10);

    test_multiplication(multiplier1, multiplier2, expected_result);
}

TEST(IntegerMultiplicationTest, PositiveIntegerAndNegativeSignedIntegral)
{
    Integer       multiplier1 = integer_from_string("+454545454545454545", 10);
    std::intmax_t multiplier2 = -9001;
    Integer expected_result   =
        integer_from_string("-4091363636363636359545", 10);

    test_multiplication(multiplier1, multiplier2, expected_result);
}

TEST(IntegerMultiplicationTest, NegativeIntegerAndZeroSignedIntegral)
{
    Integer       multiplier1 = integer_from_string("-555", 10);
    std::intmax_t multiplier2 = 0;
    Integer expected_result    = ZERO_INTEGER;

    test_multiplication(multiplier1, multiplier2, expected_result);
}

TEST(IntegerMultiplicationTest, NegativeIntegerAndPositiveSignedIntegral)
{
    Integer       multiplier1 = integer_from_string("-565656565656565656", 10);
    std::intmax_t multiplier2 = +1234;
    Integer expected_result   =
        integer_from_string("-698020202020202019504", 10);

    test_multiplication(multiplier1, multiplier2, expected_result);
}

TEST(IntegerMultiplicationTest, NegativeIntegerAndNegativeSignedIntegral)
{
    Integer       multiplier1 = integer_from_string("-676767676767676767", 10);
    std::intmax_t multiplier2 = -4321;
    Integer expected_result   =
        integer_from_string("+2924313131313131310207", 10);

    test_multiplication(multiplier1, multiplier2, expected_result);
}


TEST(IntegerMultiplicationTest, ZeroIntegerAndZeroFloatingPoint)
{
    Integer     multiplier1 = ZERO_INTEGER;
    long double multiplier2 = 0.0L;
    Integer expected_result = ZERO_INTEGER;

    test_multiplication(multiplier1, multiplier2, expected_result);
}

TEST(IntegerMultiplicationTest,
     ZeroIntegerAndPositiveProperRationalFloatingPoint)
{
    Integer     multiplier1 = ZERO_INTEGER;
    long double multiplier2 = +0.9L;
    Integer expected_result = ZERO_INTEGER;

    test_multiplication(multiplier1, multiplier2, expected_result);
}

TEST(IntegerMultiplicationTest,
     ZeroIntegerAndPositiveImproperRationalFloatingPoint)
{
    Integer     multiplier1 = ZERO_INTEGER;
    long double multiplier2 = +99.9L;
    Integer expected_result = ZERO_INTEGER;

    test_multiplication(multiplier1, multiplier2, expected_result);
}

TEST(IntegerMultiplicationTest,
     ZeroIntegerAndNegativeProperRationalFloatingPoint)
{
    Integer     multiplier1 = ZERO_INTEGER;
    long double multiplier2 = -0.9L;
    Integer expected_result = ZERO_INTEGER;

    test_multiplication(multiplier1, multiplier2, expected_result);
}

TEST(IntegerMultiplicationTest,
     ZeroIntegerAndNegativeImproperRationalFloatingPoint)
{
    Integer     multiplier1 = ZERO_INTEGER;
    long double multiplier2 = -99.9L;
    Integer expected_result = ZERO_INTEGER;

    test_multiplication(multiplier1, multiplier2, expected_result);
}

TEST(IntegerMultiplicationTest, PositiveIntegerAndZeroFloatingPoint)
{
    Integer     multiplier1 = integer_from_string("+123123123123123123123", 10);
    long double multiplier2 = 0.0L;
    Integer expected_result = ZERO_INTEGER;

    test_multiplication(multiplier1, multiplier2, expected_result);
}

TEST(IntegerMultiplicationTest,
     PositiveIntegerAndPositiveProperRationalFloatingPoint)
{
    Integer     multiplier1 = integer_from_string("+100000000000000000000", 10);
    long double multiplier2 = +0.9L;
    Integer expected_result = ZERO_INTEGER;

    test_multiplication(multiplier1, multiplier2, expected_result);
}

TEST(IntegerMultiplicationTest,
     PositiveIntegerAndPositiveImproperRationalFloatingPoint)
{
    Integer     multiplier1 = integer_from_string("+100000000000000000000", 10);
    long double multiplier2 = +99.9L;
    Integer expected_result = 
        integer_from_string("+9900000000000000000000", 10);

    test_multiplication(multiplier1, multiplier2, expected_result);
}

TEST(IntegerMultiplicationTest,
     PositiveIntegerAndNegativeProperRationalFloatingPoint)
{
    Integer     multiplier1 = integer_from_string("+1111111111111111111111", 10);
    long double multiplier2 = -0.9L;
    Integer expected_result = ZERO_INTEGER;

    test_multiplication(multiplier1, multiplier2, expected_result);
}

TEST(IntegerMultiplicationTest,
     PositiveIntegerAndNegativeImproperRationalFloatingPoint)
{
    Integer     multiplier1 = integer_from_string("+1111111111111111111111", 10);
    long double multiplier2 = -99.9L;
    Integer expected_result =
        integer_from_string("-109999999999999999999989", 10);

    test_multiplication(multiplier1, multiplier2, expected_result);
}

TEST(IntegerMultiplicationTest, NegativeIntegerAndZeroFloatingPoint)
{
    Integer     multiplier1 = integer_from_string("-123123123123123123123", 10);
    long double multiplier2 = 0.0L;
    Integer expected_result = ZERO_INTEGER;

    test_multiplication(multiplier1, multiplier2, expected_result);
}

TEST(IntegerMultiplicationTest,
     NegativeIntegerAndPositiveProperRationalFloatingPoint)
{
    Integer     multiplier1 = integer_from_string("-100000000000000000000", 10);
    long double multiplier2 = +0.9L;
    Integer expected_result = ZERO_INTEGER;

    test_multiplication(multiplier1, multiplier2, expected_result);
}

TEST(IntegerMultiplicationTest,
     NegativeIntegerAndPositiveImproperRationalFloatingPoint)
{
    Integer     multiplier1 = integer_from_string("-100000000000000000000", 10);
    long double multiplier2 = +99.9L;
    Integer expected_result = 
        integer_from_string("-9900000000000000000000", 10);

    test_multiplication(multiplier1, multiplier2, expected_result);
}

TEST(IntegerMultiplicationTest,
     NegativeIntegerAndNegativeProperRationalFloatingPoint)
{
    Integer     multiplier1 = integer_from_string("-1111111111111111111111", 10);
    long double multiplier2 = -0.9L;
    Integer expected_result = ZERO_INTEGER;

    test_multiplication(multiplier1, multiplier2, expected_result);
}

TEST(IntegerMultiplicationTest,
     NegativeIntegerAndNegativeImproperRationalFloatingPoint)
{
    Integer     multiplier1 = integer_from_string("-1111111111111111111111", 10);
    long double multiplier2 = -99.9L;
    Integer expected_result =
        integer_from_string("+109999999999999999999989", 10);

    test_multiplication(multiplier1, multiplier2, expected_result);
}

} // namespace
