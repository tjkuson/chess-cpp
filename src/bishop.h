#ifndef CHESS_CLI_BISHOP_H
#define CHESS_CLI_BISHOP_H

#include "piece.h"

class Bishop : public Piece {
public:
    // Constructor
    Bishop(std::pair<int, int> position, Colour colour);
    // Destructor
    ~Bishop() noexcept override = default;
};

#endif // CHESS_CLI_BISHOP_H
