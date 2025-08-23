#include "game.h"
#include "safe-memory.h"
#include "stdio.h"

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

void printGame(const Game* const game)
{
    const Grid* const grid = game->grid;
    const Snake* const snake = game->snake;

    Tile*** const tiles = gridTiles(grid);
    const unsigned width = gridWidth(grid);
    const unsigned height = gridHeight(grid);

    Tile** const body = snakeBody(snake);
    const unsigned length = snakeLength(snake);

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            const Tile* const tile = tiles[j][i];
            bool isSnakeTile = false;

            for (int k = 0; k < length; k++) {
                Tile* bTile = body[k];

                if (bTile == tile) {
                    printf("# ");
                    isSnakeTile = true;
                    break;
                }
            }

            if (!isSnakeTile)
                printf(". ");
        }

        printf("\n");
    }
}