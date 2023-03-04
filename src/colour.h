#ifndef CHESS_CLI_COLOUR_H
#define CHESS_CLI_COLOUR_H

#include <ostream>
enum class Colour {
    white,
    black
};

auto operator!(Colour colour) noexcept -> Colour;
auto operator<<(std::ostream& output_stream, Colour colour) noexcept -> std::ostream&;

#endif//CHESS_CLI_COLOUR_H
