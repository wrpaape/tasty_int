#include "tasty_int/detail/digits_addition.hpp"

#include <array>
#include <functional>
#include <type_traits>
#include <utility>

#include "gtest/gtest.h"

#include "tasty_int/detail/integral_digits_view.hpp"
#include "tasty_int/detail/conversions/digits_from_floating_point.hpp"
#include "tasty_int/detail/conversions/digits_from_integral.hpp"
#include "tasty_int/detail/test/binary_digits_operation_test_common.hpp"
#include "tasty_int_test/nonnegative_arithmetic_values.hpp"


namespace {

using tasty_int::detail::operator+=;
using tasty_int::detail::operator+;
using tasty_int::detail::add_into;
using tasty_int::detail::propagate_carry;
using tasty_int::detail::add_at;
using tasty_int::detail::digit_type;
using tasty_int::detail::digit_accumulator_type;
using tasty_int::detail::DIGIT_TYPE_MAX;
using tasty_int::detail::IntegralDigitsView;
using tasty_int::detail::conversions::digits_from_floating_point;
using tasty_int::detail::conversions::digits_from_integral;
using binary_digits_operation_test_common::BinaryDigitsOperationTestParam;
using binary_digits_operation_test_common::convert_to;


/**
 * @brief Creates a set of test parameters that may be used to check the consistency
 *     of a binary operation on digits and @p ArithmeticType with the
 *     equivalent binary operation on digits with @p ArithmeticType converted
 *     to digits.
 *
 * @tparam    ArithmeticType           the type of operand to be operated on
 *     with digits
 * @tparam    DigitsAndDigitsOperation the digits-digits version of the
 *     digits-ArithmeticType binary operation to be tested
 * @param[in] digits_from_arithmetic   a conversion function from @p
 *     ArithmeticType to digits
 * @param[in] operation                an instance of the digits-digits version
 *     of the digits-ArithmeticType binary operation to be tested
 * @return a set of test parameters generated by operating on a sample of test
 *     values 
 */
template<typename ArithmeticType,
         typename DigitsAndDigitsOperation>
std::vector<BinaryDigitsOperationTestParam<ArithmeticType>>
make_arithmetic_integration_test_params(
    std::vector<tasty_int::detail::digit_type>
                            (*digits_from_arithmetic)(ArithmeticType),
    DigitsAndDigitsOperation  operation
)
    requires std::is_arithmetic_v<ArithmeticType>
{
    std::vector<BinaryDigitsOperationTestParam<ArithmeticType>> test_params;

    for (ArithmeticType digits_value
         : tasty_int_test::NONNEGATIVE_ARITHMETIC_VALUES<ArithmeticType>) {
        auto digits_operand = digits_from_arithmetic(digits_value);
        for (ArithmeticType arithmetic_value
             : tasty_int_test::NONNEGATIVE_ARITHMETIC_VALUES<ArithmeticType>)
            test_params.push_back({
                .digits_operand  = digits_operand,
                .other_operand   = arithmetic_value,
                .expected_result =
                    operation(digits_operand,
                              digits_from_arithmetic(arithmetic_value))
            });
    }
        
    return test_params;
}

template<typename OtherOperandType>
std::vector<BinaryDigitsOperationTestParam<OtherOperandType>>
make_addition_integration_test_params(
    std::vector<tasty_int::detail::digit_type>
    (*digits_from_user_type)(OtherOperandType)
)
    requires std::is_arithmetic_v<OtherOperandType>
{
    return make_arithmetic_integration_test_params(
        digits_from_user_type,
        [](const auto& lhs, const auto& rhs)
        {
            return lhs + rhs;
        }
    );
}


TEST(DigitsAndDigitsAdditionTest, DigitsPlusEqualsDigitsReturnsReferenceToLhs)
{
    std::vector<digit_type> lhs = { 1, 2, 3 };
    std::vector<digit_type> rhs = { 4, 5, 6 };

    EXPECT_EQ(&lhs, &(lhs += rhs));
}

TEST(DigitsAndDigitsAdditionTest, DigitsPlusEqualsSelfDoublesValue)
{
    std::vector<digit_type> digits = { 1, 0, 2, DIGIT_TYPE_MAX, 1 };
    IntegralDigitsView carry(DIGIT_TYPE_MAX * 2);
    std::vector<digit_type> expected = {
        2, 0, 4, carry.low_digit(), carry.high_digit() + 2
    };

    digits += digits;

    EXPECT_EQ(expected, digits);
}

class DigitsAndDigitsAdditionTest
    : public ::testing::TestWithParam<
                 BinaryDigitsOperationTestParam<std::vector<digit_type>>
             >
{}; // class DigitsAndDigitsAdditionTest

TEST_P(DigitsAndDigitsAdditionTest, DigitsPlusEqualsDigits)
{
    std::vector<digit_type>        lhs             = GetParam().digits_operand;
    const std::vector<digit_type> &rhs             = GetParam().other_operand;
    const std::vector<digit_type> &expected_result = GetParam().expected_result;

    lhs += rhs;

    EXPECT_EQ(expected_result, lhs);
}

TEST_P(DigitsAndDigitsAdditionTest, DigitsPlusDigits)
{
    const std::vector<digit_type> &lhs             = GetParam().digits_operand;
    const std::vector<digit_type> &rhs             = GetParam().other_operand;
    const std::vector<digit_type> &expected_result = GetParam().expected_result;

    auto result = lhs + rhs;

    EXPECT_EQ(expected_result, result);
}

INSTANTIATE_TEST_SUITE_P(
    DigitsAndDigitsAdditionTestWithoutCarry,
    DigitsAndDigitsAdditionTest,
    ::testing::ValuesIn(
        std::vector<BinaryDigitsOperationTestParam<std::vector<digit_type>>> {
            { { 0 }, { 0 }, { 0 } },
            { { 1 }, { 2 }, { 3 } },

            { { 0, 0, 1 }, { 0, 0, 2 }, { 0, 0, 3 } },
            { { 1, 2, 3 }, { 4, 5, 6 }, { 5, 7, 9 } },

            {
                {              0,              0, 1 },
                { DIGIT_TYPE_MAX, DIGIT_TYPE_MAX    },
                { DIGIT_TYPE_MAX, DIGIT_TYPE_MAX, 1 }
            }
        }
    )
);

INSTANTIATE_TEST_SUITE_P(
    DigitsAndDigitsAdditionTestWithCarry,
    DigitsAndDigitsAdditionTest,
    ::testing::ValuesIn(
        std::vector<BinaryDigitsOperationTestParam<std::vector<digit_type>>> {
            {
                { DIGIT_TYPE_MAX }, { 1 }, { 0, 1 }
            },
            {
                { DIGIT_TYPE_MAX, DIGIT_TYPE_MAX, DIGIT_TYPE_MAX - 1 },
                {              1                                     },
                {              0,              0,     DIGIT_TYPE_MAX }
            },
            {
                { DIGIT_TYPE_MAX, DIGIT_TYPE_MAX, DIGIT_TYPE_MAX    },
                {              1                                    },
                {              0,              0,              0, 1 }
            },
            {
                { DIGIT_TYPE_MAX,              0,                  2    },
                {              1, DIGIT_TYPE_MAX, DIGIT_TYPE_MAX - 2    },
                {              0,              0,                  0, 1 }
            },
            {
                { DIGIT_TYPE_MAX, DIGIT_TYPE_MAX, DIGIT_TYPE_MAX - 1 },
                {              1                                     },
                {              0,              0,     DIGIT_TYPE_MAX }
            },
            {
                {              5,             23,     7 },
                {              7, DIGIT_TYPE_MAX,       },
                {             12,             22,     8 }
            },
            {
                { DIGIT_TYPE_MAX, DIGIT_TYPE_MAX, DIGIT_TYPE_MAX    },
                {              4                                    },
                {              3,              0,              0, 1 }
            },

        }
    )
);


TEST(DigitsAndIntegralAdditionTest,
     DigitsPlusEqualsIntegralReturnsReferenceToLhs)
{
    std::vector<digit_type> lhs = { 1, 2, 3 };
    std::uintmax_t          rhs = 456;

    EXPECT_EQ(&lhs, &(lhs += rhs));
}

class DigitsAndIntegralAdditionTest
    : public ::testing::TestWithParam<
          BinaryDigitsOperationTestParam<std::uintmax_t>
      >
{
public:
    static const std::vector<BinaryDigitsOperationTestParam<std::uintmax_t>>
    BASE_TEST_PARAMS;
}; // class DigitsAndIntegralAdditionTest

const std::vector<BinaryDigitsOperationTestParam<std::uintmax_t>>
DigitsAndIntegralAdditionTest::BASE_TEST_PARAMS = {
    { { 0 },  0, { 0 } },
    { { 1 },  2, { 3 } },

    { { 0 },  DIGIT_TYPE_MAX, { DIGIT_TYPE_MAX } },
    { { 1 },  DIGIT_TYPE_MAX, { 0, 1 } },

    {
        {                                        0 },
        std::numeric_limits<std::uintmax_t>::max(),
        { DIGIT_TYPE_MAX, DIGIT_TYPE_MAX }
    },
    {
        {                                        1 },
        std::numeric_limits<std::uintmax_t>::max(),
        { 0, 0, 1 }
    },
    {
        {                           DIGIT_TYPE_MAX },
        std::numeric_limits<std::uintmax_t>::max(),
        { DIGIT_TYPE_MAX - 1, 0, 1 }
    },
    {
        { 1, 2, 3, 4, 5 },
        std::numeric_limits<std::uintmax_t>::max(),
        { 0, 2, 4, 4, 5 }
    }
};

TEST_P(DigitsAndIntegralAdditionTest, DigitsPlusEqualsIntegral)
{
    std::vector<digit_type>        lhs             = GetParam().digits_operand;
    std::uintmax_t                 rhs             = GetParam().other_operand;
    const std::vector<digit_type> &expected_result = GetParam().expected_result;

    lhs += rhs;

    EXPECT_EQ(expected_result, lhs);
}

TEST_P(DigitsAndIntegralAdditionTest, DigitsPlusIntegral)
{
    const std::vector<digit_type> &lhs             = GetParam().digits_operand;
    std::uintmax_t                 rhs             = GetParam().other_operand;
    const std::vector<digit_type> &expected_result = GetParam().expected_result;

    auto result = lhs + rhs;

    EXPECT_EQ(expected_result, result);
}

TEST_P(DigitsAndIntegralAdditionTest, IntegralPlusDigits)
{
    std::uintmax_t                 lhs             = GetParam().other_operand;
    const std::vector<digit_type> &rhs             = GetParam().digits_operand;
    const std::vector<digit_type> &expected_result = GetParam().expected_result;

    auto result = lhs + rhs;

    EXPECT_EQ(expected_result, result);
}

INSTANTIATE_TEST_SUITE_P(
    DigitsAndIntegralAdditionBaseTest,
    DigitsAndIntegralAdditionTest,
    ::testing::ValuesIn(DigitsAndIntegralAdditionTest::BASE_TEST_PARAMS)
);

INSTANTIATE_TEST_SUITE_P(
    DigitsAndIntegralAdditionIntegrationTest,
    DigitsAndIntegralAdditionTest,
    ::testing::ValuesIn(
        make_addition_integration_test_params(digits_from_integral)
    )
);


TEST(DigitsAndFloatingPointAdditionTest,
     DigitsPlusEqualsFloatingPointReturnsReferenceToLhs)
{
    std::vector<digit_type> lhs = { 1, 2, 3 };
    long double             rhs = 456.456;

    EXPECT_EQ(&lhs, &(lhs += rhs));
}

class DigitsAndFloatingPointAdditionTest
    : public ::testing::TestWithParam<
          BinaryDigitsOperationTestParam<long double>
      >
{
public:
    static const std::vector<BinaryDigitsOperationTestParam<long double>>
    BASE_TEST_PARAMS;
}; // class DigitsAndFloatingPointAdditionTest

const std::vector<BinaryDigitsOperationTestParam<long double>>
DigitsAndFloatingPointAdditionTest::BASE_TEST_PARAMS =
    convert_to<long double>(DigitsAndIntegralAdditionTest::BASE_TEST_PARAMS);

TEST_P(DigitsAndFloatingPointAdditionTest, DigitsPlusEqualsFloatingPoint)
{
    std::vector<digit_type>        lhs             = GetParam().digits_operand;
    long double                    rhs             = GetParam().other_operand;
    const std::vector<digit_type> &expected_result = GetParam().expected_result;

    lhs += rhs;

    EXPECT_EQ(expected_result, lhs);
}

TEST_P(DigitsAndFloatingPointAdditionTest, DigitsPlusFloatingPoint)
{
    const std::vector<digit_type> &lhs             = GetParam().digits_operand;
    long double                    rhs             = GetParam().other_operand;
    const std::vector<digit_type> &expected_result = GetParam().expected_result;

    auto result = lhs + rhs;

    EXPECT_EQ(expected_result, result);
}

TEST_P(DigitsAndFloatingPointAdditionTest, FloatingPointPlusDigits)
{
    long double                    lhs             = GetParam().other_operand;
    const std::vector<digit_type> &rhs             = GetParam().digits_operand;
    const std::vector<digit_type> &expected_result = GetParam().expected_result;

    auto result = lhs + rhs;

    EXPECT_EQ(expected_result, result);
}

INSTANTIATE_TEST_SUITE_P(
    DigitsAndFloatingPointAdditionBaseTest,
    DigitsAndFloatingPointAdditionTest,
    ::testing::ValuesIn(DigitsAndFloatingPointAdditionTest::BASE_TEST_PARAMS)
);

INSTANTIATE_TEST_SUITE_P(
    DigitsAndFloatingPointAdditionTruncationBehaviorTest,
    DigitsAndFloatingPointAdditionTest,
    ::testing::ValuesIn(
        std::vector<BinaryDigitsOperationTestParam<long double>> {
            { { 1 }, 0.1, { 1 } },
            { { 1 }, 0.5, { 1 } },
            { { 1 }, 0.9, { 1 } },
            { { 1 }, 1.0, { 2 } },
            { { 1 }, 1.1, { 2 } },
            { { 10000 }, 10000.1, { 20000 } },
            { { 10000 }, 10000.5, { 20000 } },
            { { 10000 }, 10000.9, { 20000 } },
            { { 10000 }, 10001.0, { 20001 } },
            { { 10000 }, 10001.1, { 20001 } },
            { { 10000 }, 10001.5, { 20001 } },
            { { 10000 }, 10001.9, { 20001 } },
            { { 10000 }, 10002.0, { 20002 } }
        }
    )
);

INSTANTIATE_TEST_SUITE_P(
    DigitsAndFloatingPointAdditionIntegrationTest,
    DigitsAndFloatingPointAdditionTest,
    ::testing::ValuesIn(
        make_addition_integration_test_params(digits_from_floating_point)
    )
);


class AddIntoTest : public ::testing::Test
{
protected:
    using ResultType = std::pair<digit_accumulator_type,
                                 std::vector<digit_type>::iterator>;

    void
    check_result(digit_accumulator_type expected_carry,
                 ResultType             result);

    std::vector<digit_type> augend;
    std::vector<digit_type> addend;
}; // class AddIntoTest

void
AddIntoTest::check_result(digit_accumulator_type expected_carry,
                          ResultType             result)
{
    EXPECT_EQ(expected_carry, result.first);
    EXPECT_TRUE(result.second == (augend.begin() + addend.size()));
}

TEST_F(AddIntoTest, NoCarry)
{
    augend = { 0, 1 };
    addend = { DIGIT_TYPE_MAX, 1 };

    ResultType result = add_into(addend, augend);

    check_result(0, result);
}

TEST_F(AddIntoTest, Carry)
{
    augend = { DIGIT_TYPE_MAX, DIGIT_TYPE_MAX, DIGIT_TYPE_MAX };
    addend = { 1 };

    ResultType result = add_into(addend, augend);

    check_result(1, result);
}


class PropagateCarryTest : public ::testing::Test
{
protected:
    void
    check_result(digit_accumulator_type         expected_carry,
                 const std::vector<digit_type> &expected_augend,
                 digit_accumulator_type         carry);

    std::vector<digit_type> augend;
}; // class PropagateCarryTest

void
PropagateCarryTest::check_result(digit_accumulator_type         expected_carry,
                                 const std::vector<digit_type> &expected_augend,
                                 digit_accumulator_type         carry)
{
    EXPECT_EQ(expected_carry,  carry);
    EXPECT_EQ(expected_augend, augend);
}

TEST_F(PropagateCarryTest, NoCarry)
{
    augend = { 1, 2, 3 };

    auto carry = propagate_carry(10, augend.begin() + 1, augend.end());

    check_result(0, { 1, 12, 3 }, carry);
}

TEST_F(PropagateCarryTest, InnerCarry)
{
    augend = { 1, 1, 3 };

    auto carry = propagate_carry(DIGIT_TYPE_MAX, augend.begin() + 1, augend.end());

    check_result(0, { 1, 0, 4 }, carry);
}

TEST_F(PropagateCarryTest, CarryOut)
{
    augend = { DIGIT_TYPE_MAX, DIGIT_TYPE_MAX, DIGIT_TYPE_MAX, DIGIT_TYPE_MAX };

    auto carry = propagate_carry(1, augend.begin(), augend.end());

    check_result(1, { 0, 0, 0, 0 }, carry);
}


class AddAtTest : public ::testing::Test
{
protected:
    void
    check_result(digit_accumulator_type         expected_carry,
                 const std::vector<digit_type> &expected_augend,
                 digit_accumulator_type         carry);

    std::vector<digit_type> augend;
}; // class AddAtTest

void
AddAtTest::check_result(digit_accumulator_type         expected_carry,
                        const std::vector<digit_type> &expected_augend,
                        digit_accumulator_type         carry)
{
    EXPECT_EQ(expected_carry,  carry);
    EXPECT_EQ(expected_augend, augend);
}

TEST_F(AddAtTest, NoCarry)
{
    augend = { 0, 0, 0, 1 };

    auto carry = add_at(123, augend.begin() + 2);

    check_result(0, { 0, 0, 123, 1 }, carry);
}

TEST_F(AddAtTest, Carry)
{
    augend = { DIGIT_TYPE_MAX };

    auto carry = add_at(1, augend.begin());

    check_result(1, { 0 }, carry);
}

} // namespace
