#include <gtest/gtest.h>
#include "../src/board.h"

// Update_Cell
TEST(Game_Of_Life_Test, Update_Cell_Test) {
  int cell_alive_next_round = 0;
  int cell_alive_now = 0;  
  int cell_status = update_cell_status(cell_alive_now,cell_alive_next_round);
  EXPECT_EQ(cell_alive_next_round, cell_status);

  cell_alive_next_round = 1;
  cell_alive_now = 0;  
  cell_status = update_cell_status(cell_alive_now,cell_alive_next_round);
  EXPECT_EQ(cell_alive_next_round, cell_status);

  cell_alive_next_round = 0;
  cell_alive_now = 1;  
  cell_status = update_cell_status(cell_alive_now,cell_alive_next_round);
  EXPECT_EQ(cell_alive_next_round, cell_status);

  cell_alive_next_round = 1;
  cell_alive_now = 1;  
  cell_status = update_cell_status(cell_alive_now,cell_alive_next_round);
  EXPECT_EQ(cell_alive_next_round, cell_status);
  
}
