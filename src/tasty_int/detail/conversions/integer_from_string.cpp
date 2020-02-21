#include "tasty_int/detail/conversions/integer_from_string.hpp"

#include <cctype>

#include <algorithm>
#include <stdexcept>

#include "tasty_int/detail/conversions/base_prefix_from_string.hpp"
#include "tasty_int/detail/conversions/digits_from_string.hpp"


namespace tasty_int {
namespace detail {
namespace conversions {
namespace {

/**
 * This class parses a tasty_int::detail::Integer from an input string of tokens
 * and base.
 */
class IntegerParser
{
public:
    /**
     * @brief Constructor.
     *
     * @param[in] input      a string of ASCII tokens
     * @param[in] input_base the numeric base/radix in which @p tokens is
     *     interpretted
     */
    IntegerParser(std::string_view input,
                  unsigned int     input_base);

    /**
     * @brief Parses a tasty_int::detail::Integer from the provided input.
     *
     * @detail Leading whitespace is ignored.  If input base is zero, the
     *     correct base is determined from the leading tokens a la
     *     tasty_int::detail::conversions::base_prefix_from_string().
     *
     * @return tasty_int::detail::Integer representation of the input
     *
     * @throw std::invalid_argument if input tokens contains no digits
     * @throw std::invalid_argument if input base is not a supported
     *     numerical base or zero.
     * @throw std::invalid_argument if input contains an out-of-bounds token
     *     for the provided (or interpretted) base
     */
    Integer
    parse_integer();

private:
    void
    remove_leading_whitespace();

    std::string_view::size_type
    leading_whitespace_length() const;

    bool
    token_base_supports_sign_prefix() const;

    Sign
    parse_sign();

    bool
    have_leading_sign() const;

    static bool
    is_sign_token(char token);

    Sign
    get_leading_sign() const;

    static Sign
    sign_from_token(char token);

    void
    remove_leading_sign();

    void
    parse_token_base();

    bool
    have_base_prefix(unsigned int interpretted_base) const;

    void
    remove_prefix(std::string_view::size_type prefix_length);

    void
    ensure_tokens_are_nonempty() const;

    static bool
    is_zero(const std::vector<digit_type> &digits);

    std::string_view tokens;
    unsigned int     token_base;
}; // class IntegerParser

IntegerParser::IntegerParser(std::string_view input,
                             unsigned int     input_base)
    : tokens(input)
    , token_base(input_base)
{}

Integer
IntegerParser::parse_integer()
{
    Integer result;
    result.sign = Sign::POSITIVE;

    remove_leading_whitespace();

    if (token_base_supports_sign_prefix()) {
        result.sign = parse_sign();
        parse_token_base();
    }

    result.digits = digits_from_string(tokens, token_base);

    if (is_zero(result.digits))
        result.sign = Sign::ZERO;

    return result;
}

void
IntegerParser::remove_leading_whitespace()
{
    remove_prefix(leading_whitespace_length());
}

std::string_view::size_type
IntegerParser::leading_whitespace_length() const
{
    auto end_of_whitespace = std::find_if_not(
        tokens.begin(),
        tokens.end(),
        [](char token)
        {
            return std::isspace(static_cast<unsigned char>(token));
        }
    );

    return end_of_whitespace - tokens.begin();
}

bool
IntegerParser::token_base_supports_sign_prefix() const
{
    // base 63 and 64 reserve '+' => all other bases support an explicit sign
    return token_base <= 62;
}

Sign
IntegerParser::parse_sign()
{
    Sign sign = Sign::POSITIVE;

    if (have_leading_sign()) {
        sign = get_leading_sign();
        remove_leading_sign();
    }

    return sign;
}

bool
IntegerParser::have_leading_sign() const
{
    return is_sign_token(tokens.front());
}

bool
IntegerParser::is_sign_token(char token)
{
    return (token == '-') | (token == '+');
}

Sign
IntegerParser::get_leading_sign() const
{
   return sign_from_token(tokens.front());
}

Sign
IntegerParser::sign_from_token(char token)
{
    return (token == '-') ? Sign::NEGATIVE : Sign::POSITIVE;
}

void
IntegerParser::remove_leading_sign()
{
    remove_prefix(1);
}

void
IntegerParser::parse_token_base()
{
    BasePrefix base_prefix = base_prefix_from_string(tokens);
    if (have_base_prefix(base_prefix.base)) {
        remove_prefix(base_prefix.prefix_length);
        token_base = base_prefix.base;
    }
}

bool
IntegerParser::have_base_prefix(unsigned int interpretted_base) const
{
    return (token_base == 0)
        || (token_base == interpretted_base);
}

void
IntegerParser::remove_prefix(std::string_view::size_type prefix_length)
{
    tokens.remove_prefix(prefix_length);
    ensure_tokens_are_nonempty();
}

void
IntegerParser::ensure_tokens_are_nonempty() const
{
    if (tokens.empty())
        throw std::invalid_argument(
            "tasty_int::detail::conversions::integer_from_string - empty tokens"
        );
}

bool
IntegerParser::is_zero(const std::vector<digit_type> &digits)
{
    return (digits.size() == 1) && (digits.front() == 0);
}

} // namespace


Integer
integer_from_string(std::string_view tokens,
                    unsigned int     base)
{
    IntegerParser integer_parser(tokens, base);

    return integer_parser.parse_integer();
}

} // namespace conversions
} // namespace detail
} // namespace tasty_int
