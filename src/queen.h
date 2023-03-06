#ifndef CHESS_CLI_QUEEN_H
#define CHESS_CLI_QUEEN_H

#include "piece.h"

class Queen : public Piece {
public:
    // Constructor
    Queen(std::pair<int, int> position, Colour colour);
    // Destructor
    ~Queen() noexcept override = default;
};

#endif//CHESS_CLI_QUEEN_H
