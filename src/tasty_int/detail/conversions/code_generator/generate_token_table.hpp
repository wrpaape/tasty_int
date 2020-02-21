#ifndef TASTY_INT_TASTY_INT_DETAIL_CONVERSIONS_CODE_GENERATOR_GENERATE_TOKEN_TABLE_HPP
#define TASTY_INT_TASTY_INT_DETAIL_CONVERSIONS_CODE_GENERATOR_GENERATE_TOKEN_TABLE_HPP

#include "tasty_int/detail/conversions/code_generator/token_table_generator.hpp"


namespace tasty_int {
namespace detail {
namespace conversions {
namespace code_generator {

/**
 * @brief Generates the source and header files for a particular
 *     tasty_int::detail::conversions::TokenTable mapping.
 *
 * @detail Programs may forward @p argc and @argv directly from main() along
 *     with the configured @p token_map mapping.  The command line arguments
 *     are interpretted as { <program name>, <token table name>, <path to
 *     output directory> }.  If these arguments aren't provided then a usage
 *     message is printed to standard error and no files are generated.
 *
 * @param[in] argc      the length of @p argv
 * @param[in] argv      the command line arguments (interpretted as { <program
 *                      name>, <token table name>, <path to output directory> })
 * @param[in] token_map the mapping of character tokens to digit values (i.e. '1'->1)
 *
 * @pre Prints usage message and exits with `EXIT_FAILURE` if arguments are not
 *     well defined.
 */
void
generate_token_table(int                                  argc,
                     char                                *argv[],
                     const TokenTableGenerator::TokenMap &token_map);

} // namespace code_generator
} // namespace conversions
} // namespace detail
} // namespace tasty_int

#endif // ifndef TASTY_INT_TASTY_INT_DETAIL_CONVERSIONS_CODE_GENERATOR_GENERATE_TOKEN_TABLE_HPP
