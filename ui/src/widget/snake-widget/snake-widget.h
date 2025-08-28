#include "snake.h"

typedef struct SnakeWidget SnakeWidget;

SnakeWidget* allocateSnakeWidget(Snake* const snake);
void freeSnakeWidget(SnakeWidget* const widget);

void drawSnakeWidget(const SnakeWidget* const widget);