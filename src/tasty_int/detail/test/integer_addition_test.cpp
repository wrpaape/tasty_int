#include "tasty_int/detail/integer_addition.hpp"

#include <limits>

#include "gtest/gtest.h"

#include "tasty_int/detail/conversions/integer_from_string.hpp"
#include "tasty_int/detail/test/integer_arithmetic_test_common.hpp"
#include "tasty_int/detail/test/integer_test_common.hpp"

namespace {

using tasty_int::detail::Integer;
using tasty_int::detail::Sign;
using tasty_int::detail::DIGIT_TYPE_MAX;
using tasty_int::detail::conversions::integer_from_string;
using integer_arithmetic_test_common::check_expected_integer_result;


const Integer ZERO_INTEGER = { .sign = Sign::ZERO, .digits = { 0 } };

template<typename ResultType>
void
check_add_in_place_result(const Integer    &expected_result,
                          const ResultType &augend,
                          const ResultType &result)
{
    EXPECT_EQ(&augend, &result)
        << "+= did not return reference to augend";

   check_expected_integer_result(expected_result, augend);
}

template<typename LhsType, typename RhsType>
void
test_add_in_place(const LhsType &lhs,
                  const RhsType &rhs,
                  const Integer &expected_result)
{
    auto augend = lhs;

    auto &&result = (augend += rhs);

    check_add_in_place_result(expected_result, augend, result);
}

template<typename LhsType, typename RhsType>
void
test_add(const LhsType &lhs,
         const RhsType &rhs,
         const Integer &expected_result)
{
    const Integer result = lhs + rhs;

    EXPECT_EQ(expected_result, result)
        << "+ did not produce the expected result";
}

template<typename Addend1Type, typename Addend2Type>
void
test_addition(const Addend1Type &addend1,
              const Addend2Type &addend2,
              const Integer     &expected_result)
{
    test_add_in_place(addend1, addend2, expected_result);
    test_add_in_place(addend2, addend1, expected_result);

    test_add(addend1, addend2, expected_result);
    test_add(addend2, addend1, expected_result);
}


TEST(IntegerAdditionTest, ZeroIntegerAndZeroInteger)
{
    test_addition(ZERO_INTEGER, ZERO_INTEGER, ZERO_INTEGER);
}

TEST(IntegerAdditionTest, ZeroIntegerAndPositiveInteger)
{
    Integer addend1         = ZERO_INTEGER;
    Integer addend2         = integer_from_string("+111111111111111111", 10);
    Integer expected_result = integer_from_string("+111111111111111111", 10);

    test_addition(addend1, addend2, expected_result);
}

TEST(IntegerAdditionTest, ZeroIntegerAndNegativeInteger)
{
    Integer addend1         = ZERO_INTEGER;
    Integer addend2         = integer_from_string("-222222222222222222", 10);
    Integer expected_result = integer_from_string("-222222222222222222", 10);

    test_addition(addend1, addend2, expected_result);
}

TEST(IntegerAdditionTest, PositiveIntegerAndZeroInteger)
{
    Integer addend1         = integer_from_string("+12345678901234567890", 10);
    Integer addend2         = ZERO_INTEGER;
    Integer expected_result = addend1;

    test_addition(addend1, addend2, expected_result);
}

TEST(IntegerAdditionTest, NegativeIntegerAndZeroInteger)
{
    Integer addend1         = integer_from_string("-12345678901234567890", 10);
    Integer addend2         = ZERO_INTEGER;
    Integer expected_result = addend1;

    test_addition(addend1, addend2, expected_result);
}

TEST(IntegerAdditionTest, PositiveIntegerAndPositiveInteger)
{
    Integer addend1         = integer_from_string("+12345678901234567890", 10);
    Integer addend2         = integer_from_string("+12345678901234567890", 10);
    Integer expected_result = integer_from_string("+24691357802469135780", 10);

    test_addition(addend1, addend2, expected_result);
}

TEST(IntegerAdditionTest, PositiveIntegerAndSameNegativeInteger)
{
    Integer addend1 = integer_from_string("+12345678901234567890", 10);
    Integer addend2 = integer_from_string("-12345678901234567890", 10);

    test_addition(addend1, addend2, ZERO_INTEGER);
}

TEST(IntegerAdditionTest, PositiveIntegerAndSmallerNegativeInteger)
{
    Integer addend1         = integer_from_string("+12345678901234567890", 10);
    Integer addend2         = integer_from_string( "-2345678901234567890", 10);
    Integer expected_result = integer_from_string("+10000000000000000000", 10);

    test_addition(addend1, addend2, expected_result);
}

TEST(IntegerAdditionTest, PositiveIntegerAndLargerNegativeInteger)
{
    Integer addend1         = integer_from_string( "+2345678901234567890", 10);
    Integer addend2         = integer_from_string("-12345678901234567890", 10);
    Integer expected_result = integer_from_string("-10000000000000000000", 10);

    test_addition(addend1, addend2, expected_result);
}


TEST(IntegerAdditionTest, ZeroIntegerAndZeroUnsignedIntegral)
{
    test_addition(ZERO_INTEGER, std::uintmax_t(0), ZERO_INTEGER);
}

TEST(IntegerAdditionTest, ZeroIntegerAndPositiveUnsignedIntegral)
{
    Integer addend1         =                ZERO_INTEGER;
    std::uintmax_t addend2  =                      +33333;
    Integer expected_result = integer_from_string("+33333", 10);

    test_addition(addend1, addend2, expected_result);
}

TEST(IntegerAdditionTest, PositiveIntegerAndZeroUnsignedIntegral)
{
    Integer addend1         = integer_from_string("+12345678901234567890", 10);
    std::uintmax_t addend2  = 0;
    Integer expected_result = addend1;

    test_addition(addend1, addend2, expected_result);
}

TEST(IntegerAdditionTest, PositiveIntegerAndZeroUnsignedIntegralWithWrap)
{
    Integer addend1         = {
        .sign   = Sign::POSITIVE,
        .digits = { 1, 1, 1 }
    };
    std::uintmax_t addend2  = 0;
    Integer expected_result = addend1;

    test_addition(addend1, addend2, expected_result);
}

TEST(IntegerAdditionTest, PositiveIntegerAndPositiveUnsignedIntegral)
{
    Integer addend1         = integer_from_string("+10000000000000033334", 10);
    std::uintmax_t addend2  =                                     +66666;
    Integer expected_result = integer_from_string("+10000000000000100000", 10);

    test_addition(addend1, addend2, expected_result);
}

TEST(IntegerAdditionTest, PositiveIntegerAndPositiveUnsignedIntegralWithWrap)
{
    Integer addend1         = {
        .sign   = Sign::POSITIVE,
        .digits = { DIGIT_TYPE_MAX, DIGIT_TYPE_MAX, DIGIT_TYPE_MAX }
    };
    std::uintmax_t addend2  = std::numeric_limits<std::uintmax_t>::max();
    Integer expected_result = {
        .sign   = Sign::POSITIVE,
        .digits = { DIGIT_TYPE_MAX - 1, DIGIT_TYPE_MAX, 0, 1 }
    };

    test_addition(addend1, addend2, expected_result);
}

TEST(IntegerAdditionTest, NegativeIntegerAndZeroUnsignedIntegral)
{
    Integer addend1         = integer_from_string("-12345678901234567890", 10);
    std::uintmax_t addend2  = 0;
    Integer expected_result = addend1;

    test_addition(addend1, addend2, expected_result);
}

TEST(IntegerAdditionTest, NegativeIntegerAndZeroUnsignedIntegralWithWrap)
{
    Integer addend1         = {
        .sign   = Sign::NEGATIVE,
        .digits = { 2, 2, 2 }
    };
    std::uintmax_t addend2  = 0;
    Integer expected_result = addend1;

    test_addition(addend1, addend2, expected_result);
}

TEST(IntegerAdditionTest, NegativeIntegerAndSmallerUnsignedIntegral)
{
    Integer addend1         = integer_from_string("-12345678901234567890", 10);
    std::uintmax_t addend2  =                                     +57890;
    Integer expected_result = integer_from_string("-12345678901234510000", 10);

    test_addition(addend1, addend2, expected_result);
}

TEST(IntegerAdditionTest, NegativeIntegerAndUnsignedIntegralWithWrap)
{
    Integer addend1         = {
        .sign   = Sign::NEGATIVE,
        .digits = { 1, 2, DIGIT_TYPE_MAX }
    };
    std::uintmax_t addend2  = std::numeric_limits<std::uintmax_t>::max();
    Integer expected_result = {
        .sign   = Sign::NEGATIVE,
        .digits = { 2, 2, DIGIT_TYPE_MAX - 1 }
    };

    test_addition(addend1, addend2, expected_result);
}

TEST(IntegerAdditionTest, NegativeIntegerAndSameUnsignedIntegral)
{
    Integer addend1        = integer_from_string("-57890", 10);
    std::uintmax_t addend2 =                      +57890;

    test_addition(addend1, addend2, ZERO_INTEGER);
}

TEST(IntegerAdditionTest, NegativeIntegerAndLargerUnsignedIntegral)
{
    Integer addend1         = integer_from_string("-57800", 10);
    std::uintmax_t addend2  =                      +57890;
    Integer expected_result = integer_from_string(   "+90", 10);

    test_addition(addend1, addend2, expected_result);
}


TEST(IntegerAdditionTest, ZeroIntegerAndZeroSignedIntegral)
{
    test_addition(ZERO_INTEGER, std::intmax_t(0), ZERO_INTEGER);
}

TEST(IntegerAdditionTest, ZeroIntegerAndPositiveSignedIntegral)
{
    Integer addend1         =                ZERO_INTEGER;
    std::intmax_t addend2   =                      +44444;
    Integer expected_result = integer_from_string("+44444", 10);

    test_addition(addend1, addend2, expected_result);
}

TEST(IntegerAdditionTest, ZeroIntegerAndNegativeSignedIntegral)
{
    Integer addend1         =                ZERO_INTEGER;
    std::intmax_t addend2   =                      -44444;
    Integer expected_result = integer_from_string("-44444", 10);

    test_addition(addend1, addend2, expected_result);
}

TEST(IntegerAdditionTest, PositiveIntegerAndZeroSignedIntegral)
{
    Integer addend1         = integer_from_string("+12345678901234567890", 10);
    std::intmax_t addend2   = 0;
    Integer expected_result = addend1;

    test_addition(addend1, addend2, expected_result);
}

TEST(IntegerAdditionTest, PositiveIntegerAndPositiveSignedIntegral)
{
    Integer addend1         = integer_from_string("+12345678901234567890", 10);
    std::intmax_t addend2   =                                     +32109;
    Integer expected_result = integer_from_string("+12345678901234599999", 10);

    test_addition(addend1, addend2, expected_result);
}

TEST(IntegerAdditionTest, PositiveIntegerAndPositiveSignedIntegralWithWrap)
{
    Integer addend1         = {
        .sign   = Sign::POSITIVE,
        .digits = { DIGIT_TYPE_MAX - 3, DIGIT_TYPE_MAX, 1 }
    };
    std::intmax_t addend2   = 2;
    Integer expected_result = {
        .sign   = Sign::POSITIVE,
        .digits = { DIGIT_TYPE_MAX - 1, DIGIT_TYPE_MAX, 1 }
    };

    test_addition(addend1, addend2, expected_result);
}

TEST(IntegerAdditionTest, PositiveIntegerAndSameNegativeSignedIntegral)
{
    Integer addend1       = integer_from_string("+12345", 10);
    std::intmax_t addend2 =                      -12345;

    test_addition(addend1, addend2, ZERO_INTEGER);
}

TEST(IntegerAdditionTest, PositiveIntegerAndSmallerNegativeSignedIntegral)
{
    Integer addend1         = integer_from_string("+1234567890123456", 10);
    std::intmax_t addend2   =                                 -23456;
    Integer expected_result = integer_from_string("+1234567890100000", 10);

    test_addition(addend1, addend2, expected_result);
}

TEST(IntegerAdditionTest, PositiveIntegerAndLargerNegativeSignedIntegral)
{
    Integer addend1         = integer_from_string("+20000", 10);
    std::intmax_t addend2   =                      -23456;
    Integer expected_result = integer_from_string( "-3456", 10);

    test_addition(addend1, addend2, expected_result);
}

TEST(IntegerAdditionTest, PositiveIntegerAndNegativeSignedIntegralWithWrap)
{
    Integer addend1         = {
        .sign   = Sign::POSITIVE,
        .digits = { DIGIT_TYPE_MAX - 7, DIGIT_TYPE_MAX / 2, 2 }
    };
    std::intmax_t addend2   = std::numeric_limits<std::intmax_t>::lowest();
    Integer expected_result = {
        .sign   = Sign::POSITIVE,
        .digits = { DIGIT_TYPE_MAX - 7, DIGIT_TYPE_MAX, 1 }
    };

    test_addition(addend1, addend2, expected_result);
}

TEST(IntegerAdditionTest, NegativeIntegerAndZeroSignedIntegral)
{
    Integer addend1         = integer_from_string("-12345678901234567890", 10);
    std::intmax_t addend2   = 0;
    Integer expected_result = addend1;

    test_addition(addend1, addend2, expected_result);
}

TEST(IntegerAdditionTest, NegativeIntegerAndSmallerPositiveSignedIntegral)
{
    Integer addend1         = integer_from_string("-12345678901234567890", 10);
    std::intmax_t addend2   =                                     +32109;
    Integer expected_result = integer_from_string("-12345678901234535781", 10);

    test_addition(addend1, addend2, expected_result);
}

TEST(IntegerAdditionTest, NegativeIntegerAndLargerPositiveSignedIntegral)
{
    Integer addend1         = integer_from_string("-1234", 10);
    std::intmax_t addend2   =                      +32109;
    Integer expected_result = integer_from_string("+30875", 10);

    test_addition(addend1, addend2, expected_result);
}

TEST(IntegerAdditionTest, NegativeIntegerAndPositiveSignedIntegralWithWrap)
{
    Integer addend1         = {
        .sign   = Sign::NEGATIVE,
        .digits = { DIGIT_TYPE_MAX - 3, DIGIT_TYPE_MAX, 1 }
    };
    std::intmax_t addend2   = -1;
    Integer expected_result = {
        .sign   = Sign::NEGATIVE,
        .digits = { DIGIT_TYPE_MAX - 2, DIGIT_TYPE_MAX, 1 }
    };

    test_addition(addend1, addend2, expected_result);
}

TEST(IntegerAdditionTest, NegativeIntegerAndNegativeSignedIntegral)
{
    Integer addend1         = integer_from_string("-1234567890123456", 10);
    std::intmax_t addend2   =                                 -23456;
    Integer expected_result = integer_from_string("-1234567890146912", 10);

    test_addition(addend1, addend2, expected_result);
}

TEST(IntegerAdditionTest, NegativeIntegerAndNegativeSignedIntegralWithWrap)
{
    Integer addend1         = {
        .sign   = Sign::POSITIVE,
        .digits = { DIGIT_TYPE_MAX - 7, DIGIT_TYPE_MAX / 2, 2 }
    };
    std::intmax_t addend2   = std::numeric_limits<std::intmax_t>::lowest();
    Integer expected_result = {
        .sign   = Sign::POSITIVE,
        .digits = { DIGIT_TYPE_MAX - 7, DIGIT_TYPE_MAX, 1 }
    };

    test_addition(addend1, addend2, expected_result);
}


TEST(IntegerAdditionTest, ZeroIntegerAndZeroFloatingPoint)
{
    test_addition(ZERO_INTEGER, 0.0L, ZERO_INTEGER);
}

TEST(IntegerAdditionTest, ZeroIntegerAndPositiveFloatingPoint)
{
    Integer addend1         =                      ZERO_INTEGER;
    long double addend2     =                      +7777777.77L;
    Integer expected_result = integer_from_string("+7777777", 10);

    test_addition(addend1, addend2, expected_result);
}

TEST(IntegerAdditionTest, ZeroIntegerAndNegativeFloatingPoint)
{
    Integer addend1         =                      ZERO_INTEGER;
    long double addend2     =                      -7777777.77L;
    Integer expected_result = integer_from_string("-7777777", 10);

    test_addition(addend1, addend2, expected_result);
}

TEST(IntegerAdditionTest, PositiveIntegerAndZeroFloatingPoint)
{
    Integer addend1         = integer_from_string("+12345678901234567890", 10);
    long double addend2     = 0.0L;
    Integer expected_result = addend1;

    test_addition(addend1, addend2, expected_result);
}

TEST(IntegerAdditionTest, PositiveIntegerAndPositiveFloatingPoint)
{
    Integer addend1         = integer_from_string("+12345678901234567890", 10);
    long double addend2     =                                +1234567890.9999L;
    Integer expected_result = integer_from_string("+12345678902469135780", 10);

    test_addition(addend1, addend2, expected_result);
}

TEST(IntegerAdditionTest, PositiveIntegerAndSameNegativeFloatingPoint)
{
    Integer addend1     = integer_from_string("+12345", 10);
    long double addend2 =                      -12345.0L;

    test_addition(addend1, addend2, ZERO_INTEGER);
}

TEST(IntegerAdditionTest, PositiveIntegerAndSmallerNegativeFloatingPoint)
{
    Integer addend1         = integer_from_string("+1234567890123456", 10);
    long double addend2     =                                -123456.0L;
    Integer expected_result = integer_from_string("+1234567890000000", 10);

    test_addition(addend1, addend2, expected_result);
}

TEST(IntegerAdditionTest, PositiveIntegerAndLargerNegativeFloatingPoint)
{
    Integer addend1         = integer_from_string("+20000", 10);
    long double addend2     =                      -23456.0L;
    Integer expected_result = integer_from_string( "-3456", 10);

    test_addition(addend1, addend2, expected_result);
}

TEST(IntegerAdditionTest, NegativeIntegerAndZeroFloatingPoint)
{
    Integer addend1         = integer_from_string("-12345678901234567890", 10);
    long double addend2     = 0.0L;
    Integer expected_result = addend1;

    test_addition(addend1, addend2, expected_result);
}

} // namespace
