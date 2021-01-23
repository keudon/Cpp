#include <iostream>
#include <cstring>
#include "board.h"

template <class T>
T** init_board(T board_cell_init_type, int size_x, int size_y)
{
    T ** board_cells_type;

    board_cells_type = new T* [size_x] ;

    for (int i=0; i<size_x; i++)
    {
        board_cells_type[i] = new T [size_y];
        for (int j=0; j<size_y; j++)
        {
            board_cells_type[i][j] = board_cell_init_type;
        }
    }

    return board_cells_type;
}

void Board::create()
{
    int user_x, user_y;

    std::cout << "Board size x ?" << std::endl;
    std::cin >> user_x;

    std::cout << "Board size y ?" << std::endl;
    std::cin >> user_y;

    size_x = user_x;
    size_y = user_y;

    board_cells_display = init_board<char>({},size_x,size_y);
    board_cells_state = init_board<bool>(false,size_x,size_y);


//    board_cells_display = new char* [size_x] ;
//    for (int i=0; i<size_x; i++)
//    {
//        board_cells_display[i] = new char [size_y];
//        for (int j=0; j<size_y; j++)
//        {
//            board_cells_display[i][j] = {};
//        }
//    }

//    board_cells_display[size_x][size_y] = {};

}

void Board::initialize(t_user_input user_input)
{

    for (int i=0; i<user_input.init_cell_number; i++)
    {
        board_cells_display[user_input.init_cells_positions[0][i]][user_input.init_cells_positions[1][i]] = 'O';
    }

}

void Board::update(int cycle_number)
{
    std::cout << "Console cleared." << std::endl;

    for (int x=1; x<size_x; x++)
    {
        for (int y=1; y<size_y; y++)
        {


            // Analyze cells around
            //board_cells_state[x-1][y-1] board_cells_state[x-1][y] board_cells_state[x-1][y+1];
            //std::cout<<buff_str<<std::endl;

        }

    }

    std::cout << "Cycle # " << cycle_number << std::endl;

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



