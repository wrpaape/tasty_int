#include "tasty_int/detail/digits_addition.hpp"

#include <array>
#include <type_traits>

#include "gtest/gtest.h"

#include "tasty_int/detail/conversions/digits_from_integral.hpp"
#include "tasty_int/detail/conversions/digits_from_floating_point.hpp"
#include "tasty_int_test/logarithmic_range.hpp"


namespace {

using tasty_int::detail::operator+=;
using tasty_int::detail::operator+;
using tasty_int::detail::digit_type;
using tasty_int::detail::DIGIT_TYPE_MAX;
using tasty_int::detail::conversions::digits_from_integral;
using tasty_int::detail::conversions::digits_from_floating_point;


template<typename OtherOperandType>
struct BinaryDigitsOperationTestParam
{
    std::vector<digit_type> digits_operand;
    OtherOperandType        other_operand;
    std::vector<digit_type> expected_result;
}; // struct BinaryDigitsOperationTestParam

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
 * Converts a vector of BinaryDigitsOperationTestParam<T> to
 * a vector of BinaryDigitsOperationTestParam<U>.
 */
template<typename AnotherOperandType, typename OtherOperandType>
std::vector<BinaryDigitsOperationTestParam<AnotherOperandType>>
convert_to(
    const std::vector<
        BinaryDigitsOperationTestParam<OtherOperandType>
    > &input
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

/**
 * Creates a set of test parameters that may be used to check the consistency
 * of the addition of digits with user types with the addition of digits with
 * other digits.
 */
template<typename OtherOperandType>
std::vector<BinaryDigitsOperationTestParam<OtherOperandType>>
make_integration_test_params(
    std::vector<digit_type> (*digits_from_user_type)(OtherOperandType)
)
{
    std::vector<BinaryDigitsOperationTestParam<OtherOperandType>> test_params;

    std::array<OtherOperandType, 5> test_values = {
        OtherOperandType(0),
        std::numeric_limits<OtherOperandType>::min(),
        OtherOperandType(1), 
        std::numeric_limits<OtherOperandType>::max() / OtherOperandType(2),
        std::numeric_limits<OtherOperandType>::max()
    };

    for (OtherOperandType operand : test_values) {
        auto digits_operand = digits_from_user_type(operand);
        for (OtherOperandType other_operand : test_values)
            test_params.push_back({
                .digits_operand  = digits_operand,
                .other_operand   = other_operand,
                .expected_result = digits_operand
                                 + digits_from_user_type(other_operand)
            });
    }
        
    return test_params;
}


TEST(DigitsAndDigitsAdditionTest, DigitsPlusEqualsDigitsReturnsReferenceToLhs)
{
    std::vector<digit_type> lhs = { 1, 2, 3 };
    std::vector<digit_type> rhs = { 4, 5, 6 };

    EXPECT_EQ(&lhs, &(lhs += rhs));
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
    ::testing::ValuesIn(make_integration_test_params(digits_from_integral))
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
    DigitsAndFloatingPointAdditionIntegrationTest,
    DigitsAndFloatingPointAdditionTest,
    ::testing::ValuesIn(
        make_integration_test_params(digits_from_floating_point)
    )
);

} // namespace
