#include "game.h"
#include "safe-memory.h"

struct Game
{
    Grid* grid;
};

Game* allocateGame()
{
    Game* game = safeMalloc(sizeof(struct Game));

    game->grid = allocateGrid(10, 10);

    return game;
}

void freeGame(Game* const game)
{
    free(game);
}

Grid* gameGrid(const Game* const game)
{
    return game->grid;
}