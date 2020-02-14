#include "tasty_int/detail/test/int_test_common.hpp"

#include <ostream>

#include "tasty_int/detail/int.hpp"
#include "tasty_int/detail/test/sign_test_common.hpp"


namespace tasty_int {
namespace detail {
namespace {
void
PrintTo(const std::vector<digit_type> &digits,
        std::ostream                  *output)
{
    const char *separator = "{ ";

    for (auto digit : digits) {
        *output << separator << digit;
        separator = ", ";
    }

    *output << " }";
}

} // namespace

void
PrintTo(const Int    &integer,
        std::ostream *output)
{
    *output << "{ sign=";
    PrintTo(integer.sign, output);
    *output << ", digits=";
    PrintTo(integer.digits, output);
    *output << " }";
}

} // namespace detail
} // namespace tasty_int
