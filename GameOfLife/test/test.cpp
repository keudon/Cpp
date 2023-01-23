#include <gtest/gtest.h>
#include "../src/board.h"

// Demonstrate some basic assertions.
TEST(Game_Of_Life_Test, Update_Cell_Test) {
  int cell_alive_next_round = 0;
  int cell_alive = 1;
  HDC hdc; // Handle to Device Context
  HBRUSH my_red_brush, my_green_brush;
  RECT cell_geometry;

  int res;

  res = update_cells(cell_alive_next_round,cell_alive,cell_geometry,hdc,my_red_brush,my_green_brush);
  
  EXPECT_EQ(res, 0);
}
