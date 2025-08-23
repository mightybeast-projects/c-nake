#include "grid.h"
#include "grid.tests.h"
#include "snake.h"
#include "stdio.h"
#include "unity.h"

static unsigned cols = 10;
static unsigned rows = 20;
static Grid* grid;

void setUpGrid(void)
{
    grid = allocateGrid(cols, rows);
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
    TEST_ASSERT_EQUAL_UINT(cols, gridWidth(grid));
    TEST_ASSERT_EQUAL_UINT(rows, gridHeight(grid));
}

void Allocated_Grid_Should_Have_Allocated_Tiles(void)
{
    TEST_ASSERT_NOT_NULL(gridTiles(grid));
}

void Allocated_Grid_Should_Have_Tiles_With_Passed_Width_And_Height(void)
{
    Tile*** tiles = gridTiles(grid);

    for (int i = 0; i < cols; i++)
        for (int j = 0; j < rows; j++)
            TEST_ASSERT_NOT_NULL(tiles[i][j]);
}

void runGridTests(void)
{
    RUN_TEST(Grid_Allocation_Should_Return_New_Grid);
    RUN_TEST(Grid_With_Either_Zero_Cols_Or_Rows_Should_Not_Be_Allocated);
    RUN_TEST(Grid_With_Less_Than_Three_Rows_Should_Not_Be_Allocated);

    RUN_TEST(Allocated_Grid_Should_Have_Passed_Width_And_Height);
    RUN_TEST(Allocated_Grid_Should_Have_Allocated_Tiles);
    RUN_TEST(Allocated_Grid_Should_Have_Tiles_With_Passed_Width_And_Height);
}