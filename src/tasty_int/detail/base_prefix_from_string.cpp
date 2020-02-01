#include "tasty_int/detail/base_prefix_from_string.hpp"


namespace tasty_int {
namespace detail {
namespace {

const BasePrefix BINARY      = { .prefix_length = 2, .base =  2 };
const BasePrefix OCTAL       = { .prefix_length = 1, .base =  8 };
const BasePrefix DECIMAL     = { .prefix_length = 0, .base = 10 };
const BasePrefix HEXIDECIMAL = { .prefix_length = 2, .base = 16 };

bool
have_zero_prefix(std::string_view tokens)
{
    return (tokens.length() > 1) && (tokens.front() == '0');
}

char
to_lowercase(char ascii_token)
{
    constexpr char LOWERCASE_BIT = 0b00100000;

    return ascii_token | LOWERCASE_BIT;
}

} // namespace

BasePrefix
base_prefix_from_string(std::string_view tokens)
{
    if (have_zero_prefix(tokens)) {
        switch (to_lowercase(tokens[1])) {
        case 'b':
            return BINARY;

        case 'x':
            return HEXIDECIMAL;

        default:
            return OCTAL;
        }
    }

    return DECIMAL;
}

} // namespace detail
} // namespace tasty_int
