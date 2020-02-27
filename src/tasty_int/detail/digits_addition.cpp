#include "tasty_int/detail/digits_addition.hpp"

#include <cassert>
#include <cmath>

#include <algorithm>
#include <limits>
#include <utility>

#include "tasty_int/detail/digit_from_nonnegative_value.hpp"
#include "tasty_int/detail/size_digits_from_nonnegative_floating_point.hpp"
#include "tasty_int/detail/trim_trailing_zero.hpp"


namespace tasty_int {
namespace detail {
namespace {

std::pair<digit_accumulator_type, digit_accumulator_type>
split_integral(std::uintmax_t integral)
{
    return {
        digit_from_nonnegative_value(integral),
        digit_from_nonnegative_value(integral >> DIGIT_TYPE_BITS)
    };
}

void
pad_result(std::vector<digit_type>::size_type  addend_size,
           std::vector<digit_type>            &result)
{
    if (addend_size > result.size()) {
        result.reserve(addend_size + 1); // room for carry
        result.resize(addend_size);
    }
}

std::pair<const std::vector<digit_type> &, const std::vector<digit_type> &>
order_by_size(const std::vector<digit_type> &digits1,
              const std::vector<digit_type> &digits2)
{
    return std::minmax(digits1, digits2,
        [](const std::vector<digit_type> &lhs,
           const std::vector<digit_type> &rhs)
        {
            return lhs.size() < rhs.size();
        }
    );
}

std::vector<digit_type>
allocate_result(std::vector<digit_type>::size_type larger_addend_size)
{
    std::vector<digit_type> result;

    // up to one extra carry digit
    result.reserve(larger_addend_size + 1);

    return result;
}

std::vector<digit_type>
initialize_result(const std::vector<digit_type>      &digits_addend,
                  std::vector<digit_type>::size_type  larger_addend_size)
{
    std::vector<digit_type> result = allocate_result(digits_addend.size());

    result.assign(digits_addend.begin(), digits_addend.end());

    return result;
}

std::vector<digit_type>
initialize_result(const std::vector<digit_type> &digits_addend)
{
    return initialize_result(digits_addend, digits_addend.size());
}

std::vector<digit_type>
initialize_result_from_addends(
    const std::vector<digit_type> &digits_addend,
    long double                    floating_point_addend
)
{
    auto larger_addend_size = std::max(
        digits_addend.size(),
        size_digits_from_nonnegative_floating_point(floating_point_addend)
    );
    auto result = initialize_result(digits_addend, larger_addend_size);
    result.resize(larger_addend_size);

    return result;
}

digit_accumulator_type
add_into(digit_accumulator_type            addend,
         std::vector<digit_type>::iterator result_cursor)
{
    assert((std::numeric_limits<digit_accumulator_type>::max() - addend) >=
           *result_cursor);

    addend          += *result_cursor;
    *result_cursor   = digit_from_nonnegative_value(addend);
    addend         >>= DIGIT_TYPE_BITS;

    return addend;
}

std::pair<digit_accumulator_type, std::vector<digit_type>::iterator>
add_into(const std::vector<digit_type> &addend,
         std::vector<digit_type>       &result)
{
    digit_accumulator_type carry = 0;
    auto result_cursor              = result.begin();

    for (digit_type digit : addend) {
        carry += digit;

        carry = add_into(carry, result_cursor);

        ++result_cursor;
    }

    return { carry, result_cursor };
}

digit_accumulator_type
propagate_carry(digit_accumulator_type                  carry,
                std::vector<digit_type>::iterator       result_cursor,
                std::vector<digit_type>::const_iterator result_end)
{
    while ((carry > 0) && (result_cursor != result_end)) {
        carry = add_into(carry, result_cursor);

        ++result_cursor;
    }

    return carry;
}

void
append_carry_if_nonzero(digit_accumulator_type   carry,
                        std::vector<digit_type>& result)
{
    if (carry > 0)
        result.emplace_back(static_cast<digit_type>(carry));
}

void
add_into(digit_accumulator_type             addend,
         std::vector<digit_type>::iterator  result_cursor,
         std::vector<digit_type>           &result)
{
    addend = propagate_carry(addend, result_cursor, result.end());

    append_carry_if_nonzero(addend, result);
}

void
add(const std::vector<digit_type> &addend,
    std::vector<digit_type>       &result)
{
    auto [carry, lhs_cursor] = add_into(addend, result);

    add_into(carry, lhs_cursor, result);
}

void
add(digit_accumulator_type   rhs_low,
    digit_accumulator_type   rhs_high,
    std::vector<digit_type> &result)
{
    auto lhs_cursor = result.begin();

    auto carry = add_into(rhs_low, lhs_cursor);

    add_into(rhs_high + carry, ++lhs_cursor, result);
}

void
add(long double              addend,
    std::vector<digit_type> &result)
{
    constexpr long double LONG_DOUBLE_DIGIT_BASE = DIGIT_BASE;

    digit_accumulator_type carry = 0;
    auto cursor                  = result.begin();
    auto end                     = result.end();
    do {
        carry += *cursor;
        carry += digit_from_nonnegative_value(addend);
        addend /= LONG_DOUBLE_DIGIT_BASE;

        *cursor   = digit_from_nonnegative_value(carry);
        carry   >>= DIGIT_TYPE_BITS;
    } while (++cursor != end);

    trim_trailing_zero(result);

    append_carry_if_nonzero(carry, result);
}

} // namespace


std::vector<digit_type> &
operator+=(std::vector<digit_type>       &lhs,
           const std::vector<digit_type> &rhs)
{
    assert(!lhs.empty());
    assert(!rhs.empty());

    pad_result(rhs.size(), lhs);

    add(rhs, lhs);

    return lhs;
}

std::vector<digit_type> &
operator+=(std::vector<digit_type> &lhs,
           std::uintmax_t           rhs)
{
    assert(!lhs.empty());

    auto [rhs_low, rhs_high] = split_integral(rhs);

    std::vector<digit_type>::size_type size_rhs = 1 + (rhs_high > 0);
    pad_result(size_rhs, lhs);

    add(rhs_low, rhs_high, lhs);

    return lhs;
}

std::vector<digit_type> &
operator+=(std::vector<digit_type> &lhs,
           long double              rhs)
{
    assert(!lhs.empty());
    assert(std::isfinite(rhs));
    assert(rhs >= 0.0L);

    auto size_rhs = size_digits_from_nonnegative_floating_point(rhs);
    pad_result(size_rhs, lhs);

    add(rhs, lhs);

    return lhs;
}

std::vector<digit_type>
operator+(const std::vector<digit_type> &lhs,
          const std::vector<digit_type> &rhs)
{
    assert(!lhs.empty());
    assert(!rhs.empty());

    const auto &[smaller, larger] = order_by_size(lhs, rhs);
        
    auto result = initialize_result(larger);

    add(smaller, result);

    return result;
}

std::vector<digit_type>
operator+(const std::vector<digit_type> &lhs,
          std::uintmax_t                 rhs)
{
    assert(!lhs.empty());

    auto result = initialize_result(lhs);

    result += rhs;

    return result;
}

std::vector<digit_type>
operator+(std::uintmax_t                 lhs,
          const std::vector<digit_type> &rhs)
{
    return rhs + lhs;
}

std::vector<digit_type>
operator+(const std::vector<digit_type> &lhs,
          long double                    rhs)
{
    assert(!lhs.empty());
    assert(std::isfinite(rhs));
    assert(rhs >= 0.0L);

    auto result = initialize_result_from_addends(lhs, rhs);

    add(rhs, result);

    return result;
}

std::vector<digit_type>
operator+(long double                    lhs,
          const std::vector<digit_type> &rhs)
{
    return rhs + lhs;
}

} // namespace detail
} // namespace tasty_int
