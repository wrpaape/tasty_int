#ifndef TASTY_INT_TASTY_INT_DETAIL_SIGN_HPP
#define TASTY_INT_TASTY_INT_DETAIL_SIGN_HPP

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

} // namespace detail
} // namespace tasty_int

#endif // ifndef TASTY_INT_TASTY_INT_DETAIL_SIGN_HPP
