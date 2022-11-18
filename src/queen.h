// Copyright (C) 2021, Tom Kuson.
// This file queen.h is a part of Chess CLI which is released under the GPLv3.
// See LICENSE file in the project root or go to <https://www.gnu.org/licenses/> for full license details.

#ifndef CHESS_CLI_QUEEN_H
#define CHESS_CLI_QUEEN_H

#include "piece.h"

namespace chess {
class Queen : public Piece {
public:
    Queen(Colour init_colour, const Position& init_pos);
    void load_possible_moves(const Board& chess_board) override;
};
}// namespace chess

#endif//CHESS_CLI_QUEEN_H
