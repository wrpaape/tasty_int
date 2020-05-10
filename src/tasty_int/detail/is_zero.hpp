#ifndef TASTY_INT_TASTY_INT_DETAIL_IS_ZERO_HPP
#define TASTY_INT_TASTY_INT_DETAIL_IS_ZERO_HPP

#include <vector>

#include "tasty_int/detail/digit_type.hpp"


namespace tasty_int {
namespace detail {

/**
 * @brief Check if @p digits has a value of zero.
 *
 * @param[in] digits a little-endian sequence of digits
 * @return true if @p digits is zero
 */
inline bool
is_zero(const std::vector<digit_type> &digits)
{
    return (digits.size()  == 1)
        && (digits.front() == 0);
}


} // namespace detail
} // namespace tasty_int

#endif // ifndef TASTY_INT_TASTY_INT_DETAIL_IS_ZERO_HPP
