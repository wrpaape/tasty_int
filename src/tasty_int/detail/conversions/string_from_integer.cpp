#include "tasty_int/detail/conversions/string_from_integer.hpp"

#include <cassert>
#include <cmath>

#include <iterator>

#include "tasty_int/detail/conversions/base_36_token_from_value.hpp"
#include "tasty_int/detail/conversions/base_64_token_from_value.hpp"
#include "tasty_int/detail/conversions/codegen/digits_per_token_table.hpp"
#include "tasty_int/detail/conversions/ensure_base_is_supported.hpp"
#include "tasty_int/detail/conversions/token_values_from_digits.hpp"


namespace tasty_int {
namespace detail {
namespace conversions {
namespace {

/**
 * This class converts a tasty_int::detail::Integer to a string of tokens
 * presented according to the provided base.
 */
class StringConverter
{
public:
    /**
     * @brief Constructor.
     *
     * @param[in] base the numeric base/radix in which the output to
     *     convert_to_string() is presented
     *
     * @pre @p base is a supported numeric base
     */
    StringConverter(unsigned int base);

    /**
     * @brief Converts @p digits to a little-endian sequence of token values in
     *     base @p base.
     *
     * @param[in] integer an arbitrary-precision integer
     * @return the string representation of @p integer in base @p base
     */
    std::string
    convert_to_string(const Integer &integer) const;

private:
    static float
    get_token_values_per_digit(unsigned int base);

    std::string
    allocate_token_buffer(
        unsigned int                       length_prefix,
        std::vector<digit_type>::size_type count_digits
    ) const;

    std::string::size_type
    size_tokens(unsigned int                       length_prefix,
                std::vector<digit_type>::size_type count_digits) const;

    std::string::size_type
    max_count_token_values_from_count_digits(
        std::vector<digit_type>::size_type count_digits
    ) const;

    void
    emplace_minus_token(std::string &token_buffer) const;

    void
    emplace_digit_tokens(std::string::iterator left_cursor,
                         std::string::iterator right_cursor) const;


    const float                   token_values_per_digit;
    const unsigned int            token_base;
    char                  (*const token_from_value)(unsigned int);
}; // class StringConverter


StringConverter::StringConverter(unsigned int base)
    : token_values_per_digit(get_token_values_per_digit(base))
    , token_base(base)
    , token_from_value((base <= 36) ? base_36_token_from_value
                                    : base_64_token_from_value)
{}

float
StringConverter::get_token_values_per_digit(unsigned int base)
{
    assert(base >= 2);
    assert(base <= 64);

    return 1.0f / codegen::DIGITS_PER_TOKEN_TABLE[base];
}

std::string
StringConverter::convert_to_string(const Integer &integer) const
{
    unsigned int integer_is_negative = (integer.sign == Sign::NEGATIVE);
    std::string token_buffer = allocate_token_buffer(integer_is_negative,
                                                     integer.digits.size());

    token_values_from_digits(integer.digits, token_base,
                             token_buffer);

    if (integer_is_negative)
        emplace_minus_token(token_buffer);

    emplace_digit_tokens(std::next(token_buffer.begin(), integer_is_negative),
                         std::prev(token_buffer.end(),   integer_is_negative));

    // ensure the initial sizing was correct:
    assert(
       (  size_tokens(integer_is_negative, integer.digits.size())
        - token_buffer.size()) < size_tokens(integer_is_negative, 1)
    );

    return token_buffer;
}

std::string
StringConverter::allocate_token_buffer(
    unsigned int                       length_prefix,
    std::vector<digit_type>::size_type count_digits
) const
{
    std::string tokens;
    tokens.reserve(size_tokens(length_prefix, count_digits));
    return tokens;
}

std::string::size_type
StringConverter::size_tokens(
    unsigned int                       length_prefix,
    std::vector<digit_type>::size_type count_digits
) const
{
    return length_prefix
         + max_count_token_values_from_count_digits(count_digits);
}

std::string::size_type
StringConverter::max_count_token_values_from_count_digits(
    std::vector<digit_type>::size_type count_digits
) const
{
    return static_cast<std::string::size_type>(
        std::floor(token_values_per_digit * count_digits)
    ) + 1;
}

void
StringConverter::emplace_minus_token(std::string &token_buffer) const
{
    char least_significant_token = token_from_value(token_buffer.front());
    token_buffer.push_back(least_significant_token);
    token_buffer.front() = '-';
}

void
StringConverter::emplace_digit_tokens(std::string::iterator left_cursor,
                                      std::string::iterator right_cursor) const
{
    while (left_cursor <= --right_cursor) {
        char left_token  = token_from_value(*right_cursor);
        char right_token = token_from_value(*left_cursor);

        *right_cursor = right_token;
        *left_cursor  = left_token;

        ++left_cursor;
    }
}

} // namespace


std::string
string_from_integer(const Integer &integer,
                    unsigned int   base)
{
    ensure_base_is_supported(base);

    StringConverter string_converter(base);

    return string_converter.convert_to_string(integer);
}

} // namespace conversions
} // namespace detail
} // namespace tasty_int
