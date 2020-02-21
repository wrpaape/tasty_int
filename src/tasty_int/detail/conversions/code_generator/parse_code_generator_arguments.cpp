#include "tasty_int/detail/conversions/code_generator/parse_code_generator_arguments.hpp"

#include <cstdlib>

#include <iostream>


namespace tasty_int {
namespace detail {
namespace conversions {
namespace code_generator {
namespace {

void
print_usage(const char   *program,
            std::ostream &output)
{
    if (!program)
        program = "<code generator>";

    output << program << " <target name> <path to output directory>"
           << std::endl;
}

} // namespace


CodeGeneratorArguments
parse_code_generator_arguments(int         argc,
                               char *const argv[])
{
    if (argc < 3) {
        print_usage(argv[0], std::cerr);
        std::exit(EXIT_FAILURE);
    }

    return {
        .target_name      = argv[1],
        .output_directory = argv[2]
    };
}

} // namespace code_generator
} // namespace conversions
} // namespace detail
} // namespace tasty_int
