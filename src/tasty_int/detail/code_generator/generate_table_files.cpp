#include "tasty_int/detail/code_generator/generate_token_table.hpp"

#include <fstream>
#include <filesystem>
#include <iostream>


namespace tasty_int {
namespace detail {
namespace code_generator {
namespace {

void
generate_header(const TableGenerator &generator,
                const std::string    &header_path)
{
    std::ofstream header(header_path);
    generator.generate_header(header);
}

void
generate_source(const TableGenerator &generator,
                const std::string    &source_path)
{
    std::ofstream source(source_path);
    generator.generate_source(source);
}

} // namespace


void
generate_table_files(const TableGenerator &generator,
                     std::string_view      output_directory)
{
    std::filesystem::path path(output_directory);
    path /= generator.get_table_name();
    path += ".hpp";
    generate_header(generator, path.string());

    path.replace_extension(".cpp");
    generate_source(generator, path.string());
}

} // namespace code_generator
} // namespace detail
} // namespace tasty_int

