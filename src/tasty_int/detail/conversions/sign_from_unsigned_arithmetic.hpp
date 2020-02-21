#ifndef TASTY_INT_TASTY_INT_DETAIL_CONVERSIONS_SIGN_FROM_UNSIGNED_ARITHMETIC_HPP
#define TASTY_INT_TASTY_INT_DETAIL_CONVERSIONS_SIGN_FROM_UNSIGNED_ARITHMETIC_HPP

#include <type_traits>

#include "tasty_int/detail/sign.hpp"


namespace tasty_int {
namespace detail {
namespace conversions {

/**
 * @brief Encodes the integer sign of @p value as a Sign.
 *
 * @param[in] value an unsigned (integer) value
 * @return Sign::ZERO if @p value is < 1, Sign::POSITIVE otherwise
 */
template<typename T>
Sign
sign_from_unsigned_arithmetic(T value)
    requires std::is_unsigned_v<T>
{
    constexpr T ONE(1);
    return static_cast<Sign>(value >= ONE);
}

} // namespace conversions
} // namespace detail
} // namespace tasty_int

#endif // ifndef TASTY_INT_TASTY_INT_DETAIL_CONVERSIONS_SIGN_FROM_UNSIGNED_ARITHMETIC_HPP
