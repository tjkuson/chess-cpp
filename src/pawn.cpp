#include "pawn.h"

// Constructor
Pawn::Pawn(std::pair<int, int> position, Colour colour) : Piece(position, colour)
{
    // Set the icon
    if (colour == Colour::white) {
        icon = "♙";
    }
    else {
        icon = "♟";
    }
}