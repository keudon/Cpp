#include "board.h"

int update_cell_status(int cell_alive_now, int cell_alive_next_round)
{
int cell_status = cell_alive_now;
if (cell_alive_next_round != cell_alive_now)
{
    cell_status = cell_alive_next_round;
}
return cell_status;
}