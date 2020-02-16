#include "tasty_int/detail/string_from_digits.hpp"

#include <cassert>
#include <cmath>

#include "tasty_int/detail/base_36_token_from_value.hpp"
#include "tasty_int/detail/base_64_token_from_value.hpp"
#include "tasty_int/detail/codegen/digits_per_token_table.hpp"


namespace tasty_int {
namespace detail {
namespace {

/**
 * This class parses a little-endian sequence of digits from an input string of
 * digits and base.
 */
class StringParser
{
public:
    /**
     * @brief Constructor.
     *
     * @param[in] base the numeric base/radix in which the input to
     *     parse_string() is considered
     *
     * @pre @p base is a supported numeric base/radix
     */
    StringParser(unsigned int base);

    /**
     * @brief Parses a little-endian sequence of digits from @p digits.
     *
     * @param[in] digits a string of ASCII digits representing digits numerical
     *     digits in base StringParser::token_base.
     *
     * @throw std::invalid_argument if @p digits contains an out-of-bounds
     *     digit for StringParser::token_base
     *
     * @pre @p digits is not empty
     */
    std::string
    parse_string(const std::vector<digit_type> &digits) const;

private:
    static float
    get_tokens_per_digit(unsigned int base);

    std::string
    allocate_token_values(
        std::vector<digit_type>::size_type count_digits
    ) const;

    std::string::size_type
    size_token_values(std::vector<digit_type>::size_type count_digits) const;

    void
    accumulate_digit(std::string &token_values,
                     digit_type   digit) const;

    digit_accumulator_type
    multiply_accumulate(std::string            &token_values,
                        digit_accumulator_type  addend) const;

    void
    reverse_and_tokenize(std::string &token_values) const;

    const digit_accumulator_type  token_base;
    float                         tokens_per_digit;
    char                  (*const token_from_value)(unsigned int);
}; // class StringParser


StringParser::StringParser(unsigned int base)
    : token_base(base)
    , tokens_per_digit(get_tokens_per_digit(base))
    , token_from_value((base <= 36) ? base_36_token_from_value
                                    : base_64_token_from_value)
{}

float
StringParser::get_tokens_per_digit(unsigned int base)
{
    assert(base >= 2);
    assert(base <= 64);

    return 1.0f / codegen::DIGITS_PER_TOKEN_TABLE[base];
}

std::string
StringParser::parse_string(const std::vector<digit_type> &digits) const
{
    assert(!digits.empty());

    std::string token_values = allocate_token_values(digits.size());

    for(auto cursor = digits.rbegin(); cursor != digits.rend(); ++cursor)
        accumulate_digit(token_values, *cursor);

    // ensure the initial sizing was correct:
    assert(
        ((token_values.capacity() - token_values.size())
         <= (std::floor(tokens_per_digit) + 1))
     || (token_values.capacity() == std::string().capacity())
    );

    reverse_and_tokenize(token_values);

    return token_values;
}

std::string
StringParser::allocate_token_values(
    std::vector<digit_type>::size_type count_digits
) const
{
    std::string token_values;
    token_values.reserve(size_token_values(count_digits));

    return token_values;
}

std::string::size_type
StringParser::size_token_values(
    std::vector<digit_type>::size_type count_digits
) const
{
    return static_cast<std::string::size_type>(
        std::floor(tokens_per_digit * count_digits)
    ) + 1;
}

void
StringParser::accumulate_digit(std::string &token_values,
                               digit_type   digit) const
{
    digit_accumulator_type carry = multiply_accumulate(token_values, digit);

    while (carry > 0) {
        char next_token_value = static_cast<char>(carry % token_base);
        carry /= token_base;

        token_values.push_back(next_token_value);
    }
}

digit_accumulator_type
StringParser::multiply_accumulate(std::string            &token_values,
                                  digit_accumulator_type  addend) const
{
    for (char &token_value : token_values) {
        digit_accumulator_type accumulator = token_value;

        accumulator <<= DIGIT_TYPE_BITS;
        accumulator  += addend;

        token_value = static_cast<char>(accumulator % token_base);
        addend      = (accumulator / token_base);
    }

    return addend;
}

void
StringParser::reverse_and_tokenize(std::string &token_values) const
{
    auto left_cursor  = token_values.begin();
    auto right_cursor = token_values.end();

    do {
        char left_token  = token_from_value(*--right_cursor);
        char right_token = token_from_value(*left_cursor);

        *right_cursor = right_token;
        *left_cursor  = left_token;
    } while (++left_cursor < right_cursor);
}

} // namespace


std::string
string_from_digits(const std::vector<digit_type> &digits,
                   unsigned int                   base)
{
    StringParser string_parser(base);

    return string_parser.parse_string(digits);
}

} // namespace detail
} // namespace tasty_int
