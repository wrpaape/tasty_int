#ifndef TASTY_INT_TEST_FLOATING_POINT_INTEGRAL_LIMITS_HPP
#define TASTY_INT_TEST_FLOATING_POINT_INTEGRAL_LIMITS_HPP

#include <limits>
#include <type_traits>


namespace tasty_int_test {

/**
 * The purpose of this class is to provide compile-time limits for floating
 * point values in the context of an integer type:  floating point values
 * outside of the range [minimum(), maximum()] will be represented with
 * precision > 1.
 *
 * @tparam FloatingPointType the floating point type of interest
 * @tparam IntegralType      the bounding integral type
 */
template<typename FloatingPointType, typename IntegralType>
    requires std::is_floating_point_v<FloatingPointType>
          && std::is_integral_v<IntegralType>
class FloatingPointIntegralLimits
{
public:
    /**
     * @return the minimum value of @p IntegralType beyond which either @p
     *     FloatingPointType will exhibit a loss in integral precision or @p
     *     IntegralType will overflow
     */
    static constexpr IntegralType
    minimum()
    {
        if constexpr (std::is_unsigned_v<IntegralType>)
            return IntegralType(0);
        else if constexpr (have_precision_loss())
            return -make_truncated_integral_limit();
        else
            return std::numeric_limits<IntegralType>::min();
    }

    /**
     * @return the maximum value of @p IntegralType beyond which either @p
     *     FloatingPointType will exhibit a loss in integral precision or @p
     *     IntegralType will overflow
     */
    static constexpr IntegralType
    maximum()
    {
        if constexpr (have_precision_loss())
            return make_truncated_integral_limit();
        else
            return std::numeric_limits<IntegralType>::max();
    }

private:
    static constexpr bool
    have_precision_loss()
    {
        return std::numeric_limits<IntegralType>::digits
             > std::numeric_limits<FloatingPointType>::digits;
    }

    static constexpr IntegralType
    make_truncated_integral_limit()
    {
        return IntegralType(1)
            << std::numeric_limits<FloatingPointType>::digits;
    }
}; // class FloatingPointIntegralLimits

} // namespace tasty_int_test

#endif // ifndef TASTY_INT_TEST_FLOATING_POINT_INTEGRAL_LIMITS_HPP
