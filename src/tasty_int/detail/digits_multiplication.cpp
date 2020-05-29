#include "tasty_int/detail/digits_multiplication.hpp"

#include <cassert>

#include <algorithm>
#include <type_traits>
#include <utility>

#include "tasty_int/detail/digit_from_nonnegative_value.hpp"
#include "tasty_int/detail/is_zero.hpp"
#include "tasty_int/detail/trailing_zero.hpp"
#include "tasty_int/detail/order_by_size.hpp"
#include "tasty_int/detail/split_digits.hpp"
#include "tasty_int/detail/integral_digits_view.hpp"
#include "tasty_int/detail/digits_bitwise.hpp"
#include "tasty_int/detail/digits_addition.hpp"
#include "tasty_int/detail/digits_subtraction.hpp"
#include "tasty_int/detail/conversions/digits_from_floating_point.hpp"


namespace tasty_int {
namespace detail {
namespace {

std::vector<digit_type>
allocate_result(std::size_t lhs_size,
                std::size_t rhs_size)
{
    std::vector<digit_type> result(lhs_size + rhs_size);

    return result;
}

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
long_multiply_digit(const std::vector<digit_type> &lhs,
                    digit_type                    rhs_digit)
{
    auto result = allocate_result(lhs.size(), 1);

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

void
long_multiply_digits(const std::vector<digit_type> &lhs,
                     IntegralDigitsView             rhs_view,
                     std::vector<digit_type>       &result)
{
    auto result_cursor = result.begin();

    long_multiply_digit(lhs, rhs_view.low_digit(), result_cursor);

    if (rhs_view.digits_size() > 1)
        long_multiply_digit(lhs, rhs_view.high_digit(), ++result_cursor);
}

std::vector<digit_type>
karatsuba_multiply_trivial(const std::vector<digit_type> &smaller,
                           const std::vector<digit_type> &larger)
{
    if (smaller.front() > 1)
        return long_multiply_digit(larger, smaller.front());

    return (smaller.front() == 0) ? smaller : larger;
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

    auto [smaller_low, smaller_high] = split_digits<2>(smaller, split_size);
    auto [larger_low,  larger_high]  = split_digits<2>(larger,  split_size);

    struct KaratsubaPartiion result;

    result.split_size   = split_size;
    result.low_product  = smaller_low  * larger_low;
    result.high_product = smaller_high * larger_high;
    result.sum_product  = (smaller_low + smaller_high)
                        * (larger_low  + larger_high);

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

    result <<= split_size;

    result += low_product;

    high_product <<= (split_size * 2);

    result += high_product;

    assert((max_result_size - result.size()) <= 1);

    return std::move(result);
}

template<typename RhsType>
std::vector<digit_type> &
times_equals(std::vector<digit_type> &lhs,
             const RhsType           &rhs)
{
    lhs = lhs * rhs;

    return lhs;
}

} // namespace


std::vector<digit_type> &
operator*=(std::vector<digit_type>       &lhs,
           const std::vector<digit_type> &rhs)
{
    return times_equals(lhs, rhs);
}

std::vector<digit_type> &
operator*=(std::vector<digit_type> &lhs,
           std::uintmax_t           rhs)
{
    return times_equals(lhs, rhs);
}

std::vector<digit_type> &
operator*=(std::vector<digit_type> &lhs,
           long double              rhs)
{
    return times_equals(lhs, rhs);
}

std::vector<digit_type>
operator*(const std::vector<digit_type> &lhs,
          const std::vector<digit_type> &rhs)
{
    assert(!lhs.empty());
    assert(!have_trailing_zero(lhs));

    assert(!rhs.empty());
    assert(!have_trailing_zero(rhs));

    return karatsuba_multiply(rhs, lhs);
}

std::vector<digit_type>
operator*(const std::vector<digit_type> &lhs,
          std::uintmax_t                 rhs)
{
    assert(!lhs.empty());
    assert(!have_trailing_zero(lhs));

    if (rhs == 0)
        return { 0 };

    IntegralDigitsView rhs_view(rhs);

    auto result = allocate_result(lhs.size(), rhs_view.digits_size());

    long_multiply_digits(lhs, rhs_view, result);

    trim_trailing_zero(result);

    return result;
}

std::vector<digit_type>
operator*(std::uintmax_t                 lhs,
          const std::vector<digit_type> &rhs)
{
    return rhs * lhs;
}

std::vector<digit_type>
operator*(const std::vector<digit_type> &lhs,
          long double                    rhs)
{
    assert(std::isfinite(rhs));
    assert(rhs >= 0.0L);

    return lhs * conversions::digits_from_floating_point(rhs);
}

std::vector<digit_type>
operator*(long double                    lhs,
          const std::vector<digit_type> &rhs)
{
    return rhs * lhs;
}

std::vector<digit_type>
long_multiply(const std::vector<digit_type> &lhs,
              const std::vector<digit_type> &rhs)
{
    if (is_zero(lhs))
        return lhs;

    if (is_zero(rhs))
        return rhs;

    auto result = allocate_result(lhs.size(), rhs.size());

    long_multiply_digits(lhs, rhs, result);

    trim_trailing_zero(result);

    return result;
}

std::vector<digit_type>
karatsuba_multiply(const std::vector<digit_type> &lhs,
                   const std::vector<digit_type> &rhs)
{
    /// @todo TODO: tune
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
