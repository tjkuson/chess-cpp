#include "pawn.h"

// Constructor
Pawn::Pawn(std::pair<int, int> position, Colour colour)
    : Piece(position, colour, piece_type::pawn)
{
    // Set the icon
    icon = colour == Colour::white ? "♙" : "♟";
}