#include "tasty_int/detail/integer_comparison.hpp"

#include <functional>

#include "tasty_int/detail/integer_operation.hpp"
#include "tasty_int/detail/digits_comparison.hpp"


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

} // namespace detail
} // namespace tasty_int
