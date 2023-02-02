#include <gtest/gtest.h>
#include "../src/board.h"

// Rename as Compute Board State Test
class Update_Cell_Status_Test : public ::testing::TestWithParam<std::tuple<int, int>> {};

TEST_P(Update_Cell_Status_Test, TestUpdateCellStatus) {
  int cell_alive_now = std::get<0>(GetParam());
  int cell_alive_next_round = std::get<1>(GetParam());
  int cell_status = update_cell_status(cell_alive_now,cell_alive_next_round);
  EXPECT_EQ(cell_alive_next_round, cell_status);
}

INSTANTIATE_TEST_SUITE_P(
    Update_Cell_Status_Test_Instantiation, Update_Cell_Status_Test,
    ::testing::Values(std::make_tuple(0, 0), std::make_tuple(1, 0),
                      std::make_tuple(0, 1), std::make_tuple(1, 1)));