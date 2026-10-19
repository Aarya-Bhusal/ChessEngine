// Include all the necessary libraries
#include <iostream>
#include <string>

// Create the board and all game functions in Board Class.
class Board{
    public:
        std::string board_arr[8][8] = {
            {"WR1","WK1","WB1","WQ","WK","WB2","WK2","WR2"},
            {"WP1","WP2","WP3","WP4","WP5","WP6","WP7","WP8"},
            {" . "," . "," . "," . "," . "," . "," . "," . "},
            {" . "," . "," . "," . "," . "," . "," . "," . "},
            {" . "," . "," . "," . "," . "," . "," . "," . "},
            {" . "," . "," . "," . "," . "," . "," . "," . "},
            {"BP1","BP2","BP3","BP4","BP5","BP6","BP7","BP8"},
            {"BR1","BK1","BB1","BQ","BK","BB2","BK2","BR2"}
        };
        Board(){
            
        }

        void print_board(){
            for(int row=7; row>=0; row--){
                for(int column=7; column>=0; column--){
                    std::cout<<this->board_arr[row][column]<<"  ";
                }
                std::cout<<"\n";
            }
        }
        
        bool is_check(){
            
        }

        bool is_check_mate(){
            
        }

};

// Main function to run the game
int main(){
    Board board;
    board.print_board();
    return 0;
}