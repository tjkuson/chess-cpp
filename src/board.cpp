#include "board.h"

// Default constructor
Board::Board()
{
    constexpr auto num_pieces{32};
    pieces = std::vector<std::vector<Piece>>(num_pieces);
}

// Destructor
Board::~Board() = default;