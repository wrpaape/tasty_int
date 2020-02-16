#ifndef TASTY_INT_TASTY_INT_DETAIL_CODE_GENERATOR_TABLE_GENERATOR_HPP
#define TASTY_INT_TASTY_INT_DETAIL_CODE_GENERATOR_TABLE_GENERATOR_HPP

#include <cstddef>

#include <iosfwd>
#include <functional>
#include <string>
#include <string_view>


namespace tasty_int {
namespace detail {
namespace code_generator {

/**
 * This class generates C++ source code for general-purpose lookup tables.
 */
class TableGenerator
{
public:
    /**
     * This struct defines the configuration parameters for a TableGenerator.
     */
    struct TableConfig
    {
        /**
         * The name of the generated table.
         */
        std::string_view name;

        /**
         * The C++ type of the generated table.
         */
        std::string_view type;

        /**
         * The header which declares the C++ type of the generated table.
         * type_header will be forwarded as-is to an #include directive and so
         * should be surrounded with either "" or <> depending on the header.
         */
        std::string_view type_header;

        /**
         * A description of the table purpose.
         */
        std::string_view description;

        /**
         * The number of table entries. mapper will be called for table indices
         * in the range [0, num_entries).
         */
        std::size_t num_entries;

        /**
         * The function mapping table index to table value.  mapper should
         * print to `output` the value associated with the provided table
         * index, `table_index`.
         */
        std::function<
            void (std::size_t table_index, std::ostream &output)
        > mapper;
    }; // struct TableConfig

    /**
     * @brief Constructor.
     *
     * @param[in] table_config the configuration parameters
     */
    TableGenerator(const TableConfig &table_config);

    /**
     * @brief Get the name of the table.
     *
     * @return the name of the table
     */
    std::string_view
    get_table_name() const;

    /**
     * @brief Generates the header file contents declaring the named table.
     *
     * @param[out] output destination where the file contents will be written
     */
    void
    generate_header(std::ostream &output) const;

    /**
     * @brief Generates the source file contents defining the named table.
     *
     * @param[out] output destination where the file contents will be written
     */
    void
    generate_source(std::ostream &output) const;

private:
    void
    put_open_header_guard(std::ostream &output) const;

    void
    put_include_type_header(std::ostream &output) const;

    void
    put_table_declaration(std::ostream &output) const;

    void
    put_close_header_guard(std::ostream &output) const;

    void
    put_generated_header(std::ostream &output) const;

    void
    put_include_header(std::ostream &output) const;

    void
    put_table_definition(std::ostream &output) const;

    void
    put_table_entries(std::ostream &output) const;

    void
    put_open_namespaces(std::ostream &output) const;

    void
    put_close_namespaces(std::ostream &output) const;

    const std::string                                       name;
    const std::string                                       uppercase_name;
    const std::string                                       type;
    const std::string                                       type_header;
    const std::string                                       description;
    const std::size_t                                       num_entries;
    const std::function<void (std::size_t, std::ostream &)> mapper;
}; // class TableGenerator

} // namespace code_generator
} // namespace detail
} // namespace tasty_int

#endif // ifndef TASTY_INT_TASTY_INT_DETAIL_CODE_GENERATOR_TABLE_GENERATOR_HPP
