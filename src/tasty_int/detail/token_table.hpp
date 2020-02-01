#ifndef TASTY_INT_TASTY_INT_DETAIL_TOKEN_TABLE_HPP
#define TASTY_INT_TASTY_INT_DETAIL_TOKEN_TABLE_HPP

#include <array>
#include <limits>


namespace tasty_int {
namespace detail {

using TokenTable = std::array<
    unsigned char,
    std::numeric_limits<unsigned char>::max() + 1
>;

} // detail
} // tasty_int

#endif // ifndef TASTY_INT_TASTY_INT_DETAIL_TOKEN_TABLE_HPP
