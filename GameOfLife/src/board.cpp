#include "board.h"

int update_cell_status(int cell_alive_now, int cell_alive_next_round)
{
    return (cell_alive_next_round != cell_alive_now) ? cell_alive_next_round : cell_alive_now;
}

int scan_neighboors(int ** alive, int x, int y)
{
    return alive[x-1][y-1] + alive[x-1][y] + alive[x-1][y+1] + alive[x+1][y-1] + alive[x+1][y] + alive[x+1][y+1] + alive[x][y-1] + alive[x][y+1];
}