#include "bishop.h"

// Constructor
Bishop::Bishop(std::pair<int, int> position, Colour colour) : Piece(position, colour)
{
    // Set the icon
    icon = colour == Colour::white ? "♗" : "♝";
}