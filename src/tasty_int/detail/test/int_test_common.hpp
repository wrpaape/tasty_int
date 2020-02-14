#ifndef TASTY_INT_TASTY_INT_DETAIL_TEST_INT_TEST_COMMON_HPP
#define TASTY_INT_TASTY_INT_DETAIL_TEST_INT_TEST_COMMON_HPP

#include <iosfwd>


namespace tasty_int {
namespace detail {

struct Int;

/**
 * @brief Outputs tasty_int::detail::Int for diagnostic purposes.
 *
 * @details This routine is leveraged by gtest to pretty-print an argument on
 *     an assertion failure and must be defined in the same namespace as Int
 *     for visibility.  `operator<<` may also be defined for this purpose,
 *     however, the symbol `PrintTo` was chosen here in order to leave the more
 *     intuitive `operator<<` reserved for production code.
 *
 * @param[in]  integer the integer to be output
 * @param[out] output  a pointer to the output stream
 */
void
PrintTo(const Int    &integer,
        std::ostream *output);

} // namespace detail
} // namespace tasty_int

#endif // ifndef TASTY_INT_TASTY_INT_DETAIL_TEST_INT_TEST_COMMON_HPP
