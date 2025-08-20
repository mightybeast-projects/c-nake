#include "grid.tests.h"
#include "stdbool.h"
#include "tile.tests.h"
#include "unity.h"

void setUp(void)
{
    setUpTile();
    setUpGrid();
}

void tearDown(void)
{
    tearDownTile();
    tearDownGrid();
}

int main(void)
{
    UNITY_BEGIN();

    runTileTests();
    runGridTests();

    return UNITY_END();
}