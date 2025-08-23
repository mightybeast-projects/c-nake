#include "game.tests.h"
#include "game.h"
#include "unity.h"

static Game* game;

void setUpGame(void)
{
    game = allocateGame();
}

void tearDownGame(void)
{
    freeGame(game);
}

void Game_Allocation_Should_Return_New_Game()
{
    TEST_ASSERT_NOT_NULL(game);
}

void Allocated_Game_Should_Have_Grid()
{
    TEST_ASSERT_NOT_NULL(gameGrid(game));
}

void runGameTests(void)
{
    RUN_TEST(Game_Allocation_Should_Return_New_Game);

    RUN_TEST(Allocated_Game_Should_Have_Grid);
}
