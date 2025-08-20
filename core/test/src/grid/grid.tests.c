#include "grid.h"
#include "grid.tests.h"
#include "unity.h"

static Grid* grid;

void setUpGrid(void)
{
    grid = allocateGrid();
}

void tearDownGrid(void)
{
    freeGrid(grid);
}

void Grid_Allocation_Should_Return_New_Grid()
{
    TEST_ASSERT_NOT_NULL(grid);
}

void runGridTests(void)
{
    RUN_TEST(Grid_Allocation_Should_Return_New_Grid);
}