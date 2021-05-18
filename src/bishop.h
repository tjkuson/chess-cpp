// Copyright (C) 2021, Tom Kuson.
// This file is a part of Chess CLI which is released under the GPLv3.
// See LICENSE file in the project root or go to <https://www.gnu.org/licenses/> for full license details.

// bishop.h

#ifndef BISHOP_H
#define BISHOP_H

#include "piece.h"

namespace chess {
	class bishop : public piece {
	public:
		bishop(colour init_colour, const position& init_pos);
		void load_possible_moves(const board& chess_board) override;
	};
}

#endif //BISHOP_H
