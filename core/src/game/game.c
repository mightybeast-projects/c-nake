#include "game.h"
#include "safe-memory.h"

Game* allocateGame()
{
    Game* game = safeMalloc(sizeof(struct Game));

    return game;
}

void freeGame(Game* const game)
{
    free(game);
}
