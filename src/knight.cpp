// Copyright (C) 2021, Tom Kuson.
// This file is a part of Chess CLI which is released under the GPLv3.
// See LICENSE file in the project root or go to <https://www.gnu.org/licenses/> for full license details.

// knight.cpp

#include "knight.h"

using namespace chess;

// Parameterised constructor
knight::knight(const colour init_colour, const position& init_pos)
		:piece{ init_colour, init_pos }
{
	piece_icon = (piece_colour==colour::white) ? "♘" : "♞";
}

// Find all possible "L-shaped" moves, not considering king check
void knight::load_possible_moves(const board& chess_board)
{
	possible_moves.clear();
	const std::vector<position> knight_moves{
			// Eight L-shaped moves
			piece_pos.get_offset(2, -1),
			piece_pos.get_offset(2, 1),
			piece_pos.get_offset(-2, -1),
			piece_pos.get_offset(-2, 1),
			piece_pos.get_offset(1, -2),
			piece_pos.get_offset(-1, -2),
			piece_pos.get_offset(1, 2),
			piece_pos.get_offset(-1, 2),
	};
	// Copy moves to possible  moves vector if they are empty or attacking enemy
	std::copy_if(knight_moves.begin(), knight_moves.end(), std::back_inserter(possible_moves),
			[&](const auto& possible_position) {
			  if (chess_board.in_range(possible_position)) {
				  return !chess_board.occupied(possible_position)
						  || attacking_enemy(possible_position, chess_board);
			  }
			  return false;
			});
}
