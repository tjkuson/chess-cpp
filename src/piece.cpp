#include "piece.h"
#include <utility>

// Constructor; note that the position is passed by value and then moved into
// the position member variable
Piece::Piece(std::pair<int, int> position, Colour colour, piece_type type)
    : position(std::move(position)), colour(colour), type(type)
{}
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
auto Piece::get_type() const -> piece_type
{
    return type;
}

// Overload the << operator to print the piece
auto operator<<(std::ostream& output_stream, const Piece& piece) noexcept
    -> std::ostream&
{
    return output_stream << piece.icon;
}
