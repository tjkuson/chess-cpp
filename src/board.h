// Chess CLI: command-line chess
// Copyright (c) 2022 Tom Kuson
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.

#ifndef CHESS_CLI_BOARD_H
#define CHESS_CLI_BOARD_H

#include "colour.h"
#include "main.h"
#include "piece.h"
#include "position.h"
#include <memory>
#include <vector>

namespace chess {
// Forward declare piece class to resolve circular dependency \
    This allows the board class to store piece class pointers before piece class has been defined
class Piece;

class Board {
private:
    const std::pair<int, int> dimensions;// row, col
    std::vector<std::shared_ptr<Piece>> squares;

public:
    // Prototype constructor and destructor
    Board(int rows, int cols);
    ~Board();
    // Prototype functions
    [[nodiscard]] bool in_range(const Position& pos) const;
    [[nodiscard]] bool occupied(const Position& pos) const;
    void place_piece(const Position& pos, const std::shared_ptr<Piece>& piece_ptr);
    void place_piece_no_update(const Position& pos,
                               const std::shared_ptr<Piece>& piece_ptr);
    [[nodiscard]] std::shared_ptr<Piece> get_piece(const Position& pos) const;
    [[nodiscard]] Position find_king(const Colour& king_colour) const;
    [[nodiscard]] std::pair<bool, Position>
    promotable_pawn(const Colour& pawn_colour) const;
    [[nodiscard]] auto get_icon(const Position& pos) const noexcept -> std::string;
};
}// namespace chess

#endif//CHESS_CLI_BOARD_H
