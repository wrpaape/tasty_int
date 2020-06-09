#include "tasty_int/detail/digits_division.hpp"

#include <cassert>
#include <cmath>

#include <algorithm>
#include <iterator>
#include <utility>

#include "tasty_int/detail/digit_from_nonnegative_value.hpp"
#include "tasty_int/detail/is_zero.hpp"
#include "tasty_int/detail/trailing_zero.hpp"
#include "tasty_int/detail/split_digits.hpp"
#include "tasty_int/detail/next_power_of_two.hpp"
#include "tasty_int/detail/integral_digits_view.hpp"
#include "tasty_int/detail/extended_digit_accumulator.hpp"
#include "tasty_int/detail/digits_comparison.hpp"
#include "tasty_int/detail/digits_bitwise.hpp"
#include "tasty_int/detail/digits_addition.hpp"
#include "tasty_int/detail/digits_subtraction.hpp"
#include "tasty_int/detail/digits_multiplication.hpp"
#include "tasty_int/detail/conversions/digits_from_floating_point.hpp"


namespace tasty_int {
namespace detail {
namespace {

DigitsDivisionResult
make_zero_quotient_result(const std::vector<digit_type> &dividend)
{
    return { .quotient = { 0 }, .remainder = dividend };
}

template<typename RhsType>
std::vector<digit_type> &
operator-=(std::vector<digit_type> &lhs,
           const RhsType           &rhs)
{
    [[maybe_unused]] auto sign = subtract_in_place(rhs, lhs);
    assert(sign >= Sign::ZERO);

    return lhs;
}

std::vector<digit_type>
operator*(const std::vector<digit_type> &lhs,
          digit_type                     rhs)
{
    return tasty_int::detail::operator*(lhs, std::uintmax_t(rhs));
}

template<typename DigitsType>
auto
magnitude(DigitsType digits) -> decltype(digits.digits_size())
{
    return digits.digits_size();
}

std::vector<digit_type>::size_type
magnitude(const std::vector<digit_type>& digits)
{
    return digits.size();
}

digit_type
most_significant_digit(IntegralDigitsView digits)
{
    return digits.most_significant_digit();
}

digit_type
most_significant_digit(const std::vector<digit_type>& digits)
{
    return digits.back();
}

template<typename DivisorType>
DigitsShiftOffset
long_divide_normal_shift_offset(const DivisorType &divisor)
{
    auto sig_divisor_digit = most_significant_digit(divisor);
    DigitsShiftOffset normal_offset = {
        .digits = 0,
        .bits   = count_leading_zero_bits_from_digit(sig_divisor_digit)
    };
    return normal_offset;
}

std::vector<digit_type>
digits_from_remainder_accumulator(ExtendedDigitAccumulator remainder)
{
    assert(remainder.digits_size() <= 2);

    auto have_middle_digit = (remainder.middle_digit() != 0);

    std::vector<digit_type> digits;
    digits.reserve(1 + have_middle_digit);

    digits.emplace_back(remainder.low_digit());
    if (have_middle_digit)
        digits.emplace_back(remainder.middle_digit());

    return digits;
}

digit_type
estimate_digit_quotient(digit_accumulator_type sig_dividend,
                        digit_type             sig_divisor_digit)
{
    digit_accumulator_type sig_divisor = sig_divisor_digit;

    auto tentative_quotient = sig_dividend / sig_divisor;
    if (tentative_quotient > DIGIT_TYPE_MAX)
        tentative_quotient = DIGIT_TYPE_MAX;

    return static_cast<digit_type>(tentative_quotient);
}

digit_accumulator_type
significant_dividend_digits(const std::vector<digit_type> &dividend,
                            std::size_t                    divisor_mag)
{
    digit_accumulator_type sig_dividend = dividend.back();
    if (dividend.size() > divisor_mag) {
        sig_dividend <<= DIGIT_TYPE_BITS;
        sig_dividend  |= *std::next(dividend.rbegin());
    }
    return sig_dividend;
}

digit_accumulator_type
significant_dividend_digits(ExtendedDigitAccumulator dividend,
                            std::size_t              divisor_mag)
{
    switch (dividend.digits_size())
    {
    case 1:
        return dividend.low_digit();

    case 2:
        return (divisor_mag < 2)
             ? dividend.front()
             : dividend.middle_digit();

    default:
        return (dividend.back()  << DIGIT_TYPE_BITS)
             | (dividend.front() >> DIGIT_TYPE_BITS);
    }
}

template<typename DividendType>
digit_type
estimate_digit_quotient(const DividendType &dividend,
                        std::size_t         divisor_mag,
                        digit_type          sig_divisor_digit)
{
    auto sig_dividend = significant_dividend_digits(dividend, divisor_mag);

    return estimate_digit_quotient(sig_dividend,
                                   sig_divisor_digit);
}

template<typename DivisorType, typename DividendType>
digit_type
estimate_digit_quotient(const DividendType &dividend,
                        const DivisorType  &divisor)
{
    assert((magnitude(dividend) - magnitude(divisor)) <= 1);

    return estimate_digit_quotient(dividend,
                                   magnitude(divisor),
                                   most_significant_digit(divisor));
}

template<typename DivisorType, typename DividendType>
std::pair<digit_type, DividendType>
quotient_divisor_product(digit_type          tentative_quotient,
                         const DivisorType  &divisor,
                         const DividendType &dividend)
{
    auto product = divisor * tentative_quotient;

    if (product > dividend) {
        product -= divisor;
        --tentative_quotient;

        if (product > dividend) {
            product -= divisor;
            --tentative_quotient;
        }
    }

    return { tentative_quotient, std::move(product) };
}

template<typename DivisorType,typename DividendType>
digit_type
divide_similar_magnitude_in_place(const DivisorType &divisor,
                                  DividendType      &dividend)
{
    if (magnitude(dividend) < magnitude(divisor))
        return 0;

    auto tentative_quotient = estimate_digit_quotient(dividend, divisor);

    auto [quotient, product] = quotient_divisor_product(tentative_quotient,
                                                        divisor,
                                                        dividend);
    dividend -= product;

    return quotient;
}

void
multiply_digit_base_accumulate_in_place(digit_type               addend,
                                        std::vector<digit_type> &result)
{
    result <<= 1;
    result.front() = addend;
}

void
multiply_digit_base_accumulate_in_place(digit_type                addend,
                                        ExtendedDigitAccumulator &result)
{
    result.multiply_digit_base_accumulate(addend);
}

template<typename DivisorType>
std::vector<digit_type>
allocate_quotient(const std::vector<digit_type> &dividend,
                  const DivisorType             &divisor)
{
    auto max_quotient_mag = magnitude(dividend) + 1
                          - magnitude(divisor);
    std::vector<digit_type> quotient;
    quotient.reserve(max_quotient_mag);

    return quotient;
}

std::vector<digit_type>
allocate_remainder(const std::vector<digit_type> &divisor)
{
    auto max_remainder_mag = magnitude(divisor) + 1;
    std::vector<digit_type> remainder;
    remainder.reserve(max_remainder_mag);

    return remainder;
}

template<typename DivisorType, typename RemainderType>
std::vector<digit_type>
build_reversed_quotient(const std::vector<digit_type> &dividend,
                        const DivisorType             &divisor,
                        RemainderType                 &remainder)
{
    auto quotient = allocate_quotient(dividend, divisor);

    auto dividend_cursor = dividend.rbegin();
    do {
        multiply_digit_base_accumulate_in_place(*dividend_cursor, remainder);

        auto quotient_digit = divide_similar_magnitude_in_place(divisor,
                                                                remainder);
        quotient.emplace_back(quotient_digit);
    } while (++dividend_cursor != dividend.rend());

    return quotient;
}

void
correct_reversed_quotient(std::vector<digit_type> &quotient)
{
    std::reverse(quotient.begin(), quotient.end());

    trim_trailing_zeros(quotient);
}

template<typename DivisorType, typename RemainderType>
std::vector<digit_type>
normalized_long_divide(const std::vector<digit_type> &dividend,
                       const DivisorType             &divisor,
                       RemainderType                 &remainder)
{
    auto quotient = build_reversed_quotient(dividend, divisor, remainder);

    correct_reversed_quotient(quotient);

    return quotient;
}

bool
is_odd(std::vector<digit_type>::size_type value)
{
    return (value & 1) != 0;
}

bool
is_divide_and_conquer_divide_base_case(
    std::vector<digit_type>::size_type divisor_mag
)
{
    /// @todo TODO: tune
    constexpr std::vector<digit_type>::size_type
        LONG_DIVIDE_THRESHOLD_DIVISOR_MAGNITUDE = 32;

    return is_odd(divisor_mag)
        || (divisor_mag <= LONG_DIVIDE_THRESHOLD_DIVISOR_MAGNITUDE);
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
    dividend_upper -= divisor_high;

    result.remainder = std::move(dividend_upper);

    return result;
}

void
correct_divide_normalized_3n_2n_split_remainder(
    Sign                           remainder_sign,
    const std::vector<digit_type> &divisor,
    DigitsDivisionResult          &result
)
{
    auto &remainder = result.remainder;
    auto &quotient  = result.quotient;

    while (remainder_sign < Sign::ZERO) {
        quotient -= std::uintmax_t(1);

        remainder_sign = subtract_in_place(divisor, remainder);
        remainder_sign = -remainder_sign;
    }
}

DigitsShiftOffset
divide_and_conquer_normal_shift_offset(
    const std::vector<digit_type>      &divisor,
    std::vector<digit_type>::size_type  divisor_piece_mag
)
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
    auto &quotient  = result.quotient;
    auto &remainder = result.remainder;

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

template<typename DivisorType>
std::vector<digit_type>
divide_replace_dividend(const DivisorType       &divisor,
                        std::vector<digit_type> &dividend)
{
    auto result = divide(dividend, divisor);

    dividend = std::move(result.quotient);

    return std::move(result.remainder);
}

} // namespace


std::vector<digit_type>
divide_in_place(const std::vector<digit_type> &divisor,
                std::vector<digit_type>       &dividend)
{
    return divide_replace_dividend(divisor, dividend);
}

std::vector<digit_type>
divide_in_place(std::uintmax_t           divisor,
                std::vector<digit_type> &dividend)
{
    return divide_replace_dividend(divisor, dividend);
}

std::vector<digit_type>
divide_in_place(long double              divisor,
                std::vector<digit_type> &dividend)
{
    return divide_replace_dividend(divisor, dividend);
}

DigitsDivisionResult
divide(const std::vector<digit_type> &dividend,
       const std::vector<digit_type> &divisor)
{
    assert(!is_zero(divisor));

    return (divisor <= dividend)
         ? divide_and_conquer_divide(dividend, divisor)
         : make_zero_quotient_result(dividend);
}

DigitsDivisionResult
divide(const std::vector<digit_type> &dividend,
       std::uintmax_t                 divisor)
{
    assert(divisor > 0);

    return (divisor <= dividend)
         ? long_divide(dividend, divisor)
         : make_zero_quotient_result(dividend);
}

DigitsDivisionResult
divide(const std::vector<digit_type> &dividend,
       long double                    divisor)
{
    assert(std::isfinite(divisor));
    assert(divisor >= 1.0L);

    return (divisor <= dividend)
         ? divide_and_conquer_divide(
               dividend,
               conversions::digits_from_floating_point(divisor)
           )
         : make_zero_quotient_result(dividend);
}

DigitsDivisionResult
long_divide(const std::vector<digit_type> &dividend,
            const std::vector<digit_type> &divisor)
{
    assert(!is_zero(divisor));
    assert(dividend.size() >= divisor.size());

    auto normal_offset = long_divide_normal_shift_offset(divisor);

    auto normalized_dividend = dividend << normal_offset;
    auto normalized_divisor  = divisor  << normal_offset;

    DigitsDivisionResult result;

    auto &remainder = result.remainder;
    remainder = allocate_remainder(normalized_divisor);
    remainder.emplace_back(0);

    result.quotient = normalized_long_divide(normalized_dividend,
                                             normalized_divisor,
                                             remainder);

    remainder >>= normal_offset;

    return result;
}

DigitsDivisionResult
long_divide(const std::vector<digit_type> &dividend,
            std::uintmax_t                 divisor)
{

    auto normal_offset =
        long_divide_normal_shift_offset(IntegralDigitsView(divisor));

    auto normalized_dividend = dividend << normal_offset;
    auto normalized_divisor  = divisor  << normal_offset.bits;

    DigitsDivisionResult result;
    IntegralDigitsView normalized_divisor_view(normalized_divisor);
    ExtendedDigitAccumulator remainder{};
    result.quotient = normalized_long_divide(normalized_dividend,
                                             normalized_divisor_view,
                                             remainder);

    remainder >>= normal_offset.bits;

    result.remainder = digits_from_remainder_accumulator(remainder);

    return result;
}


DigitsDivisionResult
divide_and_conquer_divide(const std::vector<digit_type> &dividend,
                          const std::vector<digit_type> &divisor)
{
    /// @todo TODO: tune
    constexpr std::vector<digit_type>::size_type DIVISION_PIECE_MAGNITUDE = 32;

    if (divisor.size() < DIVISION_PIECE_MAGNITUDE)
        return long_divide(dividend, divisor);

    auto normal_offset =
        divide_and_conquer_normal_shift_offset(divisor,
                                               DIVISION_PIECE_MAGNITUDE);

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
        return make_zero_quotient_result(dividend);

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
        return make_zero_quotient_result(dividend);

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

    result.remainder <<= split_size;
    result.remainder  += dividend_low;
    auto remainder_sign = subtract_in_place(result.quotient * divisor_low,
                                            result.remainder);

    correct_divide_normalized_3n_2n_split_remainder(remainder_sign,
                                                    divisor,
                                                    result);
    assert(result.remainder < divisor);

    return result;
}

} // namespace detail
} // namespace tasty_int
