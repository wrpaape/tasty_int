#ifndef TASTY_INT_TASTY_INT_DETAIL_DIGITS_FROM_INTEGRAL_HPP
#define TASTY_INT_TASTY_INT_DETAIL_DIGITS_FROM_INTEGRAL_HPP

#include "tasty_int/detail/digit_type.hpp"

#include <cstdint>

#include <vector>


namespace tasty_int {
namespace detail {

/**
 * TODO
 */
std::vector<digit_type>
digits_from_integral(std::uintmax_t value);

} // namespace detail
} // namespace tasty_int

#endif // ifndef TASTY_INT_TASTY_INT_DETAIL_DIGITS_FROM_INTEGRAL_HPP
