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

} // namespace comparison_test_common

#endif // ifndef TASTY_INT_TASTY_INT_DETAIL_TEST_COMPARISON_TEST_COMMON
