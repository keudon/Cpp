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

int update_cell_status(int cell_alive_next_round,int cell_alive);

int scan_neighboors(int ** alive, int x, int y);

int predict_cells_status(int total_neighboors_alive, int cell_alive);
