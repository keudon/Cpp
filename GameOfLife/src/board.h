#include <windows.h>

struct Cell {
    RECT ** geometry;
    int ** alive;
    int ** alive_next_round;
};

class Board {
public:
    Cell * p_cell;
    int number_of_row, number_of_column;
    int number_of_rounds;
    bool game_on {false};
};

int update_cells(int cell_alive_next_round,int cell_alive,RECT cell_geometry,HDC hdc,HBRUSH my_red_brush,HBRUSH my_green_brush);