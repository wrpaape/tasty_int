#include "tasty_int/detail/next_power_of_two.hpp"

#include <cassert>

#include <limits>
#include <type_traits>

#ifdef INTRINSIC_COUNT_LEADING_ZEROS_HEADER
#   include INTRINSIC_COUNT_LEADING_ZEROS_HEADER
#endif // ifdef INTRINSIC_COUNT_LEADING_ZEROS_HEADER


namespace tasty_int {
namespace detail {
namespace {

constexpr std::uintmax_t MAX_EXPONENT =
    std::numeric_limits<std::uintmax_t>::digits - 1;

std::uintmax_t
count_leading_zeros(std::uintmax_t value)
{
#if HAVE_INTRINSIC_COUNT_LEADING_ZEROS
    return INTRINSIC_COUNT_LEADING_ZEROS(value);
#else
    auto index_of_most_significant_bit = MAX_EXPONENT;
    while (true) {
        auto next_bit = std::uintmax_t(1) << index_of_most_significant_bit;
        if ((next_bit & value) != 0)
            return MAX_EXPONENT - index_of_most_significant_bit;

        --index_of_most_significant_bit;
    }
#endif // HAVE_INTRINSIC_COUNT_LEADING_ZEROS
}

} // namespace


std::uintmax_t
next_power_of_two(std::uintmax_t value)
{
    [[maybe_unused]] constexpr std::uintmax_t MAX_POWER_OF_TWO =
        std::uintmax_t(1) << MAX_EXPONENT;

    assert(value > 0);
    assert(value < MAX_POWER_OF_TWO);

    auto exponent = std::numeric_limits<std::uintmax_t>::digits
                  - count_leading_zeros(value);

    return std::uintmax_t(1) << exponent;
}

} // namespace detail
} // namespace tasty_int
