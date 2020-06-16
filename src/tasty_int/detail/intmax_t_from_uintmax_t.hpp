#ifndef TASTY_INT_TASTY_INT_DETAIL_INTMAX_T_FROM_UINTMAX_T_HPP
#define TASTY_INT_TASTY_INT_DETAIL_INTMAX_T_FROM_UINTMAX_T_HPP

#include <cstdint>

#include <limits>


namespace tasty_int {
namespace detail {

/**
 * @brief Safely casts a std::uintmax_t @p value to its signed counterpart.
 *
 * @param[in] value the unsigned integral value
 * @return the signed representation of @p value
 *
 * @details This routine will collapse to a nop for x86 and ARM architectures
 *     on g++, clang, and msvc with optimization but is necessary to avoid
 *     signed overflow (undefined behavior).
 */
inline std::intmax_t
intmax_t_from_uintmax_t(std::uintmax_t value)
{
    constexpr auto UNSIGNED_INTMAX_MIN = static_cast<std::uintmax_t>(
        std::numeric_limits<std::intmax_t>::lowest()
    );

    // `value` may safely be represented as a negative std::intmax_t.
    if (value >= UNSIGNED_INTMAX_MIN) {
        // Overflow detected: roll back so that `value` may be safely cast to
        // std::intmax_t and then safely roll forward.
        value -= UNSIGNED_INTMAX_MIN;
         return static_cast<std::intmax_t>(value)
              + std::numeric_limits<std::intmax_t>::lowest();
    }

    // `value` may safely be represented as a positive std::intmax_t.
    return static_cast<std::intmax_t>(value);
}

} // namespace detail
} // namespace tasty_int

#endif // ifndef TASTY_INT_TASTY_INT_DETAIL_INTMAX_T_FROM_UINTMAX_T_HPP
