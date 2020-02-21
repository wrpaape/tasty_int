#ifndef TASTY_INT_TASTY_INT_DETAIL_CONVERSIONS_CODE_GENERATOR_TEST_TABLE_GENERATOR_TEST_FIXTURE_HPP
#define TASTY_INT_TASTY_INT_DETAIL_CONVERSIONS_CODE_GENERATOR_TEST_TABLE_GENERATOR_TEST_FIXTURE_HPP

#include "tasty_int/detail/conversions/code_generator/table_generator.hpp"

#include <sstream>
#include <string>
#include <string_view>

#include "gtest/gtest.h"


namespace table_generator_test_fixture {

/**
 * This test fixture checks the output of a
 * tasty_int::detail::conversions::code_generator::TableGenerator against an
 * expected configuration.
 */
class TableGeneratorTestFixture : public ::testing::Test
{
protected:
    using TableGenerator =
        tasty_int::detail::conversions::code_generator::TableGenerator;

    /**
     * @brief Constructor.
     *
     * @param[in] test_table_config a reference to the expected table
     *     configuration
     */
    TableGeneratorTestFixture(
        const TableGenerator::TableConfig &test_table_config
    );

    /**
     * @brief Emits a non-fatal failure and prints @p header to gtest output if
     *     @p header is ill-formed.
     */
    void
    check_header(std::string_view header) const;

    /**
     * @brief Emits a non-fatal failure and prints @p source to gtest output if
     *     @p source is ill-formed.
     */
    void
    check_source(std::string_view source) const;

private:
    void
    check_include_type_header(std::string_view header) const;

    void
    check_table_declaration(std::string_view header) const;

    void
    check_table_definition(std::string_view source) const;

    void
    check_table_definition_declarator(std::string_view source) const;

    void
    check_table_definition_expression(std::string_view source) const;

    static std::string_view::size_type
    find_start_of_entries(std::string_view source);

    static std::string_view::size_type
    find_end_of_entries(std::string_view            source,
                        std::string_view::size_type start_of_entries);

    void
    check_table_entries(const char *entries_begin,
                        const char *entries_end) const;

    std::string
    get_mapped_value(std::size_t entry) const;

    void
    check_common_file_content(std::string_view file_content) const;

    void
    check_description(std::string_view file_content) const;

    static void
    check_namespaces(std::string_view file_content);

    static std::string
    to_uppercase(std::string_view string);


    const TableGenerator::TableConfig &table_config;
}; // class TableGeneratorTestFixture

} // namespace table_generator_test_fixture

#endif // ifndef TASTY_INT_TASTY_INT_DETAIL_CONVERSIONS_CODE_GENERATOR_TEST_TABLE_GENERATOR_TEST_FIXTURE_HPP
