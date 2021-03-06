#ifndef TASTY_INT_TASTY_INT_DETAIL_DIGITS_COMPARISON_OPERATORS_HPP
#define TASTY_INT_TASTY_INT_DETAIL_DIGITS_COMPARISON_OPERATORS_HPP

#include <vector>

#include "tasty_int/detail/digit_type.hpp"

namespace tasty_int {
namespace detail {

/**
 * @defgroup DigitsComparisonOperators Digits Comparison Operators
 *
 * These operations operate on little-endian `std::vector`s of `digit_type`.
 * For inputs of inequal magnitudes, the larger-magnitude input is considered
 * greater.  For inputs of equal magntitudes, the digit sequences are compared
 * from most to least-signficant digit, and the first mismatch determines the
 * ordering.
 */
/// @{
bool
operator==(const std::vector<digit_type> &lhs,
           const std::vector<digit_type> &rhs);
bool
operator==(const std::vector<digit_type> &lhs,
           std::uintmax_t                 rhs);
bool
operator==(std::uintmax_t                 lhs,
           const std::vector<digit_type> &rhs);
bool
operator==(const std::vector<digit_type> &lhs,
           long double                    rhs);
bool
operator==(long double                    lhs,
           const std::vector<digit_type> &rhs);

bool
operator!=(const std::vector<digit_type> &lhs,
           const std::vector<digit_type> &rhs);
bool
operator!=(const std::vector<digit_type> &lhs,
           std::uintmax_t                 rhs);
bool
operator!=(std::uintmax_t                 lhs,
           const std::vector<digit_type> &rhs);
bool
operator!=(const std::vector<digit_type> &lhs,
           long double                    rhs);
bool
operator!=(long double                    lhs,
           const std::vector<digit_type> &rhs);

bool
operator<(const std::vector<digit_type> &lhs,
          const std::vector<digit_type> &rhs);
bool
operator<(const std::vector<digit_type> &lhs,
          std::uintmax_t                 rhs);
bool
operator<(std::uintmax_t                 lhs,
          const std::vector<digit_type> &rhs);
bool
operator<(const std::vector<digit_type> &lhs,
          long double                    rhs);
bool
operator<(long double                    lhs,
          const std::vector<digit_type> &rhs);

bool
operator>(const std::vector<digit_type> &lhs,
          const std::vector<digit_type> &rhs);
bool
operator>(const std::vector<digit_type> &lhs,
          std::uintmax_t                 rhs);
bool
operator>(std::uintmax_t                 lhs,
          const std::vector<digit_type> &rhs);
bool
operator>(const std::vector<digit_type> &lhs,
          long double                    rhs);
bool
operator>(long double                    lhs,
          const std::vector<digit_type> &rhs);

bool
operator<=(const std::vector<digit_type> &lhs,
           const std::vector<digit_type> &rhs);
bool
operator<=(const std::vector<digit_type> &lhs,
           std::uintmax_t                 rhs);
bool
operator<=(std::uintmax_t                 lhs,
           const std::vector<digit_type> &rhs);
bool
operator<=(const std::vector<digit_type> &lhs,
           long double                    rhs);
bool
operator<=(long double                    lhs,
           const std::vector<digit_type> &rhs);

bool
operator>=(const std::vector<digit_type> &lhs,
           const std::vector<digit_type> &rhs);
bool
operator>=(const std::vector<digit_type> &lhs,
           std::uintmax_t                 rhs);
bool
operator>=(std::uintmax_t                 lhs,
           const std::vector<digit_type> &rhs);
bool
operator>=(const std::vector<digit_type> &lhs,
           long double                    rhs);
bool
operator>=(long double                    lhs,
           const std::vector<digit_type> &rhs);

bool
less_than(std::vector<digit_type>::const_iterator lhs_begin,
          std::vector<digit_type>::const_iterator lhs_end,
          std::vector<digit_type>::const_iterator rhs_begin,
          std::vector<digit_type>::const_iterator rhs_end);
/// @}

} // namespace detail
} // namespace tasty_int

#endif // ifndef TASTY_INT_TASTY_INT_DETAIL_DIGITS_COMPARISON_OPERATORS_HPP
