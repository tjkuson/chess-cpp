#ifndef CHESS_CLI_BOARD_H
#define CHESS_CLI_BOARD_H

#include "piece.h"
#include <vector>

class Board {
private:
    std::vector<std::vector<Piece>> pieces;// vector of all 32 pieces

public:
    Board();// Construct with default pieces
    ~Board();
};

#endif//CHESS_CLI_BOARD_H
