#include "tasty_int/detail/conversions/token_values_from_digits.hpp"

#include <cassert>

#include <limits>


namespace tasty_int {
namespace detail {
namespace conversions {
namespace {

/**
 * This class converts a little-endian sequence of digits to a little-endian
 * sequence of values according to the provided base.
 */
class TokenValuesConverter
{
public:
    /**
     * @brief Constructor.
     *
     * @param[in] base the numeric base/radix in which the output to
     *     convert_to_token_values() is presented
     *
     * @pre `(base >= 2) && (base <= (std::numeric_limits<char>::max() + 1))`
     */
    TokenValuesConverter(unsigned int base);

    /**
     * @brief Converts @p digits to a little-endian sequence of token values in
     *     base @p base.
     *
     * @param[in]  digits       a little-endian sequence of digits
     * @param[out] token_values @p digits converted to base @base
     *
     * @pre @p digits is not empty
     * @pre @p token_values is empty
     */
    void
    convert_to_token_values(const std::vector<digit_type> &digits,
                            std::string                   &token_values) const;

private:
    void
    accumulate_digit(std::string &token_values,
                     digit_type   digit) const;

    digit_accumulator_type
    multiply_accumulate(std::string            &token_values,
                        digit_accumulator_type  addend) const;

    const digit_accumulator_type token_base;
}; // class TokenValuesConverter


TokenValuesConverter::TokenValuesConverter(unsigned int base)
    : token_base(base)
{
    assert(base >= 2);
    assert(base <= (std::numeric_limits<char>::max() + 1u));
}

void
TokenValuesConverter::convert_to_token_values(
    const std::vector<digit_type> &digits,
    std::string                   &token_values
) const
{
    assert(!digits.empty());
    assert(token_values.empty());

    token_values.push_back('\0');

    for(auto cursor = digits.rbegin(); cursor != digits.rend(); ++cursor)
        accumulate_digit(token_values, *cursor);
}

void
TokenValuesConverter::accumulate_digit(std::string &token_values,
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
TokenValuesConverter::multiply_accumulate(std::string            &token_values,
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

} // namespace


void
token_values_from_digits(const std::vector<digit_type> &digits,
                         unsigned int                   base,
                         std::string                   &token_values)
{
    TokenValuesConverter token_values_converter(base);

    token_values_converter.convert_to_token_values(digits, token_values);
}

} // namespace conversions
} // namespace detail
} // namespace tasty_int
