#include "tasty_int/detail/conversions/base_64_token_from_value.hpp"

#include <cassert>

#include <array>


namespace tasty_int {
namespace detail {
namespace conversions {
namespace {

const std::array<char, 64> BASE_64_TOKENS = {
    'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O',
    'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z',
    'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o',
    'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
    '0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
    '+', '/'
};

} // namespace

char
base_64_token_from_value(unsigned int value)
{
    assert(value < 64);

    return BASE_64_TOKENS[value];
}

} // namespace conversions
} // namespace detail
} // namespace tasty_int
