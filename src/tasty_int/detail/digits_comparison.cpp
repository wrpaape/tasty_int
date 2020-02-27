#include "tasty_int/detail/digits_comparison.hpp"

#include <algorithm>
#include <functional>


namespace tasty_int {
namespace detail {
namespace {

template<template <typename> typename Compare>
struct StrictSequenceInequality
{
    bool operator()(const std::vector<digit_type> &lhs,
                    const std::vector<digit_type> &rhs)
    {
        return std::lexicographical_compare(lhs.rbegin(), lhs.rend(),
                                            rhs.rbegin(), rhs.rend(),
                                            Compare<digit_type>{});
    }
}; // struct StrictSequenceInequality

template<template <typename> typename Compare>
struct NonStrictSequenceInequality
{
    bool operator()(const std::vector<digit_type> &lhs,
                    const std::vector<digit_type> &rhs)
    {
        auto mismatch = std::mismatch(lhs.rbegin(), lhs.rend(),
                                      rhs.rbegin());

        return (mismatch.first == lhs.rend())
            || Compare<digit_type>{}(*mismatch.first, *mismatch.second);
    }
}; // struct StrictSequenceInequality

template<template <typename> typename Compare,
         template <template <typename> typename> typename SequenceCompare>
bool
have_inequality(const std::vector<digit_type> &lhs,
                const std::vector<digit_type> &rhs)
{
    return Compare<std::vector<digit_type>::size_type>{}(lhs.size(), rhs.size())
        || ((lhs.size() == rhs.size()) && SequenceCompare<Compare>{}(lhs, rhs));
}

} // namespace


bool
operator==(const std::vector<digit_type> &lhs,
           const std::vector<digit_type> &rhs)
{
    return std::operator==(lhs, rhs);
}

bool
operator!=(const std::vector<digit_type> &lhs,
           const std::vector<digit_type> &rhs)
{
    return std::operator!=(lhs, rhs);
}

bool
operator<(const std::vector<digit_type> &lhs,
          const std::vector<digit_type> &rhs)
{
    return have_inequality<std::less, StrictSequenceInequality>(lhs, rhs);
}

bool
operator>(const std::vector<digit_type> &lhs,
          const std::vector<digit_type> &rhs)
{
    return have_inequality<std::greater, StrictSequenceInequality>(lhs, rhs);
}

bool
operator<=(const std::vector<digit_type> &lhs,
           const std::vector<digit_type> &rhs)
{
    return have_inequality<std::less, NonStrictSequenceInequality>(lhs, rhs);
}

bool
operator>=(const std::vector<digit_type> &lhs,
           const std::vector<digit_type> &rhs)
{
    return have_inequality<std::greater, NonStrictSequenceInequality>(lhs, rhs);
}

} // namespace detail
} // namespace tasty_int
