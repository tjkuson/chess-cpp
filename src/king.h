#ifndef CHESS_CLI_KING_H
#define CHESS_CLI_KING_H

#include "piece.h"

class King : public Piece {
public:
    // Constructor
    King(std::pair<int, int> position, Colour colour);
    // Destructor
    ~King() noexcept override = default;
};

#endif // CHESS_CLI_KING_H
