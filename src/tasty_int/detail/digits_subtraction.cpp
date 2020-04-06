#include "tasty_int/detail/digits_subtraction.hpp"

#include "tasty_int/detail/digit_from_nonnegative_value.hpp"
#include "tasty_int/detail/digits_addition.hpp"
#include "tasty_int/detail/flip_sign.hpp"
#include "tasty_int/detail/floating_point_digits_iterator.hpp"
#include "tasty_int/detail/integral_digits_view.hpp"
#include "tasty_int/detail/sign_from_digits.hpp"
#include "tasty_int/detail/size_digits_from_nonnegative_floating_point.hpp"
#include "tasty_int/detail/trailing_zero.hpp"

#include <cassert>
#include <cmath>

#include <algorithm>
#include <type_traits>
#include <utility>


namespace tasty_int {
namespace detail {
namespace {

void
make_zero(std::vector<digit_type> &digits)
{
    digits.front() = 0;
    digits.resize(1);
}

void
pad_minuend(std::vector<digit_type>::size_type  subtrahend_size,
            std::vector<digit_type>            &minuend)
{
    if (minuend.size() < subtrahend_size)
        minuend.resize(subtrahend_size);
}

template<typename ArithmeticType>
ArithmeticType
make_digit_complement(ArithmeticType value)
    requires std::is_arithmetic_v<ArithmeticType>
{
    return digit_from_nonnegative_value(~value);
}

void
make_digit_compliment(std::vector<digit_type> &digits)
{
    for (digit_type &digit : digits)
        digit = make_digit_complement(digit);
}

digit_accumulator_type
fixed_add(const std::vector<digit_type> &addend,
          std::vector<digit_type>       &augend)
{
    auto [carry, augend_cursor] = add_into(addend, augend);

    return propagate_carry(carry, augend_cursor, augend.end());
}

digit_accumulator_type
add_with_end_around_carry(const std::vector<digit_type> &addend,
                          std::vector<digit_type>       &augend)
{
    auto carry = fixed_add(addend, augend);

    (void) propagate_carry(carry, augend.begin(), augend.end());

    return carry;
}

digit_accumulator_type
propagate_complement_carry(
    digit_accumulator_type                  carry,
    std::vector<digit_type>::iterator       augend_cursor,
    std::vector<digit_type>::const_iterator augend_end
)
{
    while (++augend_cursor != augend_end)
        carry = add_at(DIGIT_TYPE_MAX + carry, augend_cursor);

    return carry;
}

digit_accumulator_type
fixed_add_complement(digit_accumulator_type   addend_low,
                     digit_accumulator_type   addend_high,
                     std::vector<digit_type> &augend)
{
    auto cursor = augend.begin();

    auto complement_low = make_digit_complement(addend_low);
    auto carry          = add_at(complement_low, cursor);
    if (++cursor != augend.end()) {
        auto complement_high = make_digit_complement(addend_high);
        carry                = add_at(complement_high + carry, cursor);

        carry = propagate_complement_carry(carry, cursor, augend.end());
    }

    return carry;
}

digit_accumulator_type
add_complement_with_end_around_carry(digit_accumulator_type   addend_low,
                                     digit_accumulator_type   addend_high,
                                     std::vector<digit_type> &augend)
{
    auto carry = fixed_add_complement(addend_low,
                                      addend_high,
                                      augend);

    (void) propagate_carry(carry, augend.begin(), augend.end());

    return carry;
}

digit_accumulator_type
fixed_add_complement(long double              addend,
                     std::vector<digit_type> &augend)
{
    FloatingPointDigitsIterator addend_cursor(addend);
    digit_accumulator_type carry = 0;
    auto augend_cursor           = augend.begin();
    auto augend_end              = augend.end();
    do {
        auto addend_digit = *addend_cursor;
        ++addend_cursor;
        auto addend_digit_compliment = make_digit_complement(addend_digit);
        carry = add_at(addend_digit_compliment + carry, augend_cursor);
    } while (++augend_cursor != augend_end);

    return carry;
}

digit_accumulator_type
truncation_correction(long double addend,
                      long double ceil_addend)
{
    long double truncation = ceil_addend - addend;
    auto correction        = static_cast<digit_accumulator_type>(
        std::ceil(truncation)
    );
    return correction;
}

digit_accumulator_type
add_complement_with_end_around_carry(long double              addend,
                                     std::vector<digit_type> &augend)
{
    long double ceil_addend = std::ceil(addend);
    auto carry = fixed_add_complement(ceil_addend, augend);

    auto correction = std::max(carry,
                               truncation_correction(addend, ceil_addend));

    (void) propagate_carry(correction, augend.begin(), augend.end());

    return carry;
}

std::vector<digit_type>
make_padded_digits(std::vector<digit_type>::size_type operand_size,
                   std::vector<digit_type>::size_type other_operand_size)
{
    std::vector<digit_type>::size_type padded_digits_size =
        std::max(operand_size, other_operand_size);

    std::vector<digit_type> padded_digits(padded_digits_size);

    return padded_digits;
}

std::vector<digit_type>
make_padded_minuend(const std::vector<digit_type>      &minuend,
                    std::vector<digit_type>::size_type  subtrahend_size)
{
    std::vector<digit_type> padded_minuend =
        make_padded_digits(minuend.size(), subtrahend_size);

    std::copy(minuend.begin(), minuend.end(), padded_minuend.begin());

    return padded_minuend;
}

std::vector<digit_type>
make_padded_minuend(std::uintmax_t                     minuend,
                    std::vector<digit_type>::size_type subtrahend_size)
{
    IntegralDigitsView minuend_view(minuend);

    auto minuend_size = minuend_view.digits_size();

    std::vector<digit_type> padded_minuend =
        make_padded_digits(minuend_size, subtrahend_size);

    padded_minuend[0] = minuend_view.low_digit();
    if (minuend_size > 1)
        padded_minuend[1] = minuend_view.high_digit();

    return padded_minuend;
}

std::vector<digit_type>
make_padded_subtrahend(long double                    minuend,
                       const std::vector<digit_type> &subtrahend)
{
    auto minuend_size = size_digits_from_nonnegative_floating_point(minuend);

    std::vector<digit_type> padded_subtrahend =
        make_padded_digits(minuend_size, subtrahend.size());

    std::copy(subtrahend.begin(), subtrahend.end(), padded_subtrahend.begin());

    return padded_subtrahend;
}

void
trim_trailing_zeros(std::vector<digit_type> &digits)
{
    while (have_trailing_zero(digits))
        digits.pop_back();
}

Sign
complete_subtract(digit_accumulator_type   carry,
                  Sign                     carried_sign,
                  std::vector<digit_type> &minuend)
{
    Sign tentative_sign = carried_sign;

    if (carry == 0) {
        tentative_sign = flip_sign(tentative_sign);
        make_digit_compliment(minuend);
    }

    trim_trailing_zeros(minuend);

    return sign_from_digits(minuend, tentative_sign);
}

Sign
minuend_compliment_subtract_in_place(const std::vector<digit_type> &subtrahend,
                                     std::vector<digit_type>       &minuend)
{
    make_digit_compliment(minuend);

    auto carry = add_with_end_around_carry(subtrahend, minuend);

    return complete_subtract(carry, Sign::NEGATIVE, minuend);
}

Sign
subtract_distinct_in_place(const std::vector<digit_type> &subtrahend,
                           std::vector<digit_type>       &minuend)
{
    pad_minuend(subtrahend.size(), minuend);

    return minuend_compliment_subtract_in_place(subtrahend, minuend);
}

template<typename MinuendType>
std::pair<Sign, std::vector<digit_type>>
minuend_compliment_subtract(const MinuendType             &minuend,
                            const std::vector<digit_type> &subtrahend)
{
    auto result_digits = make_padded_minuend(minuend, subtrahend.size());

    Sign result_sign = minuend_compliment_subtract_in_place(subtrahend,
                                                            result_digits);

    return { .first = result_sign, .second = std::move(result_digits) };
}

} // namespace


Sign
subtract_in_place(const std::vector<digit_type> &subtrahend,
                  std::vector<digit_type>       &minuend)
{
    assert(!subtrahend.empty());
    assert(!minuend.empty());

    Sign sign = Sign::ZERO;

    if (&subtrahend != &minuend)
        sign = subtract_distinct_in_place(subtrahend, minuend);
    else
        make_zero(minuend);

    return sign;
}

Sign
subtract_in_place(std::uintmax_t           subtrahend,
                  std::vector<digit_type> &minuend)
{
    assert(!minuend.empty());

    IntegralDigitsView subtrahend_view(subtrahend);

    pad_minuend(subtrahend_view.digits_size(), minuend);

    auto carry = add_complement_with_end_around_carry(
        subtrahend_view.low_digit(),
        subtrahend_view.high_digit(),
        minuend
    );

    return complete_subtract(carry, Sign::POSITIVE, minuend);
}

Sign
subtract_in_place(long double              subtrahend,
                  std::vector<digit_type> &minuend)
{
    assert(std::isfinite(subtrahend));
    assert(subtrahend >= 0.0L);
    assert(!minuend.empty());

    auto subtrahend_size = size_digits_from_nonnegative_floating_point(subtrahend);
    pad_minuend(subtrahend_size, minuend);

    auto carry = add_complement_with_end_around_carry(subtrahend, minuend);

    return complete_subtract(carry, Sign::POSITIVE, minuend);
}

std::pair<Sign, std::vector<digit_type>>
subtract(const std::vector<digit_type> &minuend,
         const std::vector<digit_type> &subtrahend)
{
    assert(!minuend.empty());
    assert(!subtrahend.empty());

    return minuend_compliment_subtract(minuend, subtrahend);
}

std::pair<Sign, std::vector<digit_type>>
subtract(std::uintmax_t                 minuend,
         const std::vector<digit_type> &subtrahend)
{
    assert(!subtrahend.empty());

    return minuend_compliment_subtract(minuend, subtrahend);
}

std::pair<Sign, std::vector<digit_type>>
subtract(long double                    minuend,
         const std::vector<digit_type> &subtrahend)
{
    assert(std::isfinite(minuend));
    assert(minuend >= 0.0L);
    assert(!subtrahend.empty());

    auto result_digits = make_padded_subtrahend(minuend, subtrahend);

    auto carry = add_complement_with_end_around_carry(minuend, result_digits);

    Sign result_sign = complete_subtract(carry, Sign::NEGATIVE, result_digits);

    return { .first = result_sign, .second = std::move(result_digits) };
}

} // namespace detail
} // namespace tasty_int
