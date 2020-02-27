#ifndef TASTY_INT_TASTY_INT_DETAIL_DIGITS_ADDITION_OPERATORS_HPP
#define TASTY_INT_TASTY_INT_DETAIL_DIGITS_ADDITION_OPERATORS_HPP

#include <cstdint>

#include <vector>

#include "tasty_int/detail/digit_type.hpp"

namespace tasty_int {
namespace detail {

/**
 * @defgroup DigitsAdditionOperators Digits Addition Operators
 *
 * These operations operate on little-endian `std::vector`s of `digit_type`.
 *
 * @pre input digits vectors must be non-empty
 * @pre every element of input digits vectors must be `<= DIGIT_TYPE_MAX`
 */
/// @{
std::vector<digit_type> &
operator+=(std::vector<digit_type>       &lhs,
           const std::vector<digit_type> &rhs);

std::vector<digit_type> &
operator+=(std::vector<digit_type> &lhs,
           std::uintmax_t           rhs);

/// @pre `std::isfinite(rhs) && (rhs >= 0.0)`
std::vector<digit_type> &
operator+=(std::vector<digit_type> &lhs,
           long double              rhs);

std::vector<digit_type>
operator+(const std::vector<digit_type> &lhs,
          const std::vector<digit_type> &rhs);

std::vector<digit_type>
operator+(const std::vector<digit_type> &lhs,
          std::uintmax_t                 rhs);

std::vector<digit_type>
operator+(std::uintmax_t                 lhs,
          const std::vector<digit_type> &rhs);

/// @pre `std::isfinite(rhs) && (rhs >= 0.0)`
std::vector<digit_type>
operator+(const std::vector<digit_type> &lhs,
          long double                    rhs);

/// @pre `std::isfinite(lhs) && (lhs >= 0.0)`
std::vector<digit_type>
operator+(long double                    lhs,
          const std::vector<digit_type> &rhs);
/// @}

} // namespace detail
} // namespace tasty_int

#endif // ifndef TASTY_INT_TASTY_INT_DETAIL_DIGITS_ADDITION_OPERATORS_HPP
