#ifndef TASTY_INT_TASTY_INT_DETAIL_INTEGER_DIVISION_HPP
#define TASTY_INT_TASTY_INT_DETAIL_INTEGER_DIVISION_HPP

#include "tasty_int/detail/integer.hpp"

#include <cstdint>


namespace tasty_int {
namespace detail {

/**
 * @defgroup IntegerDivisionOperators Integer Division Operators
 *
 * These operators apply division to tasty_int::detail::Integer and the
 * supported arithmetic types.
 */
/// @{
Integer &
operator/=(Integer       &lhs,
           const Integer &rhs);

Integer &
operator/=(Integer        &lhs,
           std::uintmax_t  rhs);

Integer &
operator/=(Integer       &lhs,
           std::intmax_t  rhs);

/**
 * @defgroup IntegerDivisionFloatingPointOverloads Integer Division Floating Point Overloads
 *
 * These operations truncate their operand toward zero to the nearest integer
 * before dividing.
 *
 * @pre `std::isfinite(divisor) && (divisor >= 1.0)`
 */
/// @ingroup IntegerDivisionFloatingPointOverloads
Integer &
operator/=(Integer     &lhs,
           long double  rhs);


Integer
operator/(const Integer &lhs,
          const Integer &rhs);

Integer
operator/(const Integer  &lhs,
          std::uintmax_t  rhs);

// std::uintmax_t
// operator/(std::uintmax_t  lhs,
//           const Integer  &rhs); // TODO

Integer
operator/(const Integer &lhs,
          std::intmax_t  rhs);

// std::intmax_t
// operator/(std::intmax_t  lhs,
//           const Integer &rhs); // TODO

/// @ingroup IntegerDivisionFloatingPointOverloads
Integer
operator/(const Integer &lhs,
          long double    rhs);

// long double
// operator/(long double    lhs,
//           const Integer &rhs); // TODO
/// @}


/**
 * @defgroup IntegerModuloOperators Integer Modulo Operators
 *
 * These operators apply modulo to tasty_int::detail::Integer and the
 * supported arithmetic types.
 *
 * @details These operators reflect the behavior of the standard builtin `%=`
 *     and `%` operators (from
 *     https://en.cppreference.com/w/cpp/language/operator_arithmetic):
 *
 *         The binary operator % yields the remainder of the integer division
 *         of the first operand by the second . If the quotient `a/b` is
 *         representable in the result type, `(a/b)*b + a%b == a`. If the
 *         second operand is zero, the behavior is undefined.
 */
/// @{
Integer &
operator%=(Integer       &lhs,
           const Integer &rhs);

Integer &
operator%=(Integer        &lhs,
           std::uintmax_t  rhs);

Integer &
operator%=(Integer       &lhs,
           std::intmax_t  rhs);

/// @ingroup IntegerDivisionFloatingPointOverloads
Integer &
operator%=(Integer     &lhs,
           long double  rhs);


Integer
operator%(const Integer &lhs,
          const Integer &rhs);

Integer
operator%(const Integer  &lhs,
          std::uintmax_t  rhs);

// std::uintmax_t
// operator%(std::uintmax_t  lhs,
//           const Integer  &rhs); // TODO

Integer
operator%(const Integer &lhs,
          std::intmax_t  rhs);

// std::intmax_t
// operator%(std::intmax_t  lhs,
//           const Integer &rhs); // TODO

/// @ingroup IntegerDivisionFloatingPointOverloads
Integer
operator%(const Integer &lhs,
          long double    rhs);

// long double
// operator%(long double    lhs,
//           const Integer &rhs); // TODO
/// @}


/**
 * The result of an immutable division operation involving a
 * tasty_int::detail::Integer.
 */
struct IntegerDivisionResult
{
    Integer quotient;  ///< the division quotient
    Integer remainder; ///< the division remainder
}; // struct IntegerDivisionResult


/**
 * @defgroup IntegerDivOperations Integer div Operations
 *
 * These functions return the quotient and remainder from division.
 */
/// @{
IntegerDivisionResult
div(const Integer &lhs,
    const Integer &rhs);

IntegerDivisionResult
div(const Integer  &lhs,
    std::uintmax_t  rhs);

IntegerDivisionResult
div(const Integer &lhs,
    std::intmax_t  rhs);

/// @ingroup IntegerDivisionFloatingPointOverloads
IntegerDivisionResult
div(const Integer &lhs,
    long double  rhs);
/// @}

} // namespace detail
} // namespace tasty_int

#endif // TASTY_INT_TASTY_INT_DETAIL_INTEGER_DIVISION_HPP
