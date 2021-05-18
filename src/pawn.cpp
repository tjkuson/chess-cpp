// pawn.cpp

#include "pawn.h"

using namespace chess;

// Parameterised constructor
pawn::pawn(const colour init_colour, const position& init_pos)
		:piece{ init_colour, init_pos }
{
	piece_icon = (piece_colour==colour::white) ? "♙" : "♟";
}

// Find all possible pawn moves, not considering king check
void pawn::load_possible_moves(const board& chess_board)
{
	possible_moves.clear();
	const int direction{ piece_colour==colour::white ? -1 : 1 };
	const position one_step{ piece_pos.get_offset(direction, 0) };
	if (chess_board.in_range(one_step)) {
		if (!chess_board.occupied(one_step)) {
			possible_moves.push_back(one_step);
			int row{ piece_pos.get_position().first };
			if ((row==6 && piece_colour==colour::white) || (row==1 && piece_colour==colour::black)) {
				// Can move up by two squares if pawn has not yet moved
				const position two_step{ piece_pos.get_offset(2*direction, 0) };
				if (!chess_board.occupied(two_step)) {
					possible_moves.push_back(two_step);
				}
			}
		}
	}
	// Pawn can move up diagonally only if attacking
	const auto generate_attacks = [&](const int col_offset) {
	  const position attack_position{ piece_pos.get_offset(direction, col_offset) };
	  if (chess_board.in_range(attack_position)) {
		  if (attacking_enemy(attack_position, chess_board)) {
			  possible_moves.push_back(attack_position);
		  }
	  }
	};
	generate_attacks(-1); // Check forward and to the left
	generate_attacks(1); // Check forward and to the right
}
