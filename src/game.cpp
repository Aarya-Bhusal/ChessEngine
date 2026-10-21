// Include all the necessary libraries
#include <iostream>
#include "board.hpp"
#include "engine.hpp"

// main function
int main(){
    Board board;
    Engine engine;
    
    // Squares, rows and columns
    std::string from_square;
    std::string to_square;
    int from_col;
    int from_row;
    int to_col;
    int to_row;

    // Game loop
    while(true){
        board.print_board();
        std::cout<<"\n";
        std::cout<<"Enter the from square : ";
        std::cin>>from_square;
        std::cout<<"Enter the to square : ";
        std::cin>>to_square;
        from_col = (int)from_square[0] - 97;
        from_row = from_square[1]-'0';
        std::array<int, 2> from_square = {from_row-1, from_col};
        to_col = (int)to_square[0] - 97;
        to_row = to_square[1]-'0';
        std::array<int, 2> to_square = {to_row-1, to_col};
        bool is_legal = engine.is_legal(board.board_array, from_square, to_square);
        if(is_legal){
            board.make_move(from_square, to_square);
        }else{
            std::cout<<"Illegal_move";
        }
        std::cout<<"\n";
    }

    return 0;
}