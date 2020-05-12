#include "tasty_int/detail/digits_division.hpp"

#include <cassert>

#include <algorithm>
#include <array>
#include <iterator>
#include <tuple>
#include <utility>

#include "tasty_int/detail/digits_comparison.hpp"
#include "tasty_int/detail/digits_addition.hpp"
#include "tasty_int/detail/digits_subtraction.hpp"
#include "tasty_int/detail/digits_multiplication.hpp"
#include "tasty_int/detail/digit_from_nonnegative_value.hpp"
#include "tasty_int/detail/is_zero.hpp"
#include "tasty_int/detail/trailing_zero.hpp"
#include "tasty_int/detail/conversions/digits_from_integral.hpp"


namespace tasty_int {
namespace detail {
namespace {

// TODO: remove
using SmallDigitBuffer = std::array<digit_type, 3>;

// TODO: remove
void
subtract_from_buffer(digit_type        subtrahend,
                     SmallDigitBuffer &minuend)
{
    if (subtrahend <= minuend.front()) {
        minuend.front() -= subtrahend;
        return;
    }

    if (minuend[1] > 0) {
        --minuend[1];
    } else {
        assert(minuend.back() > 0);
        --minuend.back();
        minuend[1] = DIGIT_TYPE_MAX;
    }

    digit_accumulator_type accumulator = minuend.front();
    accumulator += DIGIT_BASE;
    accumulator -= subtrahend;
    minuend.front() = digit_from_nonnegative_value(accumulator);
}

// TODO: remove
DigitsDivisionResult
barrett_reduction_division(const std::vector<digit_type> &dividend,
                           const std::vector<digit_type> &divisor)
{
    assert(!is_zero(divisor));

    auto magnitude_difference = dividend.size() - divisor.size();
    auto quotient_size = magnitude_difference + 1;
    std::vector<digit_type> quotient(quotient_size);
    auto remainder     = dividend;

    std::vector<digit_type> divisor_power(dividend.size());

    std::copy(divisor.begin(),
              divisor.end(),
              divisor_power.begin() + magnitude_difference);

    if (remainder >= divisor_power) {
        [[maybe_unused]] auto sign = subtract_in_place(divisor_power,
                                                       remainder);
        assert(sign >= Sign::ZERO);
        quotient.back() = 1;
    }

    assert(remainder < divisor_power);

    auto most_sig_divisor_digit = divisor.back();

    for (auto mag         = dividend.size() - 1,
              divisor_mag = divisor.size() - 1;
         mag > divisor_mag; --mag) {

        auto next_quotient_digit = DIGIT_TYPE_MAX;

        auto prev_remainder_digit = remainder[mag - 1];
        auto next_remainder_digit = remainder[mag];
        if (next_remainder_digit != most_sig_divisor_digit) {
            digit_accumulator_type accumulator = next_remainder_digit;
            accumulator *= DIGIT_BASE;
            accumulator += prev_remainder_digit;
            accumulator /= most_sig_divisor_digit;

            next_quotient_digit = digit_from_nonnegative_value(accumulator);
        }

        const SmallDigitBuffer rhs = {
            remainder[mag - 2], prev_remainder_digit, next_remainder_digit
        };

        SmallDigitBuffer lhs = {
            divisor[mag - 1], divisor[mag], 0
        };
        digit_accumulator_type carry = 0;
        for (auto& digit : lhs) {
            digit_accumulator_type accumulator = digit;
            accumulator *= next_quotient_digit;
            accumulator += carry;
            digit = digit_from_nonnegative_value(accumulator);
            carry = accumulator >> DIGIT_TYPE_BITS;
        }

        while (std::lexicographical_compare(rhs.rbegin(), rhs.rend(),
                                            lhs.rbegin(), lhs.rend())) {
               --next_quotient_digit;
               subtract_from_buffer(next_quotient_digit, lhs);
        }

        divisor_power.erase(divisor_power.end() - divisor.size() - 1);

        auto sign = subtract_in_place(divisor_power * next_quotient_digit,
                                      remainder);
        if (sign < Sign::ZERO) {
            remainder += divisor_power;
            --next_quotient_digit;
        }

        quotient[mag - 1 - divisor_mag] = next_quotient_digit;
    }

    return {
        .quotient = std::move(quotient), .remainder = std::move(remainder)
    };
}

bool
have_order_of_magnitude_difference(const std::vector<digit_type> &larger,
                                   const std::vector<digit_type> &smaller)
{
    auto magnitude_difference = larger.size() - smaller.size();

    return (magnitude_difference > 1)
        || ((magnitude_difference == 1) &&
            (larger.back() >= smaller.back()));
}

void
multiply_digit_base_accumulate_in_place(digit_type               addend,
                                        std::vector<digit_type> &result)
{
    multiply_digit_base_power_in_place(1, result);

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

bool
is_odd(std::vector<digit_type>::size_type value)
{
    return (value & 1) != 0;
}

bool
is_divide_and_conquer_divide_base_case(
    std::vector<digit_type>::size_type split_size
)
{
    /// @todo TODO: tune
    constexpr std::vector<digit_type>::size_type
        LONG_DIVIDE_THRESHOLD_SPLIT_SIZE = 100;

    return is_odd(split_size)
        || (split_size <= LONG_DIVIDE_THRESHOLD_SPLIT_SIZE);
}

DigitsDivisionResult
divide_and_conquer_divide_2_to_1_split(const std::vector<digit_type> &dividend,
                                       const std::vector<digit_type> &divisor)
{
    assert(dividend.size() >= divisor.size());

    auto split_size = std::max(dividend.size() + 1 - divisor.size(),
                               divisor.size());

    if (is_divide_and_conquer_divide_base_case(split_size))
        return long_divide(dividend, divisor);

    return {}; // TODO
}

#ifndef NDEBUG
bool
split_size_correct(std::vector<digit_type>::size_type digits_size,
                   std::vector<digit_type>::size_type split_size,
                   std::vector<digit_type>::size_type num_splits)

{
    auto [smaller, larger] = std::minmax(digits_size, split_size * num_splits);
    return (larger - smaller) <= 1;
}
#endif // ifndef NDEBUG

std::tuple<std::vector<digit_type>,
           std::vector<digit_type>,
           std::vector<digit_type>>
threeway_split(const std::vector<digit_type>      &digits,
               std::vector<digit_type>::size_type  split_size)
{
    assert(split_size_correct(digits.size(), split_size, 3));

    auto mid_begin  = digits.begin() + split_size;
    auto high_begin = mid_begin + split_size;

    std::vector<digit_type> low(digits.begin(), mid_begin);
    trim_trailing_zeros(low);
    std::vector<digit_type> mid(mid_begin,      high_begin);
    trim_trailing_zeros(mid);
    std::vector<digit_type> high(high_begin,    digits.end());

    return { std::move(low), std::move(mid), std::move(high) };
}

std::pair<std::vector<digit_type>, std::vector<digit_type>>
twoway_split(const std::vector<digit_type>      &digits,
             std::vector<digit_type>::size_type  split_size)
{
    assert(split_size_correct(digits.size(), split_size, 2));

    auto split_at = digits.begin() + split_size;

    std::vector<digit_type> low(digits.begin(), split_at);
    trim_trailing_zeros(low);
    std::vector<digit_type> high(split_at,      digits.end());

    return { std::move(low), std::move(high) };
}

DigitsDivisionResult
divide_and_conquer_divide_3_to_2_split(const std::vector<digit_type> &dividend,
                                       const std::vector<digit_type> &divisor)
{
    assert(dividend.size() < (divisor.size() * 3 / 2));

    auto split_size = divisor.size() / 2;
    auto [dividend_low, dividend_mid, dividend_high]
        = threeway_split(dividend, split_size);

    auto [divisor_low, divisor_high] = twoway_split(divisor, split_size);

    return {}; // TODO
}

DigitsDivisionResult
divide_and_conquer_divide(const std::vector<digit_type> &dividend,
                          const std::vector<digit_type> &divisor)
{
    return {}; // TODO
}

DigitsDivisionResult
long_divide_digit(const std::vector<digit_type> &dividend,
                  digit_type                     divisor)
{
    assert(divisor != 0);

    DigitsDivisionResult result;

    auto& quotient = result.quotient;
    quotient.reserve(dividend.size());

    auto dividend_cursor = dividend.rbegin();
    digit_accumulator_type accumulator = 0;

    do {
        accumulator <<= DIGIT_TYPE_BITS;
        accumulator  |= *dividend_cursor;

        auto next_quotient_digit = accumulator / divisor;
        accumulator %= divisor;

        quotient.emplace_back(
            digit_from_nonnegative_value(next_quotient_digit)
        );
    } while (++dividend_cursor != dividend.rend());

    std::reverse(quotient.begin(), quotient.end());

    trim_trailing_zero(quotient);

    result.remainder = { digit_from_nonnegative_value(accumulator) };

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
        result = long_divide(dividend, divisor);
        // result = (divisor.size() > 1)
        //        ? divide_and_conquer_divide(dividend,
        //                                    divisor)
        //        : long_divide_digit(dividend,
        //                            divisor.front());
    } else {
        result.quotient  = { 0 };
        result.remainder = dividend;
    }

    return result;
}

} // namespace detail
} // namespace tasty_int
