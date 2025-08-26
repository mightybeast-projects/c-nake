#include "game.tests.h"
#include "game.h"
#include "unity.h"

static unsigned cols = 5;
static unsigned rows = 5;
static Game* game;

static Snake* snake;
static Tile** body;
static Tile*** tiles;

void setUpGame(void)
{
    game = allocateGame(cols, rows);

    snake = gameSnake(game);
    body = snakeBody(snake);
    tiles = gridTiles(gameGrid(game));
}

void tearDownGame(void)
{
    freeGame(game);
}

void Game_Allocation_Should_Return_New_Game(void)
{
    TEST_ASSERT_NOT_NULL(game);
}

void Allocated_Game_Should_Have_Grid(void)
{
    TEST_ASSERT_NOT_NULL(gameGrid(game));
}

void Allocated_Game_Should_Have_Grid_With_Passed_Size(void)
{
    for (int i = 0; i < cols; i++)
        for (int j = 0; j < rows; j++)
            TEST_ASSERT_NOT_NULL(tiles[i][j]);
}

void Allocated_Game_Should_Have_Snake(void)
{
    TEST_ASSERT_NOT_NULL(gameSnake(game));
}

void Game_Should_Be_Able_To_Get_Food_Tile(void)
{
    placeRandomFood(game, 1);

    TEST_ASSERT_NOT_NULL(foodTile(game));
}

void Game_Should_Place_Food_On_Random_Tile(void)
{
    placeRandomFood(game, 6);

    int foodTilesCnt = 0;

    for (int i = 0; i < cols; i++)
        for (int j = 0; j < rows; j++)
            if (tileHasFood(tiles[i][j]))
                foodTilesCnt++;

    TEST_ASSERT_EQUAL_UINT(1, foodTilesCnt);

    printGame(game);
}

void Game_Should_Not_Place_Food_On_Snake_Body(void)
{
    Game* const game = allocateGame(1, 3);
    Tile*** const tiles = gridTiles(gameGrid(game));

    placeRandomFood(game, 2);

    TEST_ASSERT_EQUAL(tiles[0][2], foodTile(game));

    printGame(game);

    freeGame(game);
}

void Game_Snake_Should_Move_In_Chosen_Direction(void)
{
    moveSnake(game);

    TEST_ASSERT_EQUAL(tiles[0][2], body[0]);
    TEST_ASSERT_EQUAL(tiles[0][1], body[1]);

    printGame(game);

    changeDirection(snake, RIGHT);

    moveSnake(game);

    TEST_ASSERT_EQUAL(tiles[1][2], body[0]);
    TEST_ASSERT_EQUAL(tiles[0][2], body[1]);

    printGame(game);

    changeDirection(snake, UP);

    moveSnake(game);

    TEST_ASSERT_EQUAL(tiles[1][1], body[0]);
    TEST_ASSERT_EQUAL(tiles[1][2], body[1]);

    printGame(game);

    changeDirection(snake, LEFT);

    moveSnake(game);

    TEST_ASSERT_EQUAL(tiles[0][1], body[0]);
    TEST_ASSERT_EQUAL(tiles[1][1], body[1]);

    printGame(game);
}

void Game_Snake_Should_Wrap_Around_On_Move_If_Next_Tile_Is_Out_Of_Bounds(void)
{
    Game* const game = allocateGame(3, 3);
    Snake* const snake = gameSnake(game);
    Tile** const body = snakeBody(snake);
    Tile*** const tiles = gridTiles(gameGrid(game));

    moveSnake(game);
    moveSnake(game);

    TEST_ASSERT_EQUAL(tiles[0][0], body[0]);
    TEST_ASSERT_EQUAL(tiles[0][2], body[1]);

    printGame(game);

    changeDirection(snake, LEFT);
    moveSnake(game);

    TEST_ASSERT_EQUAL(tiles[2][0], body[0]);
    TEST_ASSERT_EQUAL(tiles[0][0], body[1]);

    printGame(game);

    changeDirection(snake, UP);
    moveSnake(game);

    TEST_ASSERT_EQUAL(tiles[2][2], body[0]);
    TEST_ASSERT_EQUAL(tiles[2][0], body[1]);

    printGame(game);

    changeDirection(snake, RIGHT);
    moveSnake(game);

    TEST_ASSERT_EQUAL(tiles[0][2], body[0]);
    TEST_ASSERT_EQUAL(tiles[2][2], body[1]);

    printGame(game);

    freeGame(game);
}

void Game_Snake_Should_Eat_Food_If_Next_Tile_Has_Food(void)
{
    setTileFood(tiles[0][2], true);

    moveSnake(game);

    TEST_ASSERT_FALSE(tileHasFood(tiles[0][2]));

    printGame(game);
}

void Game_Snake_Should_Grow_After_Eating_Food(void)
{
    setTileFood(tiles[0][2], true);

    moveSnake(game);

    TEST_ASSERT_EQUAL_UINT(3, snakeLength(snake));
    TEST_ASSERT_EQUAL(tiles[0][2], body[0]);
    TEST_ASSERT_EQUAL(tiles[0][1], body[1]);
    TEST_ASSERT_EQUAL(tiles[0][0], body[2]);

    printGame(game);
}

void Game_Should_Randomly_Place_Next_Food_Tile_If_Snake_Ate_After_Moving(void)
{
    Tile* tile = foodTile(game);

    setTileFood(tiles[0][2], true);

    moveSnake(game);

    TEST_ASSERT_NOT_NULL(foodTile(game));
    TEST_ASSERT_NOT_EQUAL(foodTile(game), tile);

    printGame(game);
}

void runGameTests(void)
{
    RUN_TEST(Game_Allocation_Should_Return_New_Game);

    RUN_TEST(Allocated_Game_Should_Have_Grid);
    RUN_TEST(Allocated_Game_Should_Have_Grid_With_Passed_Size);
    RUN_TEST(Allocated_Game_Should_Have_Snake);

    RUN_TEST(Game_Should_Be_Able_To_Get_Food_Tile);

    RUN_TEST(Game_Should_Place_Food_On_Random_Tile);
    RUN_TEST(Game_Should_Not_Place_Food_On_Snake_Body);

    RUN_TEST(Game_Snake_Should_Move_In_Chosen_Direction);
    RUN_TEST(Game_Snake_Should_Eat_Food_If_Next_Tile_Has_Food);
    RUN_TEST(Game_Snake_Should_Wrap_Around_On_Move_If_Next_Tile_Is_Out_Of_Bounds);
    RUN_TEST(Game_Snake_Should_Grow_After_Eating_Food);
    RUN_TEST(Game_Should_Randomly_Place_Next_Food_Tile_If_Snake_Ate_After_Moving);
}