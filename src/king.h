// Copyright (C) 2021, Tom Kuson.
// This file king.h is a part of Chess CLI which is released under the GPLv3.
// See LICENSE file in the project root or go to <https://www.gnu.org/licenses/> for full license details.

#ifndef CHESS_CLI_KING_H
#define CHESS_CLI_KING_H

#include "piece.h"

namespace chess {
    class King : public Piece {
    public:
        King(Colour init_colour, const Position& init_pos);
        void load_possible_moves(const Board& chess_board) override;
    };
}

#endif //CHESS_CLI_KING_H
