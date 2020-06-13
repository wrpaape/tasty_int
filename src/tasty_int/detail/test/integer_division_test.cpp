#include "tasty_int/detail/integer_division.hpp"

#include <type_traits>

#include "gtest/gtest.h"

#include "tasty_int/detail/conversions/integer_from_string.hpp"
#include "tasty_int/detail/test/integer_test_common.hpp"


namespace {

using tasty_int::detail::Integer;
using tasty_int::detail::Sign;
using tasty_int::detail::IntegerDivisionResult;
using tasty_int::detail::conversions::integer_from_string;


const Integer ZERO_INTEGER         = {
    .sign = Sign::ZERO,     .digits = { 0 }
};
const Integer POSITIVE_ONE_INTEGER = {
    .sign = Sign::POSITIVE, .digits = { 1 }
};
const Integer NEGATIVE_ONE_INTEGER = {
    .sign = Sign::NEGATIVE, .digits = { 1 }
};

const std::uintmax_t ZERO_UNSIGNED_INTEGRAL = 0;
const std::uintmax_t ONE_UNSIGNED_INTEGRAL  = +1;

const std::intmax_t ZERO_SIGNED_INTEGRAL         = 0;
const std::intmax_t POSITIVE_ONE_SIGNED_INTEGRAL  = +1;
const std::intmax_t NEGATIVE_ONE_SIGNED_INTEGRAL = +1;

template<typename DividendType,
         typename DivisorType>
void
test_divide_in_place(const DividendType &lhs,
                     const DivisorType  &rhs,
                     const DividendType &expected_result)
{
    auto dividend = lhs;

    auto &&result = (dividend /= rhs);

    EXPECT_EQ(&dividend, &result)
        << "/= did not return reference to dividend";
    EXPECT_EQ(expected_result, dividend)
        << "/= did not produce the expected result";
}

template<typename DividendType,
         typename DivisorType>
void
test_divide(const DividendType &dividend,
            const DivisorType  &divisor,
            const DividendType &expected_result)
{
    auto &&result = dividend / divisor;

    EXPECT_EQ(expected_result, result)
        << "/ did not produce the expected result";
}

template<typename DividendType,
         typename DivisorType>
void
test_modulo_in_place(const DividendType &lhs,
                     const DivisorType  &rhs,
                     const DividendType &expected_result)
{
    auto dividend = lhs;

    auto &&result = (dividend %= rhs);

    EXPECT_EQ(&dividend, &result)
        << "%= did not return reference to dividend";
    EXPECT_EQ(expected_result, dividend)
        << "%= did not produce the expected result";
}

template<typename DividendType,
         typename DivisorType>
void
test_modulo(const DividendType &dividend,
            const DivisorType  &divisor,
            const DividendType &expected_result)
{
    auto &&result = dividend % divisor;

    EXPECT_EQ(expected_result, result)
        << "% did not produce the expected result";
}

template<typename DividendType,
         typename DivisorType,
         typename DivisionResultType>
void
test_div(const DividendType       &dividend,
         const DivisorType        &divisor,
         const DivisionResultType &expected_result)
{
    auto &&result = tasty_int::detail::div(dividend, divisor);

    EXPECT_EQ(expected_result.quotient, result.quotient)
        << "div did not produce the expected quotient";

    EXPECT_EQ(expected_result.remainder, result.remainder)
        << "div did not produce the expected remainder";
}

template<typename DividendType,
         typename DivisorType,
         typename DivisionResultType>
void
test_division(const DividendType       &dividend,
              const DivisorType        &divisor,
              const DivisionResultType &expected_result)
{
    test_divide_in_place(dividend, divisor, expected_result.quotient);
    test_divide(         dividend, divisor, expected_result.quotient);
    test_modulo_in_place(dividend, divisor, expected_result.remainder);
    test_modulo(         dividend, divisor, expected_result.remainder);
    test_div(            dividend, divisor, expected_result);
}


TEST(IntegerDivisionTest, ZeroIntegerAndPositiveInteger)
{
    Integer dividend = ZERO_INTEGER;
    Integer divisor  = integer_from_string("+111111111111111111", 10);
    IntegerDivisionResult expected_result = {
        .quotient  = ZERO_INTEGER,
        .remainder = ZERO_INTEGER
    };

    test_division(dividend, divisor, expected_result);
}

TEST(IntegerDivisionTest, ZeroIntegerAndNegativeInteger)
{
    Integer dividend        = ZERO_INTEGER;
    Integer divisor         = integer_from_string("-222222222222222222", 10);
    IntegerDivisionResult expected_result = {
        .quotient  = ZERO_INTEGER,
        .remainder = ZERO_INTEGER
    };

    test_division(dividend, divisor, expected_result);
}

TEST(IntegerDivisionTest, PositiveIntegerAndSamePositiveInteger)
{
    Integer dividend = integer_from_string("+123123123123123123123123123", 10);
    Integer divisor  = dividend;
    IntegerDivisionResult expected_result = {
        .quotient  = POSITIVE_ONE_INTEGER,
        .remainder = ZERO_INTEGER
    };

    test_division(dividend, divisor, expected_result);
}

TEST(IntegerDivisionTest, PositiveIntegerAndSameNegativeInteger)
{
    Integer dividend = integer_from_string("+123123123123123123123123123", 10);
    Integer divisor  = { .sign = Sign::NEGATIVE, .digits = dividend.digits };
    IntegerDivisionResult expected_result = {
        .quotient  = NEGATIVE_ONE_INTEGER,
        .remainder = ZERO_INTEGER
    };

    test_division(dividend, divisor, expected_result);
}

TEST(IntegerDivisionTest, LargerPositiveIntegerAndSmallerPositiveInteger)
{
    Integer dividend = integer_from_string("+3333333333333333333333333333", 10);
    Integer divisor  = integer_from_string( "+444444444444444444444444444", 10);
    IntegerDivisionResult expected_result = {
        .quotient  = integer_from_string("+7", 10),
        .remainder = integer_from_string("+222222222222222222222222225", 10)
    };

    test_division(dividend, divisor, expected_result);
}

TEST(IntegerDivisionTest, LargerPositiveIntegerAndSmallerNegativeInteger)
{
    Integer dividend = integer_from_string("+3333333333333333333333333333", 10);
    Integer divisor  = integer_from_string( "-444444444444444444444444444", 10);
    IntegerDivisionResult expected_result = {
        .quotient  = integer_from_string("-7", 10),
        .remainder = integer_from_string("+222222222222222222222222225", 10)
    };

    test_division(dividend, divisor, expected_result);
}

TEST(IntegerDivisionTest, SmallerPositiveIntegerAndLargerPositiveInteger)
{
    Integer dividend        = integer_from_string("+50000000000", 10);
    Integer divisor         = integer_from_string("+100000000000000000000", 10);
    IntegerDivisionResult expected_result = {
        .quotient  = ZERO_INTEGER,
        .remainder = dividend
    };

    test_division(dividend, divisor, expected_result);
}

TEST(IntegerDivisionTest, SmallerPositiveIntegerAndLargerNegativeInteger)
{
    Integer dividend        = integer_from_string("+50000000000", 10);
    Integer divisor         = integer_from_string("-100000000000000000000", 10);
    IntegerDivisionResult expected_result = {
        .quotient  = ZERO_INTEGER,
        .remainder = dividend
    };

    test_division(dividend, divisor, expected_result);
}

TEST(IntegerDivisionTest, NegativeIntegerAndSamePositiveInteger)
{
    Integer dividend = integer_from_string("-123123123123123123123123123", 10);
    Integer divisor  = { .sign = Sign::POSITIVE, .digits = dividend.digits };
    IntegerDivisionResult expected_result = {
        .quotient  = NEGATIVE_ONE_INTEGER,
        .remainder = ZERO_INTEGER
    };

    test_division(dividend, divisor, expected_result);
}

TEST(IntegerDivisionTest, NegativeIntegerAndSameNegativeInteger)
{
    Integer dividend = integer_from_string("-123123123123123123123123123", 10);
    Integer divisor  = dividend;
    IntegerDivisionResult expected_result = {
        .quotient  = POSITIVE_ONE_INTEGER,
        .remainder = ZERO_INTEGER
    };

    test_division(dividend, divisor, expected_result);
}

TEST(IntegerDivisionTest, LargerNegativeIntegerAndSmallerPositiveInteger)
{
    Integer dividend = integer_from_string("-5555555555555555555555555555", 10);
    Integer divisor  = integer_from_string( "+666666666666666666666666666", 10);
    IntegerDivisionResult expected_result = {
        .quotient  = integer_from_string("-8", 10),
        .remainder = integer_from_string("-222222222222222222222222227", 10)
    };

    test_division(dividend, divisor, expected_result);
}

TEST(IntegerDivisionTest, LargerNegativeIntegerAndSmallerNegativeInteger)
{
    Integer dividend = integer_from_string("-5555555555555555555555555555", 10);
    Integer divisor  = integer_from_string( "-666666666666666666666666666", 10);
    IntegerDivisionResult expected_result = {
        .quotient  = integer_from_string("+8", 10),
        .remainder = integer_from_string("-222222222222222222222222227", 10)
    };

    test_division(dividend, divisor, expected_result);
}

TEST(IntegerDivisionTest, SmallerNegativeIntegerAndLargerPositiveInteger)
{
    Integer dividend        = integer_from_string("-50000000000", 10);
    Integer divisor         = integer_from_string("+100000000000000000000", 10);
    IntegerDivisionResult expected_result = {
        .quotient  = ZERO_INTEGER,
        .remainder = dividend
    };

    test_division(dividend, divisor, expected_result);
}

TEST(IntegerDivisionTest, SmallerNegativeIntegerAndLargerNegativeInteger)
{
    Integer dividend        = integer_from_string("-50000000000", 10);
    Integer divisor         = integer_from_string("-100000000000000000000", 10);
    IntegerDivisionResult expected_result = {
        .quotient  = ZERO_INTEGER,
        .remainder = dividend
    };

    test_division(dividend, divisor, expected_result);
}


TEST(IntegerDivisionTest, ZeroIntegerAndPositiveUnsignedIntegral)
{
    Integer dividend       = ZERO_INTEGER;
    std::uintmax_t divisor = +11111;
    IntegerDivisionResult expected_result = {
        .quotient  = ZERO_INTEGER,
        .remainder = ZERO_INTEGER
    };

    test_division(dividend, divisor, expected_result);
}

TEST(IntegerDivisionTest, PositiveIntegerAndSamePositiveUnsignedIntegral)
{
    Integer dividend       = integer_from_string("+12312", 10);
    std::uintmax_t divisor =                      +12312;
    IntegerDivisionResult expected_result = {
        .quotient  = POSITIVE_ONE_INTEGER,
        .remainder = ZERO_INTEGER
    };

    test_division(dividend, divisor, expected_result);
}

TEST(IntegerDivisionTest, LargerPositiveIntegerAndSmallerPositiveUnsignedIntegral)
{
    Integer dividend       = integer_from_string("+3333333333333333333333", 10);
    std::uintmax_t divisor =                                       +44444;
    IntegerDivisionResult expected_result = {
        .quotient  = integer_from_string("+75000750007500075", 10),
        .remainder = integer_from_string("+33", 10)
    };

    test_division(dividend, divisor, expected_result);
}

TEST(IntegerDivisionTest, SmallerPositiveIntegerAndLargerPositiveUnsignedIntegral)
{
    Integer dividend       = integer_from_string("+5000", 10);
    std::uintmax_t divisor =                     +10000;
    IntegerDivisionResult expected_result = {
        .quotient  = ZERO_INTEGER,
        .remainder = dividend
    };

    test_division(dividend, divisor, expected_result);
}

TEST(IntegerDivisionTest, NegativeIntegerAndSamePositiveUnsignedIntegral)
{
    Integer dividend       = integer_from_string("-12312", 10);
    std::uintmax_t divisor =                      +12312;
    IntegerDivisionResult expected_result = {
        .quotient  = NEGATIVE_ONE_INTEGER,
        .remainder = ZERO_INTEGER
    };

    test_division(dividend, divisor, expected_result);
}

TEST(IntegerDivisionTest, LargerNegativeIntegerAndSmallerPositiveUnsignedIntegral)
{
    Integer dividend       = integer_from_string("-5555555555555555555555", 10);
    std::uintmax_t divisor =                                        +6666;
    IntegerDivisionResult expected_result = {
        .quotient  = integer_from_string("-833416675000833416", 10),
        .remainder = integer_from_string("-4499", 10)
    };

    test_division(dividend, divisor, expected_result);
}

TEST(IntegerDivisionTest, SmallerNegativeIntegerAndLargerPositiveUnsignedIntegral)
{
    Integer dividend       = integer_from_string("-5000", 10);
    std::uintmax_t divisor =                     +10000;
    IntegerDivisionResult expected_result = {
        .quotient  = ZERO_INTEGER,
        .remainder = dividend
    };

    test_division(dividend, divisor, expected_result);
}


TEST(IntegerDivisionTest, ZeroIntegerAndPositiveSignedIntegral)
{
    Integer dividend      = ZERO_INTEGER;
    std::intmax_t divisor = +11111;
    IntegerDivisionResult expected_result = {
        .quotient  = ZERO_INTEGER,
        .remainder = ZERO_INTEGER
    };

    test_division(dividend, divisor, expected_result);
}

TEST(IntegerDivisionTest, ZeroIntegerAndNegativeSignedIntegral)
{
    Integer dividend      = ZERO_INTEGER;
    std::intmax_t divisor = -11111;
    IntegerDivisionResult expected_result = {
        .quotient  = ZERO_INTEGER,
        .remainder = ZERO_INTEGER
    };

    test_division(dividend, divisor, expected_result);
}

TEST(IntegerDivisionTest, PositiveIntegerAndSamePositiveSignedIntegral)
{
    Integer dividend      = integer_from_string("+12312", 10);
    std::intmax_t divisor =                      +12312;
    IntegerDivisionResult expected_result = {
        .quotient  = POSITIVE_ONE_INTEGER,
        .remainder = ZERO_INTEGER
    };

    test_division(dividend, divisor, expected_result);
}

TEST(IntegerDivisionTest, PositiveIntegerAndSameNegativeSignedIntegral)
{
    Integer dividend      = integer_from_string("+12312", 10);
    std::intmax_t divisor =                      -12312;
    IntegerDivisionResult expected_result = {
        .quotient  = NEGATIVE_ONE_INTEGER,
        .remainder = ZERO_INTEGER
    };

    test_division(dividend, divisor, expected_result);
}

TEST(IntegerDivisionTest, LargerPositiveIntegerAndSmallerPositiveSignedIntegral)
{
    Integer dividend      = integer_from_string("+3333333333333333333333", 10);
    std::intmax_t divisor =                                       +44444;
    IntegerDivisionResult expected_result = {
        .quotient  = integer_from_string("+75000750007500075", 10),
        .remainder = integer_from_string("+33", 10)
    };

    test_division(dividend, divisor, expected_result);
}

TEST(IntegerDivisionTest, LargerPositiveIntegerAndSmallerNegativeSignedIntegral)
{
    Integer dividend      = integer_from_string("+3333333333333333333333", 10);
    std::intmax_t divisor =                                       -44444;
    IntegerDivisionResult expected_result = {
        .quotient  = integer_from_string("-75000750007500075", 10),
        .remainder = integer_from_string("+33", 10)
    };

    test_division(dividend, divisor, expected_result);
}

TEST(IntegerDivisionTest, SmallerPositiveIntegerAndLargerPositiveSignedIntegral)
{
    Integer dividend       = integer_from_string("+5000", 10);
    std::intmax_t divisor =                     +10000;
    IntegerDivisionResult expected_result = {
        .quotient  = ZERO_INTEGER,
        .remainder = dividend
    };

    test_division(dividend, divisor, expected_result);
}

TEST(IntegerDivisionTest, SmallerPositiveIntegerAndLargerNegativeSignedIntegral)
{
    Integer dividend      = integer_from_string("+5000", 10);
    std::intmax_t divisor =                     -10000;
    IntegerDivisionResult expected_result = {
        .quotient  = ZERO_INTEGER,
        .remainder = dividend
    };

    test_division(dividend, divisor, expected_result);
}

TEST(IntegerDivisionTest, NegativeIntegerAndSamePositiveSignedIntegral)
{
    Integer dividend      = integer_from_string("-12312", 10);
    std::intmax_t divisor =                      +12312;
    IntegerDivisionResult expected_result = {
        .quotient  = NEGATIVE_ONE_INTEGER,
        .remainder = ZERO_INTEGER
    };

    test_division(dividend, divisor, expected_result);
}

TEST(IntegerDivisionTest, NegativeIntegerAndSameNegativeSignedIntegral)
{
    Integer dividend      = integer_from_string("-12312", 10);
    std::intmax_t divisor =                      -12312;
    IntegerDivisionResult expected_result = {
        .quotient  = POSITIVE_ONE_INTEGER,
        .remainder = ZERO_INTEGER
    };

    test_division(dividend, divisor, expected_result);
}

TEST(IntegerDivisionTest, LargerNegativeIntegerAndSmallerPositiveSignedIntegral)
{
    Integer dividend      = integer_from_string("-5555555555555555555555", 10);
    std::intmax_t divisor =                                        +6666;
    IntegerDivisionResult expected_result = {
        .quotient  = integer_from_string("-833416675000833416", 10),
        .remainder = integer_from_string("-4499", 10)
    };

    test_division(dividend, divisor, expected_result);
}

TEST(IntegerDivisionTest, LargerNegativeIntegerAndSmallerNegativeSignedIntegral)
{
    Integer dividend      = integer_from_string("-5555555555555555555555", 10);
    std::intmax_t divisor =                                        -6666;
    IntegerDivisionResult expected_result = {
        .quotient  = integer_from_string("+833416675000833416", 10),
        .remainder = integer_from_string("-4499", 10)
    };

    test_division(dividend, divisor, expected_result);
}

TEST(IntegerDivisionTest, SmallerNegativeIntegerAndLargerPositiveSignedIntegral)
{
    Integer dividend      = integer_from_string("-5000", 10);
    std::intmax_t divisor =                     +10000;
    IntegerDivisionResult expected_result = {
        .quotient  = ZERO_INTEGER,
        .remainder = dividend
    };

    test_division(dividend, divisor, expected_result);
}

TEST(IntegerDivisionTest, SmallerNegativeIntegerAndLargerNegativeSignedIntegral)
{
    Integer dividend      = integer_from_string("-5000", 10);
    std::intmax_t divisor =                     -10000;
    IntegerDivisionResult expected_result = {
        .quotient  = ZERO_INTEGER,
        .remainder = dividend
    };

    test_division(dividend, divisor, expected_result);
}


TEST(IntegerDivisionTest, ZeroIntegerAndPositiveFloatingPoint)
{
    Integer dividend    = ZERO_INTEGER;
    long double divisor = +1.0e100L;
    IntegerDivisionResult expected_result = {
        .quotient  = ZERO_INTEGER,
        .remainder = ZERO_INTEGER
    };

    test_division(dividend, divisor, expected_result);
}

TEST(IntegerDivisionTest, ZeroIntegerAndNegativeFloatingPoint)
{
    Integer dividend      = ZERO_INTEGER;
    long double divisor = -1.0e100L;
    IntegerDivisionResult expected_result = {
        .quotient  = ZERO_INTEGER,
        .remainder = ZERO_INTEGER
    };

    test_division(dividend, divisor, expected_result);
}

TEST(IntegerDivisionTest, PositiveIntegerAndSamePositiveFloatingPoint)
{
    Integer dividend    = integer_from_string("+1000000000000000000000000", 10);
    long double divisor =                      +1.0e24L;
    IntegerDivisionResult expected_result = {
        .quotient  = POSITIVE_ONE_INTEGER,
        .remainder = ZERO_INTEGER
    };

    test_division(dividend, divisor, expected_result);
}

TEST(IntegerDivisionTest, PositiveIntegerAndSameNegativeFloatingPoint)
{
    Integer dividend    = integer_from_string("+1000000000000000000000000", 10);
    long double divisor =                      -1.0e24L;
    IntegerDivisionResult expected_result = {
        .quotient  = NEGATIVE_ONE_INTEGER,
        .remainder = ZERO_INTEGER
    };

    test_division(dividend, divisor, expected_result);
}

TEST(IntegerDivisionTest, LargerPositiveIntegerAndSmallerPositiveFloatingPoint)
{
    Integer dividend    = integer_from_string("+12345678901234567890", 10);
    long double divisor =                                +1234567891.0L;
    IntegerDivisionResult expected_result = {
        .quotient  = integer_from_string("+9999999992", 10),
        .remainder = integer_from_string("+1111111018", 10)
    };

    test_division(dividend, divisor, expected_result);
}

TEST(IntegerDivisionTest, LargerPositiveIntegerAndSmallerNegativeFloatingPoint)
{
    Integer dividend    = integer_from_string("+12345678901234567890", 10);
    long double divisor =                                -1234567891.0L;
    IntegerDivisionResult expected_result = {
        .quotient  = integer_from_string("-9999999992", 10),
        .remainder = integer_from_string("+1111111018", 10)
    };


    test_division(dividend, divisor, expected_result);
}

TEST(IntegerDivisionTest, SmallerPositiveIntegerAndLargerPositiveFloatingPoint)
{
    Integer dividend    = integer_from_string("+123", 10);
    long double divisor =                     +1234.0L;
    IntegerDivisionResult expected_result = {
        .quotient  = ZERO_INTEGER,
        .remainder = dividend
    };

    test_division(dividend, divisor, expected_result);
}

TEST(IntegerDivisionTest, SmallerPositiveIntegerAndLargerNegativeFloatingPoint)
{
    Integer dividend    = integer_from_string("+123", 10);
    long double divisor =                     -1234.0L;
    IntegerDivisionResult expected_result = {
        .quotient  = ZERO_INTEGER,
        .remainder = dividend
    };

    test_division(dividend, divisor, expected_result);
}

TEST(IntegerDivisionTest, NegativeIntegerAndSamePositiveFloatingPoint)
{
    Integer dividend    = integer_from_string("-1234567890987654321", 10);
    long double divisor =                      +1234567890987654321.0L;;
    IntegerDivisionResult expected_result = {
        .quotient  = NEGATIVE_ONE_INTEGER,
        .remainder = ZERO_INTEGER
    };

    test_division(dividend, divisor, expected_result);
}

TEST(IntegerDivisionTest, NegativeIntegerAndSameNegativeFloatingPoint)
{
    Integer dividend    = integer_from_string("-1234567890987654321", 10);
    long double divisor =                      -1234567890987654321.0L;;
    IntegerDivisionResult expected_result = {
        .quotient  = POSITIVE_ONE_INTEGER,
        .remainder = ZERO_INTEGER
    };

    test_division(dividend, divisor, expected_result);
}

TEST(IntegerDivisionTest, LargerNegativeIntegerAndSmallerPositiveFloatingPoint)
{
    Integer dividend    = integer_from_string("-789789789789789789789", 10);
    long double divisor =                            +456456456456456.0L;
    IntegerDivisionResult expected_result = {
        .quotient  = integer_from_string("-1730263", 10),
        .remainder = integer_from_string("-72072072861861", 10)
    };

    test_division(dividend, divisor, expected_result);
}

TEST(IntegerDivisionTest, LargerNegativeIntegerAndSmallerNegativeFloatingPoint)
{
    Integer dividend    = integer_from_string("-789789789789789789789", 10);
    long double divisor =                            -456456456456456.0L;
    IntegerDivisionResult expected_result = {
        .quotient  = integer_from_string("+1730263", 10),
        .remainder = integer_from_string("-72072072861861", 10)
    };

    test_division(dividend, divisor, expected_result);
}

TEST(IntegerDivisionTest, SmallerNegativeIntegerAndLargerPositiveFloatingPoint)
{
    Integer dividend    = integer_from_string("-1234567890", 10);
    long double divisor =              +102030405060708090.0L;
    IntegerDivisionResult expected_result = {
        .quotient  = ZERO_INTEGER,
        .remainder = dividend
    };

    test_division(dividend, divisor, expected_result);
}

TEST(IntegerDivisionTest, SmallerNegativeIntegerAndLargerNegativeFloatingPoint)
{
    Integer dividend    = integer_from_string("-1234567890", 10);
    long double divisor =              -102030405060708090.0L;
    IntegerDivisionResult expected_result = {
        .quotient  = ZERO_INTEGER,
        .remainder = dividend
    };

    test_division(dividend, divisor, expected_result);
}

} // namespace
