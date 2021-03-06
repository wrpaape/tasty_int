#ifndef TASTY_INT_TASTY_INT_DETAIL_CONVERSIONS_STRING_FROM_INTEGER_HPP
#define TASTY_INT_TASTY_INT_DETAIL_CONVERSIONS_STRING_FROM_INTEGER_HPP

#include <string>

#include "tasty_int/detail/integer.hpp"


namespace tasty_int {
namespace detail {
namespace conversions {

/**
 * Converts @p integer to string representation.
 *
 * @param[in] integer an arbitrary-precision integer
 * @param[in] base    the desired numeric base/radix of the output
 * @return the string representation of @p integer in base @p base
 *
 *  @throw std::invalid_argument if @p base is not a supported numeric
 *      base/radix
 *
 * @pre @p integer has a valid sign and at least one digit
 * @pre @p base is a supported numeric base/radix
 */
std::string
string_from_integer(const Integer &integer,
                    unsigned int   base);

} // namespace conversions
} // namespace detail
} // namespace tasty_int

#endif // ifndef TASTY_INT_TASTY_INT_DETAIL_CONVERSIONS_STRING_FROM_INTEGER_HPP
