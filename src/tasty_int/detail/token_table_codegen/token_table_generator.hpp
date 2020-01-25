#ifndef TASTY_INT_TASTY_INT_DETAIL_TOKEN_TABLE_CODEGEN_TOKEN_TABLE_GENERATOR_HPP
#define TASTY_INT_TASTY_INT_DETAIL_TOKEN_TABLE_CODEGEN_TOKEN_TABLE_GENERATOR_HPP

#include <iosfwd>
#include <limits>
#include <string>
#include <string_view>
#include <unordered_map>
#include <utility>


namespace tasty_int {
namespace detail {
namespace token_table_codegen {

/**
 * This class generates C++ source code for lookup tables which may be used to
 * translate string tokens ('0', '2', 'A', etc...) into digit values (0, 2, 10,
 * etc...).  TokenTableGenerator uses tasty_int::detail::TokenTable as the
 * lookup table implementation.
 */
class TokenTableGenerator
{
public:
    /**
     * This class is used to configure the lookup table mapping.  Mapped tokens
     * correspond to ASCII characters that have an associated digit value.
     */
    class TokenMap
    {
    public:
        static constexpr signed char   INVALID_VALUE = -1;
        static constexpr unsigned char MAX_VALUE =
            std::numeric_limits<signed char>::max();

        /**
         * @brief Map @p token to @p value.
         *
         * @param[in] token an element of an ASCII string of digits
         * @param[in] value the value @p token represents
         *
         * @pre `value <= MAX_VALUE`
         * @throws std::invalid_argument if @p value exceeds MAX_VALUE
         */
        void
        map_token(char token, unsigned char value);

        /**
         * @brief Retrieve the digit value associated with @p token.
         *
         * @param[in] token an element of an ASCII string of digits
         * @return the associated value or INVALID_VALUE if @p token has no
         *     associated value
         */
        signed char
        value_from_token(char token) const;

        std::unordered_map<char, signed char> map;
    }; // class TokenMap

    /**
     * @brief Constructor.
     *
     * @param[in] token_table_name the name of the generated code
     */
    TokenTableGenerator(std::string_view token_table_name);

    /**
     * @brief Generates the header file contents declaring the named
     * tasty_int::detail::TokenTable.
     *
     * @param[out] output destination where the file contents will be written
     */
    void
    generate_header(std::ostream &output) const;

    /**
     * @brief Generates the source file contents defining the named
     * tasty_int::detail::TokenTable.
     *
     * @param[out] output destination where the file contents will be written
     */
    void
    generate_source(const TokenMap &token_map,
                    std::ostream   &output) const;

private:
    void
    put_open_namespaces(std::ostream &output) const;

    void
    put_close_namespaces(std::ostream &output) const;

    void
    put_source_head(std::ostream &output) const;

    void
    put_token_table_definition(const TokenMap &token_map,
                               std::ostream   &output) const;

    void
    put_token_table_entries(const TokenMap &token_map,
                            std::ostream   &output) const;

    void
    put_token_table_entry_row(
        const TokenMap                        &token_map,
        std::pair<unsigned int, unsigned int>  token_range,
        std::ostream                          &output
    ) const;

    void
    put_token_table_entry(const TokenMap &token_map,
                          unsigned int    token,
                          std::ostream   &output) const;

    std::string_view name;
    std::string      uppercase_name;
}; // class TokenTableGenerator

} // namespace token_table_codegen
} // namespace detail
} // namespace tasty_int

#endif // ifndef TASTY_INT_TASTY_INT_DETAIL_TOKEN_TABLE_CODEGEN_TOKEN_TABLE_GENERATOR_HPP
