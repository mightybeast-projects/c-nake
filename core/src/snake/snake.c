#include "safe-memory.h"
#include "snake.h"

struct Snake
{
};

Snake* allocateSnake(void)
{
    return safeMalloc(sizeof(struct Snake));
}

void freeSnake(Snake* const snake)
{
    free(snake);
}
