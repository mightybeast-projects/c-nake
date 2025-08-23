#include "game.tests.h"
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
    setUpGame();
}

void tearDown(void)
{
    tearDownTile();
    tearDownGrid();
    tearDownSnake();
    tearDownGame();
}

int main(void)
{
    UNITY_BEGIN();

    runTileTests();
    runGridTests();
    runSnakeTests();
    runGameTests();

    return UNITY_END();
}