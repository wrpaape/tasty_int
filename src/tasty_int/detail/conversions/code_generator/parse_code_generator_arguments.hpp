#ifndef TASTY_INT_TASTY_INT_DETAIL_CONVERSIONS_CODE_GENERATOR_PARSE_CODE_GENERATOR_ARGUMENTS_HPP
#define TASTY_INT_TASTY_INT_DETAIL_CONVERSIONS_CODE_GENERATOR_PARSE_CODE_GENERATOR_ARGUMENTS_HPP

#include <string_view>


namespace tasty_int {
namespace detail {
namespace conversions {
namespace code_generator {

/**
 * This struct defines the arguments required for a code generator.
 */
struct CodeGeneratorArguments
{
    std::string_view target_name;      ///< the name of the target
    std::string_view output_directory; ///< the path to the output directory
}; // struct CodeGeneratorArguments


/**
 * @brief Parses code generator arguments from the supplied command line
 *     arguments.
 *
 * @param[in] argc      the length of @p argv
 * @param[in] argv      the command line arguments (interpretted as { <program
 *                      name>, <target name>, <path to output directory> })
 * @return
 *     tasty_int::detail::conversions::code_generator::CodeGeneratorArguments if
 *     parse succeeded
 *
 * @pre Prints usage message and exits with `EXIT_FAILURE` if arguments are not
 *     well defined.
 */
CodeGeneratorArguments
parse_code_generator_arguments(int         argc,
                               char *const argv[]);

} // namespace code_generator
} // namespace conversions
} // namespace detail
} // namespace tasty_int

#endif // ifndef TASTY_INT_TASTY_INT_DETAIL_CONVERSIONS_CODE_GENERATOR_PARSE_CODE_GENERATOR_ARGUMENTS_HPP
