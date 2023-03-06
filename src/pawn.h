#ifndef CHESS_CLI_PAWN_H
#define CHESS_CLI_PAWN_H

#include "piece.h"

class Pawn : public Piece {
public:
    // Constructor
    Pawn(std::pair<int, int> position, Colour colour);
    // Destructor
    ~Pawn() noexcept override = default;
};

#endif//CHESS_CLI_PAWN_H
