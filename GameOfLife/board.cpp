#include <iostream>
#include "board.h"

template <typename T>
T** init_board(T board_cell_init, int size_x, int size_y)
{
    T ** board_cells_type;

    board_cells_type = new T* [size_x] ;

    for (int i=0; i<size_x; i++)
    {
        board_cells_type[i] = new T [size_y];
        for (int j=0; j<size_y; j++)
        {
            board_cells_type[i][j] = board_cell_init;
        }
    }

    return board_cells_type;
}
