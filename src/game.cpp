// Include all the necessary libraries
#include <iostream>
#include "board.hpp"
#include "engine.hpp"

// main function
int main(){
    Board board;
    Engine engine;
    board.print_board();
    std::cout<<"\n";
    std::array<int,2> from_square = {3,3};
    std::array<int,2> to_square = {4,2};
    bool is_legal = engine.is_legal(board.board_array, from_square, to_square);
    if(is_legal){
        board.make_move(from_square, to_square);
    }
    board.print_board();
    std::cout<<"\n";
    return 0;
}