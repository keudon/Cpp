struct t_user_input
{
    int cycle_number;
    int init_cell_number;
    int** init_cells_positions;

};

class Board {
    int size_x, size_y;
    char ** board_cells_display;
    int ** board_cells_state;
public:
    void create();
    void initialize(t_user_input);
    void update(int);
    void display();
};
