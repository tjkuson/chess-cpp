#include "pawn.h"

// Constructor
Pawn::Pawn(std::pair<int, int> position, Colour colour) : Piece(position, colour)
{
    // Set the icon
    icon = colour == Colour::white ? "♙" : "♟";
}