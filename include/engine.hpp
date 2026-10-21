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

        // Declare the function to make a move in a given board array
        std::array<std::array<char, 8>, 8> make_move(std::array<std::array<char, 8>, 8> board_array, std::array<int, 2> from_square, std::array<int, 2> to_square);

        // Declare the function to return the num of row a pawn can move
        int forward_pawn_steps(int row, char pawn);

        // Declare the function to check if two pieces are of opposite color
        bool is_opposite(char piece, char to_sqr_element);

        // Define the function to check it is check
        bool is_check(std::array<std::array<char, 8>, 8> board_array);

        // Declare the function to list all the legal moves
        std::vector<std::array<int,2>> get_legal_move(char turn, std::array<int, 2> form_square);

        // Declare the function to check if a move is legal
        bool is_legal(std::array<std::array<char, 8>, 8> board_array, std::array<int, 2> from_square, std::array<int, 2> to_square);
};

#endif