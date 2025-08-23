#include "game.h"
#include "safe-memory.h"

struct Game
{
    Grid* grid;
    Snake* snake;
};

Game* allocateGame()
{
    Game* game = safeMalloc(sizeof(struct Game));

    game->grid = allocateGrid(10, 10);
    game->snake = allocateSnake(game->grid);

    return game;
}

void freeGame(Game* const game)
{
    freeSnake(game->snake);
    freeGrid(game->grid);
    free(game);
}

Grid* gameGrid(const Game* const game)
{
    return game->grid;
}

Snake* gameSnake(const Game* const game)
{
    return game->snake;
}
