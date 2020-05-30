#include "tasty_int/detail/digits_bitwise.hpp"

#include <cassert>

#include <algorithm>
#include <limits>

#include "tasty_int/detail/count_leading_zero_bits.hpp"
#include "tasty_int/detail/digit_from_nonnegative_value.hpp"
#include "tasty_int/detail/is_zero.hpp"


namespace tasty_int {
namespace detail {
namespace {

void
nonzero_left_shift_in_place(std::vector<digit_type>::size_type digit_offset,
                            std::vector<digit_type> &digits)
{
    auto initial_size = digits.size();
    digits.resize(initial_size + digit_offset);

    auto initial_end = digits.rbegin() + digit_offset;

    std::swap_ranges(initial_end,
                     digits.rend(),
                     digits.rbegin());
}

void
nonzero_right_shift_in_place(DigitsShiftOffset        offset,
                             std::vector<digit_type>& digits)
{
    auto leading_digit_bit_size =
        DIGIT_TYPE_BITS - count_leading_zero_bits_from_digit(digits.back());
    auto digits_shift = offset.digits
                      + (leading_digit_bit_size <= offset.bits);
    std::vector<digit_type>::difference_type post_shift_size =
        digits.size() - digits_shift;
    if (post_shift_size <= 0) {
        digits.front() = 0;
        digits.resize(1);
        return;
    }

    const auto overflow_shift        = DIGIT_TYPE_BITS - offset.bits;
    const auto overflow_mask         = DIGIT_TYPE_MAX >> overflow_shift;
    const auto overflow_digits_shift = offset.digits;

    auto dst_cursor                    = digits.begin();
    digit_accumulator_type accumulator = 0;
    while (true) {
        auto src_cursor = dst_cursor + offset.digits;
        accumulator     = digit_accumulator_type(*src_cursor) >> offset.bits;

        auto overflow_cursor = src_cursor + 1;
        if (overflow_cursor == digits.end())
            break;

        auto overflow =
            digit_accumulator_type(*overflow_cursor) & overflow_mask;
        accumulator |= (overflow << overflow_shift);

        *dst_cursor++ = digit_from_nonnegative_value(accumulator);
    }

    *dst_cursor = digit_from_nonnegative_value(accumulator);

    digits.resize(post_shift_size);
}

std::vector<digit_type>
allocate_nonzero_left_shift_result(const std::vector<digit_type> &digits,
                                   DigitsShiftOffset              offset)
{
    auto have_leading_digit_overflow =
       digits.back() > (DIGIT_TYPE_MAX >> offset.bits);

    auto shift_offset = offset.digits
                      + have_leading_digit_overflow;

    auto product_size = digits.size() + shift_offset;

    std::vector<digit_type> product;
    product.reserve(product_size);

    return product;
}

} // namespace

unsigned int
count_leading_zero_bits_from_digit(digit_type digit)
{
    constexpr auto BIT_DIFFERENCE =
        std::numeric_limits<std::uintmax_t>::digits - DIGIT_TYPE_BITS;

    return count_leading_zero_bits(digit) - BIT_DIFFERENCE;
}

/// @todo: TODO: remove if not required by digits_division
std::vector<digit_type>
multiply_digit_base(const std::vector<digit_type> &multiplicand)
{
    assert(!is_zero(multiplicand));

    std::vector<digit_type> result;

    result.reserve(multiplicand.size() + 1);

    result.emplace_back(0);

    result.insert(result.end(),
                  multiplicand.begin(),
                  multiplicand.end());

    return result;
}

std::vector<digit_type> &
operator<<=(std::vector<digit_type>            &digits,
            std::vector<digit_type>::size_type  digit_offset)
{
    if (!is_zero(digits))
        nonzero_left_shift_in_place(digit_offset, digits);

    return digits;
}

std::vector<digit_type>
operator<<(const std::vector<digit_type> &digits,
           DigitsShiftOffset              offset)
{
    assert(offset.bits <= DIGIT_TYPE_BITS);
    assert(!digits.empty());

    if (is_zero(digits))
        return digits;

    auto result = allocate_nonzero_left_shift_result(digits, offset);

    result.resize(offset.digits);

    const auto overflow_shift = DIGIT_TYPE_BITS - offset.bits;

    digit_accumulator_type overflow = 0;

    for (auto digit : digits) {
        auto accumulator = (digit_accumulator_type(digit) << offset.bits)
                         | overflow;

        result.emplace_back(digit_from_nonnegative_value(accumulator));

        overflow = digit_accumulator_type(digit) >> overflow_shift;
    }

    if (overflow > 0)
        result.emplace_back(static_cast<digit_type>(overflow));

    return result;
}

std::vector<digit_type> &
operator>>=(std::vector<digit_type> &digits,
            DigitsShiftOffset        offset)
{
    assert(offset.bits <= DIGIT_TYPE_BITS);
    assert(!digits.empty());

    if (!is_zero(digits))
        nonzero_right_shift_in_place(offset, digits);

    return digits;
}

} // namespace detail
} // namespace tasty_int
