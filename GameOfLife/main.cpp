#include <iostream>
#include <windows.h>
#include "board.h"

int board_display(t_user_input);

// Function Definition
t_user_input input()
{
    t_user_input new_input;

    std::cout << "Duration of Life ? (in number of cycles)" << std::endl;
    std::cin >> new_input.cycle_number;

    std::cout << "Initial cell(s) number ?" << std::endl;
    std::cin >> new_input.init_cell_number;



    new_input.init_cells_positions = new int* [2]; // Rows

    new_input.init_cells_positions[0] = new int [new_input.init_cell_number]; // 1st line : X
    new_input.init_cells_positions[1] = new int [new_input.init_cell_number]; // 2nd line : Y

    for (int i=0; i<new_input.init_cell_number; i++)
    {
        std::cout << "Cell " << i << " x position : " << std::endl;
        std::cin >> new_input.init_cells_positions[0][i];

        std::cout << "Cell " << i << " y position : " << std::endl;
        std::cin >> new_input.init_cells_positions[1][i];

    }

    return new_input;
}

// Main
int main()
{
    Board the_board;
    // Declarations
    t_user_input user_struct;

    user_struct = input();

    the_board.create();
    the_board.initialize(user_struct);

    for(int i=0; i<user_struct.cycle_number; i++)
    {
        the_board.display();
        Sleep(500);
        the_board.update(i);

    }



    return 0;
}

