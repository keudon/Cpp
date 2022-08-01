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
