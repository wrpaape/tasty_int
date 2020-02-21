#ifndef TASTY_INT_TASTY_INT_DETAIL_CONVERSIONS_SIGN_FROM_SIGNED_ARITHMETIC_HPP
#define TASTY_INT_TASTY_INT_DETAIL_CONVERSIONS_SIGN_FROM_SIGNED_ARITHMETIC_HPP

#include <type_traits>

#include "tasty_int/detail/sign.hpp"


namespace tasty_int {
namespace detail {
namespace conversions {

/**
 * @brief Encodes the integer sign of @p value as a Sign.
 *
 * @param[in] value a signed integer or floating-point value
 * @return Sign::NEGATIVE if @p value truncated to the nearest integer is
 * negative, Sign::ZERO if absolute value of @p value is less than one, and
 * Sign::POSITIVE otherwise
 */
template<typename T>
Sign
sign_from_signed_arithmetic(T value)
    requires std::is_signed_v<T>
{
    constexpr T POSITIVE_ONE(+1);
    constexpr T NEGATIVE_ONE(-1);

    return static_cast<Sign>((value >= POSITIVE_ONE) - (value <= NEGATIVE_ONE));
}

} // namespace conversions
} // namespace detail
} // namespace tasty_int

#endif // ifndef TASTY_INT_TASTY_INT_DETAIL_CONVERSIONS_SIGN_FROM_SIGNED_ARITHMETIC_HPP
