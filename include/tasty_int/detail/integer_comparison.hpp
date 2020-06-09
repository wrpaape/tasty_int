#ifndef TASTY_INT_TASTY_INT_DETAIL_INTEGER_COMPARISON_HPP
#define TASTY_INT_TASTY_INT_DETAIL_INTEGER_COMPARISON_HPP

#include "tasty_int/detail/integer.hpp"

#include <cstdint>


namespace tasty_int {
namespace detail {

/**
 * @defgroup IntegerComparisonOperators Integer Comparison Operators
 *
 * These operators compare tasty_int::detail::Integer and another arithmetic
 * operand like ordinary ints:
 *     
 *     - positive values are greater than zero
 *     - positive values compare greater as their magnitude increases
 *     - negative values are less than zero
 *     - negative values compare lesser as their magnitude increases
 *
 * with the exception that floating point values are truncated toward zero.
 */
/// @{
bool
operator==(const Integer &lhs,
           const Integer &rhs);
bool
operator==(const Integer  &lhs,
           std::uintmax_t  rhs);
bool
operator==(std::uintmax_t  lhs,
           const Integer  &rhs);
bool
operator==(const Integer &lhs,
           std::intmax_t  rhs);
bool
operator==(std::intmax_t  lhs,
           const Integer &rhs);
bool
operator==(const Integer &lhs,
           long double    rhs);
bool
operator==(long double    lhs,
           const Integer &rhs);

bool
operator!=(const Integer &lhs,
           const Integer &rhs);
bool
operator!=(const Integer  &lhs,
           std::uintmax_t  rhs);
bool
operator!=(std::uintmax_t  lhs,
           const Integer  &rhs);
bool
operator!=(const Integer &lhs,
           std::intmax_t  rhs);
bool
operator!=(std::intmax_t  lhs,
           const Integer &rhs);
bool
operator!=(const Integer &lhs,
           long double    rhs);
bool
operator!=(long double    lhs,
           const Integer &rhs);

bool
operator<(const Integer &lhs,
          const Integer &rhs);
bool
operator<(const Integer  &lhs,
          std::uintmax_t  rhs);
bool
operator<(std::uintmax_t  lhs,
          const Integer  &rhs);
bool
operator<(const Integer &lhs,
          std::intmax_t  rhs);
bool
operator<(std::intmax_t  lhs,
          const Integer &rhs);
bool
operator<(const Integer &lhs,
          long double    rhs);
bool
operator<(long double    lhs,
          const Integer &rhs);

bool
operator>(const Integer &lhs,
          const Integer &rhs);
bool
operator>(const Integer  &lhs,
          std::uintmax_t  rhs);
bool
operator>(std::uintmax_t  lhs,
          const Integer  &rhs);
bool
operator>(const Integer &lhs,
          std::intmax_t  rhs);
bool
operator>(std::intmax_t  lhs,
          const Integer &rhs);
bool
operator>(const Integer &lhs,
          long double    rhs);
bool
operator>(long double    lhs,
          const Integer &rhs);

bool
operator<=(const Integer &lhs,
           const Integer &rhs);
bool
operator<=(const Integer  &lhs,
           std::uintmax_t  rhs);
bool
operator<=(std::uintmax_t  lhs,
           const Integer  &rhs);
bool
operator<=(const Integer &lhs,
           std::intmax_t  rhs);
bool
operator<=(std::intmax_t  lhs,
           const Integer &rhs);
bool
operator<=(const Integer &lhs,
           long double    rhs);
bool
operator<=(long double    lhs,
           const Integer &rhs);

bool
operator>=(const Integer &lhs,
           const Integer &rhs);
bool
operator>=(const Integer  &lhs,
           std::uintmax_t  rhs);
bool
operator>=(std::uintmax_t  lhs,
           const Integer  &rhs);
bool
operator>=(const Integer &lhs,
           std::intmax_t  rhs);
bool
operator>=(std::intmax_t  lhs,
           const Integer &rhs);
bool
operator>=(const Integer &lhs,
           long double    rhs);
bool
operator>=(long double    lhs,
           const Integer &rhs);
/// @}

} // namespace detail
} // namespace tasty_int

#endif // TASTY_INT_TASTY_INT_DETAIL_INTEGER_COMPARISON_HPP
