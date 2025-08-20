#include "stdbool.h"
#include "tmp.tests.h"
#include "unity.h"

void setUp(void)
{
}

void tearDown(void)
{
}

int main(void)
{
    UNITY_BEGIN();

    runTMPTests();

    return UNITY_END();
}