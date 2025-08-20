#include "tile.h"
#include "tile.tests.h"
#include "unity.h"

static Tile* tile;

void setUpTile(void)
{
    tile = allocateTile();
}

void tearDownTile(void)
{
    freeTile(tile);
}

void Tile_Allocation_Should_Return_New_Tile(void)
{
    TEST_ASSERT_NOT_NULL(tile);
}

void runTileTests(void)
{
    RUN_TEST(Tile_Allocation_Should_Return_New_Tile);
}