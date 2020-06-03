#ifndef TASTY_INT_TASTY_INT_DETAIL_DIGITS_MULTIPLICATION_HPP
#define TASTY_INT_TASTY_INT_DETAIL_DIGITS_MULTIPLICATION_HPP

#include <vector>

#include "tasty_int/detail/digit_type.hpp"


namespace tasty_int {
namespace detail {

/**
 * @defgroup DigitsMultiplicationOperators Digits Multiplication Operators
 *
 * These operations operate on little-endian `std::vector`s of `digit_type`.
 *
 * @pre input digits vectors must be non-empty
 * @pre input digits may have no leading zeros
 * @pre every element of input digits vectors must be `<= DIGIT_TYPE_MAX`
 */
/// @{
std::vector<digit_type> &
operator*=(std::vector<digit_type>       &lhs,
           const std::vector<digit_type> &rhs);

std::vector<digit_type> &
operator*=(std::vector<digit_type> &lhs,
           std::uintmax_t           rhs);

/**
 * @defgroup DigitsMultiplicationFloatingPointOverloads Digits Multiplication Floating Point Overloads
 *
 * These operations truncate their operand to the nearest integer before
 * multiplying.
 *
 * @pre floating point operand is finite and nonnegative
 */
/// @ingroup DigitsMultiplicationFloatingPointOverloads
std::vector<digit_type> &
operator*=(std::vector<digit_type> &lhs,
           long double              rhs);

std::vector<digit_type>
operator*(const std::vector<digit_type> &lhs,
          const std::vector<digit_type> &rhs);

std::vector<digit_type>
operator*(const std::vector<digit_type> &lhs,
          std::uintmax_t                 rhs);

std::vector<digit_type>
operator*(std::uintmax_t                 lhs,
          const std::vector<digit_type> &rhs);

/// @ingroup DigitsMultiplicationFloatingPointOverloads
std::vector<digit_type>
operator*(const std::vector<digit_type> &lhs,
          long double                    rhs);

/// @ingroup DigitsMultiplicationFloatingPointOverloads
std::vector<digit_type>
operator*(long double                    lhs,
          const std::vector<digit_type> &rhs);
/// @}


/**
 * @defgroup DigitsMultiplicationAlgorithms Digits Multiplication Algorithms
 *
 * These algorithms implement `operator*`.
 *
 * @pre input digits vectors must be non-empty
 * @pre input digits may have no leading zeros
 * @pre every element of input digits vectors must be `<= DIGIT_TYPE_MAX`
 */
/// @{
std::vector<digit_type>
long_multiply(const std::vector<digit_type> &lhs,
              const std::vector<digit_type> &rhs);

std::vector<digit_type>
karatsuba_multiply(const std::vector<digit_type> &lhs,
                   const std::vector<digit_type> &rhs);

/// @}

} // namespace detail
} // namespace tasty_int

#endif // ifndef TASTY_INT_TASTY_INT_DETAIL_DIGITS_MULTIPLICATION_HPP
