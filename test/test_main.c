#include "../unity.framework/src/unity.h"
#include "../src/main.c"

void test_returnTrueReturnsTrue()
{
	TEST_ASSERT_EQUAL(true, returnTrue());
}
