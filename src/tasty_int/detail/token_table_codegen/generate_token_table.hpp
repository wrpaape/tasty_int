#ifndef TASTY_INT_TASTY_INT_DETAIL_TOKEN_TABLE_CODEGEN_GENERATE_TOKEN_TABLE_HPP
#define TASTY_INT_TASTY_INT_DETAIL_TOKEN_TABLE_CODEGEN_GENERATE_TOKEN_TABLE_HPP

#include "tasty_int/detail/token_table_codegen/token_table_generator.hpp"


namespace tasty_int {
namespace detail {
namespace token_table_codegen {

/**
 * @brief Generates the source and header files for a particular
 *     tasty_int::detail::TokenTable mapping.
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
 * @return zero if the files were successfully generated, non-zero if an error
 *     is encountered.
 */
int
generate_token_table(int                                  argc,
                     char                                *argv[],
                     const TokenTableGenerator::TokenMap &token_map);

} // namespace token_table_codegen
} // namespace detail
} // namespace tasty_int

#endif // ifndef TASTY_INT_TASTY_INT_DETAIL_TOKEN_TABLE_CODEGEN_GENERATE_TOKEN_TABLE_HPP
