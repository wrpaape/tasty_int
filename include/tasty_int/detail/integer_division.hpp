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
std::uintmax_t &
operator/=(std::uintmax_t &lhs,
           const Integer  &rhs);

Integer &
operator/=(Integer       &lhs,
           std::intmax_t  rhs);
std::intmax_t &
operator/=(std::intmax_t &lhs,
           const Integer &rhs);

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
/// @ingroup IntegerDivisionFloatingPointOverloads
long double &
operator/=(long double   &lhs,
           const Integer &rhs);


Integer
operator/(const Integer &lhs,
          const Integer &rhs);

Integer
operator/(const Integer  &lhs,
          std::uintmax_t  rhs);
std::uintmax_t
operator/(std::uintmax_t  lhs,
          const Integer  &rhs);

Integer
operator/(const Integer &lhs,
          std::intmax_t  rhs);
std::intmax_t
operator/(std::intmax_t  lhs,
          const Integer &rhs);

/// @ingroup IntegerDivisionFloatingPointOverloads
Integer
operator/(const Integer &lhs,
          long double    rhs);
/// @ingroup IntegerDivisionFloatingPointOverloads
long double
operator/(long double    lhs,
          const Integer &rhs);
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
std::uintmax_t &
operator%=(std::uintmax_t &lhs,
           const Integer  &rhs);

Integer &
operator%=(Integer       &lhs,
           std::intmax_t  rhs);
std::intmax_t &
operator%=(std::intmax_t &lhs,
           const Integer &rhs);

/// @ingroup IntegerDivisionFloatingPointOverloads
Integer &
operator%=(Integer     &lhs,
           long double  rhs);
/// @ingroup IntegerDivisionFloatingPointOverloads
long double &
operator%=(long double   &lhs,
           const Integer &rhs);


Integer
operator%(const Integer &lhs,
          const Integer &rhs);

Integer
operator%(const Integer  &lhs,
          std::uintmax_t  rhs);
std::uintmax_t
operator%(std::uintmax_t  lhs,
          const Integer  &rhs);

Integer
operator%(const Integer &lhs,
          std::intmax_t  rhs);
std::intmax_t
operator%(std::intmax_t lhs,
          const Integer &rhs);

/// @ingroup IntegerDivisionFloatingPointOverloads
Integer
operator%(const Integer &lhs,
          long double    rhs);
long double
operator%(long double    lhs,
          const Integer &rhs);
/// @}


/**
 * The result of an immutable division operation involving a
 * tasty_int::detail::Integer.
 */
template<typename DividendType>
struct IntegerDivisionResult
{
    DividendType quotient;  ///< the division quotient
    DividendType remainder; ///< the division remainder
}; // struct IntegerDivisionResult


/**
 * @defgroup IntegerDivOperations Integer div Operations
 *
 * These functions return the quotient and remainder from division.
 */
/// @{
IntegerDivisionResult<Integer>
div(const Integer &dividend,
    const Integer &divisor);

IntegerDivisionResult<Integer>
div(const Integer  &dividend,
    std::uintmax_t  divisor);
IntegerDivisionResult<std::uintmax_t>
div(std::uintmax_t  divisor,
    const Integer  &dividend);

IntegerDivisionResult<Integer>
div(const Integer &dividend,
    std::intmax_t  divisor);
IntegerDivisionResult<std::intmax_t>
div(std::intmax_t  dividend,
    const Integer &divisor);

/// @ingroup IntegerDivisionFloatingPointOverloads
IntegerDivisionResult<Integer>
div(const Integer &dividend,
    long double    divisor);
/// @ingroup IntegerDivisionFloatingPointOverloads
IntegerDivisionResult<long double>
div(long double    dividend,
    const Integer &divisor);
/// @}

} // namespace detail
} // namespace tasty_int

#endif // TASTY_INT_TASTY_INT_DETAIL_INTEGER_DIVISION_HPP
