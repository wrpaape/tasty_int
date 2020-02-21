#include "tasty_int/detail/conversions/code_generator/token_table_generator.hpp"

#include <limits>

#include "tasty_int/detail/conversions/code_generator/test/table_generator_test_fixture.hpp"


namespace {

using table_generator_test_fixture::TableGeneratorTestFixture;
using tasty_int::detail::conversions::code_generator::TokenTableGenerator;


class TokenTableGeneratorTest : public TableGeneratorTestFixture
{
protected:
    TokenTableGeneratorTest();

    static TokenTableGenerator::TokenMap
    make_token_map();

    TokenTableGenerator::TokenTableConfig token_table_config;
    TableGenerator::TableConfig           table_config;
    TokenTableGenerator                   token_table_generator;
}; // class TableGeneratorTest

TokenTableGeneratorTest::TokenTableGeneratorTest()
    : TableGeneratorTestFixture(table_config)
    , token_table_config({
          .name      = "test_generate_token_table",
          .token_map = make_token_map()
      })
    , table_config({
          .name        = token_table_config.name,
          .type        = "TokenTable",
          .type_header = "\"tasty_int/detail/conversions/token_table.hpp\"",
          .description = "token -> digit value lookup tables (DO NOT MODIFY)",
          .num_entries = std::numeric_limits<unsigned char>::max() + 1,
          .mapper      = [&](std::size_t entry, std::ostream &output) {
              char token = static_cast<char>(entry);
              output << static_cast<unsigned int>(
                  token_table_config.token_map.value_from_token(token)
              );
          }
      })
    , token_table_generator(token_table_config)
{}

TokenTableGenerator::TokenMap
TokenTableGeneratorTest::make_token_map()
{
    TokenTableGenerator::TokenMap token_map;
    token_map.map_token('0', 2);
    token_map.map_token('A', 4);
    token_map.map_token('c', 9);
    token_map.map_token('?', 7);

    return token_map;
}


TEST(TokenTableGeneratorTokenMapTest,
     MapTokenDoesNotAllowValuesGreaterThanMaxValue)
{
    char token                  = '5';
    unsigned char INVALID_VALUE = TokenTableGenerator::TokenMap::MAX_VALUE + 1;

    TokenTableGenerator::TokenMap token_map;
    try {
        token_map.map_token(token, INVALID_VALUE);
        FAIL() << "did not throw expected std::invalid_argument";

    } catch (const std::invalid_argument &exception) {
        std::ostringstream expected_message;
        expected_message <<
            "tasty_int::detail::conversions::code_generator::"
            "TokenTableGenerator::TokenMap - invalid mapping (" << token << "->"
         << static_cast<unsigned int>(INVALID_VALUE) << "): Digit value exceeds"
            " tasty_int::detail::conversions::code_generator::"
            "TokenTableGenerator::TokenMap::MAX_VALUE ("
         << static_cast<unsigned int>(TokenTableGenerator::TokenMap::MAX_VALUE)
         << ").";

        EXPECT_EQ(expected_message.str(), exception.what());
    }
}

TEST(TokenTableGeneratorTokenMapTest,
     ValueFromTokenReturnsMappedValueForMappedTokens)
{
    TokenTableGenerator::TokenMap token_map;
    token_map.map_token('7', 7);

    EXPECT_EQ(7, token_map.value_from_token('7'));
}

TEST(TokenTableGeneratorTokenMapTest,
     ValueFromTokenReturnsInvalidValueForUnmappedTokens)
{
    TokenTableGenerator::TokenMap token_map;

    EXPECT_EQ(TokenTableGenerator::TokenMap::INVALID_VALUE,
              token_map.value_from_token('7'));
}

TEST_F(TokenTableGeneratorTest, GetTableName)
{
    EXPECT_EQ(token_table_config.name, token_table_generator.get_table_name());
}

TEST_F(TokenTableGeneratorTest, GenerateHeader)
{
    std::ostringstream output;
    token_table_generator.generate_header(output);

    check_header(output.str());
}

TEST_F(TokenTableGeneratorTest, GenerateSource)
{
    std::ostringstream output;
    token_table_generator.generate_source(output);

    check_source(output.str());
}

} // namespace
