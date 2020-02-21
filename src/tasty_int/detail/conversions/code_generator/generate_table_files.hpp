#ifndef TASTY_INT_TASTY_INT_DETAIL_CONVERSIONS_CODE_GENERATOR_GENERATE_TABLE_FILES_HPP
#define TASTY_INT_TASTY_INT_DETAIL_CONVERSIONS_CODE_GENERATOR_GENERATE_TABLE_FILES_HPP

#include <string_view>

#include "tasty_int/detail/conversions/code_generator/table_generator.hpp"


namespace tasty_int {
namespace detail {
namespace conversions {
namespace code_generator {

/**
 * @brief Generates the source and header files for a particular mapping.
 *
 * @param[in] generator        the table generator
 * @param[in] output_directory the destination directory
 */
void
generate_table_files(const TableGenerator &generator,
                     std::string_view      output_directory);

} // namespace code_generator
} // namespace conversions
} // namespace detail
} // namespace tasty_int

#endif // ifndef TASTY_INT_TASTY_INT_DETAIL_CONVERSIONS_CODE_GENERATOR_GENERATE_TABLE_FILES_HPP
