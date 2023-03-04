#ifndef CHESS_CLI_BOARD_H
#define CHESS_CLI_BOARD_H

#include "piece.h"
#include <vector>

class Board {
private:
    const std::vector<std::vector<piece>> pieces;

public:
    Board();// Construct with default pieces
    ~Board();
};

#endif//CHESS_CLI_BOARD_H
