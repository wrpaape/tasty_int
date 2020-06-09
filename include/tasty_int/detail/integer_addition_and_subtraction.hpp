#ifndef TASTY_INT_TASTY_INT_DETAIL_INTEGER_ADDITION_AND_SUBTRACTION_HPP
#define TASTY_INT_TASTY_INT_DETAIL_INTEGER_ADDITION_AND_SUBTRACTION_HPP

#include "tasty_int/detail/integer.hpp"

#include <cstdint>


namespace tasty_int {
namespace detail {

/**
 * @defgroup IntegerAdditionOperators Integer Addition Operators
 *
 * These operators apply addition to tasty_int::detail::Integer and the
 * supported arithmetic types.  Note that floating point values are effectively
 * truncated toward zero before addition.
 */
/// @{
Integer &
operator+=(Integer       &lhs,
           const Integer &rhs);
Integer &
operator+=(Integer        &lhs,
           std::uintmax_t  rhs);
Integer &
operator+=(Integer       &lhs,
           std::intmax_t  rhs);
Integer &
operator+=(Integer     &lhs,
           long double  rhs);

Integer
operator+(const Integer &lhs,
          const Integer &rhs);
Integer
operator+(const Integer  &lhs,
          std::uintmax_t  rhs);
Integer
operator+(std::uintmax_t  lhs,
          const Integer  &rhs);
Integer
operator+(const Integer &lhs,
          std::intmax_t  rhs);
Integer
operator+(std::intmax_t  lhs,
          const Integer &rhs);
Integer
operator+(const Integer &lhs,
          long double    rhs);
Integer
operator+(long double    lhs,
          const Integer &rhs);
/// @}


/**
 * @defgroup IntegerSubtractionOperators Integer Subtraction Operators
 *
 * These operators apply subtraction to tasty_int::detail::Integer and the
 * supported arithmetic types.  Note that floating point values are effectively
 * truncated toward zero before subtraction.
 */
/// @{
Integer &
operator-=(Integer       &lhs,
           const Integer &rhs);
Integer &
operator-=(Integer        &lhs,
           std::uintmax_t  rhs);
Integer &
operator-=(Integer       &lhs,
           std::intmax_t  rhs);
Integer &
operator-=(Integer     &lhs,
           long double  rhs);

Integer
operator-(const Integer &lhs,
          const Integer &rhs);
Integer
operator-(const Integer  &lhs,
          std::uintmax_t  rhs);
Integer
operator-(std::uintmax_t  lhs,
          const Integer  &rhs);
Integer
operator-(const Integer &lhs,
          std::intmax_t  rhs);
Integer
operator-(std::intmax_t  lhs,
          const Integer &rhs);
Integer
operator-(const Integer &lhs,
          long double    rhs);
Integer
operator-(long double    lhs,
          const Integer &rhs);
/// @}

} // namespace detail
} // namespace tasty_int

#endif // TASTY_INT_TASTY_INT_DETAIL_INTEGER_ADDITION_AND_SUBTRACTION_HPP
