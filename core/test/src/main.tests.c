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
    setUpGame();
    setUpSnake();
}

void tearDown(void)
{
    tearDownTile();
    tearDownGrid();
    tearDownGame();
    tearDownSnake();
}

int main(void)
{
    UNITY_BEGIN();

    runTileTests();
    runGridTests();
    runGameTests();
    runSnakeTests();

    return UNITY_END();
}