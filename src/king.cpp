// Copyright (C) 2021, Tom Kuson.
// This file king.cpp is a part of Chess CLI which is released under the GPLv3.
// See LICENSE file in the project root or go to <https://www.gnu.org/licenses/> for full license details.

#include "king.h"

using namespace chess;

// Parameterised constructor
King::King(const Colour init_colour, const Position& init_pos)
		:Piece{ init_colour, init_pos }
{
	piece_icon = piece_colour==Colour::white ? "♔" : "♚";
}

// Find all possible one-step moves, not considering king check
void King::load_possible_moves(const Board& chess_board)
{
	possible_moves.clear();
	const std::vector<Position> king_moves{
			// Eight directions the king can move
			piece_pos.get_offset(1, 1),
			piece_pos.get_offset(1, 0),
			piece_pos.get_offset(1, -1),
			piece_pos.get_offset(0, 1),
			piece_pos.get_offset(0, -1),
			piece_pos.get_offset(-1, 1),
			piece_pos.get_offset(-1, 0),
			piece_pos.get_offset(-1, -1),
	};
	// Copy moves to possible  moves vector if they are empty or attacking enemy
	std::copy_if(king_moves.begin(), king_moves.end(), std::back_inserter(possible_moves),
			[&](const auto& possible_position) {
			  if (chess_board.in_range(possible_position)) {
				  return not chess_board.occupied(possible_position)
						  or attacking_enemy(possible_position, chess_board);
			  }
			  return false;
			});

}
