#include "tasty_int/detail/conversions/value_from_base_64_token.hpp"

#include "tasty_int/detail/conversions/codegen/base_64_token_values.hpp"


namespace tasty_int {
namespace detail {
namespace conversions {

unsigned int
value_from_base_64_token(char base_64_token)
{
    return codegen::BASE_64_TOKEN_VALUES[
        static_cast<unsigned char>(base_64_token)
    ];
}

} // namespace conversions
} // namespace detail
} // namespace tasty_int
