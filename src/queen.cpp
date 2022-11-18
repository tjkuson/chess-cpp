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

#include "queen.h"

using namespace chess;

// Parameterised constructor
Queen::Queen(const Colour init_colour, const Position& init_pos)
    : Piece{init_colour, init_pos}
{
    piece_icon = (piece_colour == Colour::white) ? "♕" : "♛";
}

// Find all possible horizontal, vertical, and diagonal moves, not considering king check
void Queen::load_possible_moves(const Board& chess_board)
{
    possible_moves.clear();
    // Lambda expression to search in a direction
    const auto generate_moves = [&](const int row_offset, const int col_offset) {
        bool searching{true};
        for (int offset{1}; searching; ++offset) {
            const Position visiting{
                    piece_pos.get_offset(offset * row_offset, offset * col_offset)};
            // Stop searching when another piece is encountered
            if (chess_board.in_range(visiting)) {
                if (not chess_board.occupied(visiting)) {
                    possible_moves.push_back(visiting);
                    continue;
                }
                else if (attacking_enemy(visiting, chess_board)) {
                    // If piece is enemy, then it can be captured
                    possible_moves.push_back(visiting);
                }
            }
            searching = false;
        }
    };
    generate_moves(1, 0);  // Move vertically down
    generate_moves(-1, 0); // Move vertically up
    generate_moves(0, 1);  // Move vertically right
    generate_moves(0, -1); // Move vertically left
    generate_moves(1, 1);  // Move down and to the right
    generate_moves(1, -1); // Move down and to the left
    generate_moves(-1, 1); // Move up and to the right
    generate_moves(-1, -1);// Move up and to the left
}
