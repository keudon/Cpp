#include "board.h"

int update_cells(int cell_alive_next_round,int cell_alive,RECT cell_geometry,HDC hdc,HBRUSH my_red_brush,HBRUSH my_green_brush)
{
int cell_status = cell_alive;
if (cell_alive_next_round != cell_alive)
{
    cell_status = cell_alive_next_round;
    (cell_status) ? FillRect(hdc,&cell_geometry,my_red_brush) : FillRect(hdc,&cell_geometry,my_green_brush);
}
return cell_status;
}