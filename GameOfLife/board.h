#include <windows.h>

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
};
