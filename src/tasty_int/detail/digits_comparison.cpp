#include "tasty_int/detail/digits_comparison.hpp"

#include <algorithm>
#include <functional>
#include <iterator>

#include "tasty_int/detail/integral_digits_view.hpp"
#include "tasty_int/detail/floating_point_digits_iterator.hpp"
#include "tasty_int/detail/size_digits_from_nonnegative_floating_point.hpp"


namespace tasty_int {
namespace detail {
namespace {

bool
have_unequal_high_digits(const std::vector<digit_type> &lhs,
                         IntegralDigitsView             rhs_view)
{
    return (lhs.size() == 2)
        && (lhs.back() != rhs_view.high_digit());
}

template<template <typename> typename Compare>
std::pair<bool, digit_type>
sequence_inequality_common_compare(
    const std::vector<digit_type> &lhs,
    long double                    rhs,
    bool                           equal_comparison
)
{
    auto lhs_cursor = lhs.begin();
    auto lhs_end    = lhs.end();
    auto rhs_cursor = FloatingPointDigitsIterator(rhs);

    bool last_mismatch_comparison = equal_comparison;
    do {
        digit_type lhs_digit = *lhs_cursor;
        ++lhs_cursor;
        digit_type rhs_digit = *rhs_cursor;
        ++rhs_cursor;

        if (lhs_digit != rhs_digit)
            last_mismatch_comparison =
                Compare<digit_type>{}(lhs_digit, rhs_digit);

    } while (lhs_cursor != lhs_end);

    return { last_mismatch_comparison, *rhs_cursor };
}

template<template <typename> typename Compare>
bool
sequence_inequality_compare(const std::vector<digit_type> &lhs,
                            long double                    rhs,
                            bool                           equal_comparison)
{
    auto [last_mismatch_comparison, last_rhs_digit] =
        sequence_inequality_common_compare<Compare>(lhs, rhs, equal_comparison);

    if (last_rhs_digit != 0)
        last_mismatch_comparison = Compare<digit_type>{}(0, 1);

    return last_mismatch_comparison;
}

template<template <typename> typename Compare>
struct StrictSequenceInequality
{
    bool
    operator()(std::vector<digit_type>::const_reverse_iterator lhs_rbegin,
               std::vector<digit_type>::const_reverse_iterator lhs_rend,
               std::vector<digit_type>::const_reverse_iterator rhs_rbegin,
               std::vector<digit_type>::const_reverse_iterator rhs_rend)
    {
        return std::lexicographical_compare(lhs_rbegin, lhs_rend,
                                            rhs_rbegin, rhs_rend,
                                            Compare<digit_type>{});
    }

    bool
    operator()(const std::vector<digit_type> &lhs,
               const std::vector<digit_type> &rhs)
    {
        return operator()(lhs.rbegin(), lhs.rend(),
                          rhs.rbegin(), rhs.rend());
    }

    bool
    operator()(const std::vector<digit_type> &lhs,
               IntegralDigitsView             rhs_view)
    {
        if (have_unequal_high_digits(lhs, rhs_view))
            return Compare<digit_type>{}(lhs.back(), rhs_view.high_digit());

        return Compare<digit_type>{}(lhs.front(), rhs_view.low_digit());
    }

    bool
    operator()(const std::vector<digit_type> &lhs,
               long double                    rhs)
    {
        bool equal_comparison = false;

        return sequence_inequality_compare<Compare>(lhs, rhs, equal_comparison);
    }
}; // struct StrictSequenceInequality

template<template <typename> typename Compare>
struct NonStrictSequenceInequality
{
    bool
    operator()(const std::vector<digit_type> &lhs,
               const std::vector<digit_type> &rhs)
    {
        auto mismatch = std::mismatch(lhs.rbegin(), lhs.rend(),
                                      rhs.rbegin());

        return (mismatch.first == lhs.rend())
            || Compare<digit_type>{}(*mismatch.first, *mismatch.second);
    }

    bool
    operator()(const std::vector<digit_type> &lhs,
               IntegralDigitsView             rhs_view)
    {
        if (have_unequal_high_digits(lhs, rhs_view))
            return Compare<digit_type>{}(lhs.back(), rhs_view.high_digit());

        return (lhs.front() == rhs_view.low_digit())
            || Compare<digit_type>{}(lhs.front(), rhs_view.low_digit());
    }

    bool
    operator()(const std::vector<digit_type> &lhs,
               long double                    rhs)
    {
        bool equal_comparison = true;

        return sequence_inequality_compare<Compare>(lhs, rhs, equal_comparison);
    }
}; // struct StrictSequenceInequality

template<template <typename> typename Compare,
         template <template <typename> typename> typename SequenceCompare>
bool
have_inequality(std::vector<digit_type>::const_iterator lhs_begin,
                std::vector<digit_type>::const_iterator lhs_end,
                std::vector<digit_type>::const_iterator rhs_begin,
                std::vector<digit_type>::const_iterator rhs_end)
{
    auto lhs_size = lhs_end - lhs_begin;
    auto rhs_size = rhs_end - rhs_begin;

    return Compare<std::vector<digit_type>::size_type>{}(lhs_size, rhs_size)
        || ((lhs_size == rhs_size) &&
            SequenceCompare<Compare>{}(std::make_reverse_iterator(lhs_end),
                                       std::make_reverse_iterator(lhs_begin),
                                       std::make_reverse_iterator(rhs_end),
                                       std::make_reverse_iterator(rhs_begin)));
}

template<template <typename> typename Compare,
         template <template <typename> typename> typename SequenceCompare>
bool
have_inequality(const std::vector<digit_type> &lhs,
                const std::vector<digit_type> &rhs)
{
    return Compare<std::vector<digit_type>::size_type>{}(lhs.size(), rhs.size())
        || ((lhs.size() == rhs.size()) &&
            SequenceCompare<Compare>{}(lhs, rhs));
}

template<template <typename> typename Compare,
         template <template <typename> typename> typename SequenceCompare>
bool
have_inequality(const std::vector<digit_type> &lhs,
                std::uintmax_t                 rhs)
{
    IntegralDigitsView rhs_view(rhs);

    return Compare<std::vector<digit_type>::size_type>{}(lhs.size(),
                                                         rhs_view.digits_size())
        || ((lhs.size() == rhs_view.digits_size()) &&
            SequenceCompare<Compare>{}(lhs, rhs_view));
}

template<template <typename> typename Compare,
         template <template <typename> typename> typename SequenceCompare>
bool
have_inequality(const std::vector<digit_type> &lhs,
                long double                    rhs)
{
    std::size_t rhs_max_digits =
        size_digits_from_nonnegative_floating_point(rhs);
    if (lhs.size() > rhs_max_digits)
        return Compare<int>{}(1, 0);

    std::size_t rhs_min_digits = rhs_max_digits - 1;
    if (lhs.size() < rhs_min_digits)
        return Compare<int>{}(0, 1);

    return SequenceCompare<Compare>{}(lhs, rhs);
}

template<typename RhsType>
bool
less_than(const std::vector<digit_type> &lhs,
          RhsType                        rhs)
{
    return have_inequality<std::less, StrictSequenceInequality>(lhs, rhs);
}

template<typename RhsType>
bool
greater_than(const std::vector<digit_type> &lhs,
             RhsType                        rhs)
{
    return have_inequality<std::greater, StrictSequenceInequality>(lhs, rhs);
}

template<typename RhsType>
bool
less_than_or_equal_to(const std::vector<digit_type> &lhs,
                      RhsType                        rhs)
{
    return have_inequality<std::less, NonStrictSequenceInequality>(lhs, rhs);
}

template<typename RhsType>
bool
greater_than_or_equal_to(const std::vector<digit_type> &lhs,
                         RhsType                        rhs)
{
    return have_inequality<std::greater, NonStrictSequenceInequality>(lhs, rhs);
}

} // namespace


bool
operator==(const std::vector<digit_type> &lhs,
           const std::vector<digit_type> &rhs)
{
    return std::operator==(lhs, rhs);
}

bool
operator==(const std::vector<digit_type> &lhs,
           std::uintmax_t                 rhs)
{
    IntegralDigitsView rhs_view(rhs);

    return (lhs.size() == rhs_view.digits_size())
        && (rhs_view.low_digit() == lhs.front())
        && ((lhs.size() == 1) ||
            (lhs.back() == rhs_view.high_digit()));
}

bool
operator==(std::uintmax_t                 lhs,
           const std::vector<digit_type> &rhs)
{
    return rhs == lhs;
}

bool
operator==(const std::vector<digit_type> &lhs,
           long double                    rhs)
{
    return std::equal(lhs.begin(), lhs.end(),
                      FloatingPointDigitsIterator(rhs));
}

bool
operator==(long double                    lhs,
           const std::vector<digit_type> &rhs)
{
    return rhs == lhs;
}


bool
operator!=(const std::vector<digit_type> &lhs,
           const std::vector<digit_type> &rhs)
{
    return !(lhs == rhs);
}

bool
operator!=(const std::vector<digit_type> &lhs,
           std::uintmax_t                 rhs)
{
    return !(lhs == rhs);
}

bool
operator!=(std::uintmax_t                 lhs,
           const std::vector<digit_type> &rhs)
{
    return rhs != lhs;
}

bool
operator!=(const std::vector<digit_type> &lhs,
           long double                    rhs)
{
    return !(lhs == rhs);
}

bool
operator!=(long double                    lhs,
           const std::vector<digit_type> &rhs)
{
    return rhs != lhs;
}


bool
operator<(const std::vector<digit_type> &lhs,
          const std::vector<digit_type> &rhs)
{
    return less_than(lhs, rhs);
}

bool
operator<(const std::vector<digit_type> &lhs,
          std::uintmax_t                 rhs)
{
    return less_than(lhs, rhs);
}

bool
operator<(std::uintmax_t                 lhs,
          const std::vector<digit_type> &rhs)
{
    return rhs > lhs;
}

bool
operator<(const std::vector<digit_type> &lhs,
          long double                    rhs)
{
    return less_than(lhs, rhs);
}


bool
operator<(long double                    lhs,
          const std::vector<digit_type> &rhs)
{
    return rhs > lhs;
}


bool
operator>(const std::vector<digit_type> &lhs,
          const std::vector<digit_type> &rhs)
{
    return greater_than(lhs, rhs);
}

bool
operator>(const std::vector<digit_type> &lhs,
          std::uintmax_t                 rhs)
{
    return greater_than(lhs, rhs);
}

bool
operator>(std::uintmax_t                 lhs,
          const std::vector<digit_type> &rhs)
{
    return rhs < lhs;
}

bool
operator>(const std::vector<digit_type> &lhs,
          long double                    rhs)
{
    return greater_than(lhs, rhs);
}

bool
operator>(long double                    lhs,
          const std::vector<digit_type> &rhs)
{
    return rhs < lhs;
}


bool
operator<=(const std::vector<digit_type> &lhs,
           const std::vector<digit_type> &rhs)
{
    return less_than_or_equal_to(lhs, rhs);
}

bool
operator<=(const std::vector<digit_type> &lhs,
           std::uintmax_t                 rhs)
{
    return less_than_or_equal_to(lhs, rhs);
}

bool
operator<=(std::uintmax_t                 lhs,
           const std::vector<digit_type> &rhs)
{
    return rhs >= lhs;
}

bool
operator<=(const std::vector<digit_type> &lhs,
           long double                    rhs)
{
    return less_than_or_equal_to(lhs, rhs);
}

bool
operator<=(long double                    lhs,
           const std::vector<digit_type> &rhs)
{
    return rhs >= lhs;
}


bool
operator>=(const std::vector<digit_type> &lhs,
           const std::vector<digit_type> &rhs)
{
    return greater_than_or_equal_to(lhs, rhs);
}

bool
operator>=(const std::vector<digit_type> &lhs,
           std::uintmax_t                 rhs)
{
    return greater_than_or_equal_to(lhs, rhs);
}

bool
operator>=(std::uintmax_t                 lhs,
           const std::vector<digit_type> &rhs)
{
    return rhs <= lhs;
}

bool
operator>=(const std::vector<digit_type> &lhs,
           long double                    rhs)
{
    return greater_than_or_equal_to(lhs, rhs);
}

bool
operator>=(long double                    lhs,
           const std::vector<digit_type> &rhs)
{
    return rhs <= lhs;
}

bool
less_than(std::vector<digit_type>::const_iterator lhs_begin,
          std::vector<digit_type>::const_iterator lhs_end,
          std::vector<digit_type>::const_iterator rhs_begin,
          std::vector<digit_type>::const_iterator rhs_end)
{
    return have_inequality<std::less, StrictSequenceInequality>(lhs_begin,
                                                                lhs_end,
                                                                rhs_begin,
                                                                rhs_end);
}

} // namespace detail
} // namespace tasty_int
