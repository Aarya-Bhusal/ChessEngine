# ChessEngine

This is a chess engine build from scratch using C++. The engine can identify legal and illegal moves, detect checks and checkmate, handle castle and all other special chess rules like En-passant. 

# How to complie
*Run the code below in the terminal of projec'ts root directory :*
`
g++ -I include src/game.cpp src/board.cpp src/engine.cpp -o build/game
.\build\game
`