// Copyright (C) 2021, Tom Kuson.
// This file is a part of Chess CLI which is released under the GPLv3.
// See LICENSE file in the project root or go to <https://www.gnu.org/licenses/> for full license details.

// rook.h

#ifndef ROOK_H
#define ROOK_H

#include "piece.h"

namespace chess {
	class rook : public piece {
	public:
		rook(colour init_colour, const position& init_pos);
		void load_possible_moves(const board& chess_board) override;
	};
}

#endif //ROOK_H
