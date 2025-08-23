#include "game.tests.h"
#include "game.h"
#include "unity.h"

static unsigned cols = 5;
static unsigned rows = 5;
static Game* game;

void setUpGame(void)
{
    game = allocateGame(cols, rows);
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

void Allocated_Game_Should_Have_Grid_With_Passed_Width_And_Height(void)
{
    Tile*** tiles = gridTiles(gameGrid(game));

    for (int i = 0; i < cols; i++)
        for (int j = 0; j < rows; j++)
            TEST_ASSERT_NOT_NULL(tiles[i][j]);
}

void Allocated_Game_Should_Have_Snake(void)
{
    TEST_ASSERT_NOT_NULL(gameSnake(game));
}

void Game_Should_Place_Food_On_Random_Tile(void)
{
    placeRandomFood(game, 6);

    Tile*** tiles = gridTiles(gameGrid(game));
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
    const unsigned cols = 1;
    const unsigned rows = 3;

    Game* const game = allocateGame(cols, rows);

    placeRandomFood(game, 2);

    Tile*** tiles = gridTiles(gameGrid(game));
    Tile* foodTile = NULL;

    for (int i = 0; i < cols; i++)
        for (int j = 0; j < rows; j++)
            if (tileHasFood(tiles[i][j]))
                foodTile = tiles[i][j];

    TEST_ASSERT_EQUAL(tiles[0][2], foodTile);

    printGame(game);
}

void runGameTests(void)
{
    RUN_TEST(Game_Allocation_Should_Return_New_Game);

    RUN_TEST(Allocated_Game_Should_Have_Grid);
    RUN_TEST(Allocated_Game_Should_Have_Grid_With_Passed_Width_And_Height);
    RUN_TEST(Allocated_Game_Should_Have_Snake);

    RUN_TEST(Game_Should_Place_Food_On_Random_Tile);
    RUN_TEST(Game_Should_Not_Place_Food_On_Snake_Body);
}
