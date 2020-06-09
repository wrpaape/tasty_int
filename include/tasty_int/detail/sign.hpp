#ifndef TASTY_INT_TASTY_INT_DETAIL_SIGN_HPP
#define TASTY_INT_TASTY_INT_DETAIL_SIGN_HPP

#include <type_traits>


namespace tasty_int {
namespace detail {

/**
 * This enum enumerates the possible states of an integer sign.
 */
enum Sign
{
    NEGATIVE = -1,
    ZERO     =  0,
    POSITIVE = +1
}; // enum class Sign


/**
 * @brief Flips the input sign.
 *
 * @param[in] sign the input sign
 * @return Sign::NEGATIVE if @p sign is Sign::POSITIVE, Sign::POSITIVE if @p
 *     sign is Sign::NEGATIVE, and Sign::ZERO if @p sign is Sign::ZERO
 */
inline Sign
operator-(Sign sign)
{
    return static_cast<Sign>(
        -static_cast<std::underlying_type_t<Sign>>(sign)
    );
}

/**
 * @defgroup Sign Multiplication Operations
 *
 * @brief Combines the inputs signs.
 *
 * @return Sign::ZERO if either @p lhs or @p rhs is Sign::ZERO, and if neither
 *     operand is Sign::ZERO, Sign::POSITIVE if `lhs == rhs` and Sign::NEGATIVE
 *     if `lhs != rhs`.
 */
/// @{
inline Sign
operator*(Sign lhs,
          Sign rhs)
{
    return static_cast<Sign>(
        static_cast<std::underlying_type_t<Sign>>(lhs) *
        static_cast<std::underlying_type_t<Sign>>(rhs)
    );
}

inline Sign &
operator*=(Sign &lhs,
           Sign  rhs)
{
    lhs = lhs * rhs;

    return lhs;
}
/// @}

} // namespace detail
} // namespace tasty_int

#endif // ifndef TASTY_INT_TASTY_INT_DETAIL_SIGN_HPP
