#include "tasty_int/detail/test/sign_test_common.hpp"

#include <ostream>
#include <string>

namespace tasty_int {
namespace detail {
namespace {

const std::string SIGN_NEGATIVE = "Sign::NEGATIVE";
const std::string SIGN_ZERO     = "Sign::ZERO";
const std::string SIGN_POSITIVE = "Sign::POSITIVE";

std::string
string_from_sign(Sign sign)
{
    switch (sign) {
    case Sign::NEGATIVE:
        return SIGN_NEGATIVE;

    case Sign::ZERO:
        return SIGN_ZERO;

    case Sign::POSITIVE:
        return SIGN_POSITIVE;

    default:
        return "Sign::<UNKNOWN ("
             + std::to_string(static_cast<int>(sign))
             + ")>";
    }
}

} // namespace


void
PrintTo(Sign          sign,
        std::ostream *output)
{
    *output << string_from_sign(sign);
}

} // namespace detail
} // namespace tasty_int

