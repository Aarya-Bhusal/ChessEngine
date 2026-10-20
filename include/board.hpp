#ifndef BOARD_HPP
#define BOARD_HPP

// Include all necessary libraries
#include <array>

// Structure of board class
class Board{
    public:
        // Declare teh board array
        std::array<std::array<char, 8>, 8> board_array;

        // Declare the constructor
        Board();

        // Define the function to print the board
        void print_board();
};

#endif