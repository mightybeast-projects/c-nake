#include "tile.h"
#include "tile.tests.h"
#include "unity.h"

static Tile* tile;

void setUpTile(void)
{
    tile = allocateTile(1, 2);
}

void tearDownTile(void)
{
    freeTile(tile);
}

void Tile_Allocation_Should_Return_New_Tile(void)
{
    TEST_ASSERT_NOT_NULL(tile);
}

void Allocated_Tile_Should_Have_Passed_Indexes(void)
{
    TEST_ASSERT_EQUAL_UINT(1, tileI(tile));
    TEST_ASSERT_EQUAL_UINT(2, tileJ(tile));
}

void runTileTests(void)
{
    RUN_TEST(Tile_Allocation_Should_Return_New_Tile);
    RUN_TEST(Allocated_Tile_Should_Have_Passed_Indexes);
}