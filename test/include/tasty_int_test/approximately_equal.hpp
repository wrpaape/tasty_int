#ifndef TASTY_INT_TEST_APPROXIMATELY_EQUAL_HPP
#define TASTY_INT_TEST_APPROXIMATELY_EQUAL_HPP

#include <cmath>

#include <limits>
#include <type_traits>


namespace tasty_int_test {
namespace detail {

template<typename LhsFloatingPointType,
         typename RhsFloatingPointType>
    requires std::is_floating_point_v<LhsFloatingPointType>
          && std::is_floating_point_v<RhsFloatingPointType>
bool
have_same_sign_infinity(LhsFloatingPointType lhs,
                        RhsFloatingPointType rhs)
{
    bool same_sign = (std::signbit(lhs) == std::signbit(rhs));
    return same_sign
        && std::isinf(lhs)
        && std::isinf(rhs);
}

/**
 * The following was adapted from cppreference:
 * https://en.cppreference.com/w/cpp/types/numeric_limits/epsilon
 */
template<typename LhsFloatingPointType,
         typename RhsFloatingPointType>
    requires std::is_floating_point_v<LhsFloatingPointType>
          && std::is_floating_point_v<RhsFloatingPointType>
bool
absolute_error_is_negligible(LhsFloatingPointType lhs,
                             RhsFloatingPointType rhs)
{
    using PromotedFloatingPointType =
        std::common_type_t<LhsFloatingPointType, RhsFloatingPointType>;

    PromotedFloatingPointType lhs_promoted = lhs;
    PromotedFloatingPointType rhs_promoted = rhs;

    auto abs_error = std::abs(lhs_promoted - rhs_promoted);
    auto max_error = std::numeric_limits<float>::epsilon()
                   * std::abs(lhs_promoted + rhs_promoted)
                   * PromotedFloatingPointType(2.0);
    bool abs_error_is_subnormal =
        std::isless(abs_error, std::numeric_limits<float>::min());

    return std::islessequal(abs_error, max_error) || abs_error_is_subnormal;
}

} // namespace detail


/**
 * @brief Tests for approximate equality between two floating point numbers
 *
 * @details "Approximately equal" here means that:
 *
 *     1. @p lhs and @p rhs are the both infinity and have the same sign
 *     or
 *     2. The absolute difference of @p lhs and @p rhs is:
 *         a. within two float ULPs (units in the last place)
 *         or
 *         b. in the subnormal range for float
 *
 *        to the effect that a value demoted to a float (without producing
 *        over/underflow) may compare "approximately equal" to the original
 *        value.
 *
 * @param[in] lhs a floating point number
 * @param[in] rhs a floating point number
 * @return true if @p lhs is approximately equal to @p rhs
 */
template<typename LhsFloatingPointType,
         typename RhsFloatingPointType>
    requires std::is_floating_point_v<LhsFloatingPointType>
          && std::is_floating_point_v<RhsFloatingPointType>
bool
approximately_equal(LhsFloatingPointType lhs,
                    RhsFloatingPointType rhs)
{
    return detail::have_same_sign_infinity(lhs, rhs)
        || detail::absolute_error_is_negligible(lhs, rhs);
}

} // namespace tasty_int_test

#endif // ifndef TASTY_INT_TEST_APPROXIMATELY_EQUAL_HPP
