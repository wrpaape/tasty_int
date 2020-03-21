#ifndef TASTY_INT_TASTY_INT_DETAIL_INTEGER_HPP
#define TASTY_INT_TASTY_INT_DETAIL_INTEGER_HPP

#include <cstdint>

#include <vector>

#include "tasty_int/detail/sign.hpp"
#include "tasty_int/detail/digit_type.hpp"


namespace tasty_int {
namespace detail {

/**
 * This struct serves as the internal representation of tasty_int::TastyInt.
 * Integer fields correspond to arbitrary-precision integers values
 * accordingly:
 *
 *     Negative Values:
 *         | Integer::sign  | Integer::digits                                |
 *         | -------------- | -----------------------------------------------|
 *         | Sign::NEGATIVE | { least significant [, ... most significant] } |
 *
 *     Zero:
 *         | Integer::sign  | Integer::digits                                |
 *         | -------------- | -----------------------------------------------|
 *         | Sign::ZERO     | { 0 }                                          |
 *
 *     Positive Values:
 *         | Integer::sign  | Integer::digits                                |
 *         | -------------- | -----------------------------------------------|
 *         | Sign::POSITIVE | { least significant [, ... most significant] } |
 */
struct Integer
{
    /**
     * The integer sign of Integer.
     */
    Sign                    sign;

    /**
     * The little-endian positional notation representation of Integer's
     * absolute value.
     */
    std::vector<digit_type> digits;
}; // struct Integer

/**
 * @defgroup IntegerComparisonOperators Integer Comparison Operators
 *
 * These operators compare tasty_int::detail::Integer like ordinary ints:
 *     
 *     - positive integers are greater than zero
 *     - positive integers compare greater as their magnitude increases
 *     - negative integers are less than zero
 *     - negative integers compare lesser as their magnitude increases
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

#endif // TASTY_INT_TASTY_INT_DETAIL_INTEGER_HPP
