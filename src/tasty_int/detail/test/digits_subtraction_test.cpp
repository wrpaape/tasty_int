#include "tasty_int/detail/digits_subtraction.hpp"

#include <type_traits>

#include "gtest/gtest.h"

#include "tasty_int/detail/integer.hpp"
#include "tasty_int/detail/sign_from_signed_arithmetic.hpp"
#include "tasty_int/detail/sign_from_unsigned_arithmetic.hpp"
#include "tasty_int/detail/sign_from_digits.hpp"
#include "tasty_int/detail/conversions/digits_from_floating_point.hpp"
#include "tasty_int/detail/conversions/digits_from_integral.hpp"
#include "tasty_int/detail/test/binary_digits_operation_test_common.hpp"
#include "tasty_int/detail/test/integer_test_common.hpp"
#include "tasty_int_test/logarithmic_range.hpp"


namespace {

using tasty_int::detail::subtract;
using tasty_int::detail::subtract_in_place;
using tasty_int::detail::DIGIT_BASE;
using tasty_int::detail::DIGIT_TYPE_MAX;
using tasty_int::detail::Integer;
using tasty_int::detail::Sign;
using tasty_int::detail::digit_type;
using tasty_int::detail::sign_from_signed_arithmetic;
using tasty_int::detail::sign_from_unsigned_arithmetic;
using tasty_int::detail::sign_from_digits;
using tasty_int::detail::conversions::digits_from_floating_point;
using tasty_int::detail::conversions::digits_from_integral;
using binary_digits_operation_test_common::BinaryDigitsOperationTestParam;
using binary_digits_operation_test_common::convert_to;


template<typename SubtrahendType>
void
test_subtract_in_place(const std::vector<digit_type> &minuend,
                       const SubtrahendType          &subtrahend,
                       const Integer                 &expected_result)
{
    std::vector<digit_type> result_digits = minuend;

    Sign result_sign = subtract_in_place(subtrahend, result_digits);

    Integer result = { .sign = result_sign, .digits = result_digits };
    EXPECT_EQ(expected_result, result);
}

template<typename MinuendType, typename SubtrahendType>
void
test_subtract(const MinuendType    &minuend,
              const SubtrahendType &subtrahend,
              const Integer        &expected_result)
{
    auto [result_sign, result_digits] = subtract(minuend, subtrahend);

    Integer result = { .sign = result_sign, .digits = result_digits };
    EXPECT_EQ(expected_result, result);
}

template<typename SubtrahendType>
void
test_subtract_from_digits(const std::vector<digit_type> &minuend,
                          const SubtrahendType          &subtrahend,
                          const Integer                 &expected_result)
{
    test_subtract_in_place(minuend, subtrahend, expected_result);

    if constexpr (std::is_same_v<SubtrahendType, std::vector<digit_type>>)
        test_subtract(minuend, subtrahend, expected_result);
}

template<typename SubtrahendType>
void
test_subtract_from_digits(
    const BinaryDigitsOperationTestParam<SubtrahendType> &test_param,
    Sign                                                  expected_sign
)
{
    const std::vector<digit_type> &minuend         = test_param.digits_operand;
    const SubtrahendType          &subtrahend      = test_param.other_operand;
    const std::vector<digit_type> &expected_digits = test_param.expected_result;
    Integer expected_result = {
        .sign   = expected_sign,
        .digits = expected_digits
    };

    test_subtract_from_digits(minuend, subtrahend, expected_result);
}

template<typename MinuendType>
void
test_subtract_from_arithmetic(
    const BinaryDigitsOperationTestParam<MinuendType> &test_param,
    Sign                                               expected_sign
)
    requires std::is_arithmetic_v<MinuendType>
{
    MinuendType                    minuend         = test_param.other_operand;
    const std::vector<digit_type> &subtrahend      = test_param.digits_operand;
    const std::vector<digit_type> &expected_digits = test_param.expected_result;
    Integer expected_result = {
        .sign   = expected_sign,
        .digits = expected_digits
    };

    test_subtract(minuend, subtrahend, expected_result);
}


class DigitsSubtractionIdentitiesTest
    : public ::testing::TestWithParam<std::vector<digit_type>>
{}; // class DigitsSubtractionIdentitiesTest

TEST_P(DigitsSubtractionIdentitiesTest,
       DigitsValueMinusIdenticalDigitsValueEqualsZero)
{
    std::vector<digit_type> minuend    = GetParam();
    std::vector<digit_type> subtrahend = minuend;
    Integer ZERO = { .sign = Sign::ZERO, .digits = { 0 } };

    test_subtract_from_digits(minuend, subtrahend, ZERO);
}

TEST_P(DigitsSubtractionIdentitiesTest, DigitsValueMinusSelfEqualsZero)
{
    std::vector<digit_type> digits = GetParam();
    Integer ZERO = { .sign = Sign::ZERO, .digits = { 0 } };

    auto sign = subtract_in_place(digits, digits);

    Integer result = { .sign = sign, .digits = digits };
    EXPECT_EQ(ZERO, result);
}

TEST_P(DigitsSubtractionIdentitiesTest,
       DigitsValueMinusZeroDigitsValueEqualsOriginalValue)
{
    std::vector<digit_type> minuend = GetParam();
    std::vector<digit_type> ZERO    = { 0 };
    Integer original = {
        .sign   = sign_from_digits(minuend, Sign::POSITIVE),
        .digits = minuend
    };

    test_subtract_from_digits(minuend, ZERO, original);
}

TEST_P(DigitsSubtractionIdentitiesTest,
       DigitsValueMinusZeroIntegralValueEqualsOriginalValue)
{
    std::vector<digit_type> minuend = GetParam();
    std::uintmax_t          ZERO    = 0;
    Integer original = {
        .sign   = sign_from_digits(minuend, Sign::POSITIVE),
        .digits = minuend
    };

    test_subtract_from_digits(minuend, ZERO, original);
}

INSTANTIATE_TEST_SUITE_P(
    DigitsSubtractionTest,
    DigitsSubtractionIdentitiesTest,
    ::testing::ValuesIn(
        std::vector<std::vector<digit_type>> {
            { 0 },
            { 1 },
            { 2 },
            { DIGIT_TYPE_MAX },
            { 0, 1 },
            { 1, 1 },
            { 2, 1 },
            { 0, DIGIT_TYPE_MAX },
            { 1, DIGIT_TYPE_MAX },
            { 2, DIGIT_TYPE_MAX },
            { DIGIT_TYPE_MAX, DIGIT_TYPE_MAX },
            { DIGIT_TYPE_MAX, 1 },
            { DIGIT_TYPE_MAX, 2 },
            { DIGIT_TYPE_MAX, DIGIT_TYPE_MAX },
            { 0, 0, 1 },
            { 1, 2, 3, 4, 5, 6, 7, 8, 9, 8, 7, 6, 5, 4, 3, 2, 1 },
            { DIGIT_TYPE_MAX , DIGIT_TYPE_MAX, DIGIT_TYPE_MAX },
        }
    )
);


class DigitsAndDigitsNonzeroResultSubtractionTest
    : public ::testing::TestWithParam<
          BinaryDigitsOperationTestParam<std::vector<digit_type>>
      >
{}; // class DigitsAndDigitsNonzeroResultSubtractionTest

class DigitsMinusDigitsPositiveResultSubtractionTest
    : public DigitsAndDigitsNonzeroResultSubtractionTest
{}; // class DigitsMinusDigitsPositiveResultSubtractionTest

TEST_P(DigitsMinusDigitsPositiveResultSubtractionTest,
       LargerMinusSmallerProducesPositiveResult)
{
    test_subtract_from_digits(GetParam(), Sign::POSITIVE);
}

INSTANTIATE_TEST_SUITE_P(
    DigitsSubtractionTest,
    DigitsMinusDigitsPositiveResultSubtractionTest,
    ::testing::ValuesIn(
        std::vector<BinaryDigitsOperationTestParam<std::vector<digit_type>>> {
            { { 3 }, { 2 }, { 1 } },
            { { DIGIT_TYPE_MAX }, { 7 }, { DIGIT_TYPE_MAX - 7 } },

            { { 0, 0, 3 }, { 0, 0, 1 }, { 0, 0, 2 } },
            { { 5, 7, 9 }, { 1, 2, 3 }, { 4, 5, 6 } },

            {
                {     DIGIT_TYPE_MAX,     DIGIT_TYPE_MAX,     DIGIT_TYPE_MAX },
                {                  1,                  1,                  1 },
                { DIGIT_TYPE_MAX - 1, DIGIT_TYPE_MAX - 1, DIGIT_TYPE_MAX - 1 }
            },

            {
                {              0, 1 },
                {              1    },
                { DIGIT_TYPE_MAX    }
            },
            {
                { 0,              0, 1 },
                { 0,              1    },
                { 0, DIGIT_TYPE_MAX    }
            },
            {
                {              1,              0, 1 },
                { DIGIT_TYPE_MAX, DIGIT_TYPE_MAX    },
                {              2                    }
            },
            {
                {     DIGIT_TYPE_MAX, DIGIT_TYPE_MAX, DIGIT_TYPE_MAX },
                { DIGIT_TYPE_MAX - 2, DIGIT_TYPE_MAX, DIGIT_TYPE_MAX },
                {                  2                                 }
            }
        }
    )
);


class DigitsMinusDigitsNegativeResultSubtractionTest
    : public DigitsAndDigitsNonzeroResultSubtractionTest
{}; // class DigitsMinusDigitsNegativeResultSubtractionTest

TEST_P(DigitsMinusDigitsNegativeResultSubtractionTest,
       SmallerMinusLargerProducesNegativeResult)
{
    test_subtract_from_digits(GetParam(), Sign::NEGATIVE);
}

INSTANTIATE_TEST_SUITE_P(
    DigitsSubtractionTest,
    DigitsMinusDigitsNegativeResultSubtractionTest,
    ::testing::ValuesIn(
        std::vector<BinaryDigitsOperationTestParam<std::vector<digit_type>>> {
            { { 0 }, { 1 }, { 1 } },
            { { 0 }, { 2 }, { 2 } },
            { { 0 }, { DIGIT_TYPE_MAX }, { DIGIT_TYPE_MAX } },
            { { 1 }, { 2 }, { 1 } },
            { { 1 }, { DIGIT_TYPE_MAX }, { DIGIT_TYPE_MAX - 1 } },
            { { 2 }, { 7 }, { 5 } },
            { { 2 }, { DIGIT_TYPE_MAX }, { DIGIT_TYPE_MAX - 2 } },

            { { 0, 0, 1 }, { 0, 0, 3 }, { 0, 0, 2 } },
            { { 1, 2, 3 }, { 5, 7, 9 }, { 4, 5, 6 } },

            {
                {                  1,                  1,                  1 },
                {     DIGIT_TYPE_MAX,     DIGIT_TYPE_MAX,     DIGIT_TYPE_MAX },
                { DIGIT_TYPE_MAX - 1, DIGIT_TYPE_MAX - 1, DIGIT_TYPE_MAX - 1 }
            },
            {
                {                  0                                         },
                {     DIGIT_TYPE_MAX,     DIGIT_TYPE_MAX,     DIGIT_TYPE_MAX },
                {     DIGIT_TYPE_MAX,     DIGIT_TYPE_MAX,     DIGIT_TYPE_MAX }
            },
            {
                {     DIGIT_TYPE_MAX,     DIGIT_TYPE_MAX                     },
                {     DIGIT_TYPE_MAX,     DIGIT_TYPE_MAX,     DIGIT_TYPE_MAX },
                {                  0,                  0,     DIGIT_TYPE_MAX }
            }
        }
    )
);


class IntegralSubtractionIdentitiesTest
    : public ::testing::TestWithParam<std::uintmax_t>
{}; // class IntegralSubtractionIdentitiesTest

TEST_P(IntegralSubtractionIdentitiesTest,
       DigitsValueMinusIdentiticalIntegralValueEqualsZero)
{
    Integer ZERO = { .sign = Sign::ZERO, .digits = { 0 } };

    std::uintmax_t          subtrahend = GetParam();
    std::vector<digit_type> minuend    = digits_from_integral(subtrahend);

    test_subtract_from_digits(minuend, subtrahend, ZERO);
}

TEST_P(IntegralSubtractionIdentitiesTest,
       IntegralValueMinusIdenticalDigitsValueEqualsZero)
{
    Integer ZERO = { .sign = Sign::ZERO, .digits = { 0 } };

    std::uintmax_t          minuend    = GetParam();
    std::vector<digit_type> subtrahend = digits_from_integral(minuend);

    test_subtract(minuend, subtrahend, ZERO);
}

TEST_P(IntegralSubtractionIdentitiesTest,
       IntegralValueMinusZeroDigitsValueEqualsOriginalValue)
{
    std::uintmax_t          minuend = GetParam();
    std::vector<digit_type> ZERO    = { 0 };
    Integer original = {
        .sign   = sign_from_unsigned_arithmetic(minuend),
        .digits = digits_from_integral(minuend)
    };

    test_subtract(minuend, ZERO, original);
}

INSTANTIATE_TEST_SUITE_P(
    DigitsSubtractionTest,
    IntegralSubtractionIdentitiesTest,
    tasty_int_test::logarithmic_range<std::uintmax_t>(
        0, std::numeric_limits<std::uintmax_t>::max(), 2
    )
);

class DigitsAndIntegralNonzeroResultSubtractionTest
    : public ::testing::TestWithParam<
          BinaryDigitsOperationTestParam<std::uintmax_t>
      >
{}; // class DigitsAndIntegralNonzeroResultSubtractionTest

class DigitsMinusIntegralPositiveResultSubtractionTest
    : public DigitsAndIntegralNonzeroResultSubtractionTest
{
public:
    static const std::vector<BinaryDigitsOperationTestParam<std::uintmax_t>>
    BASE_TEST_PARAMS;
}; // class DigitsMinusIntegralPositiveResultSubtractionTest

const std::vector<BinaryDigitsOperationTestParam<std::uintmax_t>>
DigitsMinusIntegralPositiveResultSubtractionTest::BASE_TEST_PARAMS = {
    { { 3 }, 2, { 1 } },
    { { DIGIT_TYPE_MAX }, 7, { DIGIT_TYPE_MAX - 7 } },

    { { 0, 3 }, DIGIT_BASE, { 0, 2 } },
    { { 5, 7 },  (DIGIT_TYPE_MAX * 2) + 3, { 4, 5 } },

    {
        {     DIGIT_TYPE_MAX, DIGIT_TYPE_MAX     },
          DIGIT_TYPE_MAX + 2,
        { DIGIT_TYPE_MAX - 1, DIGIT_TYPE_MAX - 1 }
    },

    {
        {              0, 1 },
                       1,
        { DIGIT_TYPE_MAX    }
    },
    {
        {          0,              0, 1 },
          DIGIT_BASE,
        {          0, DIGIT_TYPE_MAX    }
    },
    {
        { 1, 0, 1 },
        std::numeric_limits<std::uintmax_t>::max(),
        { 2 }
    },
    {
        { DIGIT_TYPE_MAX, DIGIT_TYPE_MAX },
        std::numeric_limits<std::uintmax_t>::max() - 2,
        { 2                              }
    },
    {
        {              0,              0,              0, 1 },
                       1,
        { DIGIT_TYPE_MAX, DIGIT_TYPE_MAX, DIGIT_TYPE_MAX    }
    },
    {
        {                  0,              0,              0, 1 },
                           2,
        { DIGIT_TYPE_MAX - 1, DIGIT_TYPE_MAX, DIGIT_TYPE_MAX    }
    },
    {
        {              0,              0,              0, 1 },
          DIGIT_TYPE_MAX,
        {              1, DIGIT_TYPE_MAX, DIGIT_TYPE_MAX }
    },
    {
        {              0,              0, 1, 1 },
              DIGIT_BASE,
        {              0, DIGIT_TYPE_MAX, 0, 1 }
    }
};

TEST_P(DigitsMinusIntegralPositiveResultSubtractionTest,
       LargerMinusSmallerProducesPositiveResult)
{
    test_subtract_from_digits(GetParam(), Sign::POSITIVE);
}

INSTANTIATE_TEST_SUITE_P(
    DigitsSubtractionTest,
    DigitsMinusIntegralPositiveResultSubtractionTest,
    ::testing::ValuesIn(
        DigitsMinusIntegralPositiveResultSubtractionTest::BASE_TEST_PARAMS
    )
);

class DigitsMinusIntegralNegativeResultSubtractionTest
    : public DigitsAndIntegralNonzeroResultSubtractionTest
{
public:
    static const std::vector<BinaryDigitsOperationTestParam<std::uintmax_t>>
    BASE_TEST_PARAMS;
}; // class DigitsMinusIntegralNegativeResultSubtractionTest

const std::vector<BinaryDigitsOperationTestParam<std::uintmax_t>>
DigitsMinusIntegralNegativeResultSubtractionTest::BASE_TEST_PARAMS = {
    { { 0 }, 1, { 1 } },
    { { 0 }, 2, { 2 } },
    { { 0 }, DIGIT_TYPE_MAX, { DIGIT_TYPE_MAX } },
    { { 1 }, 2, { 1 } },
    { { 1 }, DIGIT_TYPE_MAX, { DIGIT_TYPE_MAX - 1 } },
    { { 2 }, 7, { 5 } },
    { { 2 }, DIGIT_TYPE_MAX, { DIGIT_TYPE_MAX - 2 } },
    { { 0 }, DIGIT_BASE, { 0, 1 } },
    { { 1 }, DIGIT_BASE, { DIGIT_TYPE_MAX } },
    { { DIGIT_TYPE_MAX }, DIGIT_BASE, { 1 } },
    {
        {                                          0                 },
          std::numeric_limits<std::uintmax_t>::max(),
        {                             DIGIT_TYPE_MAX, DIGIT_TYPE_MAX }
    },
    {
        {                                          1                 },
          std::numeric_limits<std::uintmax_t>::max(),
        {                         DIGIT_TYPE_MAX - 1, DIGIT_TYPE_MAX }
    },
    {
        {                             DIGIT_TYPE_MAX },
          std::numeric_limits<std::uintmax_t>::max(),
        {                                          0, DIGIT_TYPE_MAX }
    }
};

TEST_P(DigitsMinusIntegralNegativeResultSubtractionTest,
       SmallerMinusLargerProducesNegativeResult)
{
    test_subtract_from_digits(GetParam(), Sign::NEGATIVE);
}

INSTANTIATE_TEST_SUITE_P(
    DigitsSubtractionTest,
    DigitsMinusIntegralNegativeResultSubtractionTest,
    ::testing::ValuesIn(
        DigitsMinusIntegralNegativeResultSubtractionTest::BASE_TEST_PARAMS
    )
);

class IntegralMinusDigitsPositiveResultSubtractionTest
    : public DigitsAndIntegralNonzeroResultSubtractionTest
{
public:
    static const std::vector<BinaryDigitsOperationTestParam<std::uintmax_t>>
    BASE_TEST_PARAMS;
}; // class IntegralMinusDigitsPositiveResultSubtractionTest

const std::vector<BinaryDigitsOperationTestParam<std::uintmax_t>>
IntegralMinusDigitsPositiveResultSubtractionTest::BASE_TEST_PARAMS = {
    { { 2 }, 3, { 1 } },
    { { 7 }, DIGIT_TYPE_MAX, { DIGIT_TYPE_MAX - 7 } },

    { { 0, 1 }, 3 * DIGIT_BASE, { 0, 2 } },
    { { 1, 2 }, (7 * DIGIT_BASE) + 5, { 4, 5 } },

    {
        {                         DIGIT_TYPE_MAX - 2, DIGIT_TYPE_MAX },
          std::numeric_limits<std::uintmax_t>::max(),
        {                                          2                 }
    },
    {
        {                             DIGIT_TYPE_MAX                 },
          std::numeric_limits<std::uintmax_t>::max(),
        {                                          0, DIGIT_TYPE_MAX }
    }
};

TEST_P(IntegralMinusDigitsPositiveResultSubtractionTest,
       LargerMinusSmallerProducesPositiveResult)
{
    test_subtract_from_arithmetic(GetParam(), Sign::POSITIVE);
}

INSTANTIATE_TEST_SUITE_P(
    DigitsSubtractionTest,
    IntegralMinusDigitsPositiveResultSubtractionTest,
    ::testing::ValuesIn(
        IntegralMinusDigitsPositiveResultSubtractionTest::BASE_TEST_PARAMS
    )
);

class IntegralMinusDigitsNegativeResultSubtractionTest
    : public DigitsAndIntegralNonzeroResultSubtractionTest
{
public:
    static const std::vector<BinaryDigitsOperationTestParam<std::uintmax_t>>
    BASE_TEST_PARAMS;
}; // class IntegralMinusDigitsNegativeResultSubtractionTest

const std::vector<BinaryDigitsOperationTestParam<std::uintmax_t>>
IntegralMinusDigitsNegativeResultSubtractionTest::BASE_TEST_PARAMS = { 
    { { 1 }, 0, { 1 } },
    { { 2 }, 0, { 2 } },
    { { DIGIT_TYPE_MAX }, 0, { DIGIT_TYPE_MAX } },
    { { 2 }, 1, { 1 } },
    { { DIGIT_TYPE_MAX }, 1, { DIGIT_TYPE_MAX - 1 } },
    { { 7 }, 2, { 5 } },
    { { DIGIT_TYPE_MAX }, 2, { DIGIT_TYPE_MAX - 2 } },


    { { 0, 1 }, 0, { 0, 1 } },


    { { 0, 1 }, 1, { DIGIT_TYPE_MAX } },
    { { 0, 1 }, DIGIT_TYPE_MAX, { 1 } },

    {
        { DIGIT_TYPE_MAX, DIGIT_TYPE_MAX },
                       0,
        { DIGIT_TYPE_MAX, DIGIT_TYPE_MAX }
    },
    {
        {     DIGIT_TYPE_MAX, DIGIT_TYPE_MAX },
                           1,
        { DIGIT_TYPE_MAX - 1, DIGIT_TYPE_MAX }
    },
    {
        { DIGIT_TYPE_MAX, DIGIT_TYPE_MAX },
          DIGIT_TYPE_MAX,
        {              0, DIGIT_TYPE_MAX }
    },
    {
        { DIGIT_TYPE_MAX, 0, 1 },
          std::numeric_limits<std::uintmax_t>::max(),
        {              0, 1    }
    },
    {
        { DIGIT_TYPE_MAX, DIGIT_TYPE_MAX, DIGIT_TYPE_MAX },
          std::numeric_limits<std::uintmax_t>::max(),
        {              0,              0, DIGIT_TYPE_MAX }
    }
};

TEST_P(IntegralMinusDigitsNegativeResultSubtractionTest,
       SmallerMinusLargerProducesNegativeResult)
{
    test_subtract_from_arithmetic(GetParam(), Sign::NEGATIVE);
}

INSTANTIATE_TEST_SUITE_P(
    DigitsSubtractionTest,
    IntegralMinusDigitsNegativeResultSubtractionTest,
    ::testing::ValuesIn(
        IntegralMinusDigitsNegativeResultSubtractionTest::BASE_TEST_PARAMS
    )
);


class FloatingPointSubtractionIdentitiesTest
    : public ::testing::TestWithParam<long double>
{}; // class FloatingPointSubtractionIdentitiesTest

TEST_P(FloatingPointSubtractionIdentitiesTest,
       DigitsValueMinusIdentiticalFloatingPointValueEqualsZero)
{
    Integer ZERO = { .sign = Sign::ZERO, .digits = { 0 } };

    long double             subtrahend = GetParam();
    std::vector<digit_type> minuend    = digits_from_floating_point(subtrahend);

    test_subtract_from_digits(minuend, subtrahend, ZERO);
}

TEST_P(FloatingPointSubtractionIdentitiesTest,
       FloatingPointValueMinusIdenticalDigitsValueEqualsZero)
{
    Integer ZERO = { .sign = Sign::ZERO, .digits = { 0 } };

    long double             minuend    = GetParam();
    std::vector<digit_type> subtrahend = digits_from_floating_point(minuend);

    test_subtract(minuend, subtrahend, ZERO);
}

TEST_P(FloatingPointSubtractionIdentitiesTest,
       FloatingPointValueMinusZeroDigitsValueEqualsOriginalValue)
{
    long double             minuend = GetParam();
    std::vector<digit_type> ZERO    = { 0 };
    Integer original = {
        .sign   = sign_from_signed_arithmetic(minuend),
        .digits = digits_from_floating_point(minuend)
    };

    test_subtract(minuend, ZERO, original);
}

INSTANTIATE_TEST_SUITE_P(
    DigitsSubtractionTest,
    FloatingPointSubtractionIdentitiesTest,
    tasty_int_test::logarithmic_range<long double>(
        0.0L, std::numeric_limits<long double>::max(), 1.0e40
    )
);

class DigitsAndFloatingPointNonzeroResultSubtractionTest
    : public ::testing::TestWithParam<
          BinaryDigitsOperationTestParam<long double>
      >
{}; // class DigitsAndFloatingPointNonzeroResultSubtractionTest

class DigitsMinusFloatingPointPositiveResultSubtractionTest
    : public DigitsAndFloatingPointNonzeroResultSubtractionTest
{
public:
    static const std::vector<BinaryDigitsOperationTestParam<long double>>
    BASE_TEST_PARAMS;
}; // class DigitsMinusFloatingPointPositiveResultSubtractionTest

const std::vector<BinaryDigitsOperationTestParam<long double>>
DigitsMinusFloatingPointPositiveResultSubtractionTest::BASE_TEST_PARAMS =
    convert_to<long double>(
        DigitsMinusIntegralPositiveResultSubtractionTest::BASE_TEST_PARAMS
    );

TEST_P(DigitsMinusFloatingPointPositiveResultSubtractionTest,
       LargerMinusSmallerProducesPositiveResult)
{
    test_subtract_from_digits(GetParam(), Sign::POSITIVE);
}

INSTANTIATE_TEST_SUITE_P(
    DigitsAndFloatingPointSubtractionBaseTest,
    DigitsMinusFloatingPointPositiveResultSubtractionTest,
    ::testing::ValuesIn(
        DigitsMinusFloatingPointPositiveResultSubtractionTest::BASE_TEST_PARAMS
    )
);

INSTANTIATE_TEST_SUITE_P(
    DigitsAndFloatingPointSubtractionTruncationBehaviorTest,
    DigitsMinusFloatingPointPositiveResultSubtractionTest,
    ::testing::ValuesIn(
        std::vector<BinaryDigitsOperationTestParam<long double>> {
            { { 2 }, 0.1, { 1 } },
            { { 2 }, 0.5, { 1 } },
            { { 2 }, 0.9, { 1 } },
            { { 2 }, 1.0, { 1 } },
            { { 3 }, 1.1, { 1 } },
            { { 20000 }, 10000.1, { 9999 } },
            { { 20000 }, 10000.5, { 9999 } },
            { { 20000 }, 10000.9, { 9999 } },
            { { 20000 }, 10001.0, { 9999 } },
            { { 20000 }, 10001.1, { 9998 } },
            { { 20000 }, 10001.5, { 9998 } },
            { { 20000 }, 10001.9, { 9998 } },
            { { 20000 }, 10002.0, { 9998 } }
        }
    )
);

class DigitsMinusFloatingPointNegativeResultSubtractionTest
    : public DigitsAndFloatingPointNonzeroResultSubtractionTest
{
public:
    static const std::vector<BinaryDigitsOperationTestParam<long double>>
    BASE_TEST_PARAMS;
}; // class DigitsMinusFloatingPointNegativeResultSubtractionTest

const std::vector<BinaryDigitsOperationTestParam<long double>>
DigitsMinusFloatingPointNegativeResultSubtractionTest::BASE_TEST_PARAMS =
    convert_to<long double>(
        DigitsMinusIntegralNegativeResultSubtractionTest::BASE_TEST_PARAMS
    );

TEST_P(DigitsMinusFloatingPointNegativeResultSubtractionTest,
       SmallerMinusLargerProducesNegativeResult)
{
    test_subtract_from_digits(GetParam(), Sign::NEGATIVE);
}

INSTANTIATE_TEST_SUITE_P(
    DigitsSubtractionTest,
    DigitsMinusFloatingPointNegativeResultSubtractionTest,
    ::testing::ValuesIn(
        DigitsMinusFloatingPointNegativeResultSubtractionTest::BASE_TEST_PARAMS
    )
);

INSTANTIATE_TEST_SUITE_P(
    DigitsAndFloatingPointSubtractionTruncationBehaviorTest,
    DigitsMinusFloatingPointNegativeResultSubtractionTest,
    ::testing::ValuesIn(
        std::vector<BinaryDigitsOperationTestParam<long double>> {
            { { 1 }, 2.1, { 1 } },
            { { 1 }, 2.5, { 1 } },
            { { 1 }, 2.9, { 1 } },
            { { 1 }, 3.0, { 2 } },
            { { 1 }, 3.1, { 2 } },
            { { 10000 }, 20000.1, { 10000 } },
            { { 10000 }, 20000.5, { 10000 } },
            { { 10000 }, 20000.9, { 10000 } },
            { { 10000 }, 20001.0, { 10001 } },
            { { 10000 }, 20001.1, { 10001 } },
            { { 10000 }, 20001.5, { 10001 } },
            { { 10000 }, 20001.9, { 10001 } },
            { { 10000 }, 20002.0, { 10002 } }
        }
    )
);


class FloatingPointMinusDigitsPositiveResultSubtractionTest
    : public DigitsAndFloatingPointNonzeroResultSubtractionTest
{
public:
    static const std::vector<BinaryDigitsOperationTestParam<long double>>
    BASE_TEST_PARAMS;
}; // class FloatingPointMinusDigitsPositiveResultSubtractionTest

const std::vector<BinaryDigitsOperationTestParam<long double>>
FloatingPointMinusDigitsPositiveResultSubtractionTest::BASE_TEST_PARAMS =
    convert_to<long double>(
        IntegralMinusDigitsPositiveResultSubtractionTest::BASE_TEST_PARAMS
    );

TEST_P(FloatingPointMinusDigitsPositiveResultSubtractionTest,
       LargerMinusSmallerProducesPositiveResult)
{
    test_subtract_from_arithmetic(GetParam(), Sign::POSITIVE);
}

INSTANTIATE_TEST_SUITE_P(
    DigitsSubtractionTest,
    FloatingPointMinusDigitsPositiveResultSubtractionTest,
    ::testing::ValuesIn(
        FloatingPointMinusDigitsPositiveResultSubtractionTest::BASE_TEST_PARAMS
    )
);

INSTANTIATE_TEST_SUITE_P(
    DigitsAndFloatingPointSubtractionTruncationBehaviorTest,
    FloatingPointMinusDigitsPositiveResultSubtractionTest,
    ::testing::ValuesIn(
        std::vector<BinaryDigitsOperationTestParam<long double>> {
            { { 2 }, 3.1, { 1 } },
            { { 2 }, 3.5, { 1 } },
            { { 2 }, 3.9, { 1 } },
            { { 2 }, 4.0, { 2 } },
            { { 2 }, 4.1, { 2 } },
            { { 20000 }, 30000.1, { 10000 } },
            { { 20000 }, 30000.5, { 10000 } },
            { { 20000 }, 30000.9, { 10000 } },
            { { 20000 }, 30001.0, { 10001 } },
            { { 20000 }, 30001.1, { 10001 } },
            { { 20000 }, 30001.5, { 10001 } },
            { { 20000 }, 30001.9, { 10001 } },
            { { 20000 }, 30002.0, { 10002 } }
        }
    )
);

class FloatingPointMinusDigitsNegativeResultSubtractionTest
    : public DigitsAndFloatingPointNonzeroResultSubtractionTest
{
public:
    static const std::vector<BinaryDigitsOperationTestParam<long double>>
    BASE_TEST_PARAMS;
}; // class FloatingPointMinusDigitsNegativeResultSubtractionTest

const std::vector<BinaryDigitsOperationTestParam<long double>>
FloatingPointMinusDigitsNegativeResultSubtractionTest::BASE_TEST_PARAMS =
    convert_to<long double>(
        IntegralMinusDigitsNegativeResultSubtractionTest::BASE_TEST_PARAMS
    );

TEST_P(FloatingPointMinusDigitsNegativeResultSubtractionTest,
       LargerMinusSmallerProducesNegativeResult)
{
    test_subtract_from_arithmetic(GetParam(), Sign::NEGATIVE);
}

INSTANTIATE_TEST_SUITE_P(
    DigitsSubtractionTest,
    FloatingPointMinusDigitsNegativeResultSubtractionTest,
    ::testing::ValuesIn(
        FloatingPointMinusDigitsNegativeResultSubtractionTest::BASE_TEST_PARAMS
    )
);

INSTANTIATE_TEST_SUITE_P(
    DigitsAndFloatingPointSubtractionTruncationBehaviorTest,
    FloatingPointMinusDigitsNegativeResultSubtractionTest,
    ::testing::ValuesIn(
        std::vector<BinaryDigitsOperationTestParam<long double>> {
            { { 5 }, 2.1, { 2 } },
            { { 5 }, 2.5, { 2 } },
            { { 5 }, 2.9, { 2 } },
            { { 5 }, 3.0, { 2 } },
            { { 5 }, 3.1, { 1 } },
            { { 20000 }, 10000.1, { 9999 } },
            { { 20000 }, 10000.5, { 9999 } },
            { { 20000 }, 10000.9, { 9999 } },
            { { 20000 }, 10001.0, { 9999 } },
            { { 20000 }, 10001.1, { 9998 } },
            { { 20000 }, 10001.5, { 9998 } },
            { { 20000 }, 10001.9, { 9998 } },
            { { 20000 }, 10002.0, { 9998 } }
        }
    )
);

} // namespace
