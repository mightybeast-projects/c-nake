#include "tmp.h"
#include "tmp.tests.h"
#include "unity.h"

void TMP_Test()
{
    TEST_ASSERT_TRUE(tmp());
}

void runTMPTests()
{
    RUN_TEST(TMP_Test);
}