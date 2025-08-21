#include "snake.h"
#include "snake.tests.h"
#include "unity.h"

Snake* snake;

void setUpSnake(void)
{
    snake = allocateSnake();
}

void tearDownSnake(void)
{
    freeSnake(snake);
}

void Snake_Allocation_Should_Return_New_Snake()
{
    TEST_ASSERT_NOT_NULL(snake);
}

void runSnakeTests(void)
{
    RUN_TEST(Snake_Allocation_Should_Return_New_Snake);
}