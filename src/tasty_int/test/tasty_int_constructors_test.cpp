#include "tasty_int/tasty_int.hpp"

#include <limits>

#include "gtest/gtest.h"

#include "tasty_int_test/arithmetic_types.hpp"


/**
 * @todo investigate this test for anything salvageable then delete
 */
template<typename ArithmeticType>
struct TastyIntArtihmeticTypesConstructorTest : public ::testing::Test
{
    static constexpr auto ZERO    = static_cast<ArithmeticType>(0);
    static constexpr auto MINIMUM = std::numeric_limits<ArithmeticType>::min();
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

    static constexpr auto MEDIAN         = get_middle(MINIMUM, MAXIMUM);
    static constexpr auto LOWER_QUARTILE = get_middle(MINIMUM, MEDIAN);
    static constexpr auto UPPER_QUARTILE = get_middle(MEDIAN,  MAXIMUM);

    static constexpr auto EPSILON =
        std::numeric_limits<ArithmeticType>::epsilon();
}; // struct TastyIntArtihmeticTypesConstructorTest

TYPED_TEST_SUITE(TastyIntArtihmeticTypesConstructorTest,
                 tasty_int_test::ArithmeticTypes);

TYPED_TEST(TastyIntArtihmeticTypesConstructorTest, WorksWithMinimumValue)
{
    EXPECT_NEAR(TestFixture::MINIMUM,
                TastyInt(TestFixture::MINIMUM).to_number<TypeParam>(),
                TestFixture::EPSILON);
}

TYPED_TEST(TastyIntArtihmeticTypesConstructorTest, WorksWithLowerQuartileValue)
{
    EXPECT_NEAR(TestFixture::LOWER_QUARTILE,
                TastyInt(TestFixture::LOWER_QUARTILE).to_number<TypeParam>(),
                TestFixture::EPSILON);
}

TYPED_TEST(TastyIntArtihmeticTypesConstructorTest, WorksWithMedianValue)
{
    EXPECT_NEAR(TestFixture::MEDIAN,
                TastyInt(TestFixture::MEDIAN).to_number<TypeParam>(),
                TestFixture::EPSILON);
}

TYPED_TEST(TastyIntArtihmeticTypesConstructorTest, WorksWithUpperQuartileValue)
{
    EXPECT_NEAR(TestFixture::UPPER_QUARTILE,
                TastyInt(TestFixture::UPPER_QUARTILE).to_number<TypeParam>(),
                TestFixture::EPSILON);
}

TYPED_TEST(TastyIntArtihmeticTypesConstructorTest, WorksWithMaximumValue)
{
    EXPECT_NEAR(TestFixture::MAXIMUM,
                TastyInt(TestFixture::MAXIMUM).to_number<TypeParam>(),
                TestFixture::EPSILON);
}

TYPED_TEST(TastyIntArtihmeticTypesConstructorTest, WorksWithZero)
{
    EXPECT_NEAR(TestFixture::ZERO,
                TastyInt(TestFixture::ZERO).to_number<TypeParam>(),
                TestFixture::EPSILON);
}

TEST(String, DISABLED_sign) // TODO: re-enable
{
    ASSERT_LT(TastyInt("-1").to_number<int>(), 0);

    ASSERT_LT(TastyInt("-9999999999999999999999999999999").to_number<int>(), 0);

    ASSERT_EQ(TastyInt("0").to_number<int>(), 0);

    ASSERT_GT(TastyInt("1").to_number<int>(), 0);

    ASSERT_GT(TastyInt("9999999999999999999999999999999").to_number<int>(), 0);
}
