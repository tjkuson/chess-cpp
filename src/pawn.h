// Copyright (C) 2021, Tom Kuson.
// This file pawn.h is a part of Chess CLI which is released under the GPLv3.
// See LICENSE file in the project root or go to <https://www.gnu.org/licenses/> for full license details.

#ifndef CHESS_CLI_PAWN_H
#define CHESS_CLI_PAWN_H

#include "piece.h"

namespace chess {
class Pawn : public Piece {
public:
    Pawn(Colour init_colour, const Position& init_pos);
    void load_possible_moves(const Board& chess_board) override;
};
}// namespace chess

#endif//CHESS_CLI_PAWN_H
