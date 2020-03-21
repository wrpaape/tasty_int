#ifndef TASTY_INT_TASTY_INT_DETAIL_FLIP_SIGN_HPP
#define TASTY_INT_TASTY_INT_DETAIL_FLIP_SIGN_HPP

#include "tasty_int/detail/sign.hpp"


namespace tasty_int {
namespace detail {

inline Sign
flip_sign(Sign sign)
{
    return static_cast<Sign>(-sign);
}

} // namespace detail
} // namespace tasty_int

#endif // ifndef TASTY_INT_TASTY_INT_DETAIL_FLIP_SIGN_HPP
