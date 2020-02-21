#ifndef TASTY_INT_TASTY_INT_DETAIL_INTEGER_HPP
#define TASTY_INT_TASTY_INT_DETAIL_INTEGER_HPP

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
 * @todo Replace with default comparison semantics once compiler support is
 * available.
 */
inline bool
operator==(const Integer &lhs,
           const Integer &rhs)
{
    return (lhs.sign   == rhs.sign)
        && (lhs.digits == rhs.digits);
}

} // namespace detail
} // namespace tasty_int

#endif // TASTY_INT_TASTY_INT_DETAIL_INTEGER_HPP
