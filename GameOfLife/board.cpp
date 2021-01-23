#include <iostream>
#include "board.h"

void Board::create()
{
    int user_x, user_y;

    std::cout << "Board size x ?" << std::endl;
    std::cin >> user_x;

    std::cout << "Board size y ?" << std::endl;
    std::cin >> user_y;

    size_x = user_x;
    size_y = user_y;

    board_cells_display = new char* [size_x] ;
    for (int i=0; i<size_x; i++)
    {
        board_cells_display[i] = new char [size_y];
        for (int j=0; j<size_y; j++)
        {
            board_cells_display[i][j] = {};
        }
    }

//    board_cells_display[size_x][size_y] = {};

}


void Board::display()
{
    std::cout << std::string(size_y+2,'-') << std::endl;
    for (int i=0 ; i<size_x ; i++)
    {
        std::cout << '|' ;
        for (int j=0 ; j<size_y ; j++)
        {
            std::cout << board_cells_display[i][j];
        }
        std::cout << '|' << std::endl;
    }
    std::cout << std::string(size_y+2,'-') << std::endl;
}


void Board::initialize(t_user_input user_input)
{

    for (int i=0; i<user_input.init_cell_number; i++)
    {
        board_cells_display[user_input.init_cells_positions[0][i]][user_input.init_cells_positions[1][i]] = 'X';
    }

}
