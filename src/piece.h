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

#ifndef CHESS_CLI_PIECE_H
#define CHESS_CLI_PIECE_H

#include "board.h"
#include "colour.h"
#include "position.h"
#include <algorithm>
#include <memory>
#include <vector>

namespace chess {

// Forward declare to reference board class
class Board;

class Piece {
protected:
    const Colour piece_colour;
    Position piece_pos;
    std::string piece_icon;
    std::vector<Position> possible_moves;
    std::vector<Position> legal_moves;// Moves that don't put own king in check
public:
    // Prototype constructor and destructor
    Piece(const Colour init_colour, const Position& init_pos);
    virtual ~Piece() noexcept;
    // Prototype functions
    [[nodiscard]] std::string get_icon() const;
    [[nodiscard]] Colour get_colour() const;
    [[nodiscard]] int get_num_of_legal_moves() const;
    void set_position(const Position& new_pos);
    [[nodiscard]] bool possible_move(const Position& move) const;
    [[nodiscard]] bool
    attacking_enemy(const Position& visiting_pos, const Board& game_board) const;
    // Take chess board by value as the function will manipulate piece positions
    [[nodiscard]] bool
    legal_move(const Position& init_pos, const Position& final_pos,
               Board chess_board) const;
    void load_legal_moves(const Board& chess_board);
    [[nodiscard]] bool legal_move(const Position& move) const;
    // Prototype virtual functions to be overridden by derived classes
    virtual void load_possible_moves(const Board& chess_board) = 0;
};
}// namespace chess

#endif//CHESS_CLI_PIECE_H
