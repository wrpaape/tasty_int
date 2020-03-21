#include "tasty_int/detail/integer.hpp"

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


TEST(IntegerAdditionTest, ZeroIntegerAndZeroInteger)
{
    test_subtraction(ZERO_INTEGER, ZERO_INTEGER, ZERO_INTEGER);
}

TEST(IntegerAdditionTest, PositiveIntegerAndZeroInteger)
{
    Integer minuend         = integer_from_string("+9876543210123456789", 10);
    Integer subtrahend      = ZERO_INTEGER;
    Integer expected_result = minuend;

    test_subtraction(minuend, subtrahend, expected_result);
}

TEST(IntegerAdditionTest, PositiveIntegerAndSamePositiveInteger)
{
    Integer minuend         = integer_from_string("+9876543210123456789", 10);
    Integer subtrahend      = minuend;
    Integer expected_result = ZERO_INTEGER;

    test_subtraction(minuend, subtrahend, expected_result);
}

TEST(IntegerAdditionTest, PositiveIntegerAndSmallerPositiveInteger)
{
    Integer minuend         = integer_from_string("+9876543210123456789", 10);
    Integer subtrahend      = integer_from_string(          "+123456789", 10);
    Integer expected_result = integer_from_string("+9876543210000000000", 10);

    test_subtraction(minuend, subtrahend, expected_result);
}

TEST(IntegerAdditionTest, PositiveIntegerAndLargerPositiveInteger)
{
    Integer minuend         = integer_from_string( "+9876543210123456789", 10);
    Integer subtrahend      = integer_from_string("+19876543210123456789", 10);
    Integer expected_result = integer_from_string("-10000000000000000000", 10);

    test_subtraction(minuend, subtrahend, expected_result);
}

TEST(IntegerAdditionTest, PositiveIntegerAndNegativeInteger)
{
    Integer minuend         = integer_from_string( "+9876543210123456789", 10);
    Integer subtrahend      = integer_from_string( "-9876543210123456789", 10);
    Integer expected_result = integer_from_string("+19753086420246913578", 10);

    test_subtraction(minuend, subtrahend, expected_result);
}

TEST(IntegerAdditionTest, NegativeIntegerAndZeroInteger)
{
    Integer minuend         = integer_from_string("-9876543210123456789", 10);
    Integer subtrahend      = ZERO_INTEGER;
    Integer expected_result = minuend;

    test_subtraction(minuend, subtrahend, expected_result);
}

TEST(IntegerAdditionTest, NegativeIntegerAndSameNegativeInteger)
{
    Integer minuend         = integer_from_string("-9876543210123456789", 10);
    Integer subtrahend      = minuend;
    Integer expected_result = ZERO_INTEGER;

    test_subtraction(minuend, subtrahend, expected_result);
}

TEST(IntegerAdditionTest, NegativeIntegerAndSmallerNegativeInteger)
{
    Integer minuend         = integer_from_string("-9876543210123456789", 10);
    Integer subtrahend      = integer_from_string(          "-123456789", 10);
    Integer expected_result = integer_from_string("-9876543210000000000", 10);

    test_subtraction(minuend, subtrahend, expected_result);
}

TEST(IntegerAdditionTest, NegativeIntegerAndLargerNegativeInteger)
{
    Integer minuend         = integer_from_string( "-9876543210123456789", 10);
    Integer subtrahend      = integer_from_string("-19876543210123456789", 10);
    Integer expected_result = integer_from_string("+10000000000000000000", 10);

    test_subtraction(minuend, subtrahend, expected_result);
}

TEST(IntegerAdditionTest, NegativeIntegerAndPositiveInteger)
{
    Integer minuend         = integer_from_string( "-9876543210123456789", 10);
    Integer subtrahend      = integer_from_string( "+9876543210123456789", 10);
    Integer expected_result = integer_from_string("-19753086420246913578", 10);

    test_subtraction(minuend, subtrahend, expected_result);
}


TEST(IntegerAdditionTest, ZeroIntegerAndZeroUnsignedIntegral)
{
    test_subtraction(ZERO_INTEGER, std::uintmax_t(0), ZERO_INTEGER);
}

TEST(IntegerAdditionTest, PositiveIntegerAndZeroUnsignedIntegral)
{
    Integer minuend           = integer_from_string("+54321", 10);
    std::uintmax_t subtrahend = 0;
    Integer expected_result   = minuend;

    test_subtraction(minuend, subtrahend, expected_result);
}

TEST(IntegerAdditionTest, PositiveIntegerAndSamePositiveUnsignedIntegral)
{
    Integer minuend           = integer_from_string("+54321", 10);
    std::uintmax_t subtrahend =                      +54321;
    Integer expected_result   =                ZERO_INTEGER;

    test_subtraction(minuend, subtrahend, expected_result);
}

TEST(IntegerAdditionTest, PositiveIntegerAndSmallerPositiveUnsignedIntegral)
{
    Integer minuend           = integer_from_string("+54321", 10);
    std::uintmax_t subtrahend =                      +43210;
    Integer expected_result   = integer_from_string("+11111", 10);

    test_subtraction(minuend, subtrahend, expected_result);
}

TEST(IntegerAdditionTest, PositiveIntegerAndLargerPositiveUnsignedIntegral)
{
    Integer minuend           = integer_from_string("+54321", 10);
    std::uintmax_t subtrahend =                      +65432;
    Integer expected_result   = integer_from_string("-11111", 10);

    test_subtraction(minuend, subtrahend, expected_result);
}

TEST(IntegerAdditionTest, NegativeIntegerAndZeroUnsignedIntegral)
{
    Integer minuend           = integer_from_string("-54321", 10);
    std::uintmax_t subtrahend = 0;
    Integer expected_result   = minuend;

    test_subtraction(minuend, subtrahend, expected_result);
}

TEST(IntegerAdditionTest, NegativeIntegerAndPositiveUnsignedIntegral)
{
    Integer minuend           = integer_from_string("-54321", 10);
    std::uintmax_t subtrahend =                      +11111;
    Integer expected_result   = integer_from_string("-65432", 10);

    test_subtraction(minuend, subtrahend, expected_result);
}

TEST(IntegerAdditionTest, ZeroUnsignedIntegralAndZeroInteger)
{
    test_subtraction(std::uintmax_t(0), ZERO_INTEGER, ZERO_INTEGER);
}

TEST(IntegerAdditionTest, PositiveUnsignedIntegralAndZeroInteger)
{
    std::uintmax_t minuend  =                      +54321;
    Integer subtrahend      =                ZERO_INTEGER;
    Integer expected_result = integer_from_string("+54321", 10);

    test_subtraction(minuend, subtrahend, expected_result);
}

TEST(IntegerAdditionTest, PositiveUnsignedIntegralAndSamePositiveInteger)
{
    std::uintmax_t minuend  =                      +54321;
    Integer subtrahend      = integer_from_string("+54321", 10);
    Integer expected_result = ZERO_INTEGER;

    test_subtraction(minuend, subtrahend, expected_result);
}

TEST(IntegerAdditionTest, PositiveUnsignedIntegralAndSmallerPositiveInteger)
{
    std::uintmax_t minuend  =                      +54321;
    Integer subtrahend      = integer_from_string("+43210", 10);
    Integer expected_result = integer_from_string("+11111", 10);

    test_subtraction(minuend, subtrahend, expected_result);
}

TEST(IntegerAdditionTest, PositiveUnsignedIntegralAndLargerPositiveInteger)
{
    std::uintmax_t minuend  =                      +54321;
    Integer subtrahend      = integer_from_string("+65432", 10);
    Integer expected_result = integer_from_string("-11111", 10);

    test_subtraction(minuend, subtrahend, expected_result);
}


TEST(IntegerAdditionTest, ZeroIntegerAndZeroSignedIntegral)
{
    test_subtraction(ZERO_INTEGER, std::intmax_t(0), ZERO_INTEGER);
}

TEST(IntegerAdditionTest, PositiveIntegerAndZeroSignedIntegral)
{
    Integer minuend          = integer_from_string("+32123", 10);
    std::intmax_t subtrahend = 0;
    Integer expected_result  = minuend;

    test_subtraction(minuend, subtrahend, expected_result);
}

TEST(IntegerAdditionTest, PositiveIntegerAndSamePositiveSignedIntegral)
{
    Integer minuend          = integer_from_string("+32123", 10);
    std::intmax_t subtrahend =                      +32123;
    Integer expected_result  =                ZERO_INTEGER;

    test_subtraction(minuend, subtrahend, expected_result);
}

TEST(IntegerAdditionTest, PositiveIntegerAndSmallerPositiveSignedIntegral)
{
    Integer minuend          = integer_from_string("+32123", 10);
    std::intmax_t subtrahend =                       +2123;
    Integer expected_result  = integer_from_string("+30000", 10);

    test_subtraction(minuend, subtrahend, expected_result);
}

TEST(IntegerAdditionTest, PositiveIntegerAndLargerPositiveSignedIntegral)
{
    Integer minuend          = integer_from_string("+32123", 10);
    std::intmax_t subtrahend =                      +32767;
    Integer expected_result  = integer_from_string(  "-644", 10);

    test_subtraction(minuend, subtrahend, expected_result);
}

TEST(IntegerAdditionTest, PositiveIntegerAndNegativeSignedIntegral)
{
    Integer minuend          = integer_from_string("+32123", 10);
    std::intmax_t subtrahend =                      -32123;
    Integer expected_result  = integer_from_string("+64246", 10);

    test_subtraction(minuend, subtrahend, expected_result);
}

TEST(IntegerAdditionTest, NegativeIntegerAndZeroSignedIntegral)
{
    Integer minuend          = integer_from_string("-32123", 10);
    std::intmax_t subtrahend = 0;
    Integer expected_result  = minuend;

    test_subtraction(minuend, subtrahend, expected_result);
}

TEST(IntegerAdditionTest, NegativeIntegerAndSameNegativeSignedIntegral)
{
    Integer minuend          = integer_from_string("-32123", 10);
    std::intmax_t subtrahend =                      -32123;
    Integer expected_result  =                ZERO_INTEGER;

    test_subtraction(minuend, subtrahend, expected_result);
}

TEST(IntegerAdditionTest, NegativeIntegerAndSmallerNegativeSignedIntegral)
{
    Integer minuend          = integer_from_string("-32123", 10);
    std::intmax_t subtrahend =                      -32100;
    Integer expected_result  = integer_from_string(   "-23", 10);

    test_subtraction(minuend, subtrahend, expected_result);
}

TEST(IntegerAdditionTest, NegativeIntegerAndLargerNegativeSignedIntegral)
{
    Integer minuend          = integer_from_string("-32123", 10);
    std::intmax_t subtrahend =                      -32767;
    Integer expected_result  = integer_from_string(  "+644", 10);

    test_subtraction(minuend, subtrahend, expected_result);
}

TEST(IntegerAdditionTest, NegativeIntegerAndPositiveSignedIntegral)
{
    Integer minuend          = integer_from_string("-32123", 10);
    std::intmax_t subtrahend =                      +32123;
    Integer expected_result  = integer_from_string("-64246", 10);

    test_subtraction(minuend, subtrahend, expected_result);
}

TEST(IntegerAdditionTest, ZeroSignedIntegralAndZeroInteger)
{
    test_subtraction(std::intmax_t(0), ZERO_INTEGER, ZERO_INTEGER);
}

TEST(IntegerAdditionTest, PositiveSignedIntegralAndZeroInteger)
{
    std::intmax_t minuend   =                      +32123;
    Integer subtrahend      =                ZERO_INTEGER;
    Integer expected_result = integer_from_string("+32123", 10);

    test_subtraction(minuend, subtrahend, expected_result);
}

TEST(IntegerAdditionTest, PositiveSignedIntegralAndSamePositiveInteger)
{
    std::intmax_t minuend   =                      +32123;
    Integer subtrahend      = integer_from_string("+32123", 10);
    Integer expected_result =                ZERO_INTEGER;

    test_subtraction(minuend, subtrahend, expected_result);
}

TEST(IntegerAdditionTest, PositiveSignedIntegralAndSmallerPositiveInteger)
{
    std::intmax_t minuend   =                      +32123;
    Integer subtrahend      = integer_from_string( "+2123", 10);
    Integer expected_result = integer_from_string("+30000", 10);

    test_subtraction(minuend, subtrahend, expected_result);
}

TEST(IntegerAdditionTest, PositiveSignedIntegralAndLargerPositiveInteger)
{
    std::intmax_t minuend   =                      +32123;
    Integer subtrahend      = integer_from_string("+32767", 10);
    Integer expected_result = integer_from_string(  "-644", 10);

    test_subtraction(minuend, subtrahend, expected_result);
}

TEST(IntegerAdditionTest, PositiveSignedIntegralAndNegativeInteger)
{
    std::intmax_t minuend   =                      +32123;
    Integer subtrahend      = integer_from_string("-32123", 10);
    Integer expected_result = integer_from_string("+64246", 10);

    test_subtraction(minuend, subtrahend, expected_result);
}

TEST(IntegerAdditionTest, NegativeSignedIntegralAndZeroInteger)
{
    std::intmax_t minuend   =                      -32123;
    Integer subtrahend      =                ZERO_INTEGER;
    Integer expected_result = integer_from_string("-32123", 10);

    test_subtraction(minuend, subtrahend, expected_result);
}

TEST(IntegerAdditionTest, NegativeSignedIntegralAndSameNegativeInteger)
{
    std::intmax_t minuend   =                      -32123;
    Integer subtrahend      = integer_from_string("-32123", 10);
    Integer expected_result =                ZERO_INTEGER;

    test_subtraction(minuend, subtrahend, expected_result);
}

TEST(IntegerAdditionTest, NegativeSignedIntegralAndSmallerNegativeInteger)
{
    std::intmax_t minuend   =                      -32123;
    Integer subtrahend      = integer_from_string("-32100", 10);
    Integer expected_result = integer_from_string(   "-23", 10);

    test_subtraction(minuend, subtrahend, expected_result);
}

TEST(IntegerAdditionTest, NegativeSignedIntegralAndLargerNegativeInteger)
{
    std::intmax_t minuend   =                      -32123;
    Integer subtrahend      = integer_from_string("-32767", 10);
    Integer expected_result = integer_from_string(  "+644", 10);

    test_subtraction(minuend, subtrahend, expected_result);
}

TEST(IntegerAdditionTest, NegativeSignedIntegralAndPositiveInteger)
{
    std::intmax_t minuend   =                      -32123;
    Integer subtrahend      = integer_from_string("+32123", 10);
    Integer expected_result = integer_from_string("-64246", 10);

    test_subtraction(minuend, subtrahend, expected_result);
}


TEST(IntegerAdditionTest, ZeroIntegerAndZeroFloatingPoint)
{
    test_subtraction(ZERO_INTEGER, 0.0L, ZERO_INTEGER);
}

TEST(IntegerAdditionTest, PositiveIntegerAndZeroFloatingPoint)
{
    Integer minuend         = integer_from_floating_point(+77777.0L);
    long double subtrahend  = 0;
    Integer expected_result = minuend;

    test_subtraction(minuend, subtrahend, expected_result);
}

TEST(IntegerAdditionTest, PositiveIntegerAndSamePositiveFloatingPoint)
{
    Integer minuend         = integer_from_floating_point(+123.0e17L);
    long double subtrahend  =                             +123.0e17L;
    Integer expected_result =                           ZERO_INTEGER;

    test_subtraction(minuend, subtrahend, expected_result);
}

TEST(IntegerAdditionTest, PositiveIntegerAndSmallerPositiveFloatingPoint)
{
    Integer minuend         = integer_from_floating_point(+1987654321.9L);
    long double subtrahend  =                              +987654321.0L;
    Integer expected_result = integer_from_floating_point(+1000000000.0L);

    test_subtraction(minuend, subtrahend, expected_result);
}

TEST(IntegerAdditionTest, PositiveIntegerAndLargerPositiveFloatingPoint)
{
    Integer minuend         = integer_from_floating_point(+987654321.9L);
    long double subtrahend  =                                 +54321.0L;
    Integer expected_result = integer_from_floating_point(+987600000.0L); 

    test_subtraction(minuend, subtrahend, expected_result);
}

TEST(IntegerAdditionTest, PositiveIntegerAndNegativeFloatingPoint)
{
    Integer minuend         = integer_from_floating_point( +987654321.4L);
    long double subtrahend  =                              -987654321.4L;
    Integer expected_result = integer_from_floating_point(+1975308642.0L);

    test_subtraction(minuend, subtrahend, expected_result);
}

TEST(IntegerAdditionTest, NegativeIntegerAndZeroFloatingPoint)
{
    Integer minuend         = integer_from_floating_point(-987654321.0L);
    long double subtrahend  = 0.0L;
    Integer expected_result = minuend;

    test_subtraction(minuend, subtrahend, expected_result);
}

TEST(IntegerAdditionTest, NegativeIntegerAndSameNegativeFloatingPoint)
{
    Integer minuend         = integer_from_floating_point(-456.0e25L);
    long double subtrahend  =                             -456.0e25L;
    Integer expected_result =                           ZERO_INTEGER;

    test_subtraction(minuend, subtrahend, expected_result);
}

TEST(IntegerAdditionTest, NegativeIntegerAndSmallerNegativeFloatingPoint)
{
    Integer minuend         = integer_from_floating_point(-987654321.9L);
    long double subtrahend  =                              -87654321.0L;
    Integer expected_result = integer_from_floating_point(-900000000.0L);

    test_subtraction(minuend, subtrahend, expected_result);
}

TEST(IntegerAdditionTest, NegativeIntegerAndLargerNegativeFloatingPoint)
{
    Integer minuend         = integer_from_floating_point( -87654321.9L);
    long double subtrahend  =                             -987654321.0L;
    Integer expected_result = integer_from_floating_point(+900000000.0L);

    test_subtraction(minuend, subtrahend, expected_result);
}

TEST(IntegerAdditionTest, NegativeIntegerAndPositiveFloatingPoint)
{
    Integer minuend         = integer_from_floating_point( -987654321.9L);
    long double subtrahend  =                              +987654321.9L;
    Integer expected_result = integer_from_floating_point(-1975308642.0L);

    test_subtraction(minuend, subtrahend, expected_result);
}

TEST(IntegerAdditionTest, ZeroFloatingPointAndZeroInteger)
{
    test_subtraction(0.0L, ZERO_INTEGER, ZERO_INTEGER);
}

TEST(IntegerAdditionTest, PositiveFloatingPointAndZeroInteger)
{
    long double minuend     = +987654321.0L;
    Integer subtrahend      = ZERO_INTEGER;
    Integer expected_result = integer_from_floating_point(+987654321.0L);

    test_subtraction(minuend, subtrahend, expected_result);
}

TEST(IntegerAdditionTest, PositiveFloatingPointAndSamePositiveInteger)
{
    long double minuend     =                             +987654321.0L;
    Integer subtrahend      = integer_from_floating_point(+987654321.0L);
    Integer expected_result =                              ZERO_INTEGER;

    test_subtraction(minuend, subtrahend, expected_result);
}

TEST(IntegerAdditionTest, PositiveFloatingPointAndSmallerPositiveInteger)
{
    long double minuend     =                             +1987654321.0L;
    Integer subtrahend      = integer_from_floating_point( +987654321.0L);
    Integer expected_result = integer_from_floating_point(+1000000000.0L);

    test_subtraction(minuend, subtrahend, expected_result);
}

TEST(IntegerAdditionTest, PositiveFloatingPointAndLargerPositiveInteger)
{
    long double minuend     =                              +987654321.0L;
    Integer subtrahend      = integer_from_floating_point(+1987654321.0L);
    Integer expected_result = integer_from_floating_point(-1000000000.0L);

    test_subtraction(minuend, subtrahend, expected_result);
}

TEST(IntegerAdditionTest, PositiveFloatingPointAndNegativeInteger)
{
    long double minuend     =                              +987654321.0L;
    Integer subtrahend      = integer_from_floating_point( -987654321.0L);
    Integer expected_result = integer_from_floating_point(+1975308642.0L);

    test_subtraction(minuend, subtrahend, expected_result);
}

TEST(IntegerAdditionTest, NegativeFloatingPointAndZeroInteger)
{
    long double minuend     =                             -987654321.0L;
    Integer subtrahend      =                              ZERO_INTEGER;
    Integer expected_result = integer_from_floating_point(-987654321.0L);

    test_subtraction(minuend, subtrahend, expected_result);
}

TEST(IntegerAdditionTest, NegativeFloatingPointAndSameNegativeInteger)
{
    long double minuend     =                             -987654321.0L;
    Integer subtrahend      = integer_from_floating_point(-987654321.0L);
    Integer expected_result =                              ZERO_INTEGER;

    test_subtraction(minuend, subtrahend, expected_result);
}

TEST(IntegerAdditionTest, NegativeFloatingPointAndSmallerNegativeInteger)
{
    long double minuend     =                             -1987654321.0L;
    Integer subtrahend      = integer_from_floating_point( -987654321.0L);
    Integer expected_result = integer_from_floating_point(-1000000000.0L);

    test_subtraction(minuend, subtrahend, expected_result);
}

TEST(IntegerAdditionTest, NegativeFloatingPointAndLargerNegativeInteger)
{
    long double minuend     =                              -987654321.0L;
    Integer subtrahend      = integer_from_floating_point(-1987654321.0L);
    Integer expected_result = integer_from_floating_point(+1000000000.0L);

    test_subtraction(minuend, subtrahend, expected_result);
}

TEST(IntegerAdditionTest, NegativeFloatingPointAndPositiveInteger)
{
    long double minuend   =                                -987654321.0L;
    Integer subtrahend      = integer_from_floating_point( +987654321.0L);
    Integer expected_result = integer_from_floating_point(-1975308642.0L);

    test_subtraction(minuend, subtrahend, expected_result);
}

} // namespace
