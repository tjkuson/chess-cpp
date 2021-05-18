// Copyright (C) 2021, Tom Kuson.
// This file is a part of Chess CLI which is released under the GPLv3.
// See LICENSE file in the project root or go to <https://www.gnu.org/licenses/> for full license details.

#include "game.h"

using namespace chess;

Game::Game()
		:current_player{ Colour::white }, next_player{ Colour::black }, chess_board(), game_active{ true },
		 white_castled{ false }, black_castled{ false }, can_castle_king_side{ false },
		 can_castle_queen_side{ false }
{
	// Initialise pieces on chess board
	Position piece_pos;
	std::shared_ptr<Piece> piece_ptr;
	// White and black pawns
	for (int col{ 0 }; col<8; col++) {
		piece_pos = Position{ std::pair<int, int>{ 6, col }};
		piece_ptr = std::make_shared<Pawn>(Colour::white, piece_pos);
		chess_board.place_piece(piece_pos, piece_ptr);
		piece_pos = Position{ std::pair<int, int>{ 1, col }};
		piece_ptr = std::make_shared<Pawn>(Colour::black, piece_pos);
		chess_board.place_piece(piece_pos, piece_ptr);
	}
	// Black and white rooks, knights, and bishops
	for (int row{ 0 }; row<8; row += 7) {
		Colour piece_colour;
		piece_colour = (row==0) ? Colour::black : Colour::white;
		piece_pos = Position{ std::pair<int, int>{ row, 0 }};
		piece_ptr = std::make_shared<Rook>(piece_colour, piece_pos);
		chess_board.place_piece(piece_pos, piece_ptr);
		piece_pos = Position{ std::pair<int, int>{ row, 7 }};
		piece_ptr = std::make_shared<Rook>(piece_colour, piece_pos);
		chess_board.place_piece(piece_pos, piece_ptr);
		piece_pos = Position{ std::pair<int, int>{ row, 1 }};
		piece_ptr = std::make_shared<Knight>(piece_colour, piece_pos);
		chess_board.place_piece(piece_pos, piece_ptr);
		piece_pos = Position{ std::pair<int, int>{ row, 6 }};
		piece_ptr = std::make_shared<Knight>(piece_colour, piece_pos);
		chess_board.place_piece(piece_pos, piece_ptr);
		piece_pos = Position{ std::pair<int, int>{ row, 2 }};
		piece_ptr = std::make_shared<Bishop>(piece_colour, piece_pos);
		chess_board.place_piece(piece_pos, piece_ptr);
		piece_pos = Position{ std::pair<int, int>{ row, 5 }};
		piece_ptr = std::make_shared<Bishop>(piece_colour, piece_pos);
		chess_board.place_piece(piece_pos, piece_ptr);
	}
	// White and black king and queen
	for (int row{ 0 }; row<8; row += 7) {
		Colour piece_colour{ row==0 ? Colour::black : Colour::white };
		piece_pos = Position{ std::pair<int, int>{ row, 4 }};
		piece_ptr = std::make_shared<King>(piece_colour, piece_pos);
		chess_board.place_piece(piece_pos, piece_ptr);
		piece_pos = Position{ std::pair<int, int>{ row, 3 }};
		piece_ptr = std::make_shared<Queen>(piece_colour, piece_pos);
		chess_board.place_piece(piece_pos, piece_ptr);
	}
	std::cout << "Game start!\n";
	std::cout << "White pieces look like " << "♙" << " and Black pieces look like " << "♟.\n";
}

// Destructor
Game::~Game() = default;

// Print graphical display of game board
void Game::print_chess_board() const
{
	std::ostringstream os;
	os << std::endl << "  a b c d e f g h  \n";
	for (int row{ 0 }; row<8; row++) {
		os << 8-row << " ";
		for (int col{ 0 }; col<8; col++) {
			std::string icon{ "·", std::allocator<char>() };
			const Position position_visiting{ std::pair<int, int>{ row, col }};
			if (chess_board.occupied(position_visiting)) {
				const std::shared_ptr<Piece> piece_ptr{ chess_board.get_piece(position_visiting) };
				icon = piece_ptr->get_icon();
			}
			os << icon << " ";
		}
		os << " " << 8-row << std::endl;
	}
	os << "  a b c d e f g h   \n";
	std::cout << os.str();
	os.str("", std::allocator<char>()); // Clear string stream
}

// Move piece pointers around
void Game::move_piece(const Position& init_pos, const Position& final_pos)
{
	if (!chess_board.occupied(init_pos)) {
		std::cerr << "Initial position not occupied by piece\n";
		throw std::invalid_argument("Initial position not occupied by piece");
	}
	chess_board.place_piece(final_pos, chess_board.get_piece(init_pos));
	chess_board.place_piece(init_pos, nullptr); // Empty vacated position
}

// Input move and deal with move logic
void Game::handle_move()
{
	Position init_pos;
	Position final_pos;
	bool asking_for_move{ true };
	while (asking_for_move) {
		try {
			// Take input from player
			std::string move;
			std::cout << "Input move in the form aXbY, input 'quit' to exit the game: ";
			std::cin >> move;
			// Check for exit
			if (move=="quit") {
				game_active = false;
				return;
			}
			if (move.length()!=4) {
				throw std::invalid_argument("More than four char given");
			}
			const std::pair<std::string, std::string> init_pair{ move.substr(0, 1), move.substr(1, 1) };
			const std::pair<std::string, std::string> final_pair{ move.substr(2, 1), move.substr(3, 1) };
			init_pos = Position{ init_pair }; // Will throw exception on invalid input
			if (chess_board.get_piece(init_pos)==nullptr) {
				throw std::invalid_argument("Cannot move from empty square");
			}
			final_pos = Position{ final_pair }; // Will throw exception on invalid input
			// Check if the move is a valid one
			const bool move_valid{ chess_board.get_piece(init_pos)->legal_move(final_pos) };
			const bool owns_piece{ chess_board.get_piece(init_pos)->get_colour()==current_player };
			// Player could have just castled if they moved a king, if they did we have to move things around more carefully
			// Check if the player can castle, and if they just picked up their own king
			if (owns_piece && (can_castle_king_side || can_castle_queen_side)
					&& chess_board.find_king(current_player)==init_pos) {
				const int row{ current_player==Colour::white ? 7 : 0 };
				const auto disable_castling = [&]() {
				  if (current_player==Colour::white) {
					  white_castled = true;
				  }
				  else {
					  black_castled = true;
				  }
				};
				if (can_castle_king_side && final_pos==Position{ std::pair<int, int>{ row, 6 }}) {
					// Player just king-side castled
					std::cout << current_player << " King King-side castles.\n";
					move_piece(init_pos, final_pos);
					// Move the rook to correct position
					const Position rook_init_pos{ std::pair<int, int>{ row, 7 }};
					const Position rook_final_pos{ std::pair<int, int>{ row, 5 }};
					move_piece(rook_init_pos, rook_final_pos);
					// Make sure the player can't castle again
					disable_castling();
					return;
				}
				else if (can_castle_king_side && final_pos==Position{ std::pair<int, int>{ row, 2 }}) {
					// Player just queen side castled
					std::cout << current_player << " King Queen-side castles.\n";
					move_piece(init_pos, final_pos);
					const Position rook_init_pos{ std::pair<int, int>{ row, 0 }};
					const Position rook_final_pos{ std::pair<int, int>{ row, 3 }};
					move_piece(rook_init_pos, rook_final_pos);
					// Make sure the player can't castle again
					disable_castling();
					return;
				}
			}
			// Stop loop if the move input by the user is valid
			asking_for_move = !(move_valid && owns_piece);
			if (asking_for_move) {
				std::cerr << "Invalid move, try again.\n";
			}
		}
		catch (std::invalid_argument& exception) {
			std::cerr << "Invalid input, try again.\n";
			std::cin.clear();
			std::cin.ignore();
		}
		catch (std::out_of_range& exception) {
			std::cerr << "Invalid input, try again.\n";
			std::cin.clear();
			std::cin.ignore();
		}
	}
	// They didn't castle, move as normal
	move_piece(init_pos, final_pos);
}

// Check if the enemy can capture position
auto Game::enemy_can_capture(const Position& test_pos) const -> bool
{
	for (int row{ 0 }; row<8; row++) {
		for (int col{ 0 }; col<8; col++) {
			const Position visiting_pos{ std::pair<int, int>{ row, col }};
			if (chess_board.occupied(visiting_pos)) {
				// Generate the legal moves for the piece being visited
				const std::shared_ptr<Piece> piece_ptr{ chess_board.get_piece(visiting_pos) };
				piece_ptr->load_possible_moves(chess_board);
				if (piece_ptr->possible_move(test_pos) && piece_ptr->get_colour()!=current_player) {
					return true;
				}
			}
		}
	}
	return false;
}

// Generate the moves of all the pieces on the board
void Game::generate_moves() const
{
	for (int row{ 0 }; row<8; row++) {
		for (int col{ 0 }; col<8; col++) {
			const Position visiting_pos{ std::pair<int, int>{ row, col }};
			if (chess_board.occupied(visiting_pos)) {
				// Generate the legal moves for the piece being visited
				const std::shared_ptr<Piece> piece_ptr{ chess_board.get_piece(visiting_pos) };
				piece_ptr->load_possible_moves(chess_board);
				piece_ptr->load_legal_moves(chess_board);
			}
		}
	}
}

// Count the number of legal moves the current player can make
auto Game::num_of_legal_moves() const -> int
{
	int count{ 0 };
	for (int row{ 0 }; row<8; row++) {
		for (int col{ 0 }; col<8; col++) {
			const Position visiting_pos{ std::pair<int, int>{ row, col }};
			if (chess_board.occupied(visiting_pos)) {
				const std::shared_ptr<Piece> piece_pos{ chess_board.get_piece(visiting_pos) };
				if (piece_pos->get_colour()==current_player) {
					count += piece_pos->get_num_of_legal_moves();
				}
			}
		}
	}
	return count;
}

auto Game::can_castle(const Position& king_pos) const -> std::pair<bool, bool>
{
	const bool has_castling_rights{ current_player==Colour::white ? !white_castled : !black_castled };
	const bool in_position{ (king_pos==Position(std::pair<int, int>{ 0, 4 })
			|| king_pos==Position(std::pair<int, int>{ 7, 4 })) };
	const std::string castle_icon{ current_player==Colour::white ? "♖" : "♜", std::allocator<char>() };
	bool can_king_side_castle{ false };
	bool can_queen_side_castle{ false };
	if (has_castling_rights && in_position) {
		// Check king-side
		bool searching{ true };
		int offset{ 0 };
		while (searching) {
			++offset;
			const Position visiting_pos{ king_pos.get_offset(0, offset) };
			if (chess_board.in_range(visiting_pos)) {
				if (!chess_board.occupied(visiting_pos)) {
					if (!enemy_can_capture(visiting_pos)) {
						// If safe and empty, keep searching
						continue;
					}
					else {
						searching = false;
					}
				}
				else if (chess_board.get_piece(visiting_pos)->get_icon()==castle_icon
						&& visiting_pos.get_position().second==7) {
					// If not empty, it could be our rook. If so, our path is clear!
					can_king_side_castle = true;
				}
				else {
					searching = false;
				}
			}
			else {
				searching = false;
			}
		}
		// Check queen-sde
		searching = true;
		offset = 0;
		while (searching) {
			--offset;
			const Position visiting_pos{ king_pos.get_offset(0, offset) };
			if (chess_board.in_range(visiting_pos)) {
				if (!chess_board.occupied(visiting_pos)) {
					if (!enemy_can_capture(visiting_pos)) {
						// If safe and empty, keep searching
						continue;
					}
					else {
						searching = false;
					}
				}
				else if (chess_board.get_piece(visiting_pos)->get_icon()==castle_icon
						&& visiting_pos.get_position().second==0) {
					// If not empty, it could be our rook. If so, our path is clear!
					can_queen_side_castle = true;
				}
				else {
					searching = false;
				}
			}
			else {
				searching = false;
			}
		}
	}
	return std::pair<bool, bool>{ can_king_side_castle, can_queen_side_castle };
}

void Game::check_for_pawn_promotion()
{
	// Check if there is a pawn that can be promoted
	bool can_promote_pawn{ false };
	Position promotable_pawn_pos;
	for (int row{ 0 }; row<8 && !can_promote_pawn; row += 7) {
		for (int col{ 0 }; col<8 && !can_promote_pawn; ++col) {
			const Position visiting_pos{ std::pair<int, int>{ row, col }};
			if (chess_board.occupied(visiting_pos)) {
				const std::string piece_icon{ chess_board.get_piece(visiting_pos)->get_icon() };
				if (piece_icon=="♙" || piece_icon=="♟") {
					can_promote_pawn = true; // Stops the loop, no more than one pawn can be promoted
					promotable_pawn_pos = visiting_pos;
				}
			}
		}
	}
	if (can_promote_pawn) {
		std::cout << "Can promote pawn!\n";
		bool asking_for_piece{ true };
		while (asking_for_piece) {
			try {
				std::string promotion;
				std::cout
						<< "Input the piece you'd like to promote your pawn to; 'q' for Queen; 'r' for Rook; 'k' for Knight; and 'b' for Bishop: ";
				std::cin >> promotion;
				std::shared_ptr<Piece> promoted_piece_ptr;
				if (promotion.length()!=1) {
					throw std::invalid_argument("More than one char given");
				}
				Colour init_colour{ current_player };
				if (promotion=="q") {
					promoted_piece_ptr = std::make_shared<Queen>(init_colour, promotable_pawn_pos);
				}
				else if (promotion=="r") {
					promoted_piece_ptr = std::make_shared<Rook>(init_colour, promotable_pawn_pos);
				}
				else if (promotion=="k") {
					promoted_piece_ptr = std::make_shared<Knight>(init_colour, promotable_pawn_pos);
				}
				else if (promotion=="b") {
					promoted_piece_ptr = std::make_shared<Bishop>(init_colour, promotable_pawn_pos);
				}
				else {
					throw std::invalid_argument("Not a piece");
				}
				chess_board.place_piece(promotable_pawn_pos, promoted_piece_ptr);
				asking_for_piece = false;
			}
			catch (std::invalid_argument& exception) {
				std::cerr << "Invalid input, try again.\n";
				std::cin.clear();
				std::cin.ignore();
			}
		}
	}
}

// Trigger the core gameplay loop
void Game::loop()
{
	while (game_active) {
		// Display chess board and game information
		print_chess_board();
		std::cout << current_player << "'s turn to play.\n";
		// Find the location of the current player's king
		Position king_pos{ chess_board.find_king(current_player) };
		// See if the player's king is under attack and count number of legal moves to determine checkmate
		generate_moves();
		const bool in_check{ enemy_can_capture(king_pos) };
		const int number_of_moves{ num_of_legal_moves() };
		// Check for castling
		std::tie(can_castle_king_side, can_castle_queen_side) = can_castle(king_pos);
		if (can_castle_king_side) {
			std::cout << "King-side castle possible!\n";
		}
		if (can_castle_queen_side) {
			std::cout << "Queen-side castle possible!\n";
		}
		if (number_of_moves==0) {
			std::cout << "Checkmate! " << next_player << " wins.\n";
			game_active = false;
		}
		else {
			if (in_check) {
				std::cout << "Check! " << next_player << " is attacking " << current_player << "'s king.\n";
			}
			// Moves exist! Ask for player input.
			handle_move();
			// Promote pawns, if possible
			check_for_pawn_promotion();
			// Next player
			++current_player;
			++next_player;
		}
	}
	std::cout << "Game over.\n";
}
