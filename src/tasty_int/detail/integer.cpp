#include "tasty_int/detail/integer.hpp" 

#include <cassert>
#include <cmath>

#include <algorithm>
#include <functional>
#include <ostream>
#include <type_traits>
#include <utility>

#include "tasty_int/detail/digits_addition.hpp"
#include "tasty_int/detail/digits_comparison.hpp"
#include "tasty_int/detail/digits_subtraction.hpp"
#include "tasty_int/detail/flip_sign.hpp"
#include "tasty_int/detail/sign_from_signed_arithmetic.hpp"
#include "tasty_int/detail/sign_from_unsigned_arithmetic.hpp"
#include "tasty_int/detail/conversions/base_prefix_format_from_ios_format.hpp"
#include "tasty_int/detail/conversions/string_from_integer.hpp"


namespace tasty_int {
namespace detail {
namespace {

template<typename T>
concept Arithmetic = std::is_arithmetic_v<T>;

template<typename T>
concept SignedArithmetic = std::is_signed_v<T>
                        && Arithmetic<T>;

template<typename T>
concept ArithmeticValue = std::is_unsigned_v<T>
                       || std::is_floating_point_v<T>;

template<typename T>
concept Value = ArithmeticValue<T>
             || std::is_same_v<T, std::vector<digit_type>>;

/// These specializations must be used in place of std::less, std::greater,
/// etc... to avoid the Koenig lookup of the std::vector operators over the
/// desired digit comparison semantics of the tasty_int::detail::operators.

struct DigitsLess
{
    bool
    operator()(const std::vector<digit_type> &lhs,
               const std::vector<digit_type> &rhs)
    {
        return lhs < rhs;
    }

    bool
    operator()(const std::vector<digit_type> &lhs,
               std::intmax_t                  rhs)
    {
        return lhs < static_cast<std::uintmax_t>(rhs);
    }

    bool
    operator()(std::intmax_t                  lhs,
               const std::vector<digit_type> &rhs)
    {
        return static_cast<std::uintmax_t>(lhs) < rhs;
    }

    bool
    operator()(const std::vector<digit_type> &lhs,
               long double                    rhs)
    {
        return lhs < rhs;
    }

    bool
    operator()(long double                    lhs,
               const std::vector<digit_type> &rhs)
    {
        return lhs < rhs;
    }
}; // struct DigitsLess

struct DigitsGreater
{
    bool
    operator()(const std::vector<digit_type> &lhs,
               const std::vector<digit_type> &rhs)
    {
        return lhs > rhs;
    }

    bool
    operator()(const std::vector<digit_type> &lhs,
               std::intmax_t                  rhs)
    {
        return lhs > static_cast<std::uintmax_t>(rhs);
    }

    bool
    operator()(std::intmax_t                  lhs,
               const std::vector<digit_type> &rhs)
    {
        return static_cast<std::uintmax_t>(lhs) > rhs;
    }

    bool
    operator()(const std::vector<digit_type> &lhs,
               long double                    rhs)
    {
        return lhs > rhs;
    }

    bool
    operator()(long double                    lhs,
               const std::vector<digit_type> &rhs)
    {
        return lhs > rhs;
    }
}; // struct DigitsGreater

struct DigitsLessEqual
{
    bool
    operator()(const std::vector<digit_type> &lhs,
               const std::vector<digit_type> &rhs)
    {
        return lhs <= rhs;
    }

    bool
    operator()(const std::vector<digit_type> &lhs,
               std::intmax_t                  rhs)
    {
        return lhs <= static_cast<std::uintmax_t>(rhs);
    }

    bool
    operator()(std::intmax_t                  lhs,
               const std::vector<digit_type> &rhs)
    {
        return static_cast<std::uintmax_t>(lhs) <= rhs;
    }

    bool
    operator()(const std::vector<digit_type> &lhs,
               long double                    rhs)
    {
        return lhs <= rhs;
    }

    bool
    operator()(long double                    lhs,
               const std::vector<digit_type> &rhs)
    {
        return lhs <= rhs;
    }
}; // struct DigitsLessEqual

struct DigitsGreaterEqual
{
    bool
    operator()(const std::vector<digit_type> &lhs,
               const std::vector<digit_type> &rhs)
    {
        return lhs >= rhs;
    }

    bool
    operator()(const std::vector<digit_type> &lhs,
               std::intmax_t                  rhs)
    {
        return lhs >= static_cast<std::uintmax_t>(rhs);
    }

    bool
    operator()(std::intmax_t                  lhs,
               const std::vector<digit_type> &rhs)
    {
        return static_cast<std::uintmax_t>(lhs) >= rhs;
    }

    bool
    operator()(const std::vector<digit_type> &lhs,
               long double                    rhs)
    {
        return lhs >= rhs;
    }

    bool
    operator()(long double                    lhs,
               const std::vector<digit_type> &rhs)
    {
        return lhs >= rhs;
    }
}; // struct DigitsGreaterEqual

template<ArithmeticValue  ArithmeticValueType,
         SignedArithmetic SignedArithmeticType>
bool
have_equality(const Integer        &lhs,
              SignedArithmeticType  rhs)
    requires std::is_convertible_v<SignedArithmeticType, ArithmeticValueType>
{
    Sign rhs_sign = sign_from_signed_arithmetic(rhs);
    if (lhs.sign != rhs_sign)
        return false;

    ArithmeticValueType rhs_value = (rhs_sign >= Sign::ZERO) ? rhs : -rhs;
    return lhs.digits == rhs_value;
}

template<typename CompareDigits>
bool
have_same_sign_inequality(const Integer &lhs,
                          const Integer &rhs)
{
    return (lhs.sign >= Sign::ZERO)
         ? CompareDigits{}(lhs.digits, rhs.digits)
         : CompareDigits{}(rhs.digits, lhs.digits);
}

template<template <typename> typename CompareSign,
         typename CompareDigits>
bool
have_inequality(const Integer &lhs,
                const Integer &rhs)
{
    return CompareSign<Sign>{}(lhs.sign, rhs.sign)
        || ((lhs.sign == rhs.sign) &&
            have_same_sign_inequality<CompareDigits>(lhs, rhs));
}

template<template <typename> typename CompareSign,
         typename                     CompareDigits,
         SignedArithmetic             SignedArithmeticType>
bool
have_inequality(const Integer        &lhs,
                SignedArithmeticType  rhs)
{
    Sign rhs_sign = sign_from_signed_arithmetic(rhs);
    if (lhs.sign != rhs_sign)
        return CompareSign<Sign>{}(lhs.sign, rhs_sign);

    return (rhs_sign >= Sign::ZERO)
         ? CompareDigits{}(lhs.digits, rhs)
         : CompareDigits{}(-rhs, lhs.digits);
}

template<typename RhsType>
bool
less_than(const Integer &lhs,
          RhsType        rhs)
{
    return have_inequality<std::less, DigitsLess>(lhs, rhs);
}

template<typename RhsType>
bool
greater_than(const Integer &lhs,
             RhsType        rhs)
{
    return have_inequality<std::greater, DigitsGreater>(lhs, rhs);
}

template<typename RhsType>
bool
less_than_or_equal_to(const Integer &lhs,
                      RhsType        rhs)
{
    return have_inequality<std::less, DigitsLessEqual>(lhs, rhs);
}

template<typename RhsType>
bool
greater_than_or_equal_to(const Integer &lhs,
                         RhsType        rhs)
{
    return have_inequality<std::greater, DigitsGreaterEqual>(lhs, rhs);
}

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

Sign
sign_difference(Sign minuend_sign,
                Sign digits_difference_sign)
{
    return static_cast<Sign>(minuend_sign * digits_difference_sign);
}

template<Value ValueType>
void
add_agreeing_terms_in_place(const ValueType &addend_value,
                            Sign             addend_sign,
                            Integer         &augend)
{
    augend.sign    = larger_of_agreeing_signs(augend.sign, addend_sign);
    augend.digits += addend_value;
}

template<Value ValueType>
void
subtract_value_in_place(const ValueType &subtrahend_value,
                        Integer         &minuend)
{
    Sign result_sign = subtract_in_place(subtrahend_value, minuend.digits);
    minuend.sign     = sign_difference(minuend.sign, result_sign);
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
        add_agreeing_terms_in_place(addend_value, addend_sign, augend);
    else
        subtract_value_in_place(addend_value, augend);

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
        result.sign   = sign_difference(rhs_sign, result_sign);
        result.digits = std::move(result_digits);
    }

    return result;
}

template<Value ValueType>
Integer &
subtract_signed_value_in_place(Integer         &minuend,
                               Sign             subtrahend_sign,
                               const ValueType &subtrahend_value)
{
    if (signs_agree(minuend.sign, subtrahend_sign))
        subtract_value_in_place(subtrahend_value, minuend);
    else
        minuend.digits += subtrahend_value;

    return minuend;
}

template<ArithmeticValue  ArithmeticValueType,
         SignedArithmetic SignedArithmeticType>
Integer &
subtract_signed_arithmetic_in_place(Integer              &minuend,
                                    SignedArithmeticType  subtrahend)
    requires std::is_convertible_v<SignedArithmeticType, ArithmeticValueType>
{
    auto [subtrahend_sign, subtrahend_value] =
        sign_and_value_from_signed_arithmetic<ArithmeticValueType>(subtrahend);

    return subtract_signed_value_in_place(minuend,
                                          subtrahend_sign,
                                          subtrahend_value);
}

template<Arithmetic ArithmeticType>
Integer
subtract_reverse_operands(const Integer  &lhs,
                          ArithmeticType  rhs)
{
    Integer result = rhs - lhs;

    result.sign = flip_sign(result.sign);
    
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
        result.sign   = sign_difference(larger_sign, result_sign);
        result.digits = std::move(result_digits);
    } else {
        result.sign   = larger_of_agreeing_signs(lhs_sign,
                                                 flip_sign(rhs.sign));
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


bool
operator==(const Integer &lhs,
           const Integer &rhs)
{
    return (lhs.sign   == rhs.sign)
        && (lhs.digits == rhs.digits);
}

bool
operator==(const Integer  &lhs,
           std::uintmax_t  rhs)
{
    return (lhs.sign   >= Sign::ZERO)
        && (lhs.digits == rhs);
}

bool
operator==(std::uintmax_t  lhs,
           const Integer  &rhs)
{
    return rhs == lhs;
}

bool
operator==(const Integer &lhs,
           std::intmax_t  rhs)
{
    return have_equality<std::uintmax_t>(lhs, rhs);
}

bool
operator==(std::intmax_t  lhs,
           const Integer &rhs)
{
    return rhs == lhs;
}

bool
operator==(const Integer &lhs,
           long double    rhs)
{
    return have_equality<long double>(lhs, rhs);
}

bool
operator==(long double    lhs,
           const Integer &rhs)
{
    return rhs == lhs;
}


bool
operator!=(const Integer &lhs,
           const Integer &rhs)
{
    return !(lhs == rhs);
}

bool
operator!=(const Integer  &lhs,
           std::uintmax_t  rhs)
{
    return !(lhs == rhs);
}

bool
operator!=(std::uintmax_t  lhs,
           const Integer  &rhs)
{
    return rhs != lhs;
}

bool
operator!=(const Integer &lhs,
           std::intmax_t  rhs)
{
    return !(lhs == rhs);
}

bool
operator!=(std::intmax_t  lhs,
           const Integer &rhs)
{
    return rhs != lhs;
}

bool
operator!=(const Integer &lhs,
           long double    rhs)
{
    return !(lhs == rhs);
}

bool
operator!=(long double    lhs,
           const Integer &rhs)
{
    return rhs != lhs;
}


bool
operator<(const Integer &lhs,
          const Integer &rhs)
{
    return less_than(lhs, rhs);
}

bool
operator<(const Integer  &lhs,
          std::uintmax_t  rhs)
{
    return (lhs.sign   < Sign::ZERO)
        || (lhs.digits < rhs);
}

bool
operator<(std::uintmax_t  lhs,
          const Integer  &rhs)
{
    return rhs > lhs;
}

bool
operator<(const Integer &lhs,
          std::intmax_t  rhs)
{
    return less_than(lhs, rhs);
}

bool
operator<(std::intmax_t  lhs,
          const Integer &rhs)
{
    return rhs > lhs;
}

bool
operator<(const Integer &lhs,
          long double    rhs)
{
    return less_than(lhs, rhs);
}

bool
operator<(long double    lhs,
          const Integer &rhs)
{
    return rhs > lhs;
}

bool
operator>(const Integer &lhs,
          const Integer &rhs)
{
    return greater_than(lhs, rhs);
}

bool
operator>(const Integer  &lhs,
          std::uintmax_t  rhs)
{
    return (lhs.sign   >= Sign::ZERO)
        && (lhs.digits >  rhs);
}

bool
operator>(std::uintmax_t  lhs,
          const Integer  &rhs)
{
    return rhs < lhs;
}

bool
operator>(const Integer &lhs,
          std::intmax_t  rhs)
{
    return greater_than(lhs, rhs);
}

bool
operator>(std::intmax_t  lhs,
          const Integer &rhs)
{
    return rhs < lhs;
}

bool
operator>(const Integer &lhs,
          long double    rhs)
{
    return greater_than(lhs, rhs);
}

bool
operator>(long double    lhs,
          const Integer &rhs)
{
    return rhs < lhs;
}


bool
operator<=(const Integer &lhs,
           const Integer &rhs)
{
    return less_than_or_equal_to(lhs, rhs);
}

bool
operator<=(const Integer  &lhs,
           std::uintmax_t  rhs)
{
    return (lhs.sign   <  Sign::ZERO)
        || (lhs.digits <= rhs);
}

bool
operator<=(std::uintmax_t  lhs,
           const Integer  &rhs)
{
    return rhs >= lhs;
}

bool
operator<=(const Integer &lhs,
           std::intmax_t  rhs)
{
    return less_than_or_equal_to(lhs, rhs);
}

bool
operator<=(std::intmax_t  lhs,
           const Integer &rhs)
{
    return rhs >= lhs;
}

bool
operator<=(const Integer &lhs,
           long double    rhs)
{
    return less_than_or_equal_to(lhs, rhs);
}

bool
operator<=(long double    lhs,
           const Integer &rhs)
{
    return rhs >= lhs;
}


bool
operator>=(const Integer &lhs,
           const Integer &rhs)
{
    return greater_than_or_equal_to(lhs, rhs);
}

bool
operator>=(const Integer  &lhs,
           std::uintmax_t  rhs)
{
    return (lhs.sign   >= Sign::ZERO)
        && (lhs.digits >= rhs);
}

bool
operator>=(std::uintmax_t  lhs,
           const Integer  &rhs)
{
    return rhs <= lhs;
}

bool
operator>=(const Integer &lhs,
           std::intmax_t  rhs)
{
    return greater_than_or_equal_to(lhs, rhs);
}

bool
operator>=(std::intmax_t  lhs,
           const Integer &rhs)
{
    return rhs <= lhs;
}

bool
operator>=(const Integer &lhs,
           long double    rhs)
{
    return greater_than_or_equal_to(lhs, rhs);
}

bool
operator>=(long double    lhs,
           const Integer &rhs)
{
    return rhs <= lhs;
}


Integer &
operator+=(Integer       &lhs,
           const Integer &rhs)
{
    if (signs_agree(lhs.sign, rhs.sign))
        add_agreeing_terms_in_place(rhs.digits, rhs.sign, lhs);
    else
        subtract_value_in_place(rhs.digits, lhs);

    return lhs;
}

Integer &
operator+=(Integer        &lhs,
           std::uintmax_t  rhs)
{
    if (lhs.sign >= Sign::ZERO) {
        Sign rhs_sign = sign_from_unsigned_arithmetic(rhs);
        add_agreeing_terms_in_place(rhs, rhs_sign, lhs);
    } else {
        subtract_value_in_place(rhs, lhs);
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
        result.sign   = sign_difference(lhs.sign, result_sign);
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
    return subtract_signed_value_in_place(lhs, rhs.sign, rhs.digits);
}

Integer &
operator-=(Integer        &lhs,
           std::uintmax_t  rhs)
{
    Sign rhs_sign = sign_from_unsigned_arithmetic(rhs);

    if (signs_agree(lhs.sign, rhs_sign))
        subtract_value_in_place(rhs, lhs);
    else
        lhs.digits += rhs;

    return lhs;
}

Integer &
operator-=(Integer       &lhs,
           std::intmax_t  rhs)
{
    return subtract_signed_arithmetic_in_place<std::uintmax_t>(lhs, rhs);
}

Integer &
operator-=(Integer     &lhs,
           long double  rhs)
{
    return subtract_signed_arithmetic_in_place<long double>(lhs, rhs);
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


std::ostream &
operator<<(std::ostream  &output,
           const Integer &integer)
{
    auto format =
        conversions::base_prefix_format_from_ios_format(output.flags());

    auto stringified = conversions::string_from_integer(integer, format.base);
    std::string_view digits = stringified;

    if (integer.sign >= Sign::ZERO) {
        output << format.nonnegative_sign;
    } else {
        output << '-';
        digits.remove_prefix(1);
    }

    return output << format.prefix << digits;
}

} // namespace detail
} // namespace tasty_int
