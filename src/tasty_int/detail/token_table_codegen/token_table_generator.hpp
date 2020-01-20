#ifndef TASTY_INT_TASTY_INT_DETAIL_TOKEN_TABLE_CODEGEN_TOKEN_TABLE_GENERATOR_HPP
#define TASTY_INT_TASTY_INT_DETAIL_TOKEN_TABLE_CODEGEN_TOKEN_TABLE_GENERATOR_HPP

#include <iosfwd>
#include <limits>
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
     * correspond to
     */
    class TokenMap
    {
    public:
        static constexpr signed char   INVALID_DIGIT = -1;
        static constexpr unsigned char MAX_DIGIT =
            std::numeric_limits<signed char>::max();

        /**
         * @brief Map @p token to @p digit.
         *
         * @param[in] token a token of an ASCII string of digits
         * @param[in] digit the value @p token represents
         *
         * @pre `digit <= MAX_DIGIT`
         * @throws std::invalid_argument if @p digit exceeds MAX_DIGIT
         */
        void
        map_token(char token, unsigned char digit);

        /**
         * @brief Retrieve the digit value associated with @p token.
         *
         * @param[in] token a token of an ASCII string of digits
         * @return the associated digit or INVALID_DIGIT if @p token has no
         *     associated digit
         */
        signed char
        digit_from_token(char token) const;

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
    generate_header(std::ostream &output);

    /**
     * @brief Generates the source file contents defining the named
     * tasty_int::detail::TokenTable.
     *
     * @param[out] output destination where the file contents will be written
     */
    void
    generate_source(const TokenMap &token_map,
                    std::ostream   &output);

private:
    void
    put_open_namespaces(std::ostream &output) const;

    void
    put_close_namespaces(std::ostream &output) const;

    void
    put_source_head(std::ostream &output) const;

    void
    put_token_table_definition(const TokenMap &token_map,
                               std::ostream   &output);

    void
    put_token_table_entries(const TokenMap &token_map,
                            std::ostream   &output);

    void
    put_token_table_entry_row(
        const TokenMap                        &token_map,
        std::pair<unsigned int, unsigned int>  token_range,
        std::ostream                          &output
    );

    void
    put_token_table_entry(const TokenMap &token_map,
                          unsigned int    token,
                          std::ostream   &output);

    std::string_view token_table_name;
}; // class TokenTableGenerator

} // namespace token_table_codegen
} // namespace detail
} // namespace tasty_int

#endif // ifndef TASTY_INT_TASTY_INT_DETAIL_TOKEN_TABLE_CODEGEN_TOKEN_TABLE_GENERATOR_HPP
