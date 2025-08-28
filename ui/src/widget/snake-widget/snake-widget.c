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
    freeSnake(widget->snake);
    free(widget);
}

void drawSnakeWidget(const SnakeWidget* const widget)
{
    for (int i = 0; i < snakeLength(widget->snake); i++)
        drawTileWidget(widget->bodyTilesWidgets[i], RED);
}

static TileWidget** allocateBodyTilesWidgets(Snake* const snake)
{
    const unsigned length = snakeLength(snake);
    Tile** const body = snakeBody(snake);

    TileWidget** const widgets = safeMalloc(sizeof(TileWidget**) * length);

    const unsigned width = gridWidth(snakeGrid(snake));
    const float margin = 5;
    const float size = (WIDTH - (width - 1) * margin - margin * 2) / width;

    for (int i = 0; i < length; i++) {
        const Tile* const tile = body[i];
        const float x = tileI(tile) * (size + margin) + margin;
        const float y = tileJ(tile) * (size + margin) + margin;
        const Rectangle rect = { x, y, size, size };

        widgets[i] = allocateTileWidget(body[i], rect);
    }

    return widgets;
}