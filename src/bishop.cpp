// Copyright (C) 2021, Tom Kuson.
// This file is a part of Chess CLI which is released under the GPLv3.
// See LICENSE file in the project root or go to <https://www.gnu.org/licenses/> for full license details.

// bishop.cpp

#include "bishop.h"

using namespace chess;

bishop::bishop(const colour init_colour, const position& init_pos)
		:piece{ init_colour, init_pos }
{
	piece_icon = (piece_colour==colour::white) ? "♗" : "♝";
}

// Find all possible diagonal moves, not considering king check
void bishop::load_possible_moves(const board& chess_board)
{
	possible_moves.clear();
	// Lambda expression to search in a direction
	const auto generate_moves = [this, &chess_board](const int row_offset, const int col_offset) {
	  bool searching{ true };
	  for (int offset{ 1 }; searching; ++offset) {
		  const position visiting{ piece_pos.get_offset(offset*row_offset, offset*col_offset) };
		  // Stop searching when another piece is encountered
		  if (chess_board.in_range(visiting)) {
			  if (!chess_board.occupied(visiting)) {
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
	generate_moves(1, 1); // Move down and to the right
	generate_moves(1, -1); // Move down and to the left
	generate_moves(-1, 1); // Move up and to the right
	generate_moves(-1, -1); // Move up and to the left
}
