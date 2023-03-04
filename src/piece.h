#ifndef CHESS_CLI_PIECE_H
#define CHESS_CLI_PIECE_H

#include "colour.h"
#include <utility>
class Piece {
protected:
    const Colour colour;
    std::pair<int, int> position;

public:
    // Prototype for the constructor
    Piece(std::pair<int, int> position, Colour colour);
    // Prototype for the destructor
    virtual ~Piece() noexcept;
    // Prototype getters and setters
    [[nodiscard]] auto get_position() const -> std::pair<int, int>;
    [[nodiscard]] auto get_colour() const -> Colour;
    void set_position(std::pair<int, int> pos);
};

#endif//CHESS_CLI_PIECE_H
