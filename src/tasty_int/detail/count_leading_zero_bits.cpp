#include "tasty_int/detail/count_leading_zero_bits.hpp"

#include <cassert>

#include <limits>
#include <type_traits>

#ifdef INTRINSIC_COUNT_LEADING_ZERO_BITS_HEADER
#   include INTRINSIC_COUNT_LEADING_ZERO_BITS_HEADER
#endif // ifdef INTRINSIC_COUNT_LEADING_ZERO_BITS_HEADER


namespace tasty_int {
namespace detail {

std::uintmax_t
count_leading_zero_bits(std::uintmax_t value)
{
    assert(value != 0);

#if HAVE_INTRINSIC_COUNT_LEADING_ZERO_BITS
    return INTRINSIC_COUNT_LEADING_ZERO_BITS(value);
#else
    constexpr std::uintmax_t MAX_EXPONENT =
        std::numeric_limits<std::uintmax_t>::digits - 1;

    auto index_of_most_significant_bit = MAX_EXPONENT;
    while (true) {
        auto next_bit = std::uintmax_t(1) << index_of_most_significant_bit;
        if ((next_bit & value) != 0)
            return MAX_EXPONENT - index_of_most_significant_bit;

        --index_of_most_significant_bit;
    }
#endif // HAVE_INTRINSIC_COUNT_LEADING_ZERO_BITS
}

} // namespace detail
} // namespace tasty_int
