#include "tasty_int/detail/integer_addition_and_subtraction.hpp"

#include <type_traits>

#include "gtest/gtest.h"

#include "tasty_int/detail/conversions/integer_from_floating_point.hpp"
#include "tasty_int/detail/conversions/integer_from_string.hpp"
#include "tasty_int/detail/test/integer_test_common.hpp"

namespace {

using tasty_int::detail::Integer;
using tasty_int::detail::Sign;
using tasty_int::detail::conversions::integer_from_floating_point;
using tasty_int::detail::conversions::integer_from_string;


Integer ZERO_INTEGER = { .sign = Sign::ZERO, .digits = { 0 } };

void
check_subtract_in_place_result(const Integer &expected_result,
                               const Integer &minuend,
                               const Integer &result)
{
    EXPECT_EQ(&minuend, &result)
        << "-= did not return reference to minuend";

    EXPECT_EQ(expected_result, minuend)
        << "-= did not produce the expected result";

}

template<typename SubtrahendType>
void
test_subtract_in_place(const Integer        &original_minuend,
                       const SubtrahendType &subtrahend,
                       const Integer        &expected_result)
{
    Integer minuend = original_minuend;

    const Integer &result = (minuend -= subtrahend);

    check_subtract_in_place_result(expected_result, minuend, result);
}

template<typename MinuendType, typename SubtrahendType>
void
test_subtract(const MinuendType    &minuend,
              const SubtrahendType &subtrahend,
              const Integer        &expected_result)
{
    const Integer result = minuend - subtrahend;

    EXPECT_EQ(expected_result, result)
        << "- did not produce the expected result";
}

template<typename MinuendType, typename SubtrahendType>
void
test_subtraction(const MinuendType    &minuend,
                 const SubtrahendType &subtrahend,
                 const Integer        &expected_result)
{
    if constexpr (std::is_same_v<MinuendType, Integer>)
        test_subtract_in_place(minuend, subtrahend, expected_result);

    test_subtract(minuend, subtrahend, expected_result);
}


TEST(IntegerSubtractionTest, ZeroIntegerAndZeroInteger)
{
    test_subtraction(ZERO_INTEGER, ZERO_INTEGER, ZERO_INTEGER);
}

TEST(IntegerSubtractionTest, ZeroIntegerAndPositiveInteger)
{
    Integer minuend         = ZERO_INTEGER;
    Integer subtrahend      = integer_from_string("+111111111111111111", 10);
    Integer expected_result = integer_from_string("-111111111111111111", 10);

    test_subtraction(minuend, subtrahend, expected_result);
}

TEST(IntegerSubtractionTest, ZeroIntegerAndNegativeInteger)
{
    Integer minuend         = ZERO_INTEGER;
    Integer subtrahend      = integer_from_string("-222222222222222222", 10);
    Integer expected_result = integer_from_string("+222222222222222222", 10);

    test_subtraction(minuend, subtrahend, expected_result);
}

TEST(IntegerSubtractionTest, PositiveIntegerAndZeroInteger)
{
    Integer minuend         = integer_from_string("+9876543210123456789", 10);
    Integer subtrahend      = ZERO_INTEGER;
    Integer expected_result = minuend;

    test_subtraction(minuend, subtrahend, expected_result);
}

TEST(IntegerSubtractionTest, PositiveIntegerAndSamePositiveInteger)
{
    Integer minuend         = integer_from_string("+9876543210123456789", 10);
    Integer subtrahend      = minuend;
    Integer expected_result = ZERO_INTEGER;

    test_subtraction(minuend, subtrahend, expected_result);
}

TEST(IntegerSubtractionTest, PositiveIntegerAndSmallerPositiveInteger)
{
    Integer minuend         = integer_from_string("+9876543210123456789", 10);
    Integer subtrahend      = integer_from_string(          "+123456789", 10);
    Integer expected_result = integer_from_string("+9876543210000000000", 10);

    test_subtraction(minuend, subtrahend, expected_result);
}

TEST(IntegerSubtractionTest, PositiveIntegerAndLargerPositiveInteger)
{
    Integer minuend         = integer_from_string( "+9876543210123456789", 10);
    Integer subtrahend      = integer_from_string("+19876543210123456789", 10);
    Integer expected_result = integer_from_string("-10000000000000000000", 10);

    test_subtraction(minuend, subtrahend, expected_result);
}

TEST(IntegerSubtractionTest, PositiveIntegerAndNegativeInteger)
{
    Integer minuend         = integer_from_string( "+9876543210123456789", 10);
    Integer subtrahend      = integer_from_string( "-9876543210123456789", 10);
    Integer expected_result = integer_from_string("+19753086420246913578", 10);

    test_subtraction(minuend, subtrahend, expected_result);
}

TEST(IntegerSubtractionTest, NegativeIntegerAndZeroInteger)
{
    Integer minuend         = integer_from_string("-9876543210123456789", 10);
    Integer subtrahend      = ZERO_INTEGER;
    Integer expected_result = minuend;

    test_subtraction(minuend, subtrahend, expected_result);
}

TEST(IntegerSubtractionTest, NegativeIntegerAndSameNegativeInteger)
{
    Integer minuend         = integer_from_string("-9876543210123456789", 10);
    Integer subtrahend      = minuend;
    Integer expected_result = ZERO_INTEGER;

    test_subtraction(minuend, subtrahend, expected_result);
}

TEST(IntegerSubtractionTest, NegativeIntegerAndSmallerNegativeInteger)
{
    Integer minuend         = integer_from_string("-9876543210123456789", 10);
    Integer subtrahend      = integer_from_string(          "-123456789", 10);
    Integer expected_result = integer_from_string("-9876543210000000000", 10);

    test_subtraction(minuend, subtrahend, expected_result);
}

TEST(IntegerSubtractionTest, NegativeIntegerAndLargerNegativeInteger)
{
    Integer minuend         = integer_from_string( "-9876543210123456789", 10);
    Integer subtrahend      = integer_from_string("-19876543210123456789", 10);
    Integer expected_result = integer_from_string("+10000000000000000000", 10);

    test_subtraction(minuend, subtrahend, expected_result);
}

TEST(IntegerSubtractionTest, NegativeIntegerAndPositiveInteger)
{
    Integer minuend         = integer_from_string( "-9876543210123456789", 10);
    Integer subtrahend      = integer_from_string( "+9876543210123456789", 10);
    Integer expected_result = integer_from_string("-19753086420246913578", 10);

    test_subtraction(minuend, subtrahend, expected_result);
}


TEST(IntegerSubtractionTest, ZeroIntegerAndZeroUnsignedIntegral)
{
    test_subtraction(ZERO_INTEGER, std::uintmax_t(0), ZERO_INTEGER);
}

TEST(IntegerSubtractionTest, ZeroIntegerAndPositiveUnsignedIntegral)
{
    Integer minuend           =                ZERO_INTEGER;
    std::uintmax_t subtrahend =                      +55555;
    Integer expected_result   = integer_from_string("-55555", 10);

    test_subtraction(minuend, subtrahend, expected_result);
}

TEST(IntegerSubtractionTest, PositiveIntegerAndZeroUnsignedIntegral)
{
    Integer minuend           = integer_from_string("+54321", 10);
    std::uintmax_t subtrahend = 0;
    Integer expected_result   = minuend;

    test_subtraction(minuend, subtrahend, expected_result);
}

TEST(IntegerSubtractionTest, PositiveIntegerAndSamePositiveUnsignedIntegral)
{
    Integer minuend           = integer_from_string("+54321", 10);
    std::uintmax_t subtrahend =                      +54321;
    Integer expected_result   =                ZERO_INTEGER;

    test_subtraction(minuend, subtrahend, expected_result);
}

TEST(IntegerSubtractionTest, PositiveIntegerAndSmallerPositiveUnsignedIntegral)
{
    Integer minuend           = integer_from_string("+54321", 10);
    std::uintmax_t subtrahend =                      +43210;
    Integer expected_result   = integer_from_string("+11111", 10);

    test_subtraction(minuend, subtrahend, expected_result);
}

TEST(IntegerSubtractionTest, PositiveIntegerAndLargerPositiveUnsignedIntegral)
{
    Integer minuend           = integer_from_string("+54321", 10);
    std::uintmax_t subtrahend =                      +65432;
    Integer expected_result   = integer_from_string("-11111", 10);

    test_subtraction(minuend, subtrahend, expected_result);
}

TEST(IntegerSubtractionTest, NegativeIntegerAndZeroUnsignedIntegral)
{
    Integer minuend           = integer_from_string("-54321", 10);
    std::uintmax_t subtrahend = 0;
    Integer expected_result   = minuend;

    test_subtraction(minuend, subtrahend, expected_result);
}

TEST(IntegerSubtractionTest, NegativeIntegerAndPositiveUnsignedIntegral)
{
    Integer minuend           = integer_from_string("-54321", 10);
    std::uintmax_t subtrahend =                      +11111;
    Integer expected_result   = integer_from_string("-65432", 10);

    test_subtraction(minuend, subtrahend, expected_result);
}

TEST(IntegerSubtractionTest, ZeroUnsignedIntegralAndZeroInteger)
{
    test_subtraction(std::uintmax_t(0), ZERO_INTEGER, ZERO_INTEGER);
}

TEST(IntegerSubtractionTest, PositiveUnsignedIntegralAndZeroInteger)
{
    std::uintmax_t minuend  =                      +54321;
    Integer subtrahend      =                ZERO_INTEGER;
    Integer expected_result = integer_from_string("+54321", 10);

    test_subtraction(minuend, subtrahend, expected_result);
}

TEST(IntegerSubtractionTest, PositiveUnsignedIntegralAndSamePositiveInteger)
{
    std::uintmax_t minuend  =                      +54321;
    Integer subtrahend      = integer_from_string("+54321", 10);
    Integer expected_result = ZERO_INTEGER;

    test_subtraction(minuend, subtrahend, expected_result);
}

TEST(IntegerSubtractionTest, PositiveUnsignedIntegralAndSmallerPositiveInteger)
{
    std::uintmax_t minuend  =                      +54321;
    Integer subtrahend      = integer_from_string("+43210", 10);
    Integer expected_result = integer_from_string("+11111", 10);

    test_subtraction(minuend, subtrahend, expected_result);
}

TEST(IntegerSubtractionTest, PositiveUnsignedIntegralAndLargerPositiveInteger)
{
    std::uintmax_t minuend  =                      +54321;
    Integer subtrahend      = integer_from_string("+65432", 10);
    Integer expected_result = integer_from_string("-11111", 10);

    test_subtraction(minuend, subtrahend, expected_result);
}


TEST(IntegerSubtractionTest, ZeroIntegerAndZeroSignedIntegral)
{
    test_subtraction(ZERO_INTEGER, std::intmax_t(0), ZERO_INTEGER);
}

TEST(IntegerSubtractionTest, ZeroIntegerAndPositiveSignedIntegral)
{
    Integer minuend          =                 ZERO_INTEGER;
    std::intmax_t subtrahend =                      +666666;
    Integer expected_result  = integer_from_string("-666666", 10);

    test_subtraction(minuend, subtrahend, expected_result);
}

TEST(IntegerSubtractionTest, ZeroIntegerAndNegativeSignedIntegral)
{
    Integer minuend          =                  ZERO_INTEGER;
    std::intmax_t subtrahend =                      -7777777;
    Integer expected_result  = integer_from_string("+7777777", 10);

    test_subtraction(minuend, subtrahend, expected_result);
}

TEST(IntegerSubtractionTest, PositiveIntegerAndZeroSignedIntegral)
{
    Integer minuend          = integer_from_string("+32123", 10);
    std::intmax_t subtrahend = 0;
    Integer expected_result  = minuend;

    test_subtraction(minuend, subtrahend, expected_result);
}

TEST(IntegerSubtractionTest, PositiveIntegerAndSamePositiveSignedIntegral)
{
    Integer minuend          = integer_from_string("+32123", 10);
    std::intmax_t subtrahend =                      +32123;
    Integer expected_result  =                ZERO_INTEGER;

    test_subtraction(minuend, subtrahend, expected_result);
}

TEST(IntegerSubtractionTest, PositiveIntegerAndSmallerPositiveSignedIntegral)
{
    Integer minuend          = integer_from_string("+32123", 10);
    std::intmax_t subtrahend =                       +2123;
    Integer expected_result  = integer_from_string("+30000", 10);

    test_subtraction(minuend, subtrahend, expected_result);
}

TEST(IntegerSubtractionTest, PositiveIntegerAndLargerPositiveSignedIntegral)
{
    Integer minuend          = integer_from_string("+32123", 10);
    std::intmax_t subtrahend =                      +32767;
    Integer expected_result  = integer_from_string(  "-644", 10);

    test_subtraction(minuend, subtrahend, expected_result);
}

TEST(IntegerSubtractionTest, PositiveIntegerAndNegativeSignedIntegral)
{
    Integer minuend          = integer_from_string("+32123", 10);
    std::intmax_t subtrahend =                      -32123;
    Integer expected_result  = integer_from_string("+64246", 10);

    test_subtraction(minuend, subtrahend, expected_result);
}

TEST(IntegerSubtractionTest, NegativeIntegerAndZeroSignedIntegral)
{
    Integer minuend          = integer_from_string("-32123", 10);
    std::intmax_t subtrahend = 0;
    Integer expected_result  = minuend;

    test_subtraction(minuend, subtrahend, expected_result);
}

TEST(IntegerSubtractionTest, NegativeIntegerAndSameNegativeSignedIntegral)
{
    Integer minuend          = integer_from_string("-32123", 10);
    std::intmax_t subtrahend =                      -32123;
    Integer expected_result  =                ZERO_INTEGER;

    test_subtraction(minuend, subtrahend, expected_result);
}

TEST(IntegerSubtractionTest, NegativeIntegerAndSmallerNegativeSignedIntegral)
{
    Integer minuend          = integer_from_string("-32123", 10);
    std::intmax_t subtrahend =                      -32100;
    Integer expected_result  = integer_from_string(   "-23", 10);

    test_subtraction(minuend, subtrahend, expected_result);
}

TEST(IntegerSubtractionTest, NegativeIntegerAndLargerNegativeSignedIntegral)
{
    Integer minuend          = integer_from_string("-32123", 10);
    std::intmax_t subtrahend =                      -32767;
    Integer expected_result  = integer_from_string(  "+644", 10);

    test_subtraction(minuend, subtrahend, expected_result);
}

TEST(IntegerSubtractionTest, NegativeIntegerAndPositiveSignedIntegral)
{
    Integer minuend          = integer_from_string("-32123", 10);
    std::intmax_t subtrahend =                      +32123;
    Integer expected_result  = integer_from_string("-64246", 10);

    test_subtraction(minuend, subtrahend, expected_result);
}

TEST(IntegerSubtractionTest, ZeroSignedIntegralAndZeroInteger)
{
    test_subtraction(std::intmax_t(0), ZERO_INTEGER, ZERO_INTEGER);
}

TEST(IntegerSubtractionTest, PositiveSignedIntegralAndZeroInteger)
{
    std::intmax_t minuend   =                      +32123;
    Integer subtrahend      =                ZERO_INTEGER;
    Integer expected_result = integer_from_string("+32123", 10);

    test_subtraction(minuend, subtrahend, expected_result);
}

TEST(IntegerSubtractionTest, PositiveSignedIntegralAndSamePositiveInteger)
{
    std::intmax_t minuend   =                      +32123;
    Integer subtrahend      = integer_from_string("+32123", 10);
    Integer expected_result =                ZERO_INTEGER;

    test_subtraction(minuend, subtrahend, expected_result);
}

TEST(IntegerSubtractionTest, PositiveSignedIntegralAndSmallerPositiveInteger)
{
    std::intmax_t minuend   =                      +32123;
    Integer subtrahend      = integer_from_string( "+2123", 10);
    Integer expected_result = integer_from_string("+30000", 10);

    test_subtraction(minuend, subtrahend, expected_result);
}

TEST(IntegerSubtractionTest, PositiveSignedIntegralAndLargerPositiveInteger)
{
    std::intmax_t minuend   =                      +32123;
    Integer subtrahend      = integer_from_string("+32767", 10);
    Integer expected_result = integer_from_string(  "-644", 10);

    test_subtraction(minuend, subtrahend, expected_result);
}

TEST(IntegerSubtractionTest, PositiveSignedIntegralAndNegativeInteger)
{
    std::intmax_t minuend   =                      +32123;
    Integer subtrahend      = integer_from_string("-32123", 10);
    Integer expected_result = integer_from_string("+64246", 10);

    test_subtraction(minuend, subtrahend, expected_result);
}

TEST(IntegerSubtractionTest, NegativeSignedIntegralAndZeroInteger)
{
    std::intmax_t minuend   =                      -32123;
    Integer subtrahend      =                ZERO_INTEGER;
    Integer expected_result = integer_from_string("-32123", 10);

    test_subtraction(minuend, subtrahend, expected_result);
}

TEST(IntegerSubtractionTest, NegativeSignedIntegralAndSameNegativeInteger)
{
    std::intmax_t minuend   =                      -32123;
    Integer subtrahend      = integer_from_string("-32123", 10);
    Integer expected_result =                ZERO_INTEGER;

    test_subtraction(minuend, subtrahend, expected_result);
}

TEST(IntegerSubtractionTest, NegativeSignedIntegralAndSmallerNegativeInteger)
{
    std::intmax_t minuend   =                      -32123;
    Integer subtrahend      = integer_from_string("-32100", 10);
    Integer expected_result = integer_from_string(   "-23", 10);

    test_subtraction(minuend, subtrahend, expected_result);
}

TEST(IntegerSubtractionTest, NegativeSignedIntegralAndLargerNegativeInteger)
{
    std::intmax_t minuend   =                      -32123;
    Integer subtrahend      = integer_from_string("-32767", 10);
    Integer expected_result = integer_from_string(  "+644", 10);

    test_subtraction(minuend, subtrahend, expected_result);
}

TEST(IntegerSubtractionTest, NegativeSignedIntegralAndPositiveInteger)
{
    std::intmax_t minuend   =                      -32123;
    Integer subtrahend      = integer_from_string("+32123", 10);
    Integer expected_result = integer_from_string("-64246", 10);

    test_subtraction(minuend, subtrahend, expected_result);
}


TEST(IntegerSubtractionTest, ZeroIntegerAndZeroFloatingPoint)
{
    test_subtraction(ZERO_INTEGER, 0.0L, ZERO_INTEGER);
}

TEST(IntegerSubtractionTest, PositiveIntegerAndZeroFloatingPoint)
{
    Integer minuend         = integer_from_floating_point(+77777.0L);
    long double subtrahend  = 0;
    Integer expected_result = minuend;

    test_subtraction(minuend, subtrahend, expected_result);
}

TEST(IntegerSubtractionTest, PositiveIntegerAndSamePositiveFloatingPoint)
{
    Integer minuend         = integer_from_floating_point(+123.0e17L);
    long double subtrahend  =                             +123.0e17L;
    Integer expected_result =                           ZERO_INTEGER;

    test_subtraction(minuend, subtrahend, expected_result);
}

TEST(IntegerSubtractionTest, PositiveIntegerAndSmallerPositiveFloatingPoint)
{
    Integer minuend         = integer_from_floating_point(+1987654321.9L);
    long double subtrahend  =                              +987654321.0L;
    Integer expected_result = integer_from_floating_point(+1000000000.0L);

    test_subtraction(minuend, subtrahend, expected_result);
}

TEST(IntegerSubtractionTest, PositiveIntegerAndLargerPositiveFloatingPoint)
{
    Integer minuend         = integer_from_floating_point(+987654321.9L);
    long double subtrahend  =                                 +54321.0L;
    Integer expected_result = integer_from_floating_point(+987600000.0L); 

    test_subtraction(minuend, subtrahend, expected_result);
}

TEST(IntegerSubtractionTest, PositiveIntegerAndNegativeFloatingPoint)
{
    Integer minuend         = integer_from_floating_point( +987654321.4L);
    long double subtrahend  =                              -987654321.4L;
    Integer expected_result = integer_from_floating_point(+1975308642.0L);

    test_subtraction(minuend, subtrahend, expected_result);
}

TEST(IntegerSubtractionTest, NegativeIntegerAndZeroFloatingPoint)
{
    Integer minuend         = integer_from_floating_point(-987654321.0L);
    long double subtrahend  = 0.0L;
    Integer expected_result = minuend;

    test_subtraction(minuend, subtrahend, expected_result);
}

TEST(IntegerSubtractionTest, NegativeIntegerAndSameNegativeFloatingPoint)
{
    Integer minuend         = integer_from_floating_point(-456.0e25L);
    long double subtrahend  =                             -456.0e25L;
    Integer expected_result =                           ZERO_INTEGER;

    test_subtraction(minuend, subtrahend, expected_result);
}

TEST(IntegerSubtractionTest, NegativeIntegerAndSmallerNegativeFloatingPoint)
{
    Integer minuend         = integer_from_floating_point(-987654321.9L);
    long double subtrahend  =                              -87654321.0L;
    Integer expected_result = integer_from_floating_point(-900000000.0L);

    test_subtraction(minuend, subtrahend, expected_result);
}

TEST(IntegerSubtractionTest, NegativeIntegerAndLargerNegativeFloatingPoint)
{
    Integer minuend         = integer_from_floating_point( -87654321.9L);
    long double subtrahend  =                             -987654321.0L;
    Integer expected_result = integer_from_floating_point(+900000000.0L);

    test_subtraction(minuend, subtrahend, expected_result);
}

TEST(IntegerSubtractionTest, NegativeIntegerAndPositiveFloatingPoint)
{
    Integer minuend         = integer_from_floating_point( -987654321.9L);
    long double subtrahend  =                              +987654321.9L;
    Integer expected_result = integer_from_floating_point(-1975308642.0L);

    test_subtraction(minuend, subtrahend, expected_result);
}

TEST(IntegerSubtractionTest, ZeroFloatingPointAndZeroInteger)
{
    test_subtraction(0.0L, ZERO_INTEGER, ZERO_INTEGER);
}

TEST(IntegerSubtractionTest, PositiveFloatingPointAndZeroInteger)
{
    long double minuend     = +987654321.0L;
    Integer subtrahend      = ZERO_INTEGER;
    Integer expected_result = integer_from_floating_point(+987654321.0L);

    test_subtraction(minuend, subtrahend, expected_result);
}

TEST(IntegerSubtractionTest, PositiveFloatingPointAndSamePositiveInteger)
{
    long double minuend     =                             +987654321.0L;
    Integer subtrahend      = integer_from_floating_point(+987654321.0L);
    Integer expected_result =                              ZERO_INTEGER;

    test_subtraction(minuend, subtrahend, expected_result);
}

TEST(IntegerSubtractionTest, PositiveFloatingPointAndSmallerPositiveInteger)
{
    long double minuend     =                             +1987654321.0L;
    Integer subtrahend      = integer_from_floating_point( +987654321.0L);
    Integer expected_result = integer_from_floating_point(+1000000000.0L);

    test_subtraction(minuend, subtrahend, expected_result);
}

TEST(IntegerSubtractionTest, PositiveFloatingPointAndLargerPositiveInteger)
{
    long double minuend     =                              +987654321.0L;
    Integer subtrahend      = integer_from_floating_point(+1987654321.0L);
    Integer expected_result = integer_from_floating_point(-1000000000.0L);

    test_subtraction(minuend, subtrahend, expected_result);
}

TEST(IntegerSubtractionTest, PositiveFloatingPointAndNegativeInteger)
{
    long double minuend     =                              +987654321.0L;
    Integer subtrahend      = integer_from_floating_point( -987654321.0L);
    Integer expected_result = integer_from_floating_point(+1975308642.0L);

    test_subtraction(minuend, subtrahend, expected_result);
}

TEST(IntegerSubtractionTest, NegativeFloatingPointAndZeroInteger)
{
    long double minuend     =                             -987654321.0L;
    Integer subtrahend      =                              ZERO_INTEGER;
    Integer expected_result = integer_from_floating_point(-987654321.0L);

    test_subtraction(minuend, subtrahend, expected_result);
}

TEST(IntegerSubtractionTest, NegativeFloatingPointAndSameNegativeInteger)
{
    long double minuend     =                             -987654321.0L;
    Integer subtrahend      = integer_from_floating_point(-987654321.0L);
    Integer expected_result =                              ZERO_INTEGER;

    test_subtraction(minuend, subtrahend, expected_result);
}

TEST(IntegerSubtractionTest, NegativeFloatingPointAndSmallerNegativeInteger)
{
    long double minuend     =                             -1987654321.0L;
    Integer subtrahend      = integer_from_floating_point( -987654321.0L);
    Integer expected_result = integer_from_floating_point(-1000000000.0L);

    test_subtraction(minuend, subtrahend, expected_result);
}

TEST(IntegerSubtractionTest, NegativeFloatingPointAndLargerNegativeInteger)
{
    long double minuend     =                              -987654321.0L;
    Integer subtrahend      = integer_from_floating_point(-1987654321.0L);
    Integer expected_result = integer_from_floating_point(+1000000000.0L);

    test_subtraction(minuend, subtrahend, expected_result);
}

TEST(IntegerSubtractionTest, NegativeFloatingPointAndPositiveInteger)
{
    long double minuend     =                              -987654321.0L;
    Integer subtrahend      = integer_from_floating_point( +987654321.0L);
    Integer expected_result = integer_from_floating_point(-1975308642.0L);

    test_subtraction(minuend, subtrahend, expected_result);
}

} // namespace
