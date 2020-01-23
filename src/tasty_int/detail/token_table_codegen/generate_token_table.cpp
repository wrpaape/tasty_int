#include <fstream>
#include <filesystem>
#include <iostream>

#include "tasty_int/detail/token_table_codegen/generate_token_table.hpp"


namespace tasty_int {
namespace detail {
namespace token_table_codegen {
namespace {

void
print_usage(const char   *program,
            std::ostream &output)
{
    if (!program)
        program = "./generate_token_table";

    output << program << " <token table name> <path to output directory>"
           << std::endl;
}

void
generate_header(const TokenTableGenerator &generator,
                const std::string         &header_path)
{
    std::ofstream header(header_path);
    generator.generate_header(header);
}

void
generate_source(const TokenTableGenerator           &generator,
                const std::string                   &source_path,
                const TokenTableGenerator::TokenMap &token_map)
{
    std::ofstream source(source_path);
    generator.generate_source(token_map,
                              source);
}

void
generate_files(const char                          *token_table_name,
               const char                          *output_directory,
               const TokenTableGenerator::TokenMap &token_map)
{
    const TokenTableGenerator generator(token_table_name);

    std::filesystem::path path(output_directory);
    path /= token_table_name;
    path += ".hpp";
    generate_header(generator, path.string());

    path.replace_extension(".cpp");
    generate_source(generator, path.string(), token_map);
}

} // namespace

int
generate_token_table(int                                  argc,
                     char                                *argv[],
                     const TokenTableGenerator::TokenMap &token_map)
{
    if (argc < 3) {
        print_usage(argv[0], std::cerr);
        return 1;
    }

    const char *token_table_name = argv[1];
    const char *output_directory = argv[2];
    generate_files(token_table_name, output_directory, token_map);
    return 0;
}


} // namespace token_table_codegen
} // namespace detail
} // namespace tasty_int

