#include "tasty_int/detail/integer_output.hpp"

#include <ostream>
#include <string_view>

#include "tasty_int/detail/conversions/base_prefix_format_from_ios_format.hpp"
#include "tasty_int/detail/conversions/string_from_integer.hpp"


namespace tasty_int {
namespace detail {

std::ostream &
operator<<(std::ostream  &output,
           const Integer &integer)
{
    auto format =
        conversions::base_prefix_format_from_ios_format(output.flags());

    auto stringified = conversions::string_from_integer(integer, format.base);
    std::string_view digits = stringified;

    if (integer.sign >= Sign::ZERO) {
        output << format.nonnegative_sign;
    } else {
        output << '-';
        digits.remove_prefix(1);
    }

    return output << format.prefix << digits;
}

} // namespace detail
} // namespace tasty_int
