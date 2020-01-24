#include "tasty_int/detail/token_table_codegen/token_table_generator.hpp"

#include "tasty_int/detail/token_table.hpp"

#include <cctype>
#include <ctime>

#include <algorithm>
#include <chrono>
#include <iomanip>
#include <ostream>
#include <stdexcept>


namespace tasty_int {
namespace detail {
namespace token_table_codegen {
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
        map[token] = static_cast<signed char>(value);
        return;
    }

    static const std::string FIRST_PART_OF_INVALID_MAPPING_MESSAGE =
        "TokenTableGenerator::TokenMap - invalid mapping (";

    static const std::string MIDDLE_PART_OF_INVALID_MAPPING_MESSAGE = "->";

    static const std::string LAST_PART_OF_INVALID_MAPPING_MESSAGE =
        "): Digit value exceeds TokenTableGenerator::TokenMap::MAX_VALUE ("
      + std::to_string(static_cast<unsigned int>(MAX_VALUE)) + ").";

    throw std::invalid_argument(
        FIRST_PART_OF_INVALID_MAPPING_MESSAGE
      + token
      + MIDDLE_PART_OF_INVALID_MAPPING_MESSAGE
      + std::to_string(static_cast<unsigned int>(value))
      + LAST_PART_OF_INVALID_MAPPING_MESSAGE
    );
}

signed char
TokenTableGenerator::TokenMap::value_from_token(char token) const
{
    auto found = map.find(token);
    return (found == map.end()) ? INVALID_VALUE : found->second;
}

TokenTableGenerator::TokenTableGenerator(std::string_view token_table_name)
    : token_table_name(token_table_name)
    , uppercase_token_table_name(to_uppercase(token_table_name))
{}

void
TokenTableGenerator::generate_header(std::ostream &output) const
{
    output <<
        "#ifndef TASTY_INT_TASTY_INT_DETAIL_CODEGEN_"
            << uppercase_token_table_name << "_HPP\n"
        "#define TASTY_INT_TASTY_INT_DETAIL_CODEGEN_"
            << uppercase_token_table_name << "_HPP\n"
        "\n"
        "#include \"tasty_int/detail/token_table.hpp\"\n"
        "\n"
        "\n";
    put_open_namespaces(output);
    output <<
        "\n"
        "extern const TokenTable " << uppercase_token_table_name << ";\n"
        "\n";
    put_close_namespaces(output);
    output <<
        "\n"
        "#endif // ifndef TASTY_INT_TASTY_INT_DETAIL_CODEGEN_"
            << uppercase_token_table_name << "_HPP\n";
}

void
TokenTableGenerator::generate_source(const TokenMap &token_map,
                                     std::ostream   &output) const
{
    put_source_head(output);
    output << "\n\n";
    put_open_namespaces(output);
    output << "\n";
    put_token_table_definition(token_map, output);
    output << "\n";
    put_close_namespaces(output);
}

void
TokenTableGenerator::put_open_namespaces(std::ostream &output) const
{
    output <<
        "namespace tasty_int {\n"
        "namespace detail {\n"
        "namespace codegen {\n";
}

void
TokenTableGenerator::put_close_namespaces(std::ostream &output) const
{
    output <<
        "} // namespace codegen\n"
        "} // namespace detail\n"
        "} // namespace tasty_int\n";
}

void
TokenTableGenerator::put_source_head(std::ostream &output) const
{
    auto time_now  = std::chrono::system_clock::now();
    auto timestamp = std::chrono::system_clock::to_time_t(time_now);

    output <<
        "// token -> digit value lookup tables for TastyInt (DO NOT MODIFY)\n"
        "//\n"
        "// generated on: " << std::ctime(&timestamp) // terminated with \n
     << "// =============================================================================\n"
        "#include \"tasty_int/detail/codegen/" << token_table_name << ".hpp\"\n";
}

void
TokenTableGenerator::put_token_table_definition(const TokenMap &token_map,
                                                std::ostream   &output) const
{
    output << "const TokenTable " << uppercase_token_table_name << " = {\n";
    put_token_table_entries(token_map, output);
    output << "};\n";
}

void
TokenTableGenerator::put_token_table_entries(const TokenMap &token_map,
                                             std::ostream   &output) const
{
    static const unsigned int TOKENS_END =
        std::numeric_limits<unsigned char>::max() + 1;
    static const unsigned int TOKENS_PER_ROW = 15;
    static const std::string_view INDENT = "    ";

    unsigned int row_begin = 0;
    while (true) {
        unsigned int row_end = std::min(row_begin + TOKENS_PER_ROW,
                                        TOKENS_END);
        output << INDENT;
        put_token_table_entry_row(token_map,
                                  { row_begin, row_end },
                                  output);
        if (row_end == TOKENS_END)
            break;

        row_begin = row_end;
        output << ",\n";
    }
    output << '\n';
}

void
TokenTableGenerator::put_token_table_entry_row(
    const TokenMap                        &token_map,
    std::pair<unsigned int, unsigned int>  token_range,
    std::ostream                          &output
) const
{
    unsigned int token      = token_range.first;
    unsigned int tokens_end = token_range.second;

    while (true) {
        put_token_table_entry(token_map, token, output);
        if (++token >= tokens_end)
            break;

        output << ", ";
    }
}

void
TokenTableGenerator::put_token_table_entry(const TokenMap &token_map,
                                           unsigned int    token,
                                           std::ostream   &output) const
{
    auto value = token_map.value_from_token(static_cast<char>(token));
    output << std::setw(3) << static_cast<int>(value);
}

} // namespace token_table_codegen
} // namespace detail
} // namespace tasty_int
