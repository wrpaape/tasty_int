#include "tasty_int/detail/integer.hpp"

#include <functional>

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

}; // struct DigitsLess

struct DigitsGreater
{
    bool
    operator()(const std::vector<digit_type> &lhs,
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

}; // struct DigitsLessEqual

struct DigitsGreaterEqual
{
    bool
    operator()(const std::vector<digit_type> &lhs,
               const std::vector<digit_type> &rhs)
    {
        return lhs >= rhs;
    }

}; // struct DigitsGreaterEqual

template<typename CompareDigitsNonnegative,
         typename CompareDigitsNegative>
bool
have_same_sign_inequality(const Integer &lhs,
                          const Integer &rhs)
{
    return (lhs.sign >= Sign::ZERO)
         ? CompareDigitsNonnegative{}(lhs.digits, rhs.digits)
         : CompareDigitsNegative{}(   lhs.digits, rhs.digits);
}

template<template <typename> typename CompareSign,
         typename CompareDigitsNonnegative,
         typename CompareDigitsNegative>
bool
have_inequality(const Integer &lhs,
                const Integer &rhs)
{
    return CompareSign<Sign>{}(lhs.sign, rhs.sign)
        || ((lhs.sign == rhs.sign) &&
            have_same_sign_inequality<CompareDigitsNonnegative,
                                      CompareDigitsNegative>(lhs, rhs));
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
operator!=(const Integer &lhs,
           const Integer &rhs)
{
    return !(lhs == rhs);
}

bool
operator<(const Integer &lhs,
          const Integer &rhs)
{
    return have_inequality<std::less, DigitsLess, DigitsGreater>(lhs, rhs);
}

bool
operator>(const Integer &lhs,
          const Integer &rhs)
{
    return have_inequality<std::greater, DigitsGreater, DigitsLess>(lhs, rhs);
}

bool
operator<=(const Integer &lhs,
           const Integer &rhs)
{
    return have_inequality<std::less,
                           DigitsLessEqual,
                           DigitsGreaterEqual>(lhs, rhs);
}

bool
operator>=(const Integer &lhs,
           const Integer &rhs)
{
    return have_inequality<std::greater,
                           DigitsGreaterEqual,
                           DigitsLessEqual>(lhs, rhs);
}

} // namespace detail
} // namespace tasty_int
