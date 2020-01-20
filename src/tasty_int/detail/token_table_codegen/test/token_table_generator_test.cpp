#include "tasty_int/detail/token_table_codegen/token_table_generator.hpp"

#include <limits>
#include <regex>
#include <sstream>
#include <string>

#include "gtest/gtest.h"


namespace {

using tasty_int::detail::token_table_codegen::TokenTableGenerator;

TEST(TokenTableGeneratorTest,
     TokenMapMapTokenDoesNotAllowDigitsGreaterThanMaxDigit)
{
    char token                  = '5';
    unsigned char INVALID_DIGIT = TokenTableGenerator::TokenMap::MAX_DIGIT + 1;

    TokenTableGenerator::TokenMap token_map;
    try {
        token_map.map_token(token, INVALID_DIGIT);
        FAIL() << "did not throw expected std::invalid_argument";

    } catch (const std::invalid_argument& exception) {
        // replace with std::format when available
        std::ostringstream expected_message;
        expected_message <<
            "TokenTableGenerator::TokenMap - invalid mapping (" << token
         << "->" << static_cast<unsigned int>(INVALID_DIGIT) << "): Digit "
            "exceeds TokenTableGenerator::TokenMap::MAX_DIGIT ("
         << static_cast<unsigned int>(TokenTableGenerator::TokenMap::MAX_DIGIT)
         << ").";
        EXPECT_EQ(expected_message.str(), exception.what());
    }
}

TEST(TokenTableGeneratorTest,
     TokenMapDigitFromTokenReturnsMappedDigitForMappedTokens)
{
    TokenTableGenerator::TokenMap token_map;
    token_map.map_token('7', 7);

    EXPECT_EQ(7, token_map.digit_from_token('7'));
}

TEST(TokenTableGeneratorTest,
     TokenMapDigitFromTokenReturnsInvalidDigitForUnmappedTokens)
{
    TokenTableGenerator::TokenMap token_map;

    EXPECT_EQ(TokenTableGenerator::TokenMap::INVALID_DIGIT,
              token_map.digit_from_token('7'));
}

void
check_namespaces(std::string_view file_content)
{
    std::regex namespaces(
        "namespace\\s+tasty_int\\s*\\{\\s*"
        "namespace\\s+detail\\s*\\{\\s*"
        "namespace\\s+codegen\\s*\\{"
    );

    EXPECT_TRUE(std::regex_search(file_content.begin(), file_content.end(),
                                  namespaces));
}

void
check_token_table_declaration(std::string_view header,
                              std::string_view token_table_name)
{
    std::string pattern("\\bextern\\s+const\\s+\\TokenTable\\s+");
    pattern += token_table_name;
    pattern += "\\s*;";
    std::regex token_table_declaration(pattern);

    EXPECT_TRUE(std::regex_search(header.begin(), header.end(),
                                  token_table_declaration));
}

void
check_header(std::string_view header,
             std::string_view token_table_name)
{
    check_namespaces(header);
    check_token_table_declaration(header,
                                  token_table_name);
}

TEST(TokenTableGeneratorTest, GenerateHeader)
{
    std::string_view token_table_name("TEST_GENERATE_HEADER_TOKEN_TABLE");
    TokenTableGenerator token_table_generator(token_table_name);

    std::ostringstream output;
    token_table_generator.generate_header(output);

    check_header(output.str(), token_table_name);
}

void
check_token_table_definition_declarator(std::string_view source,
                                        std::string_view token_table_name)
{
    std::string pattern("\\bconst\\s+\\TokenTable\\s+");
    pattern += token_table_name;
    pattern += "\\b";
    std::regex token_table_declaration(pattern);
    EXPECT_TRUE(std::regex_search(source.begin(), source.end(),
                                  token_table_declaration));
}

std::string_view::size_type
find_start_of_entries(std::string_view source)
{
    std::string_view::size_type cursor = 0;
    for (unsigned int rem_braces = 4;
         (rem_braces > 0) && (cursor != std::string_view::npos);
         --rem_braces)
        cursor = source.find('{', cursor + 1);

    // advance past opening brace if no error
    return cursor + (cursor != std::string_view::npos);
}

std::string_view::size_type
find_end_of_entries(std::string_view            source,
                    std::string_view::size_type start_of_entries)
{
    auto end_of_entries = source.find('}', start_of_entries);
    return end_of_entries;
}

void
check_token_table_entries(const char                          *entries_begin,
                          const char                          *entries_end,
                          const TokenTableGenerator::TokenMap &token_map)
{
    std::regex match_numbers("-?\\d+");
    auto match       = std::cregex_iterator(entries_begin, entries_end,
                                            match_numbers);
    auto matches_end = std::cregex_iterator();

    for (unsigned int token_offset = 0;
         token_offset <= std::numeric_limits<unsigned char>::max();
         ++match, ++token_offset) {
        char token = static_cast<char>(token_offset);
        ASSERT_TRUE(match != matches_end)
            << "token = " << token;

        ASSERT_EQ(token_map.digit_from_token(token), std::stoi(match->str()))
            << "token = " << token;
    }
    EXPECT_TRUE(match == matches_end) << "extra entries";
}

void
check_token_table_definition_expression(
    std::string_view                     source,
    const TokenTableGenerator::TokenMap &token_map
)
{
    auto start_of_entries = find_start_of_entries(source);
    ASSERT_NE(std::string_view::npos, start_of_entries);

    auto end_of_entries = find_end_of_entries(source, start_of_entries);
    ASSERT_NE(std::string_view::npos, end_of_entries);

    check_token_table_entries(&source[start_of_entries],
                              &source[end_of_entries],
                              token_map);
}

void
check_token_table_definition(
    std::string_view                     source,
    std::string_view                     token_table_name,
    const TokenTableGenerator::TokenMap &token_map
)
{
    check_token_table_definition_declarator(source, token_table_name);
    check_token_table_definition_expression(source, token_map);
}

void
check_source(std::string_view                     source,
             std::string_view                     token_table_name,
             const TokenTableGenerator::TokenMap &token_map)
{
    check_namespaces(source);
    check_token_table_definition(source, token_table_name, token_map);
}

TEST(TokenTableGeneratorTest, GenerateSource)
{
    std::string_view token_table_name("TEST_GENERATE_SOURCE_TOKEN_TABLE");
    TokenTableGenerator token_table_generator(token_table_name);
    TokenTableGenerator::TokenMap token_map;
    token_map.map_token( '0', 2 );
    token_map.map_token( 'A', 4 );
    token_map.map_token( 'c', 9 );
    token_map.map_token( '?', 7 );

    std::ostringstream output;
    token_table_generator.generate_source(token_map,
                                          output);

    check_source(output.str(), token_table_name, token_map);
}

} // namespace
