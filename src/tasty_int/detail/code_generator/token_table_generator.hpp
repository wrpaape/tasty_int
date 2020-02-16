#ifndef TASTY_INT_TASTY_INT_DETAIL_CODE_GENERATOR_TOKEN_TABLE_GENERATOR_HPP
#define TASTY_INT_TASTY_INT_DETAIL_CODE_GENERATOR_TOKEN_TABLE_GENERATOR_HPP

#include <limits>
#include <unordered_map>

#include "tasty_int/detail/code_generator/table_generator.hpp"


namespace tasty_int {
namespace detail {
namespace code_generator {

/**
 * This class generates C++ source code for lookup tables which may be used to
 * translate string tokens ('0', '2', 'A', etc...) into digit values (0, 2, 10,
 * etc...).  TokenTableGenerator uses tasty_int::detail::TokenTable as the
 * lookup table implementation.
 */
class TokenTableGenerator : public TableGenerator
{
public:
    /**
     * This class is used to configure the lookup table mapping.  Mapped tokens
     * correspond to ASCII characters that have an associated digit value.
     */
    class TokenMap
    {
    public:
        /**
         * ASCII tokens without a defined mapping will be mapped to this value
         * in the generated TokenTable.
         */
        static constexpr unsigned char INVALID_VALUE =
            std::numeric_limits<unsigned char>::max();

        /**
         * The maximum digit value allowed in the generated TokenTable.
         */
        static constexpr unsigned char MAX_VALUE = INVALID_VALUE - 1;

        /**
         * @brief Map @p token to @p value.
         *
         * @param[in] token an element of an ASCII string of digits
         * @param[in] value the value @p token represents
         *
         * @pre `value <= MAX_VALUE`
         * @throw std::invalid_argument if @p value exceeds MAX_VALUE
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
        unsigned char
        value_from_token(char token) const;

    private:
        std::unordered_map<char, unsigned char> mapping;
    }; // class TokenMap

    /**
     * This struct defines the configuration parameters for a
     * TokenTableGenerator.
     */
    struct TokenTableConfig
    {
        /**
         * The name of the generated table.
         */
        std::string_view name;

        /**
         * The mapping of ASCII token to digit value.
         */
        TokenMap token_map;
    }; // struct TokenTableConfig

    /**
     * @brief Constructor.
     *
     * @param[in] token_table_config the token table configuration parameters
     */
    TokenTableGenerator(const TokenTableConfig &token_table_config);

private:
    TokenMap token_map;
}; // class TokenTableGenerator

} // namespace code_generator
} // namespace detail
} // namespace tasty_int

#endif // ifndef TASTY_INT_TASTY_INT_DETAIL_CODE_GENERATOR_TOKEN_TABLE_GENERATOR_HPP
