// Copyright (C) 2021, Tom Kuson.
// This file is a part of Chess CLI which is released under the GPLv3.
// See LICENSE file in the project root or go to <https://www.gnu.org/licenses/> for full license details.

//
// Created by tjk on 02/05/2021.
//

#ifndef KING_H
#define KING_H

#include "piece.h"

namespace chess {
	class king : public piece {
	public:
		king(colour init_colour, const position& init_pos);
		void load_possible_moves(const board& chess_board) override;
	};
}

#endif //KING_H
