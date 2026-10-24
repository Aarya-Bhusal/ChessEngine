// Include all the necessary libraries
#include "engine.hpp"
#include <iostream>
#include <cstdlib>

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
bool Engine::is_check(std::array<std::array<char, 8>, 8> board_array, char color){
    return false;
}

// Define the function to check legality for pawn
bool Engine::check_pawn_legality(std::array<std::array<char, 8>, 8> board_array, std::array<int, 2> from_square, std::array<int, 2> to_square,char piece){
    // Get the info about from_square and to_square
    char to_sqr_element = board_array[to_square[0]][to_square[1]];
    int from_row = from_square[0];
    int from_col = from_square[1];
    int to_row = to_square[0];
    int to_col = to_square[1];

    // If pawn is moving in front direction
    if(from_col==to_col){
        int forward_steps = forward_pawn_steps(from_row, piece);
        bool legal_status = false;\
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
                    return true;
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
                
            if(opposite_piece) return true;
            else return false;

        }else{
            return false;
        }
    }
    return false;
}

// Define the function to check legality for bishop
bool Engine::check_bishop_legality(std::array<std::array<char, 8>, 8> board_array, std::array<int, 2> from_square, std::array<int, 2> to_square,char piece){
    // Get the info about from_square and to_square
    char to_sqr_element = board_array[to_square[0]][to_square[1]];
    int from_row = from_square[0];
    int from_col = from_square[1];
    int to_row = to_square[0];
    int to_col = to_square[1];
    
    int current_row = from_row;
    int current_col = from_col;

    bool legality = false;

    // Check if both from square and to squares lies in a diagonal
    if(std::abs(from_row-to_row) == std::abs(from_col-to_col)){
        // Top-Right Diagonal
        if((to_row>from_row) && (to_col>from_col)){
            int row = from_row+1;
            int col = from_col+1;
            while((row!=to_row) && (col!=to_col)){
                char element_at_sqr = board_array[row][col];
                std::cout<<"\n"<<element_at_sqr<<"\n";
                if(element_at_sqr!=' '){
                    return false;
                }
                row++;
                col++;
            }
            legality = true;
        }

        // Top-Left Diagonal
        else if((to_row>from_row) && (to_col<from_col)){
            int row = from_row+1;
            int col = from_col-1;
            while((row!=to_row) && (col!=to_col)){
                char element_at_sqr = board_array[row][col];
                std::cout<<"\n"<<element_at_sqr<<"\n";
                if(element_at_sqr!=' '){
                    return false;
                }
                row++;
                col--;
            }
            legality = true;
        }

        // Bottom-Right Diagonal
        else if((to_row<from_row) && (to_col>from_col)){
            int row = from_row-1;
            int col = from_col+1;
            while((row!=to_row) && (col!=to_col)){
                char element_at_sqr = board_array[row][col];
                std::cout<<"\n"<<element_at_sqr<<"\n";
                if(element_at_sqr!=' '){
                    return false;
                }
                row--;
                col++;
            }
            legality = true;
        }

        // Bottom-Left Diagonal
        else if((to_row<from_row) && (to_col<from_col)){
            int row = from_row-1;
            int col = from_col-1;
            while((row!=to_row) && (col!=to_col)){
                char element_at_sqr = board_array[row][col];
                std::cout<<"\n"<<element_at_sqr<<"\n";
                if(element_at_sqr!=' '){
                    return false;
                }
                row--;
                col--;
            }
            legality = true;
        }

        // Check if the piece at the square we want to move is a opponent's piece
        if(legality){
            if(to_sqr_element!=' '){
                bool is_opponet = is_opposite(piece, to_sqr_element);
                return is_opponet;
            }else return true;
        }
        
    }

    return false;
}

// Define the function to check legality for knight
bool Engine::check_knight_legality(std::array<std::array<char, 8>, 8> board_array, std::array<int, 2> from_square, std::array<int, 2> to_square,char piece){
    // Get the info about from_square and to_square
    char to_sqr_element = board_array[to_square[0]][to_square[1]];
    int from_row = from_square[0];
    int from_col = from_square[1];
    int to_row = to_square[0];
    int to_col = to_square[1];
    
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
    if(legal_status){
        if(to_sqr_element!=' '){
            bool is_opponent = is_opposite(piece, to_sqr_element);
            if(is_opponent){
               return true;
            };
        } else return true;
    }else return false;
}

// Define the function to check legality for rook
bool Engine::check_rook_legality(std::array<std::array<char, 8>, 8> board_array, std::array<int, 2> from_square, std::array<int, 2> to_square,char piece){
    // Get the info about from_square and to_square
    char to_sqr_element = board_array[to_square[0]][to_square[1]];
    int from_row = from_square[0];
    int from_col = from_square[1];
    int to_row = to_square[0];
    int to_col = to_square[1];
    // Top
        if((to_row>from_row) && (to_col==from_col)){
            for(int i=from_row+1; i<=to_row; i++){
                char element_at_current_sqr = board_array[i][from_col];
                if((i!=to_row) && (element_at_current_sqr!=' ')){
                    std::cout<<element_at_current_sqr<<"\n";
                    return false;
                }
                else if(i==to_row){
                    if(element_at_current_sqr!=' '){
                        return is_opposite(piece, to_sqr_element);
                    }
                    else{
                        return true;
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
                    std::cout<<element_at_current_sqr<<"\n";
                    return false;
                }
                else if(i==to_row){
                    if(element_at_current_sqr!=' '){
                        return is_opposite(piece, to_sqr_element);
                    }
                    else{
                        return true;
                    }
                }
            }
        }

        // Right
        else if((to_row==from_row) && (to_col>from_col)){
            for(int i=from_col+1; i<=to_col; i++){
                char element_at_current_sqr = board_array[i][from_col];
                if((i!=to_row) && (element_at_current_sqr!=' ')){
                    std::cout<<element_at_current_sqr<<"\n";
                    return false;
                }
                else if(i==to_row){
                    if(element_at_current_sqr!=' '){
                        return is_opposite(piece, to_sqr_element);
                    }
                    else{
                        return true;
                    }
                }
            }
        }

        // Left
        else if((to_row==from_row) && (to_col<from_col)){
            for(int i=from_col-1; i>=to_col; i--){
                char element_at_current_sqr = board_array[i][from_col];
                if((i!=to_row) && (element_at_current_sqr!=' ')){
                    std::cout<<element_at_current_sqr<<"\n";
                    return false;
                }
                else if(i==to_row){
                    if(element_at_current_sqr!=' '){
                        return is_opposite(piece, to_sqr_element);
                    }
                    else{
                        return true;
                    }
                }
            }
        }
        else return false;
}

// Define the function to check legality for king
bool Engine::check_king_legality(std::array<std::array<char, 8>, 8> board_array, std::array<int, 2> from_square, std::array<int, 2> to_square,char piece){
    // Get the info about from_square and to_square
    char to_sqr_element = board_array[to_square[0]][to_square[1]];
    int from_row = from_square[0];
    int from_col = from_square[1];
    int to_row = to_square[0];
    int to_col = to_square[1];

    if(((to_row-from_row)>=-1)&&((to_row-from_row)<=1) && ((to_col-from_col)>=-1)&&((to_col-from_col)<=1)){
            if(to_sqr_element!=' '){
                return is_opposite(piece, to_sqr_element);
            }
            else{
                return true;
            }
    }else return false;
}

// Define the function to check legality for queen
bool Engine::check_queen_legality(std::array<std::array<char, 8>, 8> board_array, std::array<int, 2> from_square, std::array<int, 2> to_square,char piece){
    // Get the info about from_square and to_square
    char to_sqr_element = board_array[to_square[0]][to_square[1]];
    int from_row = from_square[0];
    int from_col = from_square[1];
    int to_row = to_square[0];
    int to_col = to_square[1];
    
    char bishop_piece;
    char rook_piece;
    if(piece=='Q'){
        bishop_piece='B';
        rook_piece='R';
    }else{
        bishop_piece='b';
        rook_piece='r';
    }

    bool bishop_legality = check_bishop_legality(board_array, from_square, to_square, piece);
    bool rook_legality = check_rook_legality(board_array, from_square, to_square, piece);
    if(bishop_legality || rook_legality){
        return true;
    }else return false;
}
 
// Define the function to list all the legal moves
std::vector<std::array<int,2>> Engine::get_legal_move(char turn, std::array<int, 2> form_square){

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

    char color;
    if(piece>='a' && piece<='z') color='B';
    if(piece>='A' && piece<='Z') color='W';

    bool legality;

    // Check legality for pawn
    if(piece=='P' || piece=='p'){
        legality = check_pawn_legality(board_array, from_square, to_square, piece);
    }

    // Check legality for Bishop
    else if(piece=='B' || piece=='b'){
        legality = check_bishop_legality(board_array, from_square, to_square, piece);
    }

    // Check legality for Knight
    else if(piece=='N' || piece=='n'){
        legality = check_knight_legality(board_array, from_square, to_square, piece);
    }

    // Check legality for Rook
    else if(piece=='R' || piece=='r'){
        legality = check_rook_legality(board_array, from_square, to_square, piece);
    }

    // Check the legality for King
    else if(piece=='K' || piece=='k'){
        legality = check_king_legality(board_array, from_square, to_square, piece);
    }

    // Check the legality for Queen
    else if(piece=='Q' || piece=='q'){
        legality = check_queen_legality(board_array, from_square, to_square, piece);
    }
    else legality = false;

    if(legality){
        // Only allow move if it will not cause any checks
        std::array<std::array<char, 8>, 8> moved_board = make_move(board_array, from_square, to_square);
        if(is_check(moved_board, color)!=true){
            return true;
        } else {
            return false;
        }
    }
}