#include "rook.h"

// Constructor
Rook::Rook(std::pair<int, int> position, Colour colour): Piece(position, colour)
{
    // Set the icon
    icon = colour == Colour::white ? "♖" : "♜";
}