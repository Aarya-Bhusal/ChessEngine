#ifndef ENGINE_HPP
#define ENGINE_HPP

// Include all the necessary libraries
#include <array>
#include <vector>

// Structure of Engine Class
class Engine{
    public:
        // Declare the constructor
        Engine(); 

        // Declare the function to list all the legal moves
        std::vector<std::array<int,2>> get_legal_move(char turn, std::array<int, 2> form_square);

        // Declare the function to check if a move is legal
        bool is_legal(std::array<int, 2> from_square, std::array<int, 2> to_square);
};

#endif