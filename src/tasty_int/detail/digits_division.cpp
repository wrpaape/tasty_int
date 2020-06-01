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
        // LONG_DIVIDE_THRESHOLD_SPLIT_SIZE = 100;
        LONG_DIVIDE_THRESHOLD_SPLIT_SIZE = 1;

    return is_odd(divisor_size)
        || (divisor_size <= LONG_DIVIDE_THRESHOLD_SPLIT_SIZE);
}

DigitsDivisionResult
divide_normalized_3n_2n_split_upper(
    std::vector<digit_type> &&dividend_upper,
    std::vector<digit_type> &&divisor_high
)
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
    const std::vector<digit_type> &dividend_low,
    const std::vector<digit_type> &divisor_low,
    DigitsDivisionResult          &result
)
{
    auto& remainder = result.remainder;
    auto& quotient  = result.quotient;

    remainder <<= divisor_low.size();
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

std::size_t
ceil_divide(std::size_t dividend,
            std::size_t divisor)
{
    auto div = (dividend / divisor);
    auto rem = (dividend % divisor);

    return div + (rem != 0);
}

DigitsDivisionResult
divide_and_conquer_divide(const std::vector<digit_type> &dividend,
                          const std::vector<digit_type> &divisor)
{
    /// @todo: TODO: tune
    constexpr std::vector<digit_type>::size_type
        // COUNT_DIVISION_BLOCKS = 100;
        COUNT_DIVISION_BLOCKS = 1;

    if (divisor.size() < COUNT_DIVISION_BLOCKS)
        return long_divide(dividend, divisor);

    auto count_divisor_pieces =
        next_power_of_two(divisor.size() / COUNT_DIVISION_BLOCKS);
    auto divisor_piece_mag = ceil_divide(divisor.size(), count_divisor_pieces);
    auto normalized_divisor_mag = divisor_piece_mag * count_divisor_pieces;

    DigitsShiftOffset normal_shift_offset = {
        .digits = normalized_divisor_mag - divisor.size(),
        .bits   = count_leading_zero_bits_from_digit(divisor.back())
    };
    auto normalized_dividend = dividend << normal_shift_offset;
    auto normalized_divisor  = divisor  << normal_shift_offset;
    assert(count_leading_zero_bits_from_digit(normalized_divisor.back()) == 0);

    auto count_dividend_pieces = std::max<std::size_t>(
        2,
        ceil_divide(normalized_dividend.size(), normalized_divisor_mag)
    );

    auto padded_dividend_mag = count_dividend_pieces * normalized_divisor_mag;
    if ((padded_dividend_mag == normalized_dividend.size()) &&
        (count_leading_zero_bits_from_digit(normalized_dividend.back()) == 0)) {
        padded_dividend_mag += normalized_divisor_mag;
        ++count_dividend_pieces;
    }

    DigitsDivisionResult result;
    auto& quotient  = result.quotient;
    auto& remainder = result.remainder;

    auto normalized_divisor_offset = padded_dividend_mag
                                   - (2 * normalized_divisor_mag);

    remainder.assign(normalized_dividend.begin() + normalized_divisor_offset,
                     normalized_dividend.end());

    std::vector<std::vector<digit_type>> quotients;
    quotients.reserve(count_dividend_pieces - 1);
    std::vector<digit_type>::size_type quotient_mag = 0;

    while (true) {
        auto sub_result = divide_normalized_2n_1n_split(remainder,
                                                        normalized_divisor);
        quotient_mag += sub_result.quotient.size();
        quotients.emplace_back(std::move(sub_result.quotient));

        if (normalized_divisor_offset == 0) {
            remainder = std::move(sub_result.remainder);
            remainder >>= normal_shift_offset;
            break;
        }
        normalized_divisor_offset -= normalized_divisor_mag;

        auto cursor = normalized_dividend.begin() + normalized_divisor_offset;
        remainder.assign(cursor, cursor + normalized_divisor_mag);
        remainder.insert(remainder.end(),
                         sub_result.remainder.begin(),
                         sub_result.remainder.end());
        trim_trailing_zeros(remainder);
    }

    // TODO: wrong
    quotient.reserve(quotient_mag);
    for (auto cursor = quotients.rbegin(); cursor != quotients.rend(); ++cursor) {
        cursor->resize(normalized_divisor_mag);
        quotient.insert(quotient.end(),
                        cursor->begin(),
                        cursor->end());
    }

    trim_trailing_zeros(quotient);

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

    auto high_result =
        divide_normalized_3n_2n_split(dividend_high, divisor);

    auto& high_remainder = high_result.remainder;
    if (!is_zero(high_remainder)) {
        dividend_low.resize(split_size);
        dividend_low.insert(dividend_low.end(),
                            high_remainder.begin(),
                            high_remainder.end());
    }

    auto result =
        divide_normalized_3n_2n_split(dividend_low, divisor);

    auto& quotient            = result.quotient;
    const auto& high_quotient = high_result.quotient;
    if (!is_zero(high_quotient)) {
        quotient.resize(split_size);
        quotient.insert(quotient.end(),
                        high_quotient.begin(),
                        high_quotient.end());
    }

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
    assert(divisor.back() >= (DIGIT_BASE / 2));

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
                                                              result);
    correct_divide_normalized_3n_2n_split_remainder(remainder_sign,
                                                    divisor,
                                                    result);
    assert(result.remainder < divisor);

    return result;
}



} // namespace detail
} // namespace tasty_int
