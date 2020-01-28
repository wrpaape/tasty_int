#ifndef TASTY_INT_TASTY_INT_DETAIL_INT_FROM_UNSIGNED_INTEGRAL_HPP
#define TASTY_INT_TASTY_INT_DETAIL_INT_FROM_UNSIGNED_INTEGRAL_HPP

#include <cstdint>

#include "tasty_int/detail/int.hpp"


namespace tasty_int {
namespace detail {

Int
int_from_unsigned_integral(std::uintmax_t value);

} // namespace detail
} // namespace tasty_int

#endif // ifndef TASTY_INT_TASTY_INT_DETAIL_INT_FROM_UNSIGNED_INTEGRAL_HPP
