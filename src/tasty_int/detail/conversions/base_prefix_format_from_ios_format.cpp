#include "tasty_int/detail/conversions/base_prefix_format_from_ios_format.hpp"


namespace tasty_int {
namespace detail {
namespace conversions {

BasePrefixFormat
base_prefix_format_from_ios_format(std::ios_base::fmtflags format)
{
    BasePrefixFormat base_prefix_format = {
        .base             = 10,
        .nonnegative_sign = (format & std::ios_base::showpos) ? "+" : "",
        .prefix           = ""
    };

    if (format & std::ios_base::hex) {
        if (format & std::ios_base::showbase)
            base_prefix_format.prefix = "0x";

        base_prefix_format.base = 16;

    } else if (format & std::ios_base::oct) {
        if (format & std::ios_base::showbase)
            base_prefix_format.prefix = "0";

        base_prefix_format.base = 8;
    }

    return base_prefix_format;
}

} // namespace conversions
} // namespace detail
} // namespace tasty_int
