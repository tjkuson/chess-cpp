// rook.cpp

#include "rook.h"

using namespace chess;

// Parameterised constructor
rook::rook(const colour init_colour, const position& init_pos)
		:piece{ init_colour, init_pos }
{
	piece_icon = (piece_colour==colour::white) ? "♖" : "♜";
}

// Find all possible horizontal and vertical moves, not considering king check
void rook::load_possible_moves(const board& chess_board)
{
	possible_moves.clear();
	// Lambda expression to search in a direction
	const auto generate_moves = [&](const int row_offset, const int col_offset) {
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
	generate_moves(1, 0); // Move vertically down
	generate_moves(-1, 0); // Move vertically up
	generate_moves(0, 1); // Move vertically right
	generate_moves(0, -1); // Move vertically left
}
