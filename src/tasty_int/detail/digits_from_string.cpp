#include "tasty_int/detail/digits_from_string.hpp"

#include <cassert>
#include <cmath>

#include <array>
#include <stdexcept>
#include <string>
#include <utility>

#include "tasty_int/detail/codegen/digits_per_token_table.hpp"
#include "tasty_int/detail/digit_from_nonnegative_value.hpp"
#include "tasty_int/detail/ensure_base_is_supported.hpp"
#include "tasty_int/detail/value_from_base_36_token.hpp"
#include "tasty_int/detail/value_from_base_64_token.hpp"


namespace tasty_int {
namespace detail {
namespace {

/**
 * This class parses a little-endian sequence of digits from an input string of
 * tokens and base.
 */
class DigitsParser
{
public:
    /**
     * @brief Constructor.
     *
     * @param[in] base the numeric base/radix in which the input to
     *     parse_digits() is considered
     *
     * @pre @p base is a supported numeric base/radix
     */
    DigitsParser(unsigned int base);

    /**
     * @brief Parses a little-endian sequence of digits from @p tokens.
     *
     * @param[in] tokens a string of ASCII tokens representing digits numerical
     *     digits in base DigitsParser::token_base.
     *
     * @throw std::invalid_argument if @p tokens contains an out-of-bounds
     *     token for DigitsParser::token_base
     *
     * @pre @p tokens is not empty
     */
    std::vector<digit_type>
    parse_digits(std::string_view tokens) const;

private:
    static float
    get_digits_per_token(unsigned int base);

    std::pair<std::string_view::iterator, std::vector<digit_type>>
    parse_most_significant_token(std::string_view tokens) const;

    void
    accumulate_token(std::vector<digit_type> &digits,
                     char                     token) const;

    void
    accumulate_value(std::vector<digit_type> &digits,
                     digit_accumulator_type   value) const;

    std::pair<std::string_view::iterator, digit_accumulator_type>
    find_most_significant_value(std::string_view tokens) const; 

    std::vector<digit_type>
    allocate_digits(std::string_view::size_type count_significant_tokens) const;

    std::vector<digit_type>::size_type
    size_digits(std::string_view::size_type count_significant_tokens) const;

    digit_accumulator_type
    multiply_accumulate(std::vector<digit_type> &digits,
                        digit_accumulator_type   addend) const;

    digit_accumulator_type
    get_value_from_token(char token) const; 

    unsigned int          (*const value_from_token)(char);
    const digit_accumulator_type  token_base;
    const float                   digits_per_token;
}; // class DigitsParser


DigitsParser::DigitsParser(unsigned int base)
    : value_from_token((base <= 36) ? value_from_base_36_token
                                    : value_from_base_64_token)
    , token_base(base)
    , digits_per_token(get_digits_per_token(base))
{}

float
DigitsParser::get_digits_per_token(unsigned int base)
{
    assert(base >= 2);
    assert(base <= 64);

    return codegen::DIGITS_PER_TOKEN_TABLE[base];
}

std::vector<digit_type>
DigitsParser::parse_digits(std::string_view tokens) const
{
    assert(!tokens.empty());

    auto [cursor, digits] = parse_most_significant_token(tokens);

    for (auto tokens_end = tokens.end(); cursor != tokens_end; ++cursor)
        accumulate_token(digits, *cursor);

    // ensure the initial sizing was correct
    assert(
        (size_digits(tokens.end() + 1 -
                     find_most_significant_value(tokens).first) - digits.size())
        <= 1
    );

    return digits;
}

std::pair<std::string_view::iterator, std::vector<digit_type>>
DigitsParser::parse_most_significant_token(std::string_view tokens) const
{
    auto [cursor, most_sig_value] = find_most_significant_value(tokens);

    auto count_rem_sig_tokens = tokens.end() - cursor;
    auto count_sig_tokens     = 1 + count_rem_sig_tokens;

    auto digits = allocate_digits(count_sig_tokens);
    digits.emplace_back(static_cast<digit_type>(most_sig_value));

    return { cursor, std::move(digits) };
}

std::pair<std::string_view::iterator, digit_accumulator_type>
DigitsParser::find_most_significant_value(std::string_view tokens) const
{
    auto cursor     = tokens.begin();
    auto tokens_end = tokens.end();

    digit_accumulator_type most_significant_value;
    do {
        most_significant_value = get_value_from_token(*cursor);
    } while ((++cursor != tokens_end) && (most_significant_value == 0));

    return { cursor, most_significant_value };
}

std::vector<digit_type>
DigitsParser::allocate_digits(
    std::string_view::size_type count_significant_tokens
) const
{
    std::vector<digit_type> digits;
    digits.reserve(size_digits(count_significant_tokens));

    return digits;
}

std::vector<digit_type>::size_type
DigitsParser::size_digits(
    std::string_view::size_type count_significant_tokens
) const
{
    return static_cast<std::vector<digit_type>::size_type>(
        std::floor(digits_per_token * count_significant_tokens)
    ) + 1;
}

void
DigitsParser::accumulate_token(std::vector<digit_type> &digits,
                               char                     token) const
{
    digit_accumulator_type value = get_value_from_token(token);

    accumulate_value(digits, value);
}

void
DigitsParser::accumulate_value(std::vector<digit_type> &digits,
                               digit_accumulator_type   value) const
{
    digit_accumulator_type carry = multiply_accumulate(digits, value);

    if (carry > 0) {
        // carry from the last multiplication => do not need to truncate
        assert(carry <= DIGIT_TYPE_MAX);
        digits.emplace_back(static_cast<digit_type>(carry));
    }
}

digit_accumulator_type
DigitsParser::multiply_accumulate(std::vector<digit_type> &digits,
                                  digit_accumulator_type   addend) const
{
    for (digit_type &digit : digits) {
        digit_accumulator_type accumulator = digit;
        accumulator *= token_base;
        accumulator += addend;
        digit = digit_from_nonnegative_value(accumulator);
        addend = accumulator >> DIGIT_TYPE_BITS;
    }

    return addend;
}

digit_accumulator_type
DigitsParser::get_value_from_token(char token) const
{
    unsigned int value = value_from_token(token);
    if (value < token_base)
        return static_cast<digit_accumulator_type>(value);

    throw std::invalid_argument(
        std::string("tasty_int::detail::digits_from_string - invalid token ('")
      + token + "'): Token is not within the set of characters for specified "
        "base (" + std::to_string(token_base) + ")."
    );
}

} // namespace


std::vector<digit_type>
digits_from_string(std::string_view tokens,
                   unsigned int     base)
{
    assert(!tokens.empty());

    ensure_base_is_supported(base);

    DigitsParser digits_parser(base);

    return digits_parser.parse_digits(tokens);
}

} // namespace detail
} // namespace tasty_int
