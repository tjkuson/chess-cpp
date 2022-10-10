// Copyright (C) 2021, Tom Kuson.
// This file rook.cpp is a part of Chess CLI which is released under the GPLv3.
// See LICENSE file in the project root or go to <https://www.gnu.org/licenses/> for full license details.

#include "rook.h"

using namespace chess;

// Parameterised constructor
Rook::Rook(const Colour init_colour, const Position& init_pos)
        :Piece{init_colour, init_pos}
{
    piece_icon = (piece_colour==Colour::white) ? "♖" : "♜";
}

// Find all possible horizontal and vertical moves, not considering king check
void Rook::load_possible_moves(const Board& chess_board)
{
    possible_moves.clear();
    // Lambda expression to search in a direction
    const auto generate_moves = [&](const int row_offset, const int col_offset) {
        bool searching{true};
        for (int offset{1}; searching; ++offset) {
            const Position visiting{
                    piece_pos.get_offset(offset*row_offset, offset*col_offset)};
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
    generate_moves(1, 0); // Move vertically down
    generate_moves(-1, 0); // Move vertically up
    generate_moves(0, 1); // Move vertically right
    generate_moves(0, -1); // Move vertically left
}
