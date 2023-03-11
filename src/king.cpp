#include "king.h"

// Constructor
King::King(std::pair<int, int> position, Colour colour)
    : Piece(position, colour, piece_type::king)
{
    // Set the icon
    icon = colour == Colour::white ? "♔" : "♚";
}