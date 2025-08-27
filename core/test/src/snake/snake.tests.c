#include "snake.tests.h"
#include "game.h"
#include "unity.h"

static GameParams params = { 3, 3, 1 };
static Game* game;

static Grid* grid;
static Snake* snake;
static Tile** body;

static Tile*** tiles;

void setUpSnake(void)
{
    game = allocateGame(params);

    grid = gameGrid(game);
    snake = gameSnake(game);
    body = snakeBody(snake);

    tiles = gridTiles(grid);
}

void tearDownSnake(void)
{
    freeGame(game);
}

void Snake_Allocation_Should_Return_New_Snake(void)
{
    TEST_ASSERT_NOT_NULL(snake);
}

void Allocated_Snake_Should_Have_Length_Of_Two(void)
{
    TEST_ASSERT_EQUAL_UINT(2, snakeLength(snake));
}

void Allocated_Snake_Should_Occupy_First_Tiles_Of_First_Two_Rows(void)
{
    TEST_ASSERT_EQUAL(tiles[0][1], body[0]);
    TEST_ASSERT_EQUAL(tiles[0][0], body[1]);
}

void Allocated_Snake_Should_Have_Head(void)
{
    TEST_ASSERT_EQUAL(tiles[0][1], snakeHead(snake));
}

void Allocated_Snake_Should_Have_Tail(void)
{
    TEST_ASSERT_EQUAL(tiles[0][0], snakeTail(snake));
}

void Allocated_Snake_Should_Have_Down_Direction(void)
{
    TEST_ASSERT_EQUAL(DOWN, snakeDirection(snake));
}

void Allocated_Snake_Should_Know_About_Grid()
{
    TEST_ASSERT_EQUAL(grid, snakeGrid(snake));
}

void Snake_Should_Be_Able_To_Change_Direction(void)
{
    changeSnakeDirection(snake, RIGHT);

    TEST_ASSERT_EQUAL(RIGHT, snakeDirection(snake));
}

void Snake_Should_Not_Change_Its_Direction_If_New_Direction_Is_Up_When_Current_Is_Down(void)
{
    changeSnakeDirection(snake, UP);

    TEST_ASSERT_EQUAL(DOWN, snakeDirection(snake));
}

void Snake_Should_Not_Change_Its_Direction_If_New_Direction_Is_Left_When_Current_Is_Right(void)
{
    changeSnakeDirection(snake, RIGHT);
    changeSnakeDirection(snake, LEFT);

    TEST_ASSERT_EQUAL(RIGHT, snakeDirection(snake));
}

void Snake_Should_Not_Change_Its_Direction_If_New_Direction_Is_Down_When_Current_Is_Up(void)
{
    changeSnakeDirection(snake, RIGHT);
    changeSnakeDirection(snake, UP);
    changeSnakeDirection(snake, DOWN);

    TEST_ASSERT_EQUAL(UP, snakeDirection(snake));
}

void Snake_Should_Not_Change_Its_Direction_If_New_Direction_Is_Right_When_Current_Is_Left(void)
{
    changeSnakeDirection(snake, LEFT);
    changeSnakeDirection(snake, RIGHT);

    TEST_ASSERT_EQUAL(LEFT, snakeDirection(snake));
}

void Snake_Should_Move_Down(void)
{
    moveSnake(snake);

    TEST_ASSERT_EQUAL(tiles[0][2], body[0]);
    TEST_ASSERT_EQUAL(tiles[0][1], body[1]);

    printGame(game);
}

void Snake_Should_Move_Right(void)
{
    changeSnakeDirection(snake, RIGHT);

    moveSnake(snake);

    TEST_ASSERT_EQUAL(tiles[1][1], body[0]);
    TEST_ASSERT_EQUAL(tiles[0][1], body[1]);

    printGame(game);
}

void Snake_Should_Move_Up(void)
{
    changeSnakeDirection(snake, RIGHT);
    moveSnake(snake);
    changeSnakeDirection(snake, UP);

    moveSnake(snake);

    TEST_ASSERT_EQUAL(tiles[1][0], body[0]);
    TEST_ASSERT_EQUAL(tiles[1][1], body[1]);

    printGame(game);
}

void Snake_Should_Move_Left(void)
{
    changeSnakeDirection(snake, RIGHT);
    moveSnake(snake);
    changeSnakeDirection(snake, UP);
    moveSnake(snake);
    changeSnakeDirection(snake, LEFT);

    moveSnake(snake);

    TEST_ASSERT_EQUAL(tiles[0][0], body[0]);
    TEST_ASSERT_EQUAL(tiles[1][0], body[1]);

    printGame(game);
}

void Snake_Should_Wrap_Around_Lower_Side_Of_The_Grid_On_Move(void)
{
    moveSnake(snake);

    moveSnake(snake);

    TEST_ASSERT_EQUAL(tiles[0][0], body[0]);
    TEST_ASSERT_EQUAL(tiles[0][2], body[1]);

    printGame(game);
}

void Snake_Should_Wrap_Around_Left_Side_Of_The_Grid_On_Move(void)
{
    changeSnakeDirection(snake, LEFT);

    moveSnake(snake);

    TEST_ASSERT_EQUAL(tiles[2][1], body[0]);
    TEST_ASSERT_EQUAL(tiles[0][1], body[1]);

    printGame(game);
}

void Snake_Should_Wrap_Around_Upper_Side_Of_The_Grid_On_Move(void)
{
    changeSnakeDirection(snake, LEFT);
    moveSnake(snake);
    changeSnakeDirection(snake, UP);
    moveSnake(snake);

    moveSnake(snake);

    TEST_ASSERT_EQUAL(tiles[2][2], body[0]);
    TEST_ASSERT_EQUAL(tiles[2][0], body[1]);

    printGame(game);
}

void Snake_Should_Wrap_Around_Right_Side_Of_The_Grid_On_Move(void)
{
    changeSnakeDirection(snake, LEFT);
    moveSnake(snake);
    changeSnakeDirection(snake, UP);
    moveSnake(snake);
    moveSnake(snake);
    changeSnakeDirection(snake, RIGHT);

    moveSnake(snake);

    TEST_ASSERT_EQUAL(tiles[0][2], body[0]);
    TEST_ASSERT_EQUAL(tiles[2][2], body[1]);

    printGame(game);
}

void Snake_Should_Eat_Food_If_Next_Tile_Has_Food(void)
{
    setTileFood(tiles[0][2], true);

    moveSnake(snake);

    TEST_ASSERT_FALSE(tileHasFood(tiles[0][2]));

    printGame(game);
}

void Snake_Should_Grow_After_Eating_Food_On_Shift(void)
{
    setTileFood(tiles[0][2], true);

    moveSnake(snake);

    TEST_ASSERT_EQUAL_UINT(3, snakeLength(snake));
    TEST_ASSERT_EQUAL(tiles[0][2], body[0]);
    TEST_ASSERT_EQUAL(tiles[0][1], body[1]);
    TEST_ASSERT_EQUAL(tiles[0][0], body[2]);

    printGame(game);
}

void Snake_Should_Check_If_It_Contains_Tile(void)
{
    TEST_ASSERT_TRUE(snakeContainsTile(snake, tiles[0][0]));
    TEST_ASSERT_TRUE(snakeContainsTile(snake, tiles[0][1]));
    TEST_ASSERT_FALSE(snakeContainsTile(snake, tiles[0][2]));
}

void Snake_Should_Check_If_It_Eats_Itself(void)
{
    body[0] = body[1];

    TEST_ASSERT_TRUE(snakeEatsItself(snake));
}

void runSnakeTests(void)
{
    RUN_TEST(Snake_Allocation_Should_Return_New_Snake);

    RUN_TEST(Allocated_Snake_Should_Occupy_First_Tiles_Of_First_Two_Rows);
    RUN_TEST(Allocated_Snake_Should_Have_Head);
    RUN_TEST(Allocated_Snake_Should_Have_Tail);
    RUN_TEST(Allocated_Snake_Should_Have_Down_Direction);
    RUN_TEST(Allocated_Snake_Should_Know_About_Grid);

    RUN_TEST(Snake_Should_Be_Able_To_Change_Direction);
    RUN_TEST(Snake_Should_Not_Change_Its_Direction_If_New_Direction_Is_Up_When_Current_Is_Down);
    RUN_TEST(Snake_Should_Not_Change_Its_Direction_If_New_Direction_Is_Left_When_Current_Is_Right);
    RUN_TEST(Snake_Should_Not_Change_Its_Direction_If_New_Direction_Is_Up_When_Current_Is_Down);
    RUN_TEST(Snake_Should_Not_Change_Its_Direction_If_New_Direction_Is_Right_When_Current_Is_Left);

    RUN_TEST(Snake_Should_Move_Down);
    RUN_TEST(Snake_Should_Move_Right);
    RUN_TEST(Snake_Should_Move_Up);
    RUN_TEST(Snake_Should_Move_Left);

    RUN_TEST(Snake_Should_Wrap_Around_Lower_Side_Of_The_Grid_On_Move);
    RUN_TEST(Snake_Should_Wrap_Around_Left_Side_Of_The_Grid_On_Move);
    RUN_TEST(Snake_Should_Wrap_Around_Upper_Side_Of_The_Grid_On_Move);
    RUN_TEST(Snake_Should_Wrap_Around_Right_Side_Of_The_Grid_On_Move);

    RUN_TEST(Snake_Should_Eat_Food_If_Next_Tile_Has_Food);
    RUN_TEST(Snake_Should_Grow_After_Eating_Food_On_Shift);

    RUN_TEST(Snake_Should_Check_If_It_Contains_Tile);

    RUN_TEST(Snake_Should_Check_If_It_Eats_Itself);
}