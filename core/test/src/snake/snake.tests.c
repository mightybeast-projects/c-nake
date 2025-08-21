#include "snake.h"
#include "snake.tests.h"
#include "unity.h"

Grid* grid;
Snake* snake;

void setUpSnake(void)
{
    grid = allocateGrid(10, 10);
    snake = allocateSnake(grid);
}

void tearDownSnake(void)
{
    freeSnake(snake);
    freeGrid(grid);
}

void Snake_Allocation_Should_Return_New_Snake()
{
    TEST_ASSERT_NOT_NULL(snake);
}

void Allocated_Snake_Should_Know_About_Grid()
{
    TEST_ASSERT_EQUAL(grid, snakeGrid(snake));
}

void runSnakeTests(void)
{
    RUN_TEST(Snake_Allocation_Should_Return_New_Snake);

    RUN_TEST(Allocated_Snake_Should_Know_About_Grid);
}