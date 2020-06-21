#ifndef TASTY_INT_TASTY_INT_DETAIL_INTEGER_INPUT_HPP
#define TASTY_INT_TASTY_INT_DETAIL_INTEGER_INPUT_HPP

#include "tasty_int/detail/integer.hpp"

#include <iosfwd>


namespace tasty_int {
namespace detail {

/**
 * @brief Integer input operator.
 *
 * @details Input is a string of ASCII tokens interpretted in the base
 *     according to the input basefield flag:
 *
 *     | input basefield flag | interpretted base         |
 *     | -------------------- | --------------------------|
 *     | <none>               | depends on numeric prefix |
 *     | std::dec             | 10                        |
 *     | std::hex             | 16                        |
 *     | std::oct             | 8                         |
 *
 * @details @p input's failbit will be set if a parse error is encountered.
 *
 * @note For standard streams, the basefield flag is set to `dec` on
 *     initialization.
 *
 * @param[in,out] intput  the input stream
 * @param[out]    integer an arbitrary-precision integer
 * @return a reference to @p input
 */
std::istream &
operator>>(std::istream &input,
           Integer      &integer);

} // namespace detail
} // namespace tasty_int

#endif // TASTY_INT_TASTY_INT_DETAIL_INTEGER_INPUT_HPP
