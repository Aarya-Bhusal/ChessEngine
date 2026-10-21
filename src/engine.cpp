// Include all the necessary libraries
#include "engine.hpp"
#include <iostream>

// Define the Engine consturctor
Engine::Engine(){

}

// Declare the function to make a move in a given board array
std::array<std::array<char, 8>, 8> Engine::make_move(std::array<std::array<char, 8>, 8> board_array, std::array<int, 2> from_square, std::array<int, 2> to_square){
    char piece = board_array[from_square[0]][from_square[1]];
    board_array[from_square[0]][from_square[1]] = ' ';
    board_array[to_square[0]][to_square[1]] = piece;
    return board_array;
}

// Define the function to return the num of row a pawn can move
int Engine::forward_pawn_steps(int row, char pawn){
    if(row==1 && pawn=='P'){
        return 2;
    }else if(row==6 && pawn=='p'){
        return 2;
    }
    return 1;
}

// Define the function to check if two pieces are of opposite color
bool Engine::is_opposite(char piece, char to_sqr_element){
    int asci = (int)to_sqr_element;
    int piece_asci = (int) piece;

    if((asci>=(int)'a' && asci<=(int)'z') && (piece_asci>=(int)'A' && piece_asci<=(int)'Z')){
        return true;
    }else if((asci>=(int)'A' && asci<=(int)'Z') && (piece_asci>=(int)'a' && piece_asci<=(int)'z')){
        return true;
    }else return false;
}

// Define the function to check it is check
bool Engine::is_check(std::array<std::array<char, 8>, 8> board_array){
    return false;
}

// Define the function to list all the legal moves
std::vector<std::array<int,2>> get_legal_move(char turn, std::array<int, 2> form_square){

}

// Define the function to check if a move is legal
bool Engine::is_legal(std::array<std::array<char, 8>, 8> board_array, std::array<int, 2> from_square, std::array<int, 2> to_square){
    // Get the info about from_square and to_square
    char piece = board_array[from_square[0]][from_square[1]];
    char to_sqr_element = board_array[to_square[0]][to_square[1]];
    int from_row = from_square[0];
    int from_col = from_square[1];
    int to_row = to_square[0];
    int to_col = to_square[1];

    // Check legality for pawn
    if(piece=='P' || piece=='p'){
        // If pawn is only moving in front direction
        if(from_col==to_col){
            int forward_steps = forward_pawn_steps(from_row, piece);
            bool legal_status = false;
            for(int i=1; i<=forward_steps; i++){
                char piece_at_i;
                int current_row;
                // Check if the piece is white or black
                if(piece=='P'){
                    piece_at_i = board_array[from_row+i][from_col];
                    current_row = from_row+i;
                }else{
                    piece_at_i = board_array[from_row-i][from_col];
                    current_row = from_row-i;
                }

                // Check if there is any piece in to_square or 
                if(piece_at_i!=' '){
                    return false;
                }else{
                    if((current_row==to_row) && (from_col==to_col)){
                        std::array<std::array<char, 8>, 8> moved_board_arr = make_move(board_array, from_square, to_square);
                        if(is_check(moved_board_arr)!=true){
                            return true;
                        }
                    }
                }
            }
        }
        
        // If pawn wants to move diagonally
        else{
            // Check in which row a piece can capture
            int capturing_row;
            if(piece=='P') capturing_row = from_row+1;
            else capturing_row = from_row-1;
            
            // Check if the to-square is even in the squares the pawn can move
            if((capturing_row == to_row) && (from_col+1 == to_col || from_col-1 == to_col)){
                // Only allow capturing opposite color
                bool opposite_piece = is_opposite(piece, to_sqr_element);
                std::cout<<opposite_piece<<"\n";
                
                if(opposite_piece){
                    // Check if the move will cause check or not
                    std::array<std::array<char, 8>, 8> moved_board_arr = make_move(board_array, from_square, to_square);
                    if(is_check(moved_board_arr)!=true) return true;
                    else return false;
                } else return false;

            }else{
                return false;
            }
        }

        return false;
    }

    // Check legality for Bishop
    else if(piece=='B' || piece=='b'){
        int current_row = from_row;
        int current_col = from_col;

        // Top-Right Diagonal
        if((to_row>from_row) && (to_col>from_col)){
            while((current_row<=to_row)&&(current_col<=to_col)){
                current_row++;
                current_col++;
                char element_at_current_sqr = board_array[current_row][current_col];
                
                // Return false if any piece lies in diagonal between from-square and to-square
                if((current_row!=to_row) && (current_col!=to_col)){
                    if(element_at_current_sqr!=' ') return false;
                }
                else{
                    if(to_sqr_element!=' '){
                        bool opposide_piece = is_opposite(piece, to_sqr_element);
                        if(opposide_piece){
                            // Check if the move will cause check or not
                            std::array<std::array<char, 8>, 8> moved_board_arr = make_move(board_array, from_square, to_square);
                            if(is_check(moved_board_arr)!=true) return true;
                            else return false;
                        }
                    } else return true;
                }
            }
        }

        // Top-Left Diagonal
        if((to_row>from_row) && (to_col<from_col)){
            while((current_row<=to_row) && (current_col>=to_col)){
                current_row++;
                current_col--;
                char element_at_current_sqr = board_array[current_row][current_col];
                
                // Return false if any piece lies in diagonal between from-square and to-square
                if((current_row!=to_row) && (current_col!=to_col)){
                    if(element_at_current_sqr!=' ') return false;
                }
                else{
                    if(to_sqr_element!=' '){
                        bool opposide_piece = is_opposite(piece, to_sqr_element);
                        if(opposide_piece){
                            // Check if the move will cause check or not
                            std::array<std::array<char, 8>, 8> moved_board_arr = make_move(board_array, from_square, to_square);
                            if(is_check(moved_board_arr)!=true) return true;
                            else return false;
                        }
                    } else return true;
                }
            }  
        }

        // Bottom-Right Diagonal
        if((to_row<from_row) && (to_col>from_col)){
            while((current_row>=to_row) && (current_col<=to_col)){
                current_row--;
                current_col++;
                char element_at_current_sqr = board_array[current_row][current_col];

                // Return false if any piece lies in diagonal between from-square and to-square
                if((current_row!=to_row) && (current_col!=to_col)){
                    if(element_at_current_sqr!=' ') return false;
                }
                else{
                    if(to_sqr_element!=' '){
                        bool opposide_piece = is_opposite(piece, to_sqr_element);
                        if(opposide_piece){
                            // Check if the move will cause check or not
                            std::array<std::array<char, 8>, 8> moved_board_arr = make_move(board_array, from_square, to_square);
                            if(is_check(moved_board_arr)!=true) return true;
                            else return false;
                        }
                    } else return true;
                }
            }
        }

        // Bottom-Left Diagonal
        if((to_row<from_row) && (to_col<from_col)){
            while((current_row>=to_row) && (current_col>=to_col)){
                current_row--;
                current_col--;
                char element_at_current_sqr = board_array[current_row][current_col];

                // Return false if any piece lies in diagonal between from-square and to-square
                if((current_row!=to_row) && (current_col!=to_col)){
                    if(element_at_current_sqr!=' ') return false;
                }
                else{
                    if(to_sqr_element!=' '){
                        bool opposide_piece = is_opposite(piece, to_sqr_element);
                        if(opposide_piece){
                            // Check if the move will cause check or not
                            std::array<std::array<char, 8>, 8> moved_board_arr = make_move(board_array, from_square, to_square);
                            if(is_check(moved_board_arr)!=true) return true;
                            else return false;
                        }
                    } else return true;
                }
            }
        }
        return false;
    }

    // Check legality for Knight
    else if(piece=='N' || piece=='n'){
        bool legal_status = false;
        // L figure in Top-Right
        if((from_row+2==to_row) && (from_col+1==to_col)){
            legal_status = true;
        }
        // L figure in Top-Left
        else if((from_row+2==to_row) && (from_col-1==to_col)){
            legal_status = true;
        }
        // L figure in Right-Top
        else if((from_row+1==to_row) && (from_col+2==to_col)){
            legal_status = true;
        }
        // L figure in Right-Bottom
        else if((from_row-1==to_row) && (from_col+2==to_col)){
            legal_status = true;
        }
        // L figure in Bottom-Right
        else if((from_row-2==to_row) && (from_col+1==to_col)){
            legal_status = true;
        }
        // L figure in Bottom-Left
        else if((from_row-2==to_row) && (from_col-1==to_col)){
            legal_status = true;
        }
        // L figure in Left-Bottom
        else if((from_row-1==to_row) && (from_col-2==to_col)){
            legal_status = true;
        }
        // L figure in Left-Top
        else if((from_row+1==to_row) && (from_col-2==to_col)){
            legal_status = true;
        }
        
        // Make sure there is opponent piece while capturing
        bool valid = false;
        if(legal_status){
            if(to_sqr_element!=' '){
                bool is_opponent = is_opposite(piece, to_sqr_element);
                if(is_opponent){
                    valid = true;
                };
            } else valid = true;
        }

        // Check if the move will cause check
        if(valid){
            std::array<std::array<char, 8>, 8> moved_board_arr = make_move(board_array, from_square, to_square);
            if(is_check(moved_board_arr)!=true) return true;
            else return false;
        }else return false;
    }

    // Check legality for Rook
    else if(piece=='R' || piece=='r'){
        // Top
        if((to_row>from_row) && (to_col==from_col)){
            for(int i=from_row+1; i<=to_row; i++){
                char element_at_current_sqr = board_array[i][from_col];
                if((i!=to_row) && (element_at_current_sqr!=' ')){
                    std::cout<<element_at_current_sqr<<"\n";
                    return false;
                }
                else if(i==to_row){
                    bool valid_square=false;
                    if(element_at_current_sqr!=' '){
                        valid_square = is_opposite(piece, to_sqr_element);
                    }
                    else{
                        valid_square=true;
                    }
                    if(valid_square){
                        std::array<std::array<char, 8>, 8> moved_board = make_move(board_array, from_square, to_square);
                        if(is_check(moved_board)!=true){
                            return true;
                        }
                    }
                }
            }
        }
        
        // Bottom
        else if((to_row<from_row) && (to_col==from_col)){
            std::cout<<"\nHi\n";
            for(int i=from_row-1; i>=to_row; i--){
                char element_at_current_sqr = board_array[i][from_col];
                if((i!=to_row) && (element_at_current_sqr!=' ')){
                    return false;
                }
                else if(i==to_row){
                    bool valid_square=false;
                    if(element_at_current_sqr!=' '){
                        valid_square = is_opposite(piece, to_sqr_element);
                    }
                    else{
                        valid_square=true;
                    }
                    if(valid_square){
                        std::array<std::array<char, 8>, 8> moved_board = make_move(board_array, from_square, to_square);
                        if(is_check(moved_board)!=true){
                            return true;
                        }
                    }
                }
            }
        }

        // Right
        else if((to_row==from_row) && (to_col>from_col)){
            for(int i=from_col+1; i<=to_col; i++){
                char element_at_current_sqr = board_array[from_row][i];
                if((i!=to_col) && (element_at_current_sqr!=' ')){
                    std::cout<<element_at_current_sqr<<"\n";
                    return false;
                }
                else if(i==to_col){
                    bool valid_square=false;
                    if(element_at_current_sqr!=' '){
                        valid_square = is_opposite(piece, to_sqr_element);
                    }
                    else{
                        valid_square=true;
                    }
                    if(valid_square){
                        std::array<std::array<char, 8>, 8> moved_board = make_move(board_array, from_square, to_square);
                        if(is_check(moved_board)!=true){
                            return true;
                        }
                    }
                }
            }
        }

        // Left
        else if((to_row==from_row) && (to_col<from_col)){
            for(int i=from_col-1; i>=to_col; i--){
                char element_at_current_sqr = board_array[from_row][i];
                if((i!=to_col) && (element_at_current_sqr!=' ')){
                    std::cout<<element_at_current_sqr<<"\n";
                    return false;
                }
                else if(i==to_col){
                    bool valid_square=false;
                    if(element_at_current_sqr!=' '){
                        valid_square = is_opposite(piece, to_sqr_element);
                    }
                    else{
                        valid_square=true;
                    }
                    if(valid_square){
                        std::array<std::array<char, 8>, 8> moved_board = make_move(board_array, from_square, to_square);
                        if(is_check(moved_board)!=true){
                            return true;
                        }
                    }
                }
            }
        }
        else return false;
    }

return false;
}