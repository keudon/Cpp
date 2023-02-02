#include "board.h"

int update_cell_status(int cell_alive_now, int cell_alive_next_round)
{
    return (cell_alive_next_round != cell_alive_now) ? cell_alive_next_round : cell_alive_now;
}

int scan_neighboors(int ** alive, int x, int y)
{
    return alive[x-1][y-1] + alive[x-1][y] + alive[x-1][y+1] + alive[x+1][y-1] + alive[x+1][y] + alive[x+1][y+1] + alive[x][y-1] + alive[x][y+1];
}

int predict_cells_status(int total_neighboors_alive, int cell_alive)
{
    int cell_alive_next_round;
    
    ((cell_alive==1 && (total_neighboors_alive==3 || total_neighboors_alive==2)) || (cell_alive==0 && total_neighboors_alive==3)) ? cell_alive_next_round=1 : cell_alive_next_round=0;
    
    return cell_alive_next_round;
}