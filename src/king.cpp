// king.cpp

#include "king.h"

using namespace chess;

// Parameterised constructor
king::king(const colour init_colour, const position& init_position)
		:piece{ init_colour, init_position }
{
	piece_icon = (piece_colour==colour::white) ? "♔" : "♚";
}

// Find all possible one-step moves, not considering king check
void king::load_possible_moves(const board& chess_board)
{
	possible_moves.clear();
	const std::vector<position> temp_possible_moves{
			// Eight directions the king can move
			piece_position.get_position_with_offset(1, 1),
			piece_position.get_position_with_offset(1, 0),
			piece_position.get_position_with_offset(1, -1),
			piece_position.get_position_with_offset(0, 1),
			piece_position.get_position_with_offset(0, -1),
			piece_position.get_position_with_offset(-1, 1),
			piece_position.get_position_with_offset(-1, 0),
			piece_position.get_position_with_offset(-1, -1),
	};
	// Copy moves to possible  moves vector if they are empty or attacking enemy
	std::copy_if(temp_possible_moves.begin(), temp_possible_moves.end(), std::back_inserter(possible_moves),
			[&](const auto& possible_position) {
			  if (chess_board.position_in_range(possible_position)) {
				  return !chess_board.square_is_occupied(possible_position)
						  || is_attacking_enemy(possible_position, chess_board);
			  }
			  return false;
			});

}
