#include <windows.h>

struct t_user_input
{
    int cycle_number;
    int init_cell_number;
    int** init_cells_positions;

};

struct Cell {
    RECT ** geometry;
    int ** alive;
    int ** alive_next_round;
};

class Board {
public:
    bool game_on;
    Cell * p_cell;
    int size_x, size_y;
//    char ** board_cells_display;
//    int ** board_cells_state;
//    void create();
//    void initialize(t_user_input);
//    void update(int);
//    void display();
};
