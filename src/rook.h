#ifndef CHESS_CLI_ROOK_H
#define CHESS_CLI_ROOK_H

#include "piece.h"

class Rook : public Piece {
public:
    // Constructor
    Rook(std::pair<int, int> position, Colour colour);
    // Destructor
    ~Rook() noexcept override = default;
};

#endif//CHESS_CLI_ROOK_H
