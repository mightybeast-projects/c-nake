#include "game.tests.h"
#include "game.h"
#include "unity.h"

static unsigned cols = 10;
static unsigned rows = 10;
static Game* game;

void setUpGame(void)
{
    game = allocateGame();
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

void Allocated_Game_Should_Have_Snake(void)
{
    TEST_ASSERT_NOT_NULL(gameSnake(game));
}

void Game_Should_Place_Food_On_Random_Tile(void)
{
    placeFood(game, 1);

    Tile*** tiles = gridTiles(gameGrid(game));
    int foodTilesCnt = 0;

    for (int i = 0; i < cols; i++)
        for (int j = 0; j < rows; j++)
            if (tileHasFood(tiles[i][j]))
                foodTilesCnt++;

    TEST_ASSERT_EQUAL_UINT(1, foodTilesCnt);
}

void Game_Should_Not_Place_Food_On_Snake_Body(void)
{
    const unsigned width = 1;
    const unsigned height = 3;

    Grid* grid = allocateGrid(width, height);
    Snake* snake = allocateSnake(grid);

    placeFood(game, 1);

    Tile*** tiles = gridTiles(grid);
    Tile* foodTile = NULL;

    for (int i = 0; i < cols; i++)
        for (int j = 0; j < rows; j++)
            if (tileHasFood(tiles[i][j]))
                foodTile = tiles[i][j];

    TEST_ASSERT_EQUAL(tiles[0][2], foodTile);
}

void runGameTests(void)
{
    RUN_TEST(Game_Allocation_Should_Return_New_Game);

    RUN_TEST(Allocated_Game_Should_Have_Grid);
    RUN_TEST(Allocated_Game_Should_Have_Snake);

    RUN_TEST(Game_Should_Place_Food_On_Random_Tile);
    // RUN_TEST(Game_Should_Not_Place_Food_On_Snake_Body);
}
