#include "game-widget.h"
#include "safe-memory.h"

struct GameWidget
{
    Game* game;
};

GameWidget* allocateGameWidget(Game* const game)
{
    GameWidget* widget = safeMalloc(sizeof(struct GameWidget));

    widget->game = game;

    return widget;
}

void freeGameWidget(GameWidget* const widget)
{
    freeGame(widget->game);
    free(widget);
}