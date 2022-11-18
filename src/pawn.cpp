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

#include "pawn.h"

using namespace chess;

// Parameterised constructor
Pawn::Pawn(const Colour init_colour, const Position& init_pos)
        :Piece{init_colour, init_pos}
{
    piece_icon = (piece_colour == Colour::white) ? "♙" : "♟";
}

// Find all possible pawn moves, not considering king check
void Pawn::load_possible_moves(const Board& chess_board)
{
    possible_moves.clear();
    const int direction{piece_colour == Colour::white ? - 1 : 1};
    const Position one_step{piece_pos.get_offset(direction, 0)};
    if (chess_board.in_range(one_step)) {
        if (not chess_board.occupied(one_step)) {
            possible_moves.push_back(one_step);
            int row{piece_pos.get_position().first};
            if ((row == 6 and piece_colour == Colour::white)
                    or (row == 1 and piece_colour == Colour::black)) {
                // Can move up by two squares if pawn has not yet moved
                const Position two_step{piece_pos.get_offset(2 * direction, 0)};
                if (not chess_board.occupied(two_step)) {
                    possible_moves.push_back(two_step);
                }
            }
        }
    }
    // Pawn can move up diagonally only if attacking
    const auto generate_attacks = [&](const int col_offset) {
      const Position attack_position{piece_pos.get_offset(direction, col_offset)};
      if (chess_board.in_range(attack_position)) {
          if (attacking_enemy(attack_position, chess_board)) {
              possible_moves.push_back(attack_position);
          }
      }
    };
    generate_attacks(- 1); // Check forward and to the left
    generate_attacks(1); // Check forward and to the right
}
