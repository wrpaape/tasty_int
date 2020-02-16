#include "tasty_int/detail/code_generator/generate_token_table.hpp"

#include "tasty_int/detail/code_generator/parse_code_generator_arguments.hpp"
#include "tasty_int/detail/code_generator/generate_table_files.hpp"


namespace tasty_int {
namespace detail {
namespace code_generator {

void
generate_token_table(int                                  argc,
                     char                                *argv[],
                     const TokenTableGenerator::TokenMap &token_map)
{
    auto args = parse_code_generator_arguments(argc, argv);

    const TokenTableGenerator generator({
         .name      = args.target_name,
         .token_map = token_map
    });

    generate_table_files(generator, args.output_directory);
}

} // namespace code_generator
} // namespace detail
} // namespace tasty_int

