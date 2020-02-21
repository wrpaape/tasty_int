#ifndef TASTY_INT_TASTY_INT_DETAIL_INTEGER_FROM_SIGNED_INTEGRAL_HPP
#define TASTY_INT_TASTY_INT_DETAIL_INTEGER_FROM_SIGNED_INTEGRAL_HPP

#include <cstdint>

#include "tasty_int/detail/integer.hpp"


namespace tasty_int {
namespace detail {

/**
 * @brief constructs a new tasty_int::detail::Integer from @p value
 *
 * @param[in] value a signed integer value
 * @return the tasty_int::detail:Integer representation of @p value
 */
Integer
integer_from_signed_integral(std::intmax_t value);

} // namespace detail
} // namespace tasty_int

#endif // ifndef TASTY_INT_TASTY_INT_DETAIL_INTEGER_FROM_SIGNED_INTEGRAL_HPP
