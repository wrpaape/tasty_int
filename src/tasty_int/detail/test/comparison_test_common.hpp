#ifndef TASTY_INT_TASTY_INT_DETAIL_TEST_COMPARISON_TEST_COMMON
#define TASTY_INT_TASTY_INT_DETAIL_TEST_COMPARISON_TEST_COMMON

#include "gtest/gtest.h"


namespace comparison_test_common {

/**
 * This test parameter is used in conjunction with expect_unequal to exercise
 * comparison operations with unequal operands.
 *
 * @tparam SmallerType the type of the smaller magnitude operand
 * @tparam LargerType  the type of the larger magnitude operand
 */
template<typename SmallerType, typename LargerType>
struct InequalityTestParam
{
    SmallerType smaller; ///< the smaller magnitude operand
    LargerType  larger;  ///< the larger magnitude operand
}; // struct InequalityTestParam

/**
 * @brief Outputs InequalityTestParam for diagnostic purposes.
 *
 * @tparam SmallerType the type of the smaller magnitude operand
 * @tparam LargerType  the type of the larger magnitude operand
 *
 * @param[in,out] output the output stream
 * @param[in]     test_param the InequalityTestParam
 * @return a reference to @p output
 */
template<typename SmallerType, typename LargerType>
std::ostream &
operator<<(std::ostream                                       &output,
           const InequalityTestParam<SmallerType, LargerType> &test_param)
{
    return output
        << "{ smaller=" << ::testing::PrintToString(test_param.smaller)
        << ", larger="  << ::testing::PrintToString(test_param.larger) << " }";
}


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
