#include "tasty_int/detail/test/from_string_test_common.hpp"

#include <ostream>


namespace from_string_test_common {

std::ostream &
operator<<(std::ostream              &output,
           const FromStringTestParam &test_param)
{
    auto [base, tokens] = test_param;

    return output << "[base=" << base << ", tokens=\"" << tokens << "\"]";
}

} // namespace from_string_test_common
