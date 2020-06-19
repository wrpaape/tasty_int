#include "tasty_int/detail/integer_subtraction.hpp"

#include <cassert>
#include <cmath>

#include <algorithm>
#include <type_traits>
#include <utility>

#include "tasty_int/detail/integer_operation.hpp"
#include "tasty_int/detail/digits_addition.hpp"
#include "tasty_int/detail/digits_subtraction.hpp"
#include "tasty_int/detail/intmax_t_from_uintmax_t.hpp"
#include "tasty_int/detail/conversions/unsigned_integral_from_integer.hpp"
#include "tasty_int/detail/conversions/floating_point_from_integer.hpp"


namespace tasty_int {
namespace detail {
namespace {

template<Value ValueType>
void
subtract_agreeing_terms_in_place(Sign             subtrahend_sign,
                                 const ValueType &subtrahend_value,
                                 Integer         &minuend)
{
    Sign result_sign = subtract_in_place(subtrahend_value, minuend.digits);
    auto larger_sign = larger_of_agreeing_signs(minuend.sign, subtrahend_sign);
    minuend.sign     = larger_sign * result_sign;
}

template<Value ValueType>
Integer &
subtract_signed_value_in_place(Sign             subtrahend_sign,
                               const ValueType &subtrahend_value,
                               Integer         &minuend)
{
    if (signs_agree(minuend.sign, subtrahend_sign))
        subtract_agreeing_terms_in_place(subtrahend_sign,
                                         subtrahend_value,
                                         minuend);
    else
        minuend.digits += subtrahend_value;

    return minuend;
}

template<SignedArithmetic SignedArithmeticType>
Integer &
subtract_signed_arithmetic_in_place(SignedArithmeticType  subtrahend,
                                    Integer              &minuend)
{
    auto [subtrahend_sign, subtrahend_value] =
        sign_and_value_from_arithmetic(subtrahend);

    return subtract_signed_value_in_place(subtrahend_sign,
                                          subtrahend_value,
                                          minuend);
}

template<Arithmetic ArithmeticType>
Integer
subtract_reverse_operands(const Integer  &lhs,
                          ArithmeticType  rhs)
{
    Integer result = rhs - lhs;

    result.sign = -result.sign;
    
    return result;
}

template<Value ValueType>
Integer
subtract_signed_value(Sign             lhs_sign,
                      const ValueType &lhs_value,
                      const Integer   &rhs)
{
    Integer result;

    if (signs_agree(lhs_sign, rhs.sign)) {
        Sign larger_sign = larger_of_agreeing_signs(lhs_sign, rhs.sign);
        auto [result_sign, result_digits] = subtract(lhs_value, rhs.digits);
        result.sign   = larger_sign * result_sign;
        result.digits = std::move(result_digits);
    } else {
        result.sign   = larger_of_agreeing_signs(lhs_sign,
                                                 -rhs.sign);
        result.digits = lhs_value + rhs.digits;
    }

    return result;
}

template<SignedArithmetic SignedArithmeticType>
Integer
subtract_signed_arithmetic(SignedArithmeticType  lhs,
                           const Integer        &rhs)
{
    auto [lhs_sign, lhs_value] = sign_and_value_from_arithmetic(lhs);

    return subtract_signed_value(lhs_sign, lhs_value, rhs);
}

} // namespace


Integer &
operator-=(Integer       &lhs,
           const Integer &rhs)
{
    return subtract_signed_value_in_place(rhs.sign, rhs.digits, lhs);
}

Integer &
operator-=(Integer        &lhs,
           std::uintmax_t  rhs)
{
    Sign rhs_sign = sign_from_integer_operand(rhs);

    return subtract_signed_value_in_place(rhs_sign, rhs, lhs);
}

std::uintmax_t &
operator-=(std::uintmax_t &lhs,
           const Integer  &rhs)
{
    return lhs -= conversions::unsigned_integral_from_integer(rhs);
}

Integer &
operator-=(Integer       &lhs,
           std::intmax_t  rhs)
{
    return subtract_signed_arithmetic_in_place(rhs, lhs);
}

std::intmax_t &
operator-=(std::intmax_t &lhs,
           const Integer &rhs)
{
    auto unsigned_lhs = static_cast<std::uintmax_t>(lhs);

    unsigned_lhs -= rhs;

    lhs = intmax_t_from_uintmax_t(unsigned_lhs);

    return lhs;
}

Integer &
operator-=(Integer     &lhs,
           long double  rhs)
{
    return subtract_signed_arithmetic_in_place(rhs, lhs);
}

long double &
operator-=(long double   &lhs,
           const Integer &rhs)
{
    lhs = std::trunc(lhs);

    return lhs -= conversions::floating_point_from_integer(rhs);
}


Integer
operator-(const Integer &lhs,
          const Integer &rhs)
{
    return subtract_signed_value(lhs.sign, lhs.digits, rhs);
}

Integer
operator-(const Integer  &lhs,
          std::uintmax_t  rhs)
{
    return subtract_reverse_operands(lhs, rhs);
}

Integer
operator-(std::uintmax_t  lhs,
          const Integer  &rhs)
{
    Integer result;

    if (rhs.sign >= Sign::ZERO) {
        auto [result_sign, result_digits] = subtract(lhs, rhs.digits);
        result.sign   = result_sign;
        result.digits = std::move(result_digits);
    } else {
        result.sign   = Sign::POSITIVE;
        result.digits = rhs.digits + lhs;
    }

    return result;
}

Integer
operator-(const Integer &lhs,
          std::intmax_t  rhs)
{
    return subtract_reverse_operands(lhs, rhs);
}

Integer
operator-(std::intmax_t  lhs,
          const Integer &rhs)
{
    return subtract_signed_arithmetic(lhs, rhs);
}

Integer
operator-(const Integer &lhs,
          long double    rhs)
{
    return subtract_reverse_operands(lhs, rhs);
}

Integer
operator-(long double    lhs,
          const Integer &rhs)
{
    return subtract_signed_arithmetic(lhs, rhs);
}

} // namespace detail
} // namespace tasty_int
