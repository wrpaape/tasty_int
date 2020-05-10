#include "tasty_int/detail/digits_multiplication.hpp"

#include <cassert>

#include <algorithm>
#include <utility>

#include "tasty_int/detail/digit_from_nonnegative_value.hpp"
#include "tasty_int/detail/is_zero.hpp"
#include "tasty_int/detail/trailing_zero.hpp"
#include "tasty_int/detail/order_by_size.hpp"
#include "tasty_int/detail/digits_addition.hpp"
#include "tasty_int/detail/digits_subtraction.hpp"


namespace tasty_int {
namespace detail {
namespace {

void
long_multiply_digit(const std::vector<digit_type>    &lhs,
                    digit_type                        rhs_digit,
                    std::vector<digit_type>::iterator result_cursor)
{
    digit_accumulator_type carry = 0;

    for (auto lhs_digit : lhs) {
        digit_accumulator_type accumulator = lhs_digit;
        accumulator *= rhs_digit;
        accumulator += carry;
        accumulator += *result_cursor;

        *result_cursor++ = digit_from_nonnegative_value(accumulator);
        carry = accumulator >> DIGIT_TYPE_BITS;
    }

    *result_cursor = digit_from_nonnegative_value(carry);
}

std::vector<digit_type>
long_multiply_digit(const std::vector<digit_type>    &lhs,
                    digit_type                        rhs_digit)
{
    std::vector<digit_type> result(lhs.size() + 1);

    long_multiply_digit(lhs, rhs_digit, result.begin());

    trim_trailing_zero(result);

    return result;
}

void
long_multiply_digits(const std::vector<digit_type> &lhs,
                     const std::vector<digit_type> &rhs,
                     std::vector<digit_type>       &result)
{
    auto result_cursor = result.begin();

    for (auto rhs_digit : rhs)
        long_multiply_digit(lhs, rhs_digit, result_cursor++);
}

std::vector<digit_type>
karatsuba_multiply_trivial(const std::vector<digit_type> &smaller,
                           const std::vector<digit_type> &larger)
{
    if (smaller.front() > 1)
        return long_multiply_digit(larger, smaller.front());

    return (smaller.front() == 0) ? smaller : larger;
}

std::pair<std::vector<digit_type>, std::vector<digit_type>>
split(const std::vector<digit_type>      &digits,
      std::vector<digit_type>::size_type  index)
{

    auto split_at = digits.begin() + index;

    std::vector<digit_type> low(digits.begin(), split_at);
    while ((low.back() == 0) && (low.size() > 1))
        low.pop_back();

    std::vector<digit_type> high(split_at,      digits.end());

    return { std::move(low), std::move(high) };
}

void
multiply_digit_power(std::vector<digit_type>::size_type  digit_power,
                     std::vector<digit_type>            &multiplicand)
{
    auto initial_size = multiplicand.size();
    multiplicand.resize(initial_size + digit_power);

    auto initial_end = multiplicand.rbegin() + digit_power;

    std::swap_ranges(initial_end,
                     multiplicand.rend(),
                     multiplicand.rbegin());
}


struct KaratsubaPartiion
{
    std::vector<digit_type>::size_type split_size;
    std::vector<digit_type>            low_product;
    std::vector<digit_type>            high_product;
    std::vector<digit_type>            sum_product;
}; // struct KaratsubaPartiion

KaratsubaPartiion
karatsuba_partition(const std::vector<digit_type>      &smaller,
                    const std::vector<digit_type>      &larger,
                    std::vector<digit_type>::size_type  split_size)
{

    auto [smaller_low, smaller_high] = split(smaller, split_size);
    auto [larger_low,  larger_high]  = split(larger,  split_size);

    struct KaratsubaPartiion result;

    result.split_size   = split_size;
    result.low_product  = karatsuba_multiply(smaller_low, larger_low);
    result.high_product = karatsuba_multiply(smaller_high, larger_high);
    result.sum_product  = karatsuba_multiply(smaller_low + smaller_high,
                                             larger_low  + larger_high);

    return result;
}

std::vector<digit_type>
karatsuba_merge(KaratsubaPartiion                  &partition,
                std::vector<digit_type>::size_type  max_result_size)
{
    auto split_size    = partition.split_size;
    auto &low_product  = partition.low_product;
    auto &high_product = partition.high_product;
    auto &result       = partition.sum_product;

    result.reserve(max_result_size);

    [[maybe_unused]] auto sign1 = subtract_in_place(high_product, result);
    assert(sign1 >= Sign::ZERO);

    [[maybe_unused]] auto sign2 = subtract_in_place(low_product, result);
    assert(sign2 >= Sign::ZERO);

    multiply_digit_power(split_size, result);

    result += low_product;

    multiply_digit_power(split_size * 2, high_product);

    result += high_product;

    assert((max_result_size - result.size()) <= 1);

    return std::move(result);
}

} // namespace


std::vector<digit_type> &
operator*=(std::vector<digit_type>       &lhs,
           const std::vector<digit_type> &rhs)
{
    lhs = lhs * rhs;

    return lhs;
}

std::vector<digit_type> &
operator*=(std::vector<digit_type> &lhs,
           std::uintmax_t           rhs)
{
    return lhs; // TODO
}

std::vector<digit_type> &
operator*=(std::vector<digit_type> &lhs,
           long double              rhs)
{
    return lhs; // TODO
}

std::vector<digit_type>
operator*(const std::vector<digit_type> &lhs,
          const std::vector<digit_type> &rhs)
{
    // return karatsuba_multiply(rhs, lhs);
    return long_multiply(rhs, lhs);
}

std::vector<digit_type>
operator*(const std::vector<digit_type> &lhs,
          std::uintmax_t                 rhs)
{
    return lhs; // TODO
}

std::vector<digit_type>
operator*(std::uintmax_t                 lhs,
          const std::vector<digit_type> &rhs)
{
    return rhs; // TODO
}

std::vector<digit_type>
operator*(const std::vector<digit_type> &lhs,
          long double                    rhs)
{
    return lhs; // TODO
}

std::vector<digit_type>
operator*(long double                    lhs,
          const std::vector<digit_type> &rhs)
{
    return rhs; // TODO
}


std::vector<digit_type>
long_multiply(const std::vector<digit_type> &lhs,
              const std::vector<digit_type> &rhs)
{
    if (is_zero(lhs))
        return lhs;

    if (is_zero(rhs))
        return rhs;

    std::vector<digit_type> result(lhs.size() + rhs.size());

    long_multiply_digits(lhs, rhs, result);

    trim_trailing_zero(result);

    return result;
}

std::vector<digit_type>
karatsuba_multiply(const std::vector<digit_type> &lhs,
                   const std::vector<digit_type> &rhs)
{
    constexpr std::vector<digit_type>::size_type 
        LONG_MULTIPLY_THRESHOLD_MAGNTIUDE = 100;

    const auto &[smaller, larger] = order_by_size(lhs, rhs);

    if (larger.size() <= LONG_MULTIPLY_THRESHOLD_MAGNTIUDE)
        return long_multiply(smaller, larger);

    if (smaller.size() == 1)
        return karatsuba_multiply_trivial(smaller, larger);

    const auto split_size = smaller.size() / 2;

    auto &&partition = karatsuba_partition(smaller, larger, split_size);

    auto max_result_size = smaller.size() + larger.size();

    return karatsuba_merge(partition, max_result_size);
}

} // namespace detail
} // namespace tasty_int
