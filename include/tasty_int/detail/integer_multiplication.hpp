#ifndef TASTY_INT_TASTY_INT_DETAIL_INTEGER_MULTIPLICATION_HPP
#define TASTY_INT_TASTY_INT_DETAIL_INTEGER_MULTIPLICATION_HPP

#include "tasty_int/detail/integer.hpp"

#include <cstdint>


namespace tasty_int {
namespace detail {

/**
 * @defgroup IntegerMultiplicationOperators Integer Multiplication Operators
 *
 * These operators apply multiplication to tasty_int::detail::Integer and the
 * supported arithmetic types.
 */
/// @{
Integer &
operator*=(Integer       &lhs,
           const Integer &rhs);

Integer &
operator*=(Integer        &lhs,
           std::uintmax_t  rhs);

std::uintmax_t &
operator*=(std::uintmax_t &lhs,
           const Integer  &rhs);

Integer &
operator*=(Integer       &lhs,
           std::intmax_t  rhs);

std::intmax_t &
operator*=(std::intmax_t &lhs,
           const Integer &rhs);

/**
 * @defgroup IntegerMultiplicationFloatingPointOverloads Integer Multiplication Floating Point Overloads
 *
 * These operations truncate their operand toward zero to the nearest integer
 * before multiplying.
 *
 * @pre `std::isfinite(divisor)`
 */
/// @ingroup IntegerMultiplicationFloatingPointOverloads
Integer &
operator*=(Integer     &lhs,
           long double  rhs);

/// @ingroup IntegerMultiplicationFloatingPointOverloads
long double &
operator*=(long double   &lhs,
           const Integer &rhs);


Integer
operator*(const Integer &lhs,
          const Integer &rhs);

Integer
operator*(const Integer  &lhs,
          std::uintmax_t  rhs);

Integer
operator*(std::uintmax_t  lhs,
          const Integer  &rhs);

Integer
operator*(const Integer &lhs,
          std::intmax_t  rhs);

Integer
operator*(std::intmax_t  lhs,
          const Integer &rhs);

/// @ingroup IntegerMultiplicationFloatingPointOverloads
Integer
operator*(const Integer &lhs,
          long double    rhs);

/// @ingroup IntegerMultiplicationFloatingPointOverloads
Integer
operator*(long double    lhs,
          const Integer &rhs);
/// @}

} // namespace detail
} // namespace tasty_int

#endif // TASTY_INT_TASTY_INT_DETAIL_INTEGER_MULTIPLICATION_HPP
