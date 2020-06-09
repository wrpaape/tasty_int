#ifndef TASTY_INT_TASTY_INT_DETAIL_INTEGER_OUTPUT_HPP
#define TASTY_INT_TASTY_INT_DETAIL_INTEGER_OUTPUT_HPP

#include "tasty_int/detail/integer.hpp"

#include <iosfwd>


namespace tasty_int {
namespace detail {

/**
 * @brief Integer output operator.
 *
 * @details Output is formatted as follows:
 *
 *     [sign][prefix][digits]
 *
 * where
 *
 *     sign   := - if integer is negative, + if integer is nonnegative and
 *               output has been modified with std::shopos, otherwise the empty
 *               string
 *     prefix := 0x or 0 if output has been modified with std::hex or std::oct
 *               respectively, otherwise the empty string
 *     digits := the string representation of the numerical portion of
 *               integer
 *
 * @param[in,out] output the output stream
 * @param[in]     integer an arbitrary-precision integer
 * @return a reference to @p output
 */
std::ostream &
operator<<(std::ostream  &output,
           const Integer &integer);

} // namespace detail
} // namespace tasty_int

#endif // TASTY_INT_TASTY_INT_DETAIL_INTEGER_OUTPUT_HPP
