#include "tasty_int/detail/digits_bitwise.hpp"

#include <cassert>

#include <algorithm>

#include "tasty_int/detail/digit_from_nonnegative_value.hpp"
#include "tasty_int/detail/is_zero.hpp"


namespace tasty_int {
namespace detail {
namespace {

std::vector<digit_type>
allocate_multiply_powers_product(const std::vector<digit_type> &multiplicand,
                                 MultiplierExponents            exponents)
{
    auto have_leading_digit_overflow =
       multiplicand.back() > (DIGIT_TYPE_MAX >> exponents.two);

    auto shift_offset = exponents.digit_base
                      + have_leading_digit_overflow;

    auto product_size = multiplicand.size() + shift_offset;

    std::vector<digit_type> product;
    product.reserve(product_size);

    return product;
}

} // namespace

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

void
multiply_digit_base_power_in_place(
    std::vector<digit_type>::size_type  exponent,
    std::vector<digit_type>            &multiplicand
)
{
    if (is_zero(multiplicand))
        return;

    auto initial_size = multiplicand.size();
    multiplicand.resize(initial_size + exponent);

    auto initial_end = multiplicand.rbegin() + exponent;

    std::swap_ranges(initial_end,
                     multiplicand.rend(),
                     multiplicand.rbegin());
}

std::vector<digit_type>
multiply_powers(const std::vector<digit_type> &multiplicand,
                MultiplierExponents            exponents)
{
    assert(exponents.two <= DIGIT_TYPE_BITS);
    assert(!is_zero(multiplicand));
    assert(!multiplicand.empty());

    auto product = allocate_multiply_powers_product(multiplicand, exponents);

    product.resize(exponents.digit_base);

    const auto overflow_shift = DIGIT_TYPE_BITS - exponents.two;

    digit_accumulator_type overflow = 0;

    for (auto digit : multiplicand) {
        auto accumulator = (digit_accumulator_type(digit) << exponents.two)
                         | overflow;

        product.emplace_back(digit_from_nonnegative_value(accumulator));

        overflow = digit_accumulator_type(digit) >> overflow_shift;
    }

    if (overflow > 0)
        product.emplace_back(static_cast<digit_type>(overflow));

    return product;
}

} // namespace detail
} // namespace tasty_int
