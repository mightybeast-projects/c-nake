#include "grid.h"
#include "grid.tests.h"
#include "stdio.h"
#include "unity.h"

static unsigned width = 10;
static unsigned height = 15;
static Grid* grid;

void setUpGrid(void)
{
    grid = allocateGrid(width, height);
}

void tearDownGrid(void)
{
    freeGrid(grid);
}

void Grid_Allocation_Should_Return_New_Grid(void)
{
    TEST_ASSERT_NOT_NULL(grid);
}

void Grid_With_Either_Zero_Cols_Or_Rows_Should_Not_Be_Allocated(void)
{
    Grid* grid;

    grid = allocateGrid(0, 0);
    grid = allocateGrid(0, 1);
    grid = allocateGrid(1, 0);

    TEST_ASSERT_NULL(grid);

    freeGrid(grid);
}

void Grid_With_Less_Than_Three_Rows_Should_Not_Be_Allocated(void)
{
    Grid* grid;

    grid = allocateGrid(1, 1);
    grid = allocateGrid(1, 2);

    TEST_ASSERT_NULL(grid);

    freeGrid(grid);
}

void Allocated_Grid_Should_Have_Passed_Width_And_Height(void)
{
    TEST_ASSERT_EQUAL_UINT(width, gridWidth(grid));
    TEST_ASSERT_EQUAL_UINT(height, gridHeight(grid));
}

void Allocated_Grid_Should_Have_Allocated_Tiles(void)
{
    TEST_ASSERT_NOT_NULL(gridTiles(grid));
}

void Allocated_Grid_Should_Have_Tiles_With_Passed_Width_And_Height(void)
{
    Tile*** tiles = gridTiles(grid);

    for (int i = 0; i < width; i++)
        for (int j = 0; j < height; j++)
            TEST_ASSERT_NOT_NULL(tiles[i][j]);
}

void Grid_Should_Place_Food_On_Random_Tile()
{
    placeFood(grid, 1);

    Tile*** tiles = gridTiles(grid);
    int foodTilesCnt = 0;

    for (int i = 0; i < width; i++)
        for (int j = 0; j < height; j++)
            if (tileHasFood(tiles[i][j]))
                foodTilesCnt++;

    TEST_ASSERT_EQUAL_UINT(1, foodTilesCnt);
}

void runGridTests(void)
{
    RUN_TEST(Grid_Allocation_Should_Return_New_Grid);
    RUN_TEST(Grid_With_Either_Zero_Cols_Or_Rows_Should_Not_Be_Allocated);
    RUN_TEST(Grid_With_Less_Than_Three_Rows_Should_Not_Be_Allocated);

    RUN_TEST(Allocated_Grid_Should_Have_Passed_Width_And_Height);
    RUN_TEST(Allocated_Grid_Should_Have_Allocated_Tiles);
    RUN_TEST(Allocated_Grid_Should_Have_Tiles_With_Passed_Width_And_Height);

    RUN_TEST(Grid_Should_Place_Food_On_Random_Tile);
}