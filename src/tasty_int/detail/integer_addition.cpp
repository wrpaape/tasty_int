#include "tasty_int/detail/integer_addition.hpp"

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
add_agreeing_terms_in_place(Sign             addend_sign,
                            const ValueType &addend_value,
                            Integer         &augend)
{
    augend.sign    = larger_of_agreeing_signs(augend.sign, addend_sign);
    augend.digits += addend_value;
}

template<Value ValueType>
void
subtract_value_in_place_from_nonzero(const ValueType &subtrahend_value,
                                     Integer         &minuend)
{
    Sign result_sign = subtract_in_place(subtrahend_value, minuend.digits);
    minuend.sign     = minuend.sign * result_sign;
}

template<SignedArithmetic SignedArithmeticType>
Integer &
add_signed_arithmetic_in_place(SignedArithmeticType  addend,
                               Integer              &augend)
{
    auto [addend_sign, addend_value] = sign_and_value_from_arithmetic(addend);

    if (signs_agree(augend.sign, addend_sign))
        add_agreeing_terms_in_place(addend_sign, addend_value, augend);
    else
        subtract_value_in_place_from_nonzero(addend_value, augend);

    return augend;
}

template<SignedArithmetic SignedArithmeticType>
Integer
add_signed_arithmetic(const Integer        &lhs,
                      SignedArithmeticType  rhs)
{
    Integer result;

    auto [rhs_sign, rhs_value] = sign_and_value_from_arithmetic(rhs);

    if (signs_agree(lhs.sign, rhs_sign)) {
        result.sign   = larger_of_agreeing_signs(lhs.sign, rhs_sign);
        result.digits = lhs.digits + rhs_value;
    } else {
        auto [result_sign, result_digits] = subtract(rhs_value, lhs.digits);
        result.sign   = rhs_sign * result_sign;
        result.digits = std::move(result_digits);
    }

    return result;
}

} // namespace


Integer &
operator+=(Integer       &lhs,
           const Integer &rhs)
{
    if (signs_agree(lhs.sign, rhs.sign))
        add_agreeing_terms_in_place(rhs.sign, rhs.digits, lhs);
    else
        subtract_value_in_place_from_nonzero(rhs.digits, lhs);

    return lhs;
}

Integer &
operator+=(Integer        &lhs,
           std::uintmax_t  rhs)
{
    if (lhs.sign >= Sign::ZERO) {
        Sign rhs_sign = sign_from_integer_operand(rhs);
        add_agreeing_terms_in_place(rhs_sign, rhs, lhs);
    } else {
        subtract_value_in_place_from_nonzero(rhs, lhs);
    }

    return lhs;
}

std::uintmax_t &
operator+=(std::uintmax_t &lhs,
           const Integer  &rhs)
{
    return lhs += conversions::unsigned_integral_from_integer(rhs);
}

Integer &
operator+=(Integer       &lhs,
           std::intmax_t  rhs)
{
    return add_signed_arithmetic_in_place(rhs, lhs);
}


std::intmax_t &
operator+=(std::intmax_t &lhs,
           const Integer &rhs)
{
    auto unsigned_lhs = static_cast<std::uintmax_t>(lhs);

    unsigned_lhs += rhs;

    lhs = intmax_t_from_uintmax_t(unsigned_lhs);

    return lhs;
}

Integer &
operator+=(Integer     &lhs,
           long double  rhs)
{
    return add_signed_arithmetic_in_place(rhs, lhs);
}

long double &
operator+=(long double   &lhs,
           const Integer &rhs)
{
    lhs = std::trunc(lhs);

    return lhs += conversions::floating_point_from_integer(rhs);
}


Integer
operator+(const Integer &lhs,
          const Integer &rhs)
{
    Integer result;

    if (signs_agree(lhs.sign, rhs.sign)) {
        result.sign   = larger_of_agreeing_signs(lhs.sign, rhs.sign);
        result.digits = lhs.digits + rhs.digits;
    } else {
        auto [result_sign, result_digits] = subtract(lhs.digits, rhs.digits);
        result.sign   = lhs.sign * result_sign;
        result.digits = std::move(result_digits);
    }

    return result;
}

Integer
operator+(const Integer  &lhs,
          std::uintmax_t  rhs)
{
    Integer result;

    if (lhs.sign >= Sign::ZERO) {
        Sign rhs_sign = sign_from_integer_operand(rhs);
        result.sign   = larger_of_agreeing_signs(lhs.sign, rhs_sign);
        result.digits = lhs.digits + rhs;
    } else {
        auto [result_sign, result_digits] = subtract(rhs, lhs.digits);
        result.sign   = result_sign;
        result.digits = std::move(result_digits);
    }

    return result;
}

Integer
operator+(std::uintmax_t  lhs,
          const Integer  &rhs)
{
    return rhs + lhs;
}

Integer
operator+(const Integer &lhs,
          std::intmax_t  rhs)
{
    return add_signed_arithmetic(lhs, rhs);
}

Integer
operator+(std::intmax_t  lhs,
          const Integer &rhs)
{
    return rhs + lhs;
}

Integer
operator+(const Integer &lhs,
          long double    rhs)
{
    return add_signed_arithmetic(lhs, rhs);
}

Integer
operator+(long double    lhs,
          const Integer &rhs)
{
    return rhs + lhs;
}

} // namespace detail
} // namespace tasty_int
