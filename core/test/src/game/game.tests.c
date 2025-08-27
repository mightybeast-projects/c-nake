#include "game.tests.h"
#include "game.h"
#include "unity.h"

static GameParams params = { 1, 3, 1 };
static Game* game;

static Snake* snake;
static Tile** body;
static Tile*** tiles;

void setUpGame(void)
{
    game = allocateGame(params);

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
    for (int i = 0; i < params.cols; i++)
        for (int j = 0; j < params.rows; j++)
            TEST_ASSERT_NOT_NULL(tiles[i][j]);
}

void Allocated_Game_Should_Have_Snake(void)
{
    TEST_ASSERT_NOT_NULL(gameSnake(game));
}

void Allocated_Game_Should_Not_Be_Finished(void)
{
    TEST_ASSERT_FALSE(gameIsFinished(game));
}

void Allocated_Game_Should_Place_Food_On_Random_Tile(void)
{
    int foodTilesCnt = 0;

    for (int i = 0; i < params.cols; i++)
        for (int j = 0; j < params.rows; j++)
            if (tileHasFood(tiles[i][j]))
                foodTilesCnt++;

    TEST_ASSERT_EQUAL_UINT(1, foodTilesCnt);

    printGame(game);
}

void Game_Should_Be_Able_To_Get_Food_Tile(void)
{
    TEST_ASSERT_NOT_NULL(foodTile(game));
}

void Game_Should_Not_Place_Food_On_Snake_Body(void)
{
    const GameParams params = { 1, 3, 2 };
    Game* const game = allocateGame(params);
    Tile*** const tiles = gridTiles(gameGrid(game));

    TEST_ASSERT_EQUAL(tiles[0][2], foodTile(game));

    printGame(game);

    freeGame(game);
}

void Game_Should_Move_Snake_On_Update(void)
{
    updateGame(game);

    TEST_ASSERT_EQUAL(tiles[0][2], body[0]);
    TEST_ASSERT_EQUAL(tiles[0][1], body[1]);
}

void Game_Should_Randomly_Place_Next_Food_After_Snake_Eats_One_On_Update(void)
{
    const GameParams params = { 2, 3, 3 };
    Game* const game = allocateGame(params);
    Tile* const tile = foodTile(game);

    updateGame(game);

    TEST_ASSERT_NOT_NULL(foodTile(game));
    TEST_ASSERT_NOT_EQUAL(foodTile(game), tile);

    printGame(game);

    freeGame(game);
}

void Game_Should_Finish_If_Snake_Ate_All_Food_On_Update(void)
{
    updateGame(game);

    TEST_ASSERT_TRUE(gameIsFinished(game));

    printGame(game);
}

void Game_Should_Finish_If_Snake_Eats_Itself_On_Update(void)
{
    changeSnakeDirection(snake, RIGHT);

    updateGame(game);

    TEST_ASSERT_TRUE(gameIsFinished(game));

    printGame(game);
}

void Game_Should_Not_Place_Food_On_Update_If_It_Is_Finished(void)
{
    updateGame(game);

    TEST_ASSERT_NULL(foodTile(game));

    printGame(game);
}

void Game_Should_Not_Move_Snake_On_Update_If_It_Is_Finished(void)
{
    updateGame(game);

    updateGame(game);
    updateGame(game);

    TEST_ASSERT_EQUAL(tiles[0][2], snakeHead(snake));

    printGame(game);
}

void runGameTests(void)
{
    RUN_TEST(Game_Allocation_Should_Return_New_Game);

    RUN_TEST(Allocated_Game_Should_Not_Be_Finished);
    RUN_TEST(Allocated_Game_Should_Have_Grid);
    RUN_TEST(Allocated_Game_Should_Have_Grid_With_Passed_Size);
    RUN_TEST(Allocated_Game_Should_Have_Snake);
    RUN_TEST(Allocated_Game_Should_Place_Food_On_Random_Tile);

    RUN_TEST(Game_Should_Be_Able_To_Get_Food_Tile);

    RUN_TEST(Game_Should_Not_Place_Food_On_Snake_Body);

    RUN_TEST(Game_Should_Move_Snake_On_Update);
    RUN_TEST(Game_Should_Randomly_Place_Next_Food_After_Snake_Eats_One_On_Update);
    RUN_TEST(Game_Should_Finish_If_Snake_Ate_All_Food_On_Update);
    RUN_TEST(Game_Should_Finish_If_Snake_Eats_Itself_On_Update);

    RUN_TEST(Game_Should_Not_Place_Food_On_Update_If_It_Is_Finished);
    RUN_TEST(Game_Should_Not_Move_Snake_On_Update_If_It_Is_Finished);
}