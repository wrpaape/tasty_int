#include "tasty_int/detail/integer_addition_and_subtraction.hpp"

#include <cassert>
#include <cmath>

#include <algorithm>
#include <type_traits>
#include <utility>

#include "tasty_int/concepts.hpp"
#include "tasty_int/detail/concepts.hpp"
#include "tasty_int/detail/digits_addition.hpp"
#include "tasty_int/detail/digits_subtraction.hpp"
#include "tasty_int/detail/sign_from_signed_arithmetic.hpp"
#include "tasty_int/detail/sign_from_unsigned_arithmetic.hpp"


namespace tasty_int {
namespace detail {
namespace {

template<typename T>
concept Value = ArithmeticValue<T>
             || std::is_same_v<T, std::vector<digit_type>>;

bool
signs_agree(Sign sign1,
            Sign sign2)
{
    int sign_diff = std::abs(sign1 - sign2);
    return (sign_diff <= 1);
}

Sign
larger_of_agreeing_signs(Sign sign1,
                         Sign sign2)
{
    assert(signs_agree(sign1, sign2));

    return static_cast<Sign>(sign1 | sign2);
}

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
subtract_agreeing_terms_in_place(Sign             subtrahend_sign,
                                 const ValueType &subtrahend_value,
                                 Integer         &minuend)
{
    Sign result_sign = subtract_in_place(subtrahend_value, minuend.digits);
    auto larger_sign = larger_of_agreeing_signs(minuend.sign, subtrahend_sign);
    minuend.sign     = larger_sign * result_sign;
}

template<Value ValueType>
void
subtract_value_in_place_from_nonzero(const ValueType &subtrahend_value,
                                     Integer         &minuend)
{
    Sign result_sign = subtract_in_place(subtrahend_value, minuend.digits);
    minuend.sign     = minuend.sign * result_sign;
}

template<ArithmeticValue  ArithmeticValueType,
         SignedArithmetic SignedArithmeticType>
std::pair<Sign, ArithmeticValueType>
sign_and_value_from_signed_arithmetic(SignedArithmeticType signed_value)
    requires std::is_convertible_v<SignedArithmeticType, ArithmeticValueType>
{
    return {
        sign_from_signed_arithmetic(signed_value),
        std::abs(signed_value)
    };
}

template<ArithmeticValue  ArithmeticValueType,
         SignedArithmetic SignedArithmeticType>
Integer &
add_signed_arithmetic_in_place(SignedArithmeticType  addend,
                               Integer              &augend)
    requires std::is_convertible_v<SignedArithmeticType, ArithmeticValueType>
{
    auto [addend_sign, addend_value] =
        sign_and_value_from_signed_arithmetic<ArithmeticValueType>(addend);

    if (signs_agree(augend.sign, addend_sign))
        add_agreeing_terms_in_place(addend_sign, addend_value, augend);
    else
        subtract_value_in_place_from_nonzero(addend_value, augend);

    return augend;
}

template<ArithmeticValue  ArithmeticValueType,
         SignedArithmetic SignedArithmeticType>
Integer
add_signed_arithmetic(const Integer        &lhs,
                      SignedArithmeticType  rhs)
    requires std::is_convertible_v<SignedArithmeticType, ArithmeticValueType>
{
    Integer result;

    auto [rhs_sign, rhs_value] =
        sign_and_value_from_signed_arithmetic<ArithmeticValueType>(rhs);

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

template<ArithmeticValue  ArithmeticValueType,
         SignedArithmetic SignedArithmeticType>
Integer &
subtract_signed_arithmetic_in_place(SignedArithmeticType  subtrahend,
                                    Integer              &minuend)
    requires std::is_convertible_v<SignedArithmeticType, ArithmeticValueType>
{
    auto [subtrahend_sign, subtrahend_value] =
        sign_and_value_from_signed_arithmetic<ArithmeticValueType>(subtrahend);

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

template<ArithmeticValue  ArithmeticValueType,
         SignedArithmetic SignedArithmeticType>
Integer
subtract_signed_arithmetic(SignedArithmeticType  lhs,
                           const Integer        &rhs)
    requires std::is_convertible_v<SignedArithmeticType, ArithmeticValueType>
{
    auto [lhs_sign, lhs_value] =
        sign_and_value_from_signed_arithmetic<ArithmeticValueType>(lhs);

    return subtract_signed_value<ArithmeticValueType>(lhs_sign, lhs_value, rhs);
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
        Sign rhs_sign = sign_from_unsigned_arithmetic(rhs);
        add_agreeing_terms_in_place(rhs_sign, rhs, lhs);
    } else {
        subtract_value_in_place_from_nonzero(rhs, lhs);
    }

    return lhs;
}

Integer &
operator+=(Integer       &lhs,
           std::intmax_t  rhs)
{
    return add_signed_arithmetic_in_place<std::uintmax_t>(rhs, lhs);
}

Integer &
operator+=(Integer     &lhs,
           long double  rhs)
{
    return add_signed_arithmetic_in_place<long double>(rhs, lhs);
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
        Sign rhs_sign = sign_from_unsigned_arithmetic(rhs);
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
    return add_signed_arithmetic<std::uintmax_t>(lhs, rhs);
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
    return add_signed_arithmetic<long double>(lhs, rhs);
}

Integer
operator+(long double    lhs,
          const Integer &rhs)
{
    return rhs + lhs;
}


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
    Sign rhs_sign = sign_from_unsigned_arithmetic(rhs);

    return subtract_signed_value_in_place(rhs_sign, rhs, lhs);
}

Integer &
operator-=(Integer       &lhs,
           std::intmax_t  rhs)
{
    return subtract_signed_arithmetic_in_place<std::uintmax_t>(rhs, lhs);
}

Integer &
operator-=(Integer     &lhs,
           long double  rhs)
{
    return subtract_signed_arithmetic_in_place<long double>(rhs, lhs);
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
    return subtract_signed_arithmetic<std::uintmax_t>(lhs, rhs);
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
    return subtract_signed_arithmetic<long double>(lhs, rhs);
}

} // namespace detail
} // namespace tasty_int
