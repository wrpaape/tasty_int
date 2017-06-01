#include "gtest/gtest.h"
#include "tasty_int/tasty_int.hpp"
#include <limits>

// TastyInt(char).
TEST(Arithmetic, char) {
  TastyInt x('x');

  EXPECT_EQ('x', x.to_number<char>());
}
