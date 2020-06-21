#include "tasty_int/detail/integer_input.hpp"

#include <istream>
#include <stdexcept>
#include <string>

#include "tasty_int/detail/conversions/integer_from_string.hpp"


namespace tasty_int {
namespace detail {
namespace {

unsigned int
base_from_ios_format(std::ios_base::fmtflags format)
{
    unsigned int base = 0;

    if (format & std::ios_base::hex)
        base = 16;
    else if (format & std::ios_base::dec)
        base = 10;
    else if (format & std::ios_base::oct)
        base = 8;

    return base;
}

} // namespace


std::istream &
operator>>(std::istream &input,
           Integer      &integer)
{
    if (std::string tokens; input >> tokens) {
        auto base = base_from_ios_format(input.flags());

        try {
            integer = conversions::integer_from_string(tokens, base);
        } catch (std::invalid_argument &) {
            input.clear(input.rdstate() | std::ios_base::failbit);
        }
    }

    return input;
}

} // namespace detail
} // namespace tasty_int
