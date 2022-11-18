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

#include "knight.h"

using namespace chess;

// Parameterised constructor
Knight::Knight(const Colour init_colour, const Position& init_pos)
    : Piece{init_colour, init_pos}
{
    piece_icon = (piece_colour == Colour::white) ? "♘" : "♞";
}

// Find all possible "L-shaped" moves, not considering king check
void Knight::load_possible_moves(const Board& chess_board)
{
    possible_moves.clear();
    const std::vector<Position> knight_moves{
            // Eight L-shaped moves
            piece_pos.get_offset(2, -1),
            piece_pos.get_offset(2, 1),
            piece_pos.get_offset(-2, -1),
            piece_pos.get_offset(-2, 1),
            piece_pos.get_offset(1, -2),
            piece_pos.get_offset(-1, -2),
            piece_pos.get_offset(1, 2),
            piece_pos.get_offset(-1, 2),
    };
    // Copy moves to possible  moves vector if they are empty or attacking enemy
    std::copy_if(knight_moves.begin(), knight_moves.end(),
                 std::back_inserter(possible_moves),
                 [&](const auto& possible_position) {
                     if (chess_board.in_range(possible_position)) {
                         return not chess_board.occupied(possible_position)
                                 or attacking_enemy(possible_position, chess_board);
                     }
                     return false;
                 });
}
