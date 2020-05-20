#include "tasty_int/detail/next_power_of_two.hpp"

#include <cassert>

#include <limits>
#include <type_traits>

#include "tasty_int/detail/count_leading_zero_bits.hpp"


namespace tasty_int {
namespace detail {

std::uintmax_t
next_power_of_two(std::uintmax_t value)
{
    constexpr std::uintmax_t MAX_EXPONENT =
        std::numeric_limits<std::uintmax_t>::digits - 1;

    [[maybe_unused]] constexpr std::uintmax_t MAX_POWER_OF_TWO =
        std::uintmax_t(1) << MAX_EXPONENT;

    assert(value > 0);
    assert(value < MAX_POWER_OF_TWO);

    auto exponent = std::numeric_limits<std::uintmax_t>::digits
                  - count_leading_zero_bits(value);

    return std::uintmax_t(1) << exponent;
}

} // namespace detail
} // namespace tasty_int
