#include <iostream>
struct t_user_input
{
    int cycle_number;
    int init_cell_number;
    int** init_cells_positions;

};

int board_display(t_user_input user_input)
{
    char board[10][10] = {};

    for (int i=0;i<user_input.init_cell_number;i++) {
                board[user_input.init_cells_positions[0][i]][user_input.init_cells_positions[1][i]] = 'X';
    }


    for (int i=0 ; i<10 ; i++) {
        for (int j=0 ; j<10 ; j++) {
            std::cout << board[i][j];
        }
        std::cout << std::endl;
     }

    return 0;
}
