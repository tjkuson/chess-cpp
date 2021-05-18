// piece.cpp

#include "piece.h"

using namespace chess;

// Parameterised constructor
piece::piece(const colour init_colour, const position& init_pos)
		:piece_colour{ init_colour }, piece_pos{ init_pos } { }

// Default destructor
piece::~piece()
{
	possible_moves.clear();
	legal_moves.clear();
}

std::string piece::get_icon() const
{
	return piece_icon;
}

colour piece::get_colour() const
{
	return piece_colour;
}

int piece::get_num_of_legal_moves() const
{
	// .size() method returns size_type value
	return static_cast<int>(legal_moves.size());
}

void piece::set_position(const position& new_pos)
{
	piece_pos = new_pos;
}

// Check if move is in the possible moves vector
bool piece::possible_move(const position& move) const
{
	return std::find(possible_moves.begin(), possible_moves.end(), move)!=possible_moves.end();
}

// Check is position points to enemy piece
bool piece::attacking_enemy(const position& visiting_pos, const board& game_board) const
{
	// Return false if no piece in square
	if (!game_board.occupied(visiting_pos) || !game_board.in_range(visiting_pos)) {
		return false;
	}
	// Return false if piece is of same colour
	const std::shared_ptr<piece> piece_ptr{ game_board.get_piece(visiting_pos) };
	return piece_ptr->get_colour()!=piece_colour;
}

// Return true if move does not put king in check
bool piece::legal_move(const position& init_pos, const position& final_pos,
		board chess_board) const
{
	// Create a temp chess board to see what happens should the move be permitted
	chess_board.place_piece_no_update(final_pos, chess_board.get_piece(init_pos));
	chess_board.place_piece_no_update(init_pos, nullptr); // Empty vacated position
	// Find the location of the king after the proposed move
	const position king_pos{ chess_board.find_king(piece_colour) };
	// Check if the enemy can attack the king after proposed move
	for (int row{ 0 }; row<8; row++) {
		for (int col{ 0 }; col<8; col++) {
			const position visiting_pos{ std::pair<int, int>{ row, col }};
			if (chess_board.occupied(visiting_pos)) {
				const std::shared_ptr<piece> piece_ptr{ chess_board.get_piece(visiting_pos) };
				if (piece_ptr->get_colour()!=piece_colour) {
					// We don't check for *legal* moves for the opponent as it doesn't matter if they put their king in\
                    in check if it means ours can be capture. It would also create an infinite loop.
					piece_ptr->load_possible_moves(chess_board);
					if (piece_ptr->possible_move(king_pos)) {
						return false;
					}
				}
			}
		}
	}
	return true;
}

// Filter the possible moves vector for legal moves e.g. that don't put King in check and store in legal moves vector
void piece::load_legal_moves(const board& chess_board)
{
	legal_moves.clear();
	std::copy_if(possible_moves.begin(), possible_moves.end(), std::back_inserter(legal_moves),
			[&](const auto& trial_move) {
			  return legal_move(piece_pos, trial_move, chess_board);
			}
	);
}

// Check if move is in list of legal moves
bool piece::legal_move(const position& move) const
{
	return std::find(legal_moves.begin(), legal_moves.end(), move)!=legal_moves.end();
}
