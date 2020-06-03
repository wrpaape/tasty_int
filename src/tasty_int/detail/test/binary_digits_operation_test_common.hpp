#ifndef TASTY_INT_TASTY_INT_DETAIL_TEST_BINARY_DIGITS_OPERATION_TEST_COMMON_HPP
#define TASTY_INT_TASTY_INT_DETAIL_TEST_BINARY_DIGITS_OPERATION_TEST_COMMON_HPP

#include <vector>
#include <ostream>
#include <type_traits>

#include "tasty_int/detail/digit_type.hpp"


namespace binary_digits_operation_test_common {

/**
 * This struct is used for preparing parametric test cases for binary
 * operations involving vectors of digits that produce a vector of digits as a
 * result.
 *
 * @tparam OtherOperandType the type of operand, other_operand, to be operated
 *     on with `digits_operand`.
 */
template<typename OtherOperandType>
struct BinaryDigitsOperationTestParam
{
    /// The digits operand
    std::vector<tasty_int::detail::digit_type> digits_operand;
    /// The other operand
    OtherOperandType                           other_operand;
    /// The expected result
    std::vector<tasty_int::detail::digit_type> expected_result;
}; // struct BinaryDigitsOperationTestParam


/**
 * @brief Outputs BinaryDigitsOperationTestParam for diagnostic purposes.
 *
 * @tparam OtherOperandType the type of operand to be operated on with digits
 *
 * @param[in,out] output the output stream
 * @param[in]     test_param the BinaryDigitsOperationTestParam
 * @return a reference to @p output
 */
template<typename OtherOperandType>
std::ostream &
operator<<(std::ostream                                           &output,
           const BinaryDigitsOperationTestParam<OtherOperandType> &test_param)
{
    return output << "{ digits_operand="
                  << ::testing::PrintToString(test_param.digits_operand)
                  << ", other_operand="
                  << ::testing::PrintToString(test_param.other_operand)
                  << ", expected_result="
                  << ::testing::PrintToString(test_param.expected_result)
                  << " }";
}


/**
 * @brief Converts a vector of BinaryDigitsOperationTestParam<T> to a vector of
 *     BinaryDigitsOperationTestParam<U>.
 *
 * @tparam    AnotherOperandType the output test parameters specialization type
 * @tparam    OperandType        the input test parameters specialization type
 * @param[in] input              the input test parameters
 * @return a vector of BinaryDigitsOperationTestParam<AnotherOperandType> that
 *      is logically equivalent to @p input
 */
template<typename AnotherOperandType, typename OtherOperandType>
std::vector<BinaryDigitsOperationTestParam<AnotherOperandType>>
convert_to(
    const std::vector<BinaryDigitsOperationTestParam<OtherOperandType>> &input
)
    requires std::is_convertible_v<OtherOperandType, AnotherOperandType>
{
    std::vector<BinaryDigitsOperationTestParam<AnotherOperandType>> output;

    output.reserve(input.size());
    for (const auto &input_test_param : input)
        output.push_back({
            .digits_operand  = input_test_param.digits_operand,
            .other_operand   =
                static_cast<AnotherOperandType>(input_test_param.other_operand),
            .expected_result = input_test_param.expected_result
        });

    return output;
}

} // namespace binary_digits_operation_test_common

#endif // ifndef TASTY_INT_TASTY_INT_DETAIL_TEST_BINARY_DIGITS_OPERATION_TEST_COMMON_HPP
