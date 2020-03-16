#include "tasty_int/detail/integer.hpp" 

#include <cmath>

#include <algorithm>
#include <functional>
#include <type_traits>
#include <utility>

#include "tasty_int/detail/digits_comparison.hpp"
#include "tasty_int/detail/digits_addition.hpp"
#include "tasty_int/detail/digits_subtraction.hpp"
#include "tasty_int/detail/sign_from_signed_arithmetic.hpp"
#include "tasty_int/detail/sign_from_unsigned_arithmetic.hpp"


namespace tasty_int {
namespace detail {
namespace {

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

template<typename ValueType,
         typename SignedArithmeticType>
bool
have_equality(const Integer        &lhs,
              SignedArithmeticType  rhs)
    requires std::is_convertible_v<SignedArithmeticType, ValueType>
          && std::is_arithmetic_v<SignedArithmeticType>
          && std::is_signed_v<SignedArithmeticType>
{
    Sign rhs_sign = sign_from_signed_arithmetic(rhs);
    if (lhs.sign != rhs_sign)
        return false;

    ValueType rhs_value = (rhs_sign >= Sign::ZERO) ? rhs : -rhs;
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
         typename CompareDigits,
         typename SignedArithmeticType>
bool
have_inequality(const Integer        &lhs,
                SignedArithmeticType  rhs)
    requires std::is_arithmetic_v<SignedArithmeticType>
          && std::is_signed_v<SignedArithmeticType>
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
sign_sum_from_agreeing_signs(Sign addend_sign1,
                             Sign addend_sign2)
{
    return static_cast<Sign>(addend_sign1 | addend_sign2);
}

Sign
sign_difference(Sign minuend_sign,
                Sign digits_difference_sign)
{
    return static_cast<Sign>(minuend_sign * digits_difference_sign);
}

template<typename ValueType>
void
add_aggreeing_terms_in_place(const ValueType &addend_value,
                             Sign             addend_sign,
                             Integer         &augend)
{
    augend.sign    = sign_sum_from_agreeing_signs(augend.sign, addend_sign);
    augend.digits += addend_value;
}

template<typename ValueType>
void
subtract_disaggreeing_terms_in_place(const ValueType &subtrahend_value,
                                     Integer         &minuend)
{
    Sign result_sign = subtract_in_place(subtrahend_value, minuend.digits);
    minuend.sign     = sign_difference(minuend.sign, result_sign);
}

template<typename ValueType,
         typename SignedArithmeticType>
Integer &
add_signed_arithmetic_in_place(SignedArithmeticType  addend,
                               Integer              &augend)
    requires std::is_arithmetic_v<ValueType>
          && std::is_signed_v<SignedArithmeticType>
          && std::is_arithmetic_v<SignedArithmeticType>
{
    Sign addend_sign       = sign_from_signed_arithmetic(addend);
    ValueType addend_value = std::abs(addend);

    if (signs_agree(augend.sign, addend_sign)) {
        add_aggreeing_terms_in_place(addend_value, addend_sign, augend);
    } else {
        Sign result_sign = subtract_in_place(addend_value, augend.digits);
        augend.sign      = sign_difference(augend.sign, result_sign);
    }

    return augend;
}

template<typename ValueType,
         typename SignedArithmeticType>
Integer
add_signed_arithmetic(const Integer        &lhs,
                      SignedArithmeticType  rhs)
    requires std::is_arithmetic_v<ValueType>
          && std::is_signed_v<SignedArithmeticType>
          && std::is_arithmetic_v<SignedArithmeticType>
{
    Integer result;

    Sign rhs_sign       = sign_from_signed_arithmetic(rhs);
    ValueType rhs_value = std::abs(rhs);

    if (signs_agree(lhs.sign, rhs_sign)) {
        result.sign   = sign_sum_from_agreeing_signs(lhs.sign, rhs_sign);
        result.digits = lhs.digits + rhs_value;
    } else {
        auto [result_sign, result_digits] = subtract(rhs_value, lhs.digits);
        result.sign   = sign_difference(rhs_sign, result_sign);
        result.digits = std::move(result_digits);
    }

    return result;
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
        add_aggreeing_terms_in_place(rhs.digits, rhs.sign, lhs);
    else
        subtract_disaggreeing_terms_in_place(rhs.digits, lhs);

    return lhs;
}

Integer &
operator+=(Integer        &lhs,
           std::uintmax_t  rhs)
{
    if (lhs.sign >= Sign::ZERO) {
        Sign rhs_sign  = sign_from_unsigned_arithmetic(rhs);
        add_aggreeing_terms_in_place(rhs, rhs_sign, lhs);
    } else {
        subtract_disaggreeing_terms_in_place(rhs, lhs);
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
        result.sign   = sign_sum_from_agreeing_signs(lhs.sign, rhs.sign);
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
        result.sign   = sign_sum_from_agreeing_signs(lhs.sign, rhs_sign);
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

} // namespace detail
} // namespace tasty_int
