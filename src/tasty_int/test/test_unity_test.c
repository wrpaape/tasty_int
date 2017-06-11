#include "unity/unity.h" /* UNITY testing framework */

void
test_pass(void)
{
	TEST_ASSERT_TRUE_MESSAGE(1, "test_pass: FAILED");
}
