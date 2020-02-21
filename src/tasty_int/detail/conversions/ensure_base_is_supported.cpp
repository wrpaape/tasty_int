#include "tasty_int/detail/conversions/ensure_base_is_supported.hpp"

#include <stdexcept>
#include <string>


namespace tasty_int {
namespace detail {
namespace conversions {

void
ensure_base_is_supported(unsigned int base)
{
    if ((base < 2) || (base > 64))
        throw std::invalid_argument(
            "tasty_int::detail::conversions::ensure_base_is_supported - invalid"
            " base (" + std::to_string(base) + "): Base is not within the range"
            " of supported values [2,64]."
        );
}

} // namespace conversions
} // namespace detail
} // namespace tasty_int
