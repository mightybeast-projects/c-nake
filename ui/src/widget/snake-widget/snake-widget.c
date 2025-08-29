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
        Tile* const tile = snakeBody(widget->snake)[i];

        if (widget->bodyTilesWidgets[i] == NULL)
            widget->bodyTilesWidgets[i] = allocateTileWidget(tile);

        TileWidget* const tileWidget = widget->bodyTilesWidgets[i];

        setTileWidgetTile(tileWidget, tile);
        calculateTileWidgetRect(tileWidget);
    }
}

void drawSnakeWidget(const SnakeWidget* const widget)
{
    Tile** const body = snakeBody(widget->snake);

    for (int i = 0; i < snakeLength(widget->snake); i++) {
        TileWidget* const tileWidget = widget->bodyTilesWidgets[i];
        Tile* const tile = body[i];

        Color color;

        if (snakeHead(widget->snake) == tile)
            color = (Color) { 13, 250, 0, 255 };
        else if (snakeTail(widget->snake) == tile)
            color = (Color) { 11, 160, 0, 255 };
        else
            color = (Color) { 13, 190, 0, 255 };

        drawTileWidget(tileWidget, color);
    }
}

static TileWidget** allocateBodyTilesWidgets(Snake* const snake)
{
    const unsigned length = snakeLength(snake);
    Tile** const body = snakeBody(snake);
    Grid* const grid = snakeGrid(snake);
    const unsigned width = gridWidth(grid);
    const unsigned height = gridHeight(grid);

    TileWidget** const widgets = safeMalloc(sizeof(TileWidget*) * width * height);

    for (int i = 0; i < length; i++)
        widgets[i] = allocateTileWidget(body[i]);
    for (int i = length; i < width * height; i++)
        widgets[i] = NULL;

    return widgets;
}