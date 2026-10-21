// Include all the necessary libraries
#include <iostream>
#include "board.hpp"
#include "engine.hpp"

// main function
int main(){
    Board board;
    Engine engine;
    board.print_board();
    std::array<int,2> from_square = {1,4};
    std::array<int,2> to_square = {2,5};
    bool is_legal = engine.is_legal(board.board_array, from_square, to_square);
    if(is_legal){
        board.make_move(from_square, to_square);
    }
    board.print_board();
    return 0;
}