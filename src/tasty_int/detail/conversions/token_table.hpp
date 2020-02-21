#ifndef TASTY_INT_TASTY_INT_DETAIL_CONVERSIONS_TOKEN_TABLE_HPP
#define TASTY_INT_TASTY_INT_DETAIL_CONVERSIONS_TOKEN_TABLE_HPP

#include <array>
#include <limits>


namespace tasty_int {
namespace detail {
namespace conversions {

using TokenTable = std::array<
    unsigned char,
    std::numeric_limits<unsigned char>::max() + 1
>;

} // namespace detail
} // namespace conversions
} // namespace tasty_int

#endif // ifndef TASTY_INT_TASTY_INT_DETAIL_CONVERSIONS_TOKEN_TABLE_HPP
