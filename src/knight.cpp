#include "knight.h"

// Constructor
Knight::Knight(std::pair<int, int> position, Colour colour) : Piece(position, colour)
{
    // Set the icon
    icon = colour == Colour::white ? "♘" : "♞";
}