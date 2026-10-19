// Include all the necessary libraries
#include <iostream>
#include <string>
#include <unordered_map>
#include <array>
#include <vector>

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
            {"","","","","","","",""},
            {"","","","","","","",""},
            {"","","","","","","",""},
            {"","","","","","","",""},
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
                    std::string current_element = this->board_arr[row][column];
                    if(current_element != ""){
                        std::cout<<current_element<<"  ";
                    }
                    else{
                        std::cout<<" . "<<"  ";
                    }
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

        std::vector<std::array<int, 2>> get_legal_moves(std::string piece, std::array<int, 2>current_position, std::array<int, 2>move_positon){
            // Get the essential positions
            int current_row = current_position[0];
            int current_column = current_position[1];
            int row_to_move = move_positon[0];
            int column_to_move = move_positon[1];

            // Create the vector that would store all the legal moves
            std::vector<std::array<int, 2>> legal_moves;
            
            // Get the piece type and color
            char piece_type = piece[1];
            char piece_color = piece[0];

            // Check the legal moves for pawn
            if(piece_type=='P'){
                // Check the legal moves for white pawn
                if(piece_color=='W'){
                    // Determine wheather pwan can move 1 or 2 steps
                    int forward_moves_allowed=1;
                    if(current_row==6){
                        forward_moves_allowed=2;
                    }

                    for(int i=1; i<=forward_moves_allowed; i++){
                        int legal_move_row = current_row-i;
                        int legal_move_column = current_column;
                        std::string element_at_legal_square = this->board_arr[legal_move_row][legal_move_column];
                        
                        // Check if there is any other pieces in forward
                        if(element_at_legal_square==""){
                            std::array<int, 2> legal_move = {legal_move_row,legal_move_column};
                            legal_moves.push_back(legal_move);
                        }
                    }

                    // Check if pawn can capture in left/right
                    int capturing_square_row = current_row-1;
                    std::array<bool, 2> left_right_capture_capcity;
                    if(current_column==7) left_right_capture_capcity = {true, false};
                    else if(current_column==0) left_right_capture_capcity = {false, true};
                    else left_right_capture_capcity = {true, true};

                    for(int i=1; i<=2; i++){
                        if(left_right_capture_capcity[i-1]){
                            if(i==1){
                                int capturing_square_column = current_column-1;
                                std::string element_at_capturing_square = this->board_arr[capturing_square_row][capturing_square_column];
                                if(element_at_capturing_square!=""){
                                    char piece_color_at_capturing_square = element_at_capturing_square[0];
                                    if(piece_color!=piece_color_at_capturing_square){
                                        std::array<int, 2> legal_move= {capturing_square_row, capturing_square_column};
                                        legal_moves.push_back(legal_move);
                                    }
                                }
                            }else{
                                int capturing_square_column = current_column+1;
                                std::string element_at_capturing_square = this->board_arr[capturing_square_row][capturing_square_column];
                                if(element_at_capturing_square!=""){
                                    char piece_color_at_capturing_square = element_at_capturing_square[0];
                                    if(piece_color!=piece_color_at_capturing_square){
                                        std::array<int, 2> legal_move= {capturing_square_row, capturing_square_column};
                                        legal_moves.push_back(legal_move);
                                    }
                                }
                            }
                        }
                    }
                }
            }

            // Return all the legal moves
            return legal_moves;
        }
        
        // Function to identify if the move is legal or illegal
        bool is_legal(std::string piece, std::array<int, 2>current_position, std::array<int, 2>move_positon){

            // Get the essential positions
            int row_to_move = move_positon[0];
            int column_to_move = move_positon[1];
            std::array<int, 2> positon_to_move = {row_to_move, column_to_move};
            
            // Get all the legal moves
            std::vector<std::array<int,2>> legal_moves = get_legal_moves(piece, current_position, move_positon);
            for(int i=0; i<legal_moves.size(); i++){
                std::array<int,2> legal_move = legal_moves[i];
                int legal_row = legal_move[0];
                int legal_column = legal_move[1];
                if((row_to_move==legal_row)&&(column_to_move==legal_column)){
                    return true;
                }
            }

            // Return false if any legal move was not found in the loops
            return false;
        }

        // Function to make a move in the board
        void make_move(std::string piece, std::string move){
            // Get the current row and column of the piece
            std::array<int, 2> current_position = get_piece_position(piece);
            int current_row = current_position[0];
            int current_column = current_position[1];

            // Get the move's row and column
            char row = (char) move[1];
            int row_to_move = 7-(int(row - '0')-1);
            int column_to_move = int(this->alphabet_position[move[0]]);

            // Make move only if it is legal
            bool move_validity = is_legal(piece, {current_row, current_column}, {row_to_move, column_to_move});
            if(move_validity){
                //Delete the piece at it's current position
                this->board_arr[current_row][current_column] = "";

                // Move the piece to the given position
                this->board_arr[row_to_move][column_to_move] = piece;
            }
            else{
                std::cout<<"\nIllegal Move\n";
            }
        }

};

// Main function to run the game
int main(){
    // Initialize the game board
    Board board;

    // Keep the game playing
    std::string piece_to_move;
    std::string square_to_move;
    while(true){
        std::cout<<"\n";
        board.print_board();
        std::cout<<"\nEnter the piece to move : ";
        std::cin>>piece_to_move;
        std::cout<<"\nEnter the square to move on : ";
        std::cin>>square_to_move;
        board.make_move(piece_to_move, square_to_move);
    }
    
    return 0;
}