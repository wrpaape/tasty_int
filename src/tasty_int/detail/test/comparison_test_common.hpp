#ifndef TASTY_INT_TASTY_INT_DETAIL_TEST_COMPARISON_TEST_COMMON
#define TASTY_INT_TASTY_INT_DETAIL_TEST_COMPARISON_TEST_COMMON

#include "gtest/gtest.h"


namespace comparison_test_common {

/**
 * @brief EXPECT that `lhs == rhs`.
 *
 * @details Exercises all 6 comparison operators on two expectedly-equal
 *     operands and emits non-fatal google test failures if any operators
 *     behave unexpectedly.  The boolean variants of the EXPECT macros are used
 *     here in place of EXPECT_LE, EXPECT_GE, etc... so that the caller may
 *     steer ADL with `using` statements and namespace of instantiation.
 *
 * @param[in] lhs the left-hand operand
 * @param[in] rhs the right-hand operand
 */
template<typename T, typename U>
void
expect_equal(const T &lhs,
             const U &rhs)
{
    EXPECT_TRUE( lhs == rhs);
    EXPECT_TRUE( rhs == lhs);

    EXPECT_FALSE(lhs != rhs);
    EXPECT_FALSE(rhs != lhs);

    EXPECT_FALSE(lhs < rhs);
    EXPECT_FALSE(rhs < lhs);

    EXPECT_FALSE(lhs > rhs);
    EXPECT_FALSE(rhs > lhs);

    EXPECT_TRUE(lhs <= rhs);
    EXPECT_TRUE(rhs <= lhs);

    EXPECT_TRUE(lhs >= rhs);
    EXPECT_TRUE(rhs >= lhs);
}

/**
 * @brief EXPECT that `lhs < rhs`.
 *
 * @details Exercises all 6 comparison operators on two
 *     expectedly-strictly-unequal operands and emits non-fatal google test
 *     failures if any operators behave unexpectedly.  The boolean variants of
 *     the EXPECT macros are used here in place of EXPECT_LE, EXPECT_GE, etc...
 *     so that the caller may steer ADL with `using` statements and namespace
 *     of instantiation.
 *
 * @param[in] lesser the left-hand operand
 * @param[in] greater the right-hand operand
 */
template<typename T, typename U>
void
expect_unequal(const T &lesser,
               const U &greater)
{
    EXPECT_TRUE(lesser  != greater);
    EXPECT_TRUE(greater != lesser);

    EXPECT_FALSE(lesser  == greater);
    EXPECT_FALSE(greater == lesser);

    EXPECT_TRUE( lesser  < greater);
    EXPECT_FALSE(greater < lesser);

    EXPECT_TRUE( greater > lesser);
    EXPECT_FALSE(lesser  > greater);

    EXPECT_TRUE( lesser  <= greater);
    EXPECT_FALSE(greater <= lesser);

    EXPECT_TRUE( greater >= lesser);
    EXPECT_FALSE(lesser  >= greater);
}

} // namespace comparison_test_common

#endif // ifndef TASTY_INT_TASTY_INT_DETAIL_TEST_COMPARISON_TEST_COMMON
