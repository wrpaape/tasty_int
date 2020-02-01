#include "value_from_base_36_token.hpp"

#include "tasty_int/detail/codegen/base_36_token_values.hpp"


namespace tasty_int {
namespace detail {

unsigned int
value_from_base_36_token(char base_36_token)
{
    return codegen::BASE_36_TOKEN_VALUES[
        static_cast<unsigned char>(base_36_token)
    ];
}

} // namespace detail
} // namespace tasty_int
