#include "tasty_int/detail/conversions/base_36_token_from_value.hpp"

#include <cassert>

#include <array>


namespace tasty_int {
namespace detail {
namespace conversions {
namespace {

const std::array<char, 36> BASE_36_TOKENS = {
    '0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
    'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o',
    'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'
};

} // namespace

char
base_36_token_from_value(unsigned int value)
{
    assert(value < 36);

    return BASE_36_TOKENS[value];
}

} // namespace conversions
} // namespace detail
} // namespace tasty_int
