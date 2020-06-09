#ifndef TASTY_INT_TASTY_INT_DETAIL_INTEGER_MULTIPLICATION_AND_DIVISION_HPP
#define TASTY_INT_TASTY_INT_DETAIL_INTEGER_MULTIPLICATION_AND_DIVISION_HPP

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
Integer &
operator*=(Integer       &lhs,
           std::intmax_t  rhs);
Integer &
operator*=(Integer     &lhs,
           long double  rhs);

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
Integer
operator*(const Integer &lhs,
          long double    rhs);
Integer
operator*(long double    lhs,
          const Integer &rhs);
/// @}


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
Integer
operator/(const Integer &lhs,
          long double    rhs);
// long double
// operator/(long double    lhs,
//           const Integer &rhs); // TODO


Integer &
operator%=(Integer       &lhs,
           const Integer &rhs);
Integer &
operator%=(Integer        &lhs,
           std::uintmax_t  rhs);
Integer &
operator%=(Integer       &lhs,
           std::intmax_t  rhs);
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
Integer
operator%(const Integer &lhs,
          long double    rhs);
// long double
// operator%(long double    lhs,
//           const Integer &rhs); // TODO


/**
 * TODO
 */
struct IntegerDivisionResult
{
    Integer quotient;
    Integer remainder;
}; // struct IntegerDivisionResult

IntegerDivisionResult
div(const Integer &lhs,
    const Integer &rhs);
IntegerDivisionResult
div(const Integer  &lhs,
    std::uintmax_t  rhs);
IntegerDivisionResult
div(const Integer &lhs,
    std::intmax_t  rhs);
IntegerDivisionResult
div(const Integer &lhs,
    long double  rhs);
/// @}

} // namespace detail
} // namespace tasty_int

#endif // TASTY_INT_TASTY_INT_DETAIL_INTEGER_MULTIPLICATION_AND_DIVISION_HPP
