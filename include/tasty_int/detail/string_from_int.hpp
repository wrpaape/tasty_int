#ifndef TASTY_INT_TASTY_INT_DETAIL_STRING_FROM_INT_HPP
#define TASTY_INT_TASTY_INT_DETAIL_STRING_FROM_INT_HPP

#include <string>

#include "tasty_int/detail/int.hpp"


namespace tasty_int {
namespace detail {

/**
 * Converts @p integer to string representation.
 *
 * @param[in] integer an arbitrary-precision integer
 * @param[in] base    the desired numeric base/radix of the output
 * @return the string representation of @p integer in base @p base
 */
std::string
string_from_int(const Int    &integer,
                unsigned int  base);

} // namespace detail
} // namespace tasty_int

#endif // ifndef TASTY_INT_TASTY_INT_DETAIL_STRING_FROM_INT_HPP
