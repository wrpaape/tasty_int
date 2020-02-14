#ifndef TASTY_INT_TASTY_INT_DETAIL_INT_HPP
#define TASTY_INT_TASTY_INT_DETAIL_INT_HPP

#include <vector>

#include "tasty_int/detail/sign.hpp"
#include "tasty_int/detail/digit_type.hpp"


namespace tasty_int {
namespace detail {

/**
 * This struct serves as the low-level representation of tasty_int::TastyInt.
 * Int fields correspond to arbitrary-precision integers values accordingly:
 *
 *     Negative Values:
 *         | Int::sign      | Int::digits                |
 *         | -------------- | ---------------------------|
 *         | Sign::NEGATIVE | { lowest [, ... highest] } |
 *
 *     Zero:
 *         | Int::sign      | Int::digits                |
 *         | -------------- | ---------------------------|
 *         | Sign::ZERO     | { 0 }                      |
 *
 *     Positive Values:
 *         | Int::sign      | Int::digits                |
 *         | -------------- | ---------------------------|
 *         | Sign::POSITIVE | { lowest [, ... highest] } |
 */
struct Int
{
    /**
     * The integer sign of Int.
     */
    Sign                    sign;

    /**
     * The little-endian positional notation representation of Int's absolute
     * value.
     */
    std::vector<digit_type> digits;

}; // struct Int

/// @todo Replace with default comparison semantics once compiler support is available.
inline bool
operator==(const Int &lhs,
           const Int &rhs)
{
    return (lhs.sign   == rhs.sign)
        && (lhs.digits == rhs.digits);
}

} // namespace detail
} // namespace tasty_int

#endif // TASTY_INT_TASTY_INT_DETAIL_INT_HPP
