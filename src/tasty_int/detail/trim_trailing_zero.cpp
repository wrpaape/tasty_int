#include "tasty_int/detail/trim_trailing_zero.hpp"


namespace tasty_int {
namespace detail {
namespace {

bool
have_trailing_zero(const std::vector<digit_type> &digits)
{
    return ((digits.size() > 1) && (digits.back() == 0));
}

} // namespace


void
trim_trailing_zero(std::vector<digit_type> &digits)
{
    if (have_trailing_zero(digits))
        digits.pop_back();
}

} // namespace detail
} // namespace tasty_int
