#include "tasty_int/detail/integer_multiplication_and_division.hpp"

#include <cassert>
#include <cmath>

#include <type_traits>
#include <utility>

#include "tasty_int/concepts.hpp"
#include "tasty_int/detail/concepts.hpp"
#include "tasty_int/detail/digits_multiplication.hpp"
#include "tasty_int/detail/digits_division.hpp"
#include "tasty_int/detail/sign_from_signed_arithmetic.hpp"
#include "tasty_int/detail/sign_from_unsigned_arithmetic.hpp"
#include "tasty_int/detail/sign_from_digits.hpp"


namespace tasty_int {
namespace detail {
namespace {

template<typename T>
concept Operand = Arithmetic<T>
               || std::is_same_v<T, Integer>;

Sign
sign_from_operand(const Integer &operand)
{
    return operand.sign;
}

Sign
sign_from_operand(std::uintmax_t operand)
{
    return sign_from_unsigned_arithmetic(operand);
}

template<SignedArithmetic SignedArithmeticValueType>
Sign
sign_from_operand(SignedArithmeticValueType operand)
{
    return sign_from_signed_arithmetic(operand);
}

const std::vector<digit_type> &
value_from_operand(const Integer &operand)
{
    return operand.digits;
}

std::uintmax_t
value_from_operand(std::uintmax_t operand)
{
    return operand;
}

std::uintmax_t
value_from_operand(std::intmax_t operand)
{
    return static_cast<std::uintmax_t>(std::abs(operand));
}

long double
value_from_operand(long double operand)
{
    return std::abs(operand);
}

template<Operand OperandType>
auto
sign_and_value_from_operand(const OperandType operand)
{
    return std::make_pair(sign_from_operand(operand),
                          value_from_operand(operand));
}

template<Operand MultiplierType>
Integer &
multiply_in_place(const MultiplierType &multiplier,
                  Integer              &multiplicand)
{
    multiplicand.sign   *= sign_from_operand(multiplier);
    multiplicand.digits *= value_from_operand(multiplier);

    return multiplicand;
}

template<Operand MultiplierType>
Integer
multiply(const Integer        &multiplicand,
         const MultiplierType &multiplier)
{
    Integer result;
    result.sign   = multiplicand.sign   * sign_from_operand(multiplier);
    result.digits = multiplicand.digits * value_from_operand(multiplier);

    return result;
}

template<Operand DivisorType>
Integer &
divide_in_place(const DivisorType &divisor,
                Integer           &dividend)
{
    auto nonzero_quotient_sign = dividend.sign * sign_from_operand(divisor);
    auto &&divisor_value       = value_from_operand(divisor);
    (void) tasty_int::detail::divide_in_place(divisor_value, dividend.digits);
    dividend.sign = sign_from_digits(dividend.digits, nonzero_quotient_sign);

    return dividend;
}

template<Operand DivisorType>
Integer
divide(const Integer     &dividend,
       const DivisorType &divisor)
{
    auto nonzero_quotient_sign = dividend.sign * sign_from_operand(divisor);
    auto &&divisor_value       = value_from_operand(divisor);
    Integer result;
    result.digits = tasty_int::detail::divide(dividend.digits,
                                              divisor_value).quotient;
    result.sign   = sign_from_digits(result.digits, nonzero_quotient_sign);

    return result;
}

template<Operand DivisorType>
Integer
remainder(const Integer     &dividend,
          const DivisorType &divisor)
{
    auto &&divisor_value = value_from_operand(divisor);

    Integer result;
    result.digits = tasty_int::detail::divide(dividend.digits,
                                              divisor_value).remainder;
    result.sign   = sign_from_digits(result.digits, dividend.sign);

    return result;
}

template<Operand DivisorType>
Integer &
remainder_in_place(const DivisorType &divisor,
                   Integer           &dividend)
{
    dividend = remainder(dividend, divisor);

    return dividend;
}

IntegerDivisionResult
integer_division_result_from_digits_division_result(
    DigitsDivisionResult &&digits_result,
    Sign                   quotient_sign,
    Sign                   remainder_sign
)
{
    IntegerDivisionResult result;
    result.quotient.sign    = sign_from_digits(digits_result.quotient,
                                               quotient_sign);
    result.quotient.digits  = std::move(digits_result.quotient);
    result.remainder.sign   = sign_from_digits(digits_result.remainder,
                                               remainder_sign);
    result.remainder.digits = std::move(digits_result.remainder);

    return result;
}

template<Operand DivisorType>
IntegerDivisionResult
divide_and_remainder(const Integer     &dividend,
                     const DivisorType &divisor)
{
    return integer_division_result_from_digits_division_result(
        tasty_int::detail::divide(dividend.digits, value_from_operand(divisor)),
        dividend.sign * sign_from_operand(divisor),
        dividend.sign
    );
}

} // namespace


Integer &
operator*=(Integer       &lhs,
           const Integer &rhs)
{
    return multiply_in_place(rhs, lhs);
}

Integer &
operator*=(Integer        &lhs,
           std::uintmax_t  rhs)
{
    return multiply_in_place(rhs, lhs);
}

Integer &
operator*=(Integer       &lhs,
           std::intmax_t  rhs)
{
    return multiply_in_place(rhs, lhs);
}

Integer &
operator*=(Integer     &lhs,
           long double  rhs)
{
    assert(std::isfinite(rhs));

    return multiply_in_place(rhs, lhs);
}


Integer
operator*(const Integer &lhs,
          const Integer &rhs)
{
    return multiply(lhs, rhs);
}

Integer
operator*(const Integer  &lhs,
          std::uintmax_t  rhs)
{
    return multiply(lhs, rhs);
}

Integer
operator*(std::uintmax_t  lhs,
          const Integer  &rhs)
{
    return rhs * lhs;
}

Integer
operator*(const Integer &lhs,
          std::intmax_t  rhs)
{
    return multiply(lhs, rhs);
}

Integer
operator*(std::intmax_t  lhs,
          const Integer &rhs)
{
    return rhs * lhs;
}

Integer
operator*(const Integer &lhs,
          long double    rhs)
{
    assert(std::isfinite(rhs));

    return multiply(lhs, rhs);
}

Integer
operator*(long double    lhs,
          const Integer &rhs)
{
    return rhs * lhs;
}


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

Integer &
operator/=(Integer       &lhs,
           std::intmax_t  rhs)
{
    return divide_in_place(rhs, lhs);
}

Integer &
operator/=(Integer     &lhs,
           long double  rhs)
{
    assert(std::isfinite(rhs));

    return divide_in_place(rhs, lhs);
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

// std::uintmax_t
// operator/(std::uintmax_t  lhs,
//           const Integer  &rhs)
// {
//     (void) rhs;
//     return lhs; // TODO
// }

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
    (void) rhs;
    return lhs; // TODO
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
    (void) rhs;
    return lhs; // TODO
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

Integer &
operator%=(Integer       &lhs,
           std::intmax_t  rhs)
{
    return remainder_in_place(rhs, lhs);
}

Integer &
operator%=(Integer     &lhs,
           long double  rhs)
{
    assert(std::isfinite(rhs));

    return remainder_in_place(rhs, lhs);
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
    (void) rhs;
    return lhs; // TODO
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
    (void) rhs;
    return lhs; // TODO
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
    (void) rhs;
    return lhs; // TODO
}


IntegerDivisionResult
div(const Integer &lhs,
    const Integer &rhs)
{
    return divide_and_remainder(lhs, rhs);
}

IntegerDivisionResult
div(const Integer  &lhs,
    std::uintmax_t  rhs)
{
    return divide_and_remainder(lhs, rhs);
}

IntegerDivisionResult
div(const Integer &lhs,
    std::intmax_t  rhs)
{
    return divide_and_remainder(lhs, rhs);
}

IntegerDivisionResult
div(const Integer &lhs,
    long double  rhs)
{
    return divide_and_remainder(lhs, rhs);
}

} // namespace detail
} // namespace tasty_int
