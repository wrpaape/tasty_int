#ifndef TASTY_INT_TASTY_INT_TEST_SAMPLE_ARITHMETIC_TEST_HPP
#define TASTY_INT_TASTY_INT_TEST_SAMPLE_ARITHMETIC_TEST_HPP

#include <array>
#include <limits>
#include <type_traits>


namespace tasty_int_test {

/**
 * This collection of values is used to provide suitable test input for most
 * templated interfaces requiring an arithmetic type.
 *
 * @tparam ArithmeticType the type of the sampled value
 */
template<typename ArithmeticType>
    requires std::is_arithmetic_v<ArithmeticType>
struct SampleArithmetic
{
    static constexpr auto ZERO    = static_cast<ArithmeticType>(0);
    static constexpr auto ONE     = static_cast<ArithmeticType>(1);
    static constexpr auto MINIMUM =
        std::numeric_limits<ArithmeticType>::lowest();
    static constexpr auto MAXIMUM = std::numeric_limits<ArithmeticType>::max();

    static constexpr ArithmeticType
    get_middle(ArithmeticType lower_bound,
               ArithmeticType upper_bound)
    {
        // promote to long double to avoid overflow
        auto range = static_cast<long double>(upper_bound)
                   - static_cast<long double>(lower_bound);
        return lower_bound + static_cast<ArithmeticType>(range / 2.0L);
    }

    static constexpr auto MEDIAN = std::is_signed_v<ArithmeticType>
                                 ? ZERO // avoid overflow for long double
                                 : get_middle(MINIMUM, MAXIMUM);
    static constexpr auto LOWER_QUARTILE = get_middle(MINIMUM, MEDIAN);
    static constexpr auto UPPER_QUARTILE = get_middle(MEDIAN,  MAXIMUM);

    /// a collection of all sampled values
    static constexpr std::array<ArithmeticType, 7> VALUES = {
        ZERO,
        ONE,
        MINIMUM,
        LOWER_QUARTILE,
        MEDIAN,
        UPPER_QUARTILE,
        MAXIMUM
    };
}; // struct SampleArithmetic

} // namespace tasty_int_test

#endif // ifndef TASTY_INT_TASTY_INT_TEST_SAMPLE_ARITHMETIC_TEST_HPP
