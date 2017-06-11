#include "unity_test/unity.h" /* UNITY testing framework */

void
test_pass(void)
{
	TEST_ASSERT_TRUE_MESSAGE(1, "test_pass: FAILED");
}

void
test_fail(void)
{
	TEST_ASSERT_TRUE_MESSAGE(0, "test_fail: FAILED");
}
