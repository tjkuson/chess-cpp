#include "queen.h"

// Constructor
Queen::Queen(std::pair<int, int> position, Colour colour)
    : Piece(position, colour, piece_type::queen)
{
    // Set the icon
    icon = colour == Colour::white ? "♕" : "♛";
}