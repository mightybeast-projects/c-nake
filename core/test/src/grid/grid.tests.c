#include "grid.h"
#include "grid.tests.h"
#include "unity.h"

static Grid* grid;

void setUpGrid(void)
{
    grid = allocateGrid(10, 15);
}

void tearDownGrid(void)
{
    freeGrid(grid);
}

void Grid_Allocation_Should_Return_New_Grid()
{
    TEST_ASSERT_NOT_NULL(grid);
}

void Allocated_Grid_Should_Have_Passed_Width_And_Height()
{
    TEST_ASSERT_EQUAL_UINT(10, gridWidth(grid));
    TEST_ASSERT_EQUAL_UINT(15, gridHeight(grid));
}

void Allocated_Grid_Should_Have_Allocated_Tiles()
{
    TEST_ASSERT_NOT_NULL(gridTiles(grid));
}

void runGridTests(void)
{
    RUN_TEST(Grid_Allocation_Should_Return_New_Grid);

    RUN_TEST(Allocated_Grid_Should_Have_Passed_Width_And_Height);
    RUN_TEST(Allocated_Grid_Should_Have_Allocated_Tiles);
}