#include "tasty_int/detail/conversions/signed_integral_from_integer.hpp"

#include <cassert>

#include <limits>

#include "tasty_int/detail/conversions/unsigned_integral_from_integer.hpp"


namespace tasty_int {
namespace detail {
namespace conversions {
namespace {

/**
 * This routine will collapse to a noop for x86 and ARM architectures on g++,
 * clang, and msvc with optimization but is necessary to avoid signed overflow
 * (undefined behavior).
 */
std::intmax_t
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

} // namespace


std::intmax_t
signed_integral_from_integer(const Integer &integer)
{
    assert((integer.sign == Sign::NEGATIVE) ||
           (integer.sign == Sign::ZERO)     ||
           (integer.sign == Sign::POSITIVE));
    assert(!integer.digits.empty());

    std::uintmax_t unsigned_value = unsigned_integral_from_integer(integer);

    std::intmax_t value = intmax_t_from_uintmax_t(unsigned_value);

    return value;
}

} // namespace conversions
} // namespace detail
} // namespace tasty_int
