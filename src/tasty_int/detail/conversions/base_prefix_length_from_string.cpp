#include "tasty_int/detail/conversions/base_prefix_length_from_string.hpp"


namespace tasty_int {
namespace detail {
namespace conversions {
namespace {

const BasePrefixLength BINARY      = { .prefix_length = 2, .base =  2 };
const BasePrefixLength OCTAL       = { .prefix_length = 1, .base =  8 };
const BasePrefixLength DECIMAL     = { .prefix_length = 0, .base = 10 };
const BasePrefixLength HEXIDECIMAL = { .prefix_length = 2, .base = 16 };

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

BasePrefixLength
base_prefix_length_from_string(std::string_view tokens)
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

} // namespace conversions
} // namespace detail
} // namespace tasty_int
