#include "grid.tests.h"
#include "snake.tests.h"
#include "stdbool.h"
#include "tile.tests.h"
#include "unity.h"

void setUp(void)
{
    setUpTile();
    setUpGrid();
    setUpSnake();
}

void tearDown(void)
{
    tearDownTile();
    tearDownGrid();
    tearDownSnake();
}

int main(void)
{
    UNITY_BEGIN();

    runTileTests();
    runGridTests();
    runSnakeTests();

    return UNITY_END();
}