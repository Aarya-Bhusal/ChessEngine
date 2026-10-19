// Include all the necessary libraries
#include <iostream>
#include <string>
#include <unordered_map>
#include <array>

// Create the board and all game functions in Board Class.
class Board{
    public:
        // Create some useful variables for game
        
        std::unordered_map<char, int>alphabet_position={
            {'a', 0},
            {'b', 1},
            {'c', 2},
            {'d', 3},
            {'e', 4},
            {'f', 5},
            {'g', 6},
            {'h', 7},
        };

        std::string board_arr[8][8] = {
            {"BR1","BK1","BB1","BQ","BK","BB2","BK2","BR2"},
            {"BP1","BP2","BP3","BP4","BP5","BP6","BP7","BP8"},
            {" . "," . "," . "," . "," . "," . "," . "," . "},
            {" . "," . "," . "," . "," . "," . "," . "," . "},
            {" . "," . "," . "," . "," . "," . "," . "," . "},
            {" . "," . "," . "," . "," . "," . "," . "," . "},
            {"WP1","WP2","WP3","WP4","WP5","WP6","WP7","WP8"},
            {"WR1","WK1","WB1","WQ","WK","WB2","WK2","WR2"},
        };

        char turn = 'W';

        // Class Constructor
        Board(){
            
        }

        // Function to print the board
        void print_board(){
            // Print the board from white's POV
            for(int row=0; row<=7; row++){
                for(int column=0; column<=7; column++){
                    std::cout<<this->board_arr[row][column]<<"  ";
                }
                std::cout<<"\n";
            }
        }

        // Function to find the positon of a piece in the board
        std::array<int, 2> get_piece_position(std::string piece){
            for(int row=0; row<=7; row++){
                for(int column=0; column<=7; column++){
                    std::string current_piece = this->board_arr[row][column];
                    if (current_piece==piece){
                        return {row, column};
                    }
                }
            }
        }

        // Function to check if it is check
        bool is_check(){
            return true;
        }
        
        // Function to check if it is checkmate
        bool is_check_mate(){
            return false;
        }
        
        // Function to identify if the move is legal or illegal
        bool is_legal(std::string piece, std::string move){
            return true;
        }

        // Function to make a move in the board
        void make_move(std::string piece, std::string move){
            bool move_validity = is_legal(piece, move);
            // Make move only if it is legal
            if(move_validity){
                //Delete the piece at it's current position
                std::array<int, 2> current_position = get_piece_position(piece);
                int current_row = current_position[0];
                int current_column = current_position[1];
                this->board_arr[current_row][current_column] = " . ";

                // Move the piece to the given position
                char row = (char) move[1];
                int row_to_move = 7-(int(row - '0')-1);
                int column_to_move = int(this->alphabet_position[move[0]]);
                this->board_arr[row_to_move][column_to_move] = piece;
            }
            else{
                std::cout<<"Illegal Move";
            }
        }

};

// Main function to run the game
int main(){
    Board board;
    board.print_board();
    std::cout<<"\n\n";
    board.make_move("WP5", "e4");
    board.make_move("BP5", "e5");
    board.print_board();
    return 0;
}