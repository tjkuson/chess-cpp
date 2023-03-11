#include "knight.h"

// Constructor
Knight::Knight(std::pair<int, int> position, Colour colour)
    : Piece(position, colour, piece_type::knight)
{
    // Set the icon
    icon = colour == Colour::white ? "♘" : "♞";
}