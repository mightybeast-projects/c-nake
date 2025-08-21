#pragma once

typedef struct Snake Snake;

Snake* allocateSnake(void);
void freeSnake(Snake* const snake);