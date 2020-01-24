#ifndef TASTY_INT_TASTY_INT_DETAIL_DIGIT_TYPE_HPP
#define TASTY_INT_TASTY_INT_DETAIL_DIGIT_TYPE_HPP

#include <cstdint>

#include <limits>
#include <type_traits>


namespace tasty_int {
namespace detail {

/**
 * The largest unsigned integer type.  digit_accumulator_type must be large
 * enough to hold the result of DIGIT_TYPE_MAX^2 but small enough s.t. its
 * maximum value may be stored in 2 digit_type instances.
 */
typedef std::uintmax_t digit_accumulator_type;

/**
 * The signed version of digit_accumulator_type.
 */
typedef std::make_signed_t<digit_accumulator_type> signed_digit_accumulator_type;

/**
 * The larged unsigned integer type capable of having the result of its max
 * squared stored in digit_accumulator_type.  These properties make it suitable
 * for use as an elemental type when representing large integers as an array of
 * digits.
 */
typedef std::conditional_t<(sizeof(unsigned char)      * 2) >= sizeof(digit_accumulator_type),
            unsigned char,
        std::conditional_t<(sizeof(unsigned short)     * 2) >= sizeof(digit_accumulator_type),
            unsigned short,
        std::conditional_t<(sizeof(unsigned int)       * 2) >= sizeof(digit_accumulator_type),
            unsigned int,
        std::conditional_t<(sizeof(unsigned long)      * 2) >= sizeof(digit_accumulator_type),
            unsigned long,
        std::conditional_t<(sizeof(unsigned long long) * 2) >= sizeof(digit_accumulator_type),
            unsigned long long,
            // No integer type smaller than digit_accumulator_type that can
            // express an accumulator in 2 instances.
            // => digit_type = digit_accumulator_type, and DIGIT_TYPE_MAX must
            // be truncated from its native max value.
            digit_accumulator_type
>>>>> digit_type;

/**
 * Half the bit-size of digit_accumulator_type.  Used to size DIGIT_TYPE_MAX.
 */
static constexpr unsigned int DIGIT_TYPE_BITS =
    std::numeric_limits<digit_accumulator_type>::digits / 2;

/**
 * The maximum allowable value that may be stored in digit_type without risk of
 * overflow when multiplying a result into a digit_accumulator_type.
 * DIGIT_TYPE_MAX == (2 ^ DIGIT_TYPE_BITS) - 1
 *                == (1 << DIGIT_TYPE_BITS) - 1
 *                <= floor(sqrt(max value of digit_accumulator_type))
 *                <= native max value of digit_type
 */
static constexpr digit_accumulator_type DIGIT_TYPE_MAX =
    (digit_accumulator_type(1) << DIGIT_TYPE_BITS) - digit_accumulator_type(1);

} // namespace detail
} // namespace tasty_int

#endif // ifndef TASTY_INT_TASTY_INT_DETAIL_DIGIT_TYPE_HPP
