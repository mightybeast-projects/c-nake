#include "snake-widget.h"
#include "config.h"
#include "safe-memory.h"
#include "snake.h"
#include "tile-widget.h"

struct SnakeWidget
{
    TileWidget** bodyTilesWidgets;
    Snake* snake;
};

static TileWidget** allocateBodyTilesWidgets(Snake* const snake);

SnakeWidget* allocateSnakeWidget(Snake* const snake)
{
    SnakeWidget* const widget = safeMalloc(sizeof(struct SnakeWidget));

    widget->snake = snake;
    widget->bodyTilesWidgets = allocateBodyTilesWidgets(snake);

    return widget;
}

void freeSnakeWidget(SnakeWidget* const widget)
{
    for (int i = 0; i < snakeLength(widget->snake); i++)
        freeTileWidget(widget->bodyTilesWidgets[i]);

    free(widget->bodyTilesWidgets);
    free(widget);
}

void updateSnakeWidget(SnakeWidget* const widget)
{
    for (int i = 0; i < snakeLength(widget->snake); i++) {
        TileWidget* const tileWidget = widget->bodyTilesWidgets[i];
        Tile* const tile = snakeBody(widget->snake)[i];

        setTileWidgetTile(tileWidget, tile);
        calculateTileWidgetRect(tileWidget);
    }
}

void drawSnakeWidget(const SnakeWidget* const widget)
{
    for (int i = 0; i < snakeLength(widget->snake); i++)
        drawTileWidget(widget->bodyTilesWidgets[i], GREEN);
}

static TileWidget** allocateBodyTilesWidgets(Snake* const snake)
{
    const unsigned length = snakeLength(snake);
    Tile** const body = snakeBody(snake);

    TileWidget** const widgets = safeMalloc(sizeof(TileWidget**) * length);

    for (int i = 0; i < length; i++)
        widgets[i] = allocateTileWidget(body[i]);

    return widgets;
}