#include "tasty_int/detail/digits_division.hpp"

#include <cassert>

#include <algorithm>
#include <array>
#include <iterator>
#include <utility>

#include "tasty_int/detail/digit_from_nonnegative_value.hpp"
#include "tasty_int/detail/flip_sign.hpp"
#include "tasty_int/detail/is_zero.hpp"
#include "tasty_int/detail/trailing_zero.hpp"
#include "tasty_int/detail/split_digits.hpp"
#include "tasty_int/detail/next_power_of_two.hpp"
#include "tasty_int/detail/digits_comparison.hpp"
#include "tasty_int/detail/digits_bitwise.hpp"
#include "tasty_int/detail/digits_addition.hpp"
#include "tasty_int/detail/digits_subtraction.hpp"
#include "tasty_int/detail/digits_multiplication.hpp"


namespace tasty_int {
namespace detail {
namespace {

void
multiply_digit_base_accumulate_in_place(digit_type               addend,
                                        std::vector<digit_type> &result)
{
    result <<= 1;

    result.front() = addend;
}

digit_type
estimate_digit_quotient(const std::vector<digit_type> &divisor,
                        const std::vector<digit_type> &dividend)
{
    assert((dividend.size() - divisor.size()) <= 1);

    digit_accumulator_type sig_dividend = dividend.back();
    if (dividend.size() > divisor.size()) {
        sig_dividend <<= DIGIT_TYPE_BITS;
        sig_dividend  |= *std::next(dividend.rbegin());
    }
    digit_accumulator_type sig_divisor = divisor.back();

    auto tentative_quotient = sig_dividend / sig_divisor;
    if (tentative_quotient > DIGIT_TYPE_MAX)
        tentative_quotient = DIGIT_TYPE_MAX;

    return digit_from_nonnegative_value(tentative_quotient);
}

std::pair<digit_type, std::vector<digit_type>>
quotient_divisor_product(digit_type                     tentative_quotient,
                         const std::vector<digit_type> &divisor,
                         const std::vector<digit_type> &dividend)
{
    auto product = divisor * std::uintmax_t(tentative_quotient);

    if (product > dividend) {
        [[maybe_unused]] auto sign = subtract_in_place(divisor, product);
        assert(sign >= Sign::ZERO);
        --tentative_quotient;

        if (product > dividend) {
            sign = subtract_in_place(divisor, product);
            assert(sign >= Sign::ZERO);
            --tentative_quotient;
        }
    }

    return { tentative_quotient, std::move(product) };
}

digit_type
divide_similar_magnitude_in_place(const std::vector<digit_type> &divisor,
                                  std::vector<digit_type>       &dividend)
{
    if (dividend.size() < divisor.size())
        return 0;

    auto tentative_quotient = estimate_digit_quotient(divisor, dividend);

    auto [quotient, product] = quotient_divisor_product(tentative_quotient,
                                                        divisor,
                                                        dividend);

    [[maybe_unused]] auto sign = subtract_in_place(product,
                                                   dividend);
    assert(sign >= Sign::ZERO);

    return quotient;
}

void
build_reversed_quotient(const std::vector<digit_type> &dividend,
                        const std::vector<digit_type> &divisor,
                        DigitsDivisionResult          &result)
{
    auto &quotient  = result.quotient;
    auto &remainder = result.remainder;

    auto dividend_cursor = dividend.rbegin();
    do {
        multiply_digit_base_accumulate_in_place(*dividend_cursor, remainder);

        auto quotient_digit = divide_similar_magnitude_in_place(divisor,
                                                                remainder);
        quotient.emplace_back(quotient_digit);
    } while (++dividend_cursor != dividend.rend());
}

void
correct_reversed_quotient(std::vector<digit_type> &quotient)
{
    std::reverse(quotient.begin(), quotient.end());

    trim_trailing_zeros(quotient);
}

bool
is_odd(std::vector<digit_type>::size_type value)
{
    return (value & 1) != 0;
}

bool
is_divide_and_conquer_divide_base_case(
    std::vector<digit_type>::size_type divisor_size
)
{
    /// @todo TODO: tune
    constexpr std::vector<digit_type>::size_type
        LONG_DIVIDE_THRESHOLD_DIVISOR_SIZE = 32;

    return is_odd(divisor_size)
        || (divisor_size <= LONG_DIVIDE_THRESHOLD_DIVISOR_SIZE);
}

void
append_2n_1n_split_piece(
    const std::vector<digit_type>      &piece,
    std::vector<digit_type>::size_type  split_size,
    std::vector<digit_type>            &digits
)
{
    if (!is_zero(piece)) {
        digits.resize(split_size);
        digits.insert(digits.end(),
                      piece.begin(),
                      piece.end());
    }
}

DigitsDivisionResult
divide_normalized_3n_2n_split_upper(std::vector<digit_type> &&dividend_upper,
                                    std::vector<digit_type> &&divisor_high)
{
    DigitsDivisionResult result;

    result.quotient.assign(divisor_high.size(), DIGIT_TYPE_MAX);

    dividend_upper += divisor_high;

    divisor_high <<= divisor_high.size();
    [[maybe_unused]] auto sign = subtract_in_place(divisor_high,
                                                   dividend_upper);
    assert(sign >= Sign::ZERO);

    result.remainder = std::move(dividend_upper);

    return result;
}

Sign
divide_normalized_3n_2n_split_lower(
    const std::vector<digit_type>      &dividend_low,
    const std::vector<digit_type>      &divisor_low,
    std::vector<digit_type>::size_type  split_size,
    DigitsDivisionResult               &result
)
{
    auto& remainder = result.remainder;
    auto& quotient  = result.quotient;

    remainder <<= split_size;
    remainder += dividend_low;

    auto remainder_sign = subtract_in_place(quotient * divisor_low,
                                            remainder);
    return remainder_sign;
}

void
correct_divide_normalized_3n_2n_split_remainder(
    Sign                           remainder_sign,
    const std::vector<digit_type> &divisor,
    DigitsDivisionResult          &result
)
{
    auto& remainder = result.remainder;
    auto& quotient  = result.quotient;

    while (remainder_sign < Sign::ZERO) {
        [[maybe_unused]] auto quotient_sign =
            subtract_in_place(std::uintmax_t(1), quotient);
        assert(quotient_sign >= Sign::ZERO);

        remainder_sign = subtract_in_place(divisor, remainder);
        remainder_sign = flip_sign(remainder_sign);
    }
}

DigitsShiftOffset
normal_shift_offset(const std::vector<digit_type>      &divisor,
                    std::vector<digit_type>::size_type  divisor_piece_mag)
{
    auto count_divisor_pieces =
        next_power_of_two(divisor.size() / divisor_piece_mag);
    auto normalized_divisor_mag = divisor_piece_mag * count_divisor_pieces;

    DigitsShiftOffset offset = {
        .digits = normalized_divisor_mag - divisor.size(),
        .bits   = count_leading_zero_bits_from_digit(divisor.back())
    };

    return offset;
}

std::size_t
ceil_divide(std::vector<digit_type>::size_type dividend,
            std::vector<digit_type>::size_type divisor)
{
    auto quotient  = (dividend / divisor);
    auto remainder = (dividend % divisor);

    return quotient + (remainder != 0);
}

bool
have_most_significant_one_bit(const std::vector<digit_type> &digits)
{
    constexpr digit_type MOST_SIGNIFICANT_DIGIT_BIT = DIGIT_BASE >> 1;

    return digits.back() >= MOST_SIGNIFICANT_DIGIT_BIT;
}

std::vector<digit_type>::size_type
padded_dividend_magnitude(const std::vector<digit_type> &normalized_dividend,
                          const std::vector<digit_type> &normalized_divisor)
{
    auto count_dividend_pieces = std::max<std::size_t>(
        2,
        ceil_divide(normalized_dividend.size(), normalized_divisor.size())
    );

    auto padded_magnitude = count_dividend_pieces * normalized_divisor.size();
    bool need_extra_piece = (padded_magnitude == normalized_dividend.size())
                         && have_most_significant_one_bit(normalized_dividend);

    if (need_extra_piece)
        padded_magnitude += normalized_divisor.size();

    return padded_magnitude;
}

void
append_reversed_quotient_piece(
    const std::vector<digit_type>      &quotient_piece,
    std::vector<digit_type>::size_type  divisor_mag,
    std::vector<digit_type>            &quotient
)
{
    quotient.insert(quotient.end(),
                    divisor_mag - quotient_piece.size(),
                    0);
    quotient.insert(quotient.end(),
                    quotient_piece.rbegin(),
                    quotient_piece.rend());
}

void
append_remainder_piece(const std::vector<digit_type> &remainder_piece,
                       std::vector<digit_type>       &remainder)
{
    remainder.insert(remainder.end(),
                     remainder_piece.begin(),
                     remainder_piece.end());
    trim_trailing_zeros(remainder);
}

DigitsDivisionResult
divide_and_conquer_divide_normalized(const std::vector<digit_type> &dividend,
                                     const std::vector<digit_type> &divisor)
{
    DigitsDivisionResult result;
    auto& quotient  = result.quotient;
    auto& remainder = result.remainder;

    auto dividend_offset =
        padded_dividend_magnitude(dividend, divisor)
        - (2 * divisor.size());

    auto dividend_cursor = dividend.begin() + dividend_offset;

    remainder.assign(dividend_cursor, dividend.end());

    while (true) {
        auto sub_result = divide_normalized_2n_1n_split(remainder, divisor);

        append_reversed_quotient_piece(sub_result.quotient,
                                       divisor.size(),
                                       quotient);

        if (dividend_cursor == dividend.begin()) {
            remainder = std::move(sub_result.remainder);
            break;
        }
        auto dividend_piece_end = dividend_cursor;
        dividend_cursor -= divisor.size();

        remainder.assign(dividend_cursor, dividend_piece_end);
        append_remainder_piece(sub_result.remainder, remainder);
    }

    correct_reversed_quotient(result.quotient);

    return result;
}

} // namespace


std::vector<digit_type>
divide_in_place(const std::vector<digit_type> &divisor,
                std::vector<digit_type>       &dividend)
{
    auto result = divide(dividend, divisor);

    dividend = std::move(result.quotient);

    return std::move(result.remainder);
}

DigitsDivisionResult
divide(const std::vector<digit_type> &dividend,
       const std::vector<digit_type> &divisor)
{
    DigitsDivisionResult result;

    if (divisor <= dividend) {
        result = divide_and_conquer_divide(dividend,
                                           divisor);
    } else {
        result.quotient  = { 0 };
        result.remainder = dividend;
    }

    return result;
}

DigitsDivisionResult
long_divide(const std::vector<digit_type> &dividend,
            const std::vector<digit_type> &divisor)
{
    assert(dividend.size() >= divisor.size());

    DigitsDivisionResult result;

    auto &quotient = result.quotient;
    auto max_quotient_size = dividend.size() + 1 - divisor.size();
    quotient.reserve(max_quotient_size);

    auto &remainder = result.remainder;
    auto max_remainder_size = divisor.size() + 1;
    remainder.reserve(max_remainder_size);
    remainder.emplace_back(0);

    build_reversed_quotient(dividend, divisor, result);

    correct_reversed_quotient(quotient);

    return result;
}

DigitsDivisionResult
divide_and_conquer_divide(const std::vector<digit_type> &dividend,
                          const std::vector<digit_type> &divisor)
{
    /// @todo: TODO: tune
    constexpr std::vector<digit_type>::size_type DIVISION_PIECE_MAGNITUDE = 32;

    if (divisor.size() < DIVISION_PIECE_MAGNITUDE)
        return long_divide(dividend, divisor);

    auto normal_offset = normal_shift_offset(divisor, DIVISION_PIECE_MAGNITUDE);

    auto normalized_dividend = dividend << normal_offset;
    auto normalized_divisor  = divisor  << normal_offset;

    assert(have_most_significant_one_bit(normalized_divisor));

    auto result = divide_and_conquer_divide_normalized(normalized_dividend,
                                                       normalized_divisor);

    result.remainder >>= normal_offset;

    assert(result.remainder < divisor);

    return result;
}

DigitsDivisionResult
divide_normalized_2n_1n_split(const std::vector<digit_type> &dividend,
                              const std::vector<digit_type> &divisor)
{
    assert(!dividend.empty());
    assert(!divisor.empty());
    assert(!have_trailing_zero(dividend));
    assert(!have_trailing_zero(divisor));

    if (is_divide_and_conquer_divide_base_case(divisor.size()))
        return long_divide(dividend, divisor);

    if (dividend < divisor)
        return { .quotient = { 0 }, .remainder = dividend };

    auto split_size = divisor.size() / 2;

    auto [dividend_low, dividend_high] = split_digits<2>(dividend, split_size);

    auto high_result = divide_normalized_3n_2n_split(dividend_high, divisor);

    append_2n_1n_split_piece(high_result.remainder, split_size, dividend_low);

    auto result = divide_normalized_3n_2n_split(dividend_low, divisor);

    append_2n_1n_split_piece(high_result.quotient, split_size, result.quotient);

    assert(result.remainder < divisor);

    return result;
}

DigitsDivisionResult
divide_normalized_3n_2n_split(const std::vector<digit_type> &dividend,
                              const std::vector<digit_type> &divisor)
{
    assert(!dividend.empty());
    assert(!divisor.empty());
    assert(!have_trailing_zero(dividend));
    assert(have_most_significant_one_bit(divisor));

    if (dividend < divisor)
        return { .quotient = { 0 }, .remainder = dividend };

    auto split_size = divisor.size() / 2;

    auto [dividend_low, dividend_upper] =
        split_digits<2>(dividend, split_size);

    auto [divisor_low, divisor_high] =
        split_digits<2>(divisor, split_size);


    auto dividend_high_begin = dividend.begin() + divisor.size();

    DigitsDivisionResult result = less_than(dividend_high_begin,
                                            dividend.end(),
                                            divisor_high.begin(),
                                            divisor_high.end())
        ? divide_normalized_2n_1n_split(dividend_upper,
                                        divisor_high)
        : divide_normalized_3n_2n_split_upper(std::move(dividend_upper),
                                              std::move(divisor_high));

    auto remainder_sign = divide_normalized_3n_2n_split_lower(dividend_low,
                                                              divisor_low,
                                                              split_size,
                                                              result);
    correct_divide_normalized_3n_2n_split_remainder(remainder_sign,
                                                    divisor,
                                                    result);
    assert(result.remainder < divisor);

    return result;
}

} // namespace detail
} // namespace tasty_int
