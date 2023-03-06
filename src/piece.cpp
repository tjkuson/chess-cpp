#include "piece.h"

#include <utility>

// Constructor; note that the position is passed by value and then moved into the position member variable
Piece::Piece(std::pair<int, int> position, Colour colour) : position(std::move(position)), colour(colour) {}
// Destructor
Piece::~Piece() noexcept = default;

// Getters and setters
auto Piece::get_position() const -> std::pair<int, int>
{
    return position;
}
auto Piece::get_colour() const -> Colour
{
    return colour;
}
void Piece::set_position(std::pair<int, int> pos)
{
    Piece::position = pos;
}
// Piece::set_colour is not defined because the colour of a piece is immutable

// Overload the << operator to print the piece
auto operator<<(std::ostream& output_stream, const Piece& piece) noexcept -> std::ostream&
{
    return output_stream << piece.icon;
}