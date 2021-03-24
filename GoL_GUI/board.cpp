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

//void Board::create()
//{
//    int user_x, user_y;
//
//    std::cout << "Board size x ?" << std::endl;
//    std::cin >> user_x;
//
//    std::cout << "Board size y ?" << std::endl;
//    std::cin >> user_y;
//
//    size_x = user_x;
//    size_y = user_y;
//
//    board_cells_display = init_board<char>({},size_x,size_y);
//    board_cells_state = init_board<int>(0,size_x,size_y);
//
//}
//
//void Board::initialize(t_user_input user_input)
//{
//
//    for (int i=0; i<user_input.init_cell_number; i++)
//    {
//        board_cells_display[user_input.init_cells_positions[0][i]][user_input.init_cells_positions[1][i]] = 'O';
//        board_cells_state[user_input.init_cells_positions[0][i]][user_input.init_cells_positions[1][i]] = 1;
//    }
//
//}
//
//void Board::update(int cycle_number)
//{
//    for (int x=1; x<size_x-1; x++)
//    {
//        for (int y=1; y<size_y-1; y++)
//        {
//            // Analyze cells around
//            int E,S,next_E;
//
//            E = board_cells_state[x][y];
//
//            S = board_cells_state[x-1][y-1] + board_cells_state[x-1][y] + board_cells_state[x-1][y+1] + board_cells_state[x+1][y-1] + board_cells_state[x+1][y] + board_cells_state[x+1][y+1] + board_cells_state[x][y-1] + board_cells_state[x][y+1];
//
//            (S==3 || (E==1 && S==2)) ? next_E=1 : next_E=0;
////            std::cout << "next_E" << next_E << std::endl;
//            board_cells_state[x][y] = next_E;
//
//        }
//
//    }
//
//    std::cout << "Cycle # " << cycle_number << std::endl;
//
//}


//void Board::display()
//{
//    char display_char;
//    std::cout << std::string(size_y+2,'-') << std::endl;
//    for (int i=0 ; i<size_x ; i++)
//    {
//        std::cout << '|' ;
//        for (int j=0 ; j<size_y ; j++)
//        {
//            board_cells_state[i][j]==1 ? display_char='O' : display_char=' ';
//            std::cout << display_char;
//        }
//        std::cout << '|' << std::endl;
//    }
//    std::cout << std::string(size_y+2,'-') << std::endl;
//}



