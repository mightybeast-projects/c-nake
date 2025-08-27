#include "game.tests.h"
#include "game.h"
#include "unity.h"

static unsigned cols = 3;
static unsigned rows = 3;
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

void Allocated_Game_Should_Not_Be_Finished(void)
{
    TEST_ASSERT_FALSE(gameIsFinished(game));
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

void Game_Snake_Should_Wrap_Around_Down_Side_On_Move(void)
{
    moveSnake(game);

    moveSnake(game);

    TEST_ASSERT_EQUAL(tiles[0][0], body[0]);
    TEST_ASSERT_EQUAL(tiles[0][2], body[1]);

    printGame(game);
}

void Game_Snake_Should_Wrap_Around_Left_Side_On_Move(void)
{
    changeSnakeDirection(snake, LEFT);

    moveSnake(game);

    TEST_ASSERT_EQUAL(tiles[2][1], body[0]);
    TEST_ASSERT_EQUAL(tiles[0][1], body[1]);

    printGame(game);
}

void Game_Snake_Should_Wrap_Around_Up_Side_On_Move(void)
{
    changeSnakeDirection(snake, LEFT);
    moveSnake(game);
    changeSnakeDirection(snake, UP);
    moveSnake(game);

    moveSnake(game);

    TEST_ASSERT_EQUAL(tiles[2][2], body[0]);
    TEST_ASSERT_EQUAL(tiles[2][0], body[1]);

    printGame(game);
}

void Game_Snake_Should_Wrap_Around_Right_Side_On_Move(void)
{
    changeSnakeDirection(snake, LEFT);
    moveSnake(game);
    changeSnakeDirection(snake, UP);
    moveSnake(game);
    moveSnake(game);
    changeSnakeDirection(snake, RIGHT);

    moveSnake(game);

    TEST_ASSERT_EQUAL(tiles[0][2], body[0]);
    TEST_ASSERT_EQUAL(tiles[2][2], body[1]);

    printGame(game);
}

void Game_Should_Randomly_Place_Next_Food_After_Snake_Eats_One(void)
{
    Tile* const tile = foodTile(game);

    setTileFood(tiles[0][2], true);

    moveSnake(game);

    TEST_ASSERT_NOT_NULL(foodTile(game));
    TEST_ASSERT_NOT_EQUAL(foodTile(game), tile);

    printGame(game);
}

void Game_Should_Finish_If_Snake_Ate_All_Food(void)
{
    Game* const game = allocateGame(1, 3);
    Tile*** const tiles = gridTiles(gameGrid(game));

    placeRandomFood(game, 1);

    moveSnake(game);

    TEST_ASSERT_TRUE(gameIsFinished(game));

    printGame(game);

    freeGame(game);
}

void Game_Should_Finish_If_Snake_Eats_Itself(void)
{
    Game* const game = allocateGame(1, 3);
    Snake* const snake = gameSnake(game);
    Tile*** const tiles = gridTiles(gameGrid(game));

    changeSnakeDirection(snake, RIGHT);

    moveSnake(game);

    TEST_ASSERT_TRUE(gameIsFinished(game));

    printGame(game);

    freeGame(game);
}

void Game_Should_Not_Place_Food_If_It_Is_Finished(void)
{
    Game* const game = allocateGame(1, 3);
    Snake* const snake = gameSnake(game);
    Tile*** const tiles = gridTiles(gameGrid(game));

    placeRandomFood(game, 1);
    moveSnake(game);

    TEST_ASSERT_EQUAL(snakeHead(snake), foodTile(game));

    printGame(game);

    freeGame(game);
}

void Game_Should_Not_Move_Snake_If_It_Is_Finished(void)
{
    Game* const game = allocateGame(1, 3);
    Snake* const snake = gameSnake(game);
    Tile*** const tiles = gridTiles(gameGrid(game));

    placeRandomFood(game, 1);
    moveSnake(game);

    moveSnake(game);
    moveSnake(game);

    TEST_ASSERT_EQUAL(tiles[0][2], snakeHead(snake));

    printGame(game);

    freeGame(game);
}

void runGameTests(void)
{
    RUN_TEST(Game_Allocation_Should_Return_New_Game);

    RUN_TEST(Allocated_Game_Should_Not_Be_Finished);
    RUN_TEST(Allocated_Game_Should_Have_Grid);
    RUN_TEST(Allocated_Game_Should_Have_Grid_With_Passed_Size);
    RUN_TEST(Allocated_Game_Should_Have_Snake);

    RUN_TEST(Game_Should_Be_Able_To_Get_Food_Tile);

    RUN_TEST(Game_Should_Place_Food_On_Random_Tile);
    RUN_TEST(Game_Should_Not_Place_Food_On_Snake_Body);

    RUN_TEST(Game_Snake_Should_Wrap_Around_Down_Side_On_Move);
    RUN_TEST(Game_Snake_Should_Wrap_Around_Left_Side_On_Move);
    RUN_TEST(Game_Snake_Should_Wrap_Around_Up_Side_On_Move);
    RUN_TEST(Game_Snake_Should_Wrap_Around_Right_Side_On_Move);

    RUN_TEST(Game_Should_Randomly_Place_Next_Food_After_Snake_Eats_One);

    RUN_TEST(Game_Should_Finish_If_Snake_Ate_All_Food);
    RUN_TEST(Game_Should_Finish_If_Snake_Eats_Itself);
    RUN_TEST(Game_Should_Not_Place_Food_If_It_Is_Finished);
    RUN_TEST(Game_Should_Not_Move_Snake_If_It_Is_Finished);
}