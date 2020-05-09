#ifndef TASTY_INT_DETAIL_ORDER_BY_SIZE_HPP
#define TASTY_INT_DETAIL_ORDER_BY_SIZE_HPP

#include <algorithm>
#include <vector>

#include "tasty_int/detail/digit_type.hpp"


namespace tasty_int {
namespace detail {

/**
 * @brief Order @p digits1 and @p digits2 according to `size()`.
 *
 * @param[in] digits1 a little-endian sequence of digits
 * @param[in] digits2 a little-endian sequence of digits
 * @return references to arguments ordered by size
 */
inline std::pair<const std::vector<digit_type> &,
                 const std::vector<digit_type> &>
order_by_size(const std::vector<digit_type> &digits1,
              const std::vector<digit_type> &digits2)
{
    return std::minmax(
        digits1, digits2,
        [](const auto &lhs,
           const auto &rhs)
        {
            return lhs.size() < rhs.size();
        }
    );
}

} // namespace detail
} // namespace tasty_int

#endif // ifndef TASTY_INT_DETAIL_ORDER_BY_SIZE_HPP
