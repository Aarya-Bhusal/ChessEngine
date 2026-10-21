// Include all the necessary libraries
#include <iostream>
#include "board.hpp"

// main function
int main(){
    Board board;
    std::array<int,2> from_square = {1,4};
    std::array<int,2> to_square = {3,4};
    board.make_move(from_square, to_square);
    board.print_board();
    return 0;
}