#include "tasty_int/detail/digits_addition.hpp"

#include <cassert>
#include <cmath>

#include <algorithm>
#include <limits>
#include <utility>

#include "tasty_int/detail/digit_from_nonnegative_value.hpp"
#include "tasty_int/detail/integral_digits_view.hpp"
#include "tasty_int/detail/size_digits_from_nonnegative_floating_point.hpp"
#include "tasty_int/detail/trailing_zero.hpp"


namespace tasty_int {
namespace detail {
namespace {

void
pad_augend(std::vector<digit_type>::size_type  addend_size,
           std::vector<digit_type>            &augend)
{
    if (addend_size > augend.size()) {
        augend.reserve(addend_size + 1); // room for carry
        augend.resize(addend_size);
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
allocate_augend(std::vector<digit_type>::size_type larger_addend_size)
{
    std::vector<digit_type> augend;

    augend.reserve(larger_addend_size + 1); // up to one extra carry digit

    return augend;
}

std::vector<digit_type>
initialize_augend(const std::vector<digit_type>      &addend_digits,
                  std::vector<digit_type>::size_type  larger_addend_size)
{
    std::vector<digit_type> augend = allocate_augend(larger_addend_size);

    augend.assign(addend_digits.begin(), addend_digits.end());

    return augend;
}

std::vector<digit_type>
initialize_augend(const std::vector<digit_type> &addend_digits)
{
    return initialize_augend(addend_digits, addend_digits.size());
}

std::vector<digit_type>
initialize_augend_from_addends(
    const std::vector<digit_type> &addend_digits,
    long double                    floating_point_addend
)
{
    auto larger_addend_size = std::max(
        addend_digits.size(),
        size_digits_from_nonnegative_floating_point(floating_point_addend)
    );
    auto augend = initialize_augend(addend_digits, larger_addend_size);
    augend.resize(larger_addend_size);

    return augend;
}

void
append_carry_if_nonzero(digit_accumulator_type   carry,
                        std::vector<digit_type>& augend)
{
    if (carry > 0)
        augend.emplace_back(static_cast<digit_type>(carry));
}

void
add(const std::vector<digit_type> &addend,
    std::vector<digit_type>       &augend)
{
    auto [carry, augend_cursor] = add_into(addend, augend);

    carry = propagate_carry(carry, augend_cursor, augend.end());

    append_carry_if_nonzero(carry, augend);
}

digit_accumulator_type
fixed_add(digit_accumulator_type   addend_low,
          digit_accumulator_type   addend_high,
          std::vector<digit_type> &augend)
{
    auto augend_cursor = augend.begin();

    auto carry = add_at(addend_low, augend_cursor);

    return propagate_carry(addend_high + carry, ++augend_cursor, augend.end());
}

void
add(digit_accumulator_type   addend_low,
    digit_accumulator_type   addend_high,
    std::vector<digit_type> &augend)
{
    auto carry = fixed_add(addend_low, addend_high, augend);

    append_carry_if_nonzero(carry, augend);
}

digit_accumulator_type
fixed_add(long double              addend,
          std::vector<digit_type> &augend)
{
    constexpr long double LONG_DOUBLE_DIGIT_BASE = DIGIT_BASE;

    digit_accumulator_type carry = 0;
    auto cursor                  = augend.begin();
    auto end                     = augend.end();
    do {
        carry += *cursor;
        carry += digit_from_nonnegative_value(addend);
        addend /= LONG_DOUBLE_DIGIT_BASE;

        *cursor   = digit_from_nonnegative_value(carry);
        carry   >>= DIGIT_TYPE_BITS;
    } while (++cursor != end);

    return carry;
}

void
add(long double              addend,
    std::vector<digit_type> &augend)
{
    auto carry = fixed_add(addend, augend);

    trim_trailing_zero(augend);

    append_carry_if_nonzero(carry, augend);
}

} // namespace


std::vector<digit_type> &
operator+=(std::vector<digit_type>       &lhs,
           const std::vector<digit_type> &rhs)
{
    assert(!lhs.empty());
    assert(!rhs.empty());

    pad_augend(rhs.size(), lhs);

    add(rhs, lhs);

    return lhs;
}

std::vector<digit_type> &
operator+=(std::vector<digit_type> &lhs,
           std::uintmax_t           rhs)
{
    assert(!lhs.empty());

    IntegralDigitsView rhs_view(rhs);

    pad_augend(rhs_view.digits_size(), lhs);

    add(rhs_view.low_digit(), rhs_view.high_digit(), lhs);

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
    pad_augend(size_rhs, lhs);

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
        
    auto augend = initialize_augend(larger);

    add(smaller, augend);

    return augend;
}

std::vector<digit_type>
operator+(const std::vector<digit_type> &lhs,
          std::uintmax_t                 rhs)
{
    assert(!lhs.empty());

    auto augend = initialize_augend(lhs);

    augend += rhs;

    return augend;
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

    auto augend = initialize_augend_from_addends(lhs, rhs);

    add(rhs, augend);

    return augend;
}

std::vector<digit_type>
operator+(long double                    lhs,
          const std::vector<digit_type> &rhs)
{
    return rhs + lhs;
}

std::pair<digit_accumulator_type, std::vector<digit_type>::iterator>
add_into(const std::vector<digit_type> &addend,
         std::vector<digit_type>       &augend)
{
    assert(augend.size() >= addend.size());

    digit_accumulator_type carry = 0;
    auto augend_cursor           = augend.begin();

    for (digit_type digit : addend) {
        carry += digit;

        carry = add_at(carry, augend_cursor);

        ++augend_cursor;
    }

    return { carry, augend_cursor };
}

digit_accumulator_type
propagate_carry(digit_accumulator_type                  carry,
                std::vector<digit_type>::iterator       augend_cursor,
                std::vector<digit_type>::const_iterator augend_end)
{
    while ((carry > 0) && (augend_cursor != augend_end)) {
        carry = add_at(carry, augend_cursor);

        ++augend_cursor;
    }

    return carry;
}

digit_accumulator_type
add_at(digit_accumulator_type            addend,
       std::vector<digit_type>::iterator augend_cursor)
{
    assert((std::numeric_limits<digit_accumulator_type>::max() - addend) >=
           *augend_cursor);

    addend          += *augend_cursor;
    *augend_cursor   = digit_from_nonnegative_value(addend);
    addend         >>= DIGIT_TYPE_BITS;

    return addend;
}

} // namespace detail
} // namespace tasty_int
