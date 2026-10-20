// Include all the necessary libraries
#include "board.hpp"
#include <iostream>

// Define the board consturctor
Board::Board(){
    // Create the board array
    this->board_array = {{
        {'R', 'N', 'B', 'K', 'Q', 'B', 'N', 'R'},
        {'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P'},
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'},
        {'r', 'n', 'b', 'k', 'q', 'b', 'n', 'r'}
    }};
}

// Define the print board function
void Board::print_board(){
    // Print the board from white's POV
    for(int row=7; row>=0; row--){
        for(int column=0; column<=7; column++){
            std::cout<<this->board_array[row][column]<<" ";
        }
        std::cout<<"\n";
    }
}