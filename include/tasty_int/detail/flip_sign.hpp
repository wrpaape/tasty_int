#ifndef TASTY_INT_TASTY_INT_DETAIL_FLIP_SIGN_HPP
#define TASTY_INT_TASTY_INT_DETAIL_FLIP_SIGN_HPP

#include "tasty_int/detail/sign.hpp"


namespace tasty_int {
namespace detail {

/**
 * @brief Flips the input sign.
 *
 * @param[in] sign the input sign
 * @returns Sign::NEGATIVE if @p sign is Sign::POSITIVE, Sign::POSITIVE if @p
 *     sign is Sign::NEGATIVE, and Sign::ZERO if @p sign is Sign::ZERO
 */
inline Sign
flip_sign(Sign sign)
{
    return static_cast<Sign>(-sign);
}

} // namespace detail
} // namespace tasty_int

#endif // ifndef TASTY_INT_TASTY_INT_DETAIL_FLIP_SIGN_HPP
