#include "colour.h"

// Overload the negation operator to return the opposite colour
auto operator!(Colour colour) noexcept -> Colour
{
    return colour == Colour::white ? Colour::black : Colour::white;
}

// Overload the insertion operator to print the colour
auto operator<<(std::ostream& output_stream, Colour colour) noexcept
    -> std::ostream&
{
    return output_stream << (colour == Colour::white ? "white" : "black");
}