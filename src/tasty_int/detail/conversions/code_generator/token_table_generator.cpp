#include "tasty_int/detail/conversions/code_generator/token_table_generator.hpp"

#include "tasty_int/detail/conversions/token_table.hpp"

#include <cctype>
#include <ctime>

#include <algorithm>
#include <chrono>
#include <iomanip>
#include <ostream>
#include <stdexcept>


namespace tasty_int {
namespace detail {
namespace conversions {
namespace code_generator {
namespace {

std::string
to_uppercase(std::string_view string)
{
    std::string uppercase;
    uppercase.reserve(string.size());
    for (char c : string)
        uppercase.push_back(std::toupper(c));

    return uppercase;
}

} // namespace

void
TokenTableGenerator::TokenMap::map_token(char          token,
                                         unsigned char value)
{
    if (value <= MAX_VALUE) {
        mapping[token] = value;
        return;
    }

    static const std::string FIRST_PART_OF_INVALID_MAPPING_MESSAGE =
        "tasty_int::detail::conversions::code_generator::TokenTableGenerator::"
        "TokenMap - invalid mapping (";

    static const std::string MIDDLE_PART_OF_INVALID_MAPPING_MESSAGE = "->";

    static const std::string LAST_PART_OF_INVALID_MAPPING_MESSAGE =
        "): Digit value exceeds "
        "tasty_int::detail::conversions::code_generator::TokenTableGenerator::"
        "TokenMap::MAX_VALUE ("
      + std::to_string(static_cast<unsigned int>(MAX_VALUE)) + ").";

    throw std::invalid_argument(
        FIRST_PART_OF_INVALID_MAPPING_MESSAGE
      + token
      + MIDDLE_PART_OF_INVALID_MAPPING_MESSAGE
      + std::to_string(static_cast<unsigned int>(value))
      + LAST_PART_OF_INVALID_MAPPING_MESSAGE
    );
}

unsigned char
TokenTableGenerator::TokenMap::value_from_token(char token) const
{
    auto found = mapping.find(token);
    return (found == mapping.end()) ? INVALID_VALUE : found->second;
}

TokenTableGenerator::TokenTableGenerator(
    const TokenTableConfig &token_table_config
)
    : TableGenerator({
          .name        = token_table_config.name,
          .type        = "TokenTable",
          .type_header = "\"tasty_int/detail/conversions/token_table.hpp\"",
          .description = "token -> digit value lookup tables (DO NOT MODIFY)",
          .num_entries = std::numeric_limits<unsigned char>::max() + 1,
          .mapper      = [&](std::size_t entry, std::ostream &output) {
               char token = static_cast<char>(entry);
               output << static_cast<unsigned int>(
                   token_map.value_from_token(token)
               );
          }
      })
    , token_map(token_table_config.token_map)
{}

} // namespace code_generator
} // namespace conversions
} // namespace detail
} // namespace tasty_int
