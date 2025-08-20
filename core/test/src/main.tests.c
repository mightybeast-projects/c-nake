#include "stdbool.h"
#include "tile.tests.h"
#include "unity.h"

void setUp(void)
{
    setUpTile();
}

void tearDown(void)
{
    tearDownTile();
}

int main(void)
{
    UNITY_BEGIN();

    runTileTests();

    return UNITY_END();
}