#include "tasty_int/detail/conversions/code_generator/test/table_generator_test_fixture.hpp"


namespace {

using table_generator_test_fixture::TableGeneratorTestFixture;


class TableGeneratorTest : public TableGeneratorTestFixture
{
protected:
    TableGeneratorTest();

    TableGenerator::TableConfig table_config;
    TableGenerator              table_generator;
}; // class TableGeneratorTest

TableGeneratorTest::TableGeneratorTest()
    : TableGeneratorTestFixture(table_config)
    , table_config({
          .name        = "test_generate_table",
          .type        = "TestGenerateTableType",
          .type_header = "\"path/to/test_generate_table_type.hpp\"",
          .description = "This is the TableGeneratorTest description.",
          .num_entries = 200,
          .mapper      = [](std::size_t entry, std::ostream &output) {
              output << entry + 42;
          }
      })
    , table_generator(table_config)
{}


TEST_F(TableGeneratorTest, GetTableName)
{
    EXPECT_EQ(table_config.name, table_generator.get_table_name());
}

TEST_F(TableGeneratorTest, GenerateHeader)
{
    std::ostringstream output;
    table_generator.generate_header(output);

    check_header(output.str());
}

TEST_F(TableGeneratorTest, GenerateSource)
{
    std::ostringstream output;
    table_generator.generate_source(output);

    check_source(output.str());
}

} // namespace
