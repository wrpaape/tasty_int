#include "tasty_int/detail/integer_division.hpp"

#include <cassert>
#include <cmath>

#include <utility>

#include "tasty_int/detail/integer_operation.hpp"
#include "tasty_int/detail/digits_division.hpp"
#include "tasty_int/detail/sign_from_digits.hpp"
#include "tasty_int/detail/intmax_t_from_uintmax_t.hpp"
#include "tasty_int/detail/conversions/integral_from_digits.hpp"
#include "tasty_int/detail/conversions/unsigned_integral_from_integer.hpp"
#include "tasty_int/detail/conversions/floating_point_from_integer.hpp"


namespace tasty_int {
namespace detail {
namespace {

template<IntegerOperand DivisorType>
Integer &
divide_in_place(const DivisorType &divisor,
                Integer           &dividend)
{
    auto nonzero_quotient_sign = dividend.sign
                               * sign_from_integer_operand(divisor);
    auto &&divisor_value       = value_from_integer_operand(divisor);
    (void) tasty_int::detail::divide_in_place(divisor_value, dividend.digits);
    dividend.sign = sign_from_digits(dividend.digits, nonzero_quotient_sign);

    return dividend;
}

template<IntegerOperand DivisorType>
Integer
divide(const Integer     &dividend,
       const DivisorType &divisor)
{
    auto nonzero_quotient_sign = dividend.sign
                               * sign_from_integer_operand(divisor);
    auto &&divisor_value       = value_from_integer_operand(divisor);
    Integer result;
    result.digits = tasty_int::detail::divide(dividend.digits,
                                              divisor_value).quotient;
    result.sign   = sign_from_digits(result.digits, nonzero_quotient_sign);

    return result;
}

template<IntegerOperand DivisorType>
Integer
remainder(const Integer     &dividend,
          const DivisorType &divisor)
{
    auto &&divisor_value = value_from_integer_operand(divisor);

    Integer result;
    result.digits = tasty_int::detail::divide(dividend.digits,
                                              divisor_value).remainder;
    result.sign   = sign_from_digits(result.digits, dividend.sign);

    return result;
}

template<IntegerOperand DivisorType>
Integer &
remainder_in_place(const DivisorType &divisor,
                   Integer           &dividend)
{
    dividend = remainder(dividend, divisor);

    return dividend;
}

IntegerDivisionResult<Integer>
integer_division_result_from_digits_division_result(
    DigitsDivisionResult &&digits_result,
    Sign                   quotient_sign,
    Sign                   remainder_sign
)
{
    IntegerDivisionResult<Integer> result;
    result.quotient.sign    = sign_from_digits(digits_result.quotient,
                                               quotient_sign);
    result.quotient.digits  = std::move(digits_result.quotient);
    result.remainder.sign   = sign_from_digits(digits_result.remainder,
                                               remainder_sign);
    result.remainder.digits = std::move(digits_result.remainder);

    return result;
}

template<IntegerOperand DivisorType>
IntegerDivisionResult<Integer>
divide_and_remainder(const Integer     &dividend,
                     const DivisorType &divisor)
{
    return integer_division_result_from_digits_division_result(
        tasty_int::detail::divide(dividend.digits,
                                  value_from_integer_operand(divisor)),
        dividend.sign * sign_from_integer_operand(divisor),
        dividend.sign
    );
}

} // namespace


Integer &
operator/=(Integer       &lhs,
           const Integer &rhs)
{
    return divide_in_place(rhs, lhs);
}

Integer &
operator/=(Integer        &lhs,
           std::uintmax_t  rhs)
{
    return divide_in_place(rhs, lhs);
}

std::uintmax_t &
operator/=(std::uintmax_t &lhs,
           const Integer  &rhs)
{
    return lhs = (lhs / rhs);
}

Integer &
operator/=(Integer       &lhs,
           std::intmax_t  rhs)
{
    return divide_in_place(rhs, lhs);
}

std::intmax_t &
operator/=(std::intmax_t &lhs,
           const Integer &rhs)
{
    return lhs = (lhs / rhs);
}

Integer &
operator/=(Integer     &lhs,
           long double  rhs)
{
    assert(std::isfinite(rhs));

    return divide_in_place(rhs, lhs);
}

long double &
operator/=(long double   &lhs,
           const Integer &rhs)
{
    return lhs = (lhs / rhs);
}


Integer
operator/(const Integer &lhs,
          const Integer &rhs)
{
    return divide(lhs, rhs);
}

Integer
operator/(const Integer  &lhs,
          std::uintmax_t  rhs)
{
    return divide(lhs, rhs);
}

std::uintmax_t
operator/(std::uintmax_t  lhs,
          const Integer  &rhs)
{
    return lhs / conversions::unsigned_integral_from_integer(rhs);
}

Integer
operator/(const Integer &lhs,
          std::intmax_t  rhs)
{
    return divide(lhs, rhs);
}

std::intmax_t
operator/(std::intmax_t  lhs,
          const Integer &rhs)
{
    auto [lhs_sign, lhs_value] = sign_and_value_from_arithmetic(lhs);
    auto result_sign           = lhs_sign * rhs.sign;
    auto rhs_value             = conversions::integral_from_digits(rhs.digits);
    auto result_value          = lhs_value / rhs_value;
    auto unsigned_result       = result_value * result_sign;

    return intmax_t_from_uintmax_t(unsigned_result);
}

Integer
operator/(const Integer &lhs,
          long double    rhs)
{
    assert(std::isfinite(rhs));

    return divide(lhs, rhs);
}

long double
operator/(long double    lhs,
          const Integer &rhs)
{
    return std::trunc(lhs) / conversions::floating_point_from_integer(rhs);
}


Integer &
operator%=(Integer       &lhs,
           const Integer &rhs)
{
    return remainder_in_place(rhs, lhs);
}

Integer &
operator%=(Integer        &lhs,
           std::uintmax_t  rhs)
{
    return remainder_in_place(rhs, lhs);
}

std::uintmax_t &
operator%=(std::uintmax_t &lhs,
           const Integer  &rhs)
{
    return lhs = (lhs % rhs);
}

Integer &
operator%=(Integer       &lhs,
           std::intmax_t  rhs)
{
    return remainder_in_place(rhs, lhs);
}

std::intmax_t &
operator%=(std::intmax_t &lhs,
           const Integer &rhs)
{
    return lhs = (lhs % rhs);
}

Integer &
operator%=(Integer     &lhs,
           long double  rhs)
{
    assert(std::isfinite(rhs));

    return remainder_in_place(rhs, lhs);
}

long double &
operator%=(long double   &lhs,
           const Integer &rhs)
{
    return lhs = (lhs % rhs);
}


Integer
operator%(const Integer &lhs,
          const Integer &rhs)
{
    return remainder(lhs, rhs);
}

Integer
operator%(const Integer  &lhs,
          std::uintmax_t  rhs)
{
    return remainder(lhs, rhs);
}

std::uintmax_t
operator%(std::uintmax_t  lhs,
          const Integer  &rhs)
{
    return lhs % conversions::unsigned_integral_from_integer(rhs);
}

Integer
operator%(const Integer &lhs,
          std::intmax_t  rhs)
{
    return remainder(lhs, rhs);
}

std::intmax_t
operator%(std::intmax_t  lhs,
          const Integer &rhs)
{
    auto [lhs_sign, lhs_value] = sign_and_value_from_arithmetic(lhs);
    auto rhs_value             = conversions::integral_from_digits(rhs.digits);
    auto result_value          = (lhs_value % rhs_value);
    auto unsigned_result       = result_value * lhs_sign;

    return intmax_t_from_uintmax_t(unsigned_result);
}

Integer
operator%(const Integer &lhs,
          long double    rhs)
{
    assert(std::isfinite(rhs));

    return remainder(lhs, rhs);
}

long double
operator%(long double    lhs,
          const Integer &rhs)
{
    return std::fmod(std::trunc(lhs),
                     conversions::floating_point_from_integer(rhs));
}


IntegerDivisionResult<Integer>
div(const Integer &lhs,
    const Integer &rhs)
{
    return divide_and_remainder(lhs, rhs);
}

IntegerDivisionResult<Integer>
div(const Integer  &lhs,
    std::uintmax_t  rhs)
{
    return divide_and_remainder(lhs, rhs);
}

IntegerDivisionResult<std::uintmax_t>
div(std::uintmax_t  lhs,
    const Integer  &rhs)
{
    auto unsigned_integral_rhs =
        conversions::unsigned_integral_from_integer(rhs);

    return {
        .quotient  = lhs / unsigned_integral_rhs,
        .remainder = lhs % unsigned_integral_rhs
    };
}

IntegerDivisionResult<Integer>
div(const Integer &lhs,
    std::intmax_t  rhs)
{
    return divide_and_remainder(lhs, rhs);
}

IntegerDivisionResult<std::intmax_t>
div(std::intmax_t  lhs,
    const Integer &rhs)
{
    auto [lhs_sign, lhs_value] = sign_and_value_from_arithmetic(lhs);
    auto quotient_sign         = lhs_sign * rhs.sign;
    auto rhs_value             = conversions::integral_from_digits(rhs.digits);
    auto quotient_value        = (lhs_value / rhs_value);
    auto remainder_value       = (lhs_value % rhs_value);

    return {
        .quotient  = intmax_t_from_uintmax_t(quotient_value  * quotient_sign),
        .remainder = intmax_t_from_uintmax_t(remainder_value * lhs_sign)
    };
}

IntegerDivisionResult<Integer>
div(const Integer &lhs,
    long double    rhs)
{
    return divide_and_remainder(lhs, rhs);
}

IntegerDivisionResult<long double>
div(long double    lhs,
    const Integer &rhs)
{
    auto truncated_lhs      = std::trunc(lhs);
    auto floating_point_rhs = conversions::floating_point_from_integer(rhs);

    return {
        .quotient  = truncated_lhs / floating_point_rhs,
        .remainder = std::fmod(truncated_lhs, floating_point_rhs)
    };
}

} // namespace detail
} // namespace tasty_int
