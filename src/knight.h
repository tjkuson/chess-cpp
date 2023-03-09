#ifndef CHESS_CLI_KNIGHT_H
#define CHESS_CLI_KNIGHT_H

#include "piece.h"

class Knight : public Piece {
public:
    // Constructor
    Knight(std::pair<int, int> position, Colour colour);
    // Destructor
    ~Knight() noexcept override = default;
};

#endif // CHESS_CLI_KNIGHT_H
