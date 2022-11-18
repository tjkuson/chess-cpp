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

#ifndef CHESS_CLI_BISHOP_H
#define CHESS_CLI_BISHOP_H

#include "piece.h"

namespace chess {
class Bishop : public Piece {
public:
    Bishop(Colour init_colour, const Position& init_pos);
    void load_possible_moves(const Board& chess_board) override;
};
}// namespace chess

#endif//CHESS_CLI_BISHOP_H
