#include "tasty_int/detail/code_generator/test/table_generator_test_fixture.hpp"

#include <cctype>

#include <regex>


namespace table_generator_test_fixture {

TableGeneratorTestFixture::TableGeneratorTestFixture(
    const TableGenerator::TableConfig &test_table_config
)
    : table_config(test_table_config)
{}

void
TableGeneratorTestFixture::check_header(std::string_view header) const
{
    check_common_file_content(header);
    check_include_type_header(header);
    check_table_declaration(header);

    if (::testing::Test::HasFailure())
        FAIL() << header;
}

void
TableGeneratorTestFixture::check_source(std::string_view source) const
{
    check_common_file_content(source);
    check_table_definition(source);

    if (::testing::Test::HasFailure())
        FAIL() << source;
}

void
TableGeneratorTestFixture::check_include_type_header(
    std::string_view header
) const
{
    std::string pattern("#include\\s+");
    pattern += table_config.type_header;
    pattern += "\\s*\n";
    std::regex type_header_include(pattern);

    EXPECT_TRUE(std::regex_search(header.begin(), header.end(),
                                  type_header_include))
        << "couldn't find " << pattern;
}

void
TableGeneratorTestFixture::check_table_declaration(
    std::string_view header
) const
{
    std::string pattern("\\bextern\\s+const\\s+");
    pattern += table_config.type;
    pattern += "\\s+";
    pattern += to_uppercase(table_config.name);
    pattern += "\\s*;";
    std::regex table_declaration(pattern);

    EXPECT_TRUE(std::regex_search(header.begin(), header.end(),
                                  table_declaration))
        << "couldn't find " << pattern;
}

void
TableGeneratorTestFixture::check_table_definition(std::string_view source) const
{
    check_table_definition_declarator(source);
    check_table_definition_expression(source);
}

void
TableGeneratorTestFixture::check_table_definition_declarator(
    std::string_view source
) const
{
    std::string pattern("\\bconst\\s+");
    pattern += table_config.type;
    pattern += "\\s+";
    pattern += to_uppercase(table_config.name);
    pattern += "\\b";
    std::regex table_definition_declarator(pattern);

    EXPECT_TRUE(std::regex_search(source.begin(), source.end(),
                                  table_definition_declarator))
        << "couldn't find " << pattern;
}

void
TableGeneratorTestFixture::check_table_definition_expression(
    std::string_view source
) const
{
    auto start_of_entries = find_start_of_entries(source);
    ASSERT_NE(std::string_view::npos, start_of_entries);

    auto end_of_entries = find_end_of_entries(source, start_of_entries);
    ASSERT_NE(std::string_view::npos, end_of_entries);

    check_table_entries(&source[start_of_entries],
                        &source[end_of_entries]);
}

std::string_view::size_type
TableGeneratorTestFixture::find_start_of_entries(std::string_view source)
{
    std::string_view::size_type cursor = 0;
    for (unsigned int rem_braces = 4; // 3 from namespaces + 1 for definition
         (rem_braces > 0) && (cursor != std::string_view::npos);
         --rem_braces)
        cursor = source.find('{', cursor + 1);

    // advance past opening brace if no error
    return cursor + (cursor != std::string_view::npos);
}

std::string_view::size_type
TableGeneratorTestFixture::find_end_of_entries(
    std::string_view            source,
    std::string_view::size_type start_of_entries
)
{
    auto end_of_entries = source.find('}', start_of_entries);
    return end_of_entries;
}

void
TableGeneratorTestFixture::check_table_entries(const char *entries_begin,
                                               const char *entries_end) const
{
    std::regex match_entries("[^\\s]+(?=,)");
    auto match       = std::cregex_iterator(entries_begin, entries_end,
                                            match_entries);
    auto matches_end = std::cregex_iterator();

    for (std::size_t entry = 0; entry < table_config.num_entries;
         ++match, ++entry) {
        ASSERT_TRUE(match != matches_end)
            << "entry = " << entry;

        EXPECT_EQ(get_mapped_value(entry), match->str())
            << "entry = " << entry;
    }
    EXPECT_TRUE(match == matches_end) << "extra entries";
}

std::string
TableGeneratorTestFixture::get_mapped_value(std::size_t entry) const
{
    std::ostringstream mapped_value;
    table_config.mapper(entry, mapped_value);
    return mapped_value.str();
}

void
TableGeneratorTestFixture::check_common_file_content(
    std::string_view file_content
) const
{
    check_description(file_content);
    check_namespaces(file_content);
}

void
TableGeneratorTestFixture::check_description(
    std::string_view file_content
) const
{
    EXPECT_NE(std::string::npos, file_content.find(table_config.description));
}

void
TableGeneratorTestFixture::check_namespaces(std::string_view file_content)
{
    std::string pattern(
        "namespace\\s+tasty_int\\s*\\{\\s*"
        "namespace\\s+detail\\s*\\{\\s*"
        "namespace\\s+codegen\\s*\\{"
    );
    std::regex namespaces(pattern);

    EXPECT_TRUE(std::regex_search(file_content.begin(), file_content.end(),
                                  namespaces))
        << "couldn't find " << pattern;
}
 
std::string
TableGeneratorTestFixture::to_uppercase(std::string_view input)
{
    std::string uppercase;
    uppercase.reserve(input.size());
    for (char c : input)
        uppercase.push_back(std::toupper(c));

    return uppercase;
}

} // namespace table_generator_test_fixture
