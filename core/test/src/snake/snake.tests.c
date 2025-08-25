#include "snake.tests.h"
#include "game.h"
#include "unity.h"

static Game* game;
static Grid* grid;
static Snake* snake;

void setUpSnake(void)
{
    game = allocateGame(5, 5);

    grid = gameGrid(game);
    snake = gameSnake(game);
}

void tearDownSnake(void)
{
    freeGame(game);
}

void Snake_Allocation_Should_Return_New_Snake(void)
{
    TEST_ASSERT_NOT_NULL(snake);
}

void Allocated_Snake_Should_Know_About_Grid(void)
{
    TEST_ASSERT_EQUAL(grid, snakeGrid(snake));
}

void Allocated_Snake_Should_Occupy_First_Tiles_Of_First_Two_Rows(void)
{
    Tile*** gTiles = gridTiles(grid);
    Tile** sTiles = snakeBody(snake);

    TEST_ASSERT_EQUAL(gTiles[0][1], sTiles[0]);
    TEST_ASSERT_EQUAL(gTiles[0][0], sTiles[1]);
}

void Allocated_Snake_Should_Have_Length_Of_Two(void)
{
    TEST_ASSERT_EQUAL_UINT(2, snakeLength(snake));
}

void Allocated_Snake_Should_Have_Head(void)
{
    Tile*** gTiles = gridTiles(grid);
    Tile* head = snakeHead(snake);

    TEST_ASSERT_EQUAL(gTiles[0][1], head);
}

void Allocated_Snake_Should_Have_Tail(void)
{
    Tile*** gTiles = gridTiles(grid);
    Tile* tail = snakeTail(snake);

    TEST_ASSERT_EQUAL(gTiles[0][0], tail);
}

void Allocated_Snake_Should_Have_Down_Direction(void)
{
    TEST_ASSERT_EQUAL(DOWN, snakeDirection(snake));
}

void Snake_Should_Be_Able_To_Change_Direction(void)
{
    changeDirection(snake, RIGHT);

    TEST_ASSERT_EQUAL(RIGHT, snakeDirection(snake));
}

void Snake_Should_Not_Change_Its_Direction_If_New_Direction_Is_Opposite_To_Current(void)
{
    changeDirection(snake, UP);

    TEST_ASSERT_EQUAL(DOWN, snakeDirection(snake));

    changeDirection(snake, RIGHT);
    changeDirection(snake, LEFT);

    TEST_ASSERT_EQUAL(RIGHT, snakeDirection(snake));

    changeDirection(snake, UP);
    changeDirection(snake, DOWN);

    TEST_ASSERT_EQUAL(UP, snakeDirection(snake));

    changeDirection(snake, LEFT);
    changeDirection(snake, RIGHT);

    TEST_ASSERT_EQUAL(LEFT, snakeDirection(snake));
}

void Snake_Should_Move_In_Chosen_Direction(void)
{
    bool res = move(snake);

    Tile** body = snakeBody(snake);
    Tile*** tiles = gridTiles(gameGrid(game));

    TEST_ASSERT_TRUE(res);
    TEST_ASSERT_EQUAL(tiles[0][2], body[0]);
    TEST_ASSERT_EQUAL(tiles[0][1], body[1]);

    printGame(game);

    changeDirection(snake, RIGHT);

    res = move(snake);

    TEST_ASSERT_TRUE(res);
    TEST_ASSERT_EQUAL(tiles[1][2], body[0]);
    TEST_ASSERT_EQUAL(tiles[0][2], body[1]);

    printGame(game);

    changeDirection(snake, UP);

    res = move(snake);

    TEST_ASSERT_TRUE(res);
    TEST_ASSERT_EQUAL(tiles[1][1], body[0]);
    TEST_ASSERT_EQUAL(tiles[1][2], body[1]);

    printGame(game);

    changeDirection(snake, LEFT);

    res = move(snake);

    TEST_ASSERT_TRUE(res);
    TEST_ASSERT_EQUAL(tiles[0][1], body[0]);
    TEST_ASSERT_EQUAL(tiles[1][1], body[1]);

    printGame(game);
}

void Snake_Should_Eat_Food_After_Move(void)
{
    Tile*** const tiles = gridTiles(gameGrid(game));

    setTileFood(tiles[0][2], true);

    const bool res = move(snake);

    Tile** const body = snakeBody(snake);

    TEST_ASSERT_TRUE(res);
    TEST_ASSERT_FALSE(tileHasFood(tiles[0][2]));
    TEST_ASSERT_NULL(foodTile(game));

    printGame(game);
}

void Snake_Should_Increase_Its_Length_After_Eating_Food(void)
{
    Tile*** const tiles = gridTiles(gameGrid(game));

    setTileFood(tiles[0][2], true);

    const bool res = move(snake);

    Tile** const body = snakeBody(snake);

    TEST_ASSERT_EQUAL_UINT(3, snakeLength(snake));
    TEST_ASSERT_EQUAL(tiles[0][2], body[0]);
    TEST_ASSERT_EQUAL(tiles[0][1], body[1]);
    TEST_ASSERT_EQUAL(tiles[0][0], body[2]);

    printGame(game);
}

void Snake_Should_Check_If_It_Contains_Tile(void)
{
    Tile*** const tiles = gridTiles(grid);

    TEST_ASSERT_TRUE(snakeContainsTile(snake, tiles[0][0]));
    TEST_ASSERT_TRUE(snakeContainsTile(snake, tiles[0][1]));
    TEST_ASSERT_FALSE(snakeContainsTile(snake, tiles[0][2]));
}

void runSnakeTests(void)
{
    RUN_TEST(Snake_Allocation_Should_Return_New_Snake);

    RUN_TEST(Allocated_Snake_Should_Know_About_Grid);
    RUN_TEST(Allocated_Snake_Should_Occupy_First_Tiles_Of_First_Two_Rows);
    RUN_TEST(Allocated_Snake_Should_Have_Head);
    RUN_TEST(Allocated_Snake_Should_Have_Tail);
    RUN_TEST(Allocated_Snake_Should_Have_Down_Direction);

    RUN_TEST(Snake_Should_Be_Able_To_Change_Direction);
    RUN_TEST(Snake_Should_Not_Change_Its_Direction_If_New_Direction_Is_Opposite_To_Current);

    RUN_TEST(Snake_Should_Move_In_Chosen_Direction);
    RUN_TEST(Snake_Should_Eat_Food_After_Move);
    RUN_TEST(Snake_Should_Increase_Its_Length_After_Eating_Food);

    RUN_TEST(Snake_Should_Check_If_It_Contains_Tile);
}