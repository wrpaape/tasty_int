#include "tasty_int/detail/conversions/test/string_conversion_test_common.hpp"

#include <ostream>


namespace string_conversion_test_common {

std::ostream &
operator<<(std::ostream                        &output,
           const StringViewConversionTestParam &test_param)
{
    auto [base, tokens] = test_param;

    return output << "{ base=" << base << ", tokens=\"" << tokens << "\" }";
}

std::ostream &
operator<<(std::ostream                    &output,
           const StringConversionTestParam &test_param)
{
    const auto& [base, tokens] = test_param;

    return output << StringViewConversionTestParam{ .base = base, .tokens = tokens };
}

} // namespace string_conversion_test_common
