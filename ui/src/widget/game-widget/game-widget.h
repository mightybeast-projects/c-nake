#include "game.h"

typedef struct GameWidget GameWidget;

GameWidget* allocateGameWidget(Game* const game);
void freeGameWidget(GameWidget* const widget);

void drawGameWidget(GameWidget* const widget);