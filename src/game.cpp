

#include "game.h"

using namespace chess;

game::game()
		:current_player{ colour::white }, next_player{ colour::black }, chess_board(), game_is_active{ true },
		 white_has_castled{ false }, black_has_castled{ false }, valid_king_side_castle_possible{ false },
		 valid_queen_side_castle_possible{ false }
{
	// Initialise pieces on chess board
	position piece_position;
	std::shared_ptr<piece> piece_pointer;
	// White and black pawns
	for (int col{ 0 }; col<8; col++) {
		piece_position = position{ std::pair<int, int>{ 6, col }};
		piece_pointer = std::make_shared<pawn>(colour::white, piece_position);
		chess_board.place_piece(piece_position, piece_pointer);
		piece_position = position{ std::pair<int, int>{ 1, col }};
		piece_pointer = std::make_shared<pawn>(colour::black, piece_position);
		chess_board.place_piece(piece_position, piece_pointer);
	}
	// Black and white rooks, knights, and bishops
	for (int row{ 0 }; row<8; row += 7) {
		colour piece_colour;
		piece_colour = (row==0) ? colour::black : colour::white;
		piece_position = position{ std::pair<int, int>{ row, 0 }};
		piece_pointer = std::make_shared<rook>(piece_colour, piece_position);
		chess_board.place_piece(piece_position, piece_pointer);
		piece_position = position{ std::pair<int, int>{ row, 7 }};
		piece_pointer = std::make_shared<rook>(piece_colour, piece_position);
		chess_board.place_piece(piece_position, piece_pointer);
		piece_position = position{ std::pair<int, int>{ row, 1 }};
		piece_pointer = std::make_shared<knight>(piece_colour, piece_position);
		chess_board.place_piece(piece_position, piece_pointer);
		piece_position = position{ std::pair<int, int>{ row, 6 }};
		piece_pointer = std::make_shared<knight>(piece_colour, piece_position);
		chess_board.place_piece(piece_position, piece_pointer);
		piece_position = position{ std::pair<int, int>{ row, 2 }};
		piece_pointer = std::make_shared<bishop>(piece_colour, piece_position);
		chess_board.place_piece(piece_position, piece_pointer);
		piece_position = position{ std::pair<int, int>{ row, 5 }};
		piece_pointer = std::make_shared<bishop>(piece_colour, piece_position);
		chess_board.place_piece(piece_position, piece_pointer);
	}
	// White and black king and queen
	for (int row{ 0 }; row<8; row += 7) {
		colour piece_colour{ row==0 ? colour::black : colour::white };
		piece_position = position{ std::pair<int, int>{ row, 4 }};
		piece_pointer = std::make_shared<king>(piece_colour, piece_position);
		chess_board.place_piece(piece_position, piece_pointer);
		piece_position = position{ std::pair<int, int>{ row, 3 }};
		piece_pointer = std::make_shared<queen>(piece_colour, piece_position);
		chess_board.place_piece(piece_position, piece_pointer);
	}
	std::cout << "Game start!" << std::endl;
	std::cout << "White pieces look like " << "♙" << " and Black pieces look like " << "♟." << std::endl;
}

// Destructor
game::~game() = default;

// Print graphical display of game board
void game::print_chess_board() const
{
	std::ostringstream output_stream;
	output_stream << std::endl << "  a b c d e f g h  " << std::endl;
	for (int row{ 0 }; row<8; row++) {
		output_stream << 8-row << " ";
		for (int col{ 0 }; col<8; col++) {
			std::string icon{ "·" };
			const position position_visiting{ std::pair<int, int>{ row, col }};
			if (chess_board.square_is_occupied(position_visiting)) {
				const std::shared_ptr<piece> piece_pointer{ chess_board.get_piece(position_visiting) };
				icon = piece_pointer->get_icon();
			}
			output_stream << icon << " ";
		}
		output_stream << " " << 8-row << std::endl;
	}
	output_stream << "  a b c d e f g h   " << std::endl;
	std::cout << output_stream.str();
	output_stream.str(""); // Clear string stream
}

// Move piece pointers around
void game::move_piece(const position& init_position, const position& final_position)
{
	if (!chess_board.square_is_occupied(init_position)) {
		std::cerr << "Initial position not occupied by piece" << std::endl;
		throw std::invalid_argument("Initial position not occupied by piece");
	}
	chess_board.place_piece(final_position, chess_board.get_piece(init_position));
	chess_board.place_piece(init_position, nullptr); // Empty vacated position
}

// Input move and deal with move logic
void game::handle_move()
{
	position initial_position;
	position final_position;
	bool asking_for_valid_move{ true };
	while (asking_for_valid_move) {
		try {
			// Take input from player
			std::string move;
			std::cout << "Input move in the form aXbY, input 'quit' to exit the game: ";
			std::cin >> move;
			// Check for exit
			if (move=="quit") {
				game_is_active = false;
				return;
			}
			if (move.length()!=4) {
				throw std::invalid_argument("More than four char given");
			}
			const std::pair<std::string, std::string> initial_pair{ move.substr(0, 1), move.substr(1, 1) };
			const std::pair<std::string, std::string> final_pair{ move.substr(2, 1), move.substr(3, 1) };
			initial_position = position{ initial_pair }; // Will throw exception on invalid input
			if (chess_board.get_piece(initial_position)==nullptr) {
				throw std::invalid_argument("Cannot move from empty square");
			}
			final_position = position{ final_pair }; // Will throw exception on invalid input
			// Check if the move is a valid one
			const bool valid_move_found{ chess_board.get_piece(initial_position)->is_legal_move(final_position) };
			const bool piece_belongs_to_player{ chess_board.get_piece(initial_position)->get_colour()==current_player };
			// Player could have just castled if they moved a king, if they did we have to move things around more carefully
			// Check if the player can castle, and if they just picked up their own king
			if (piece_belongs_to_player && (valid_king_side_castle_possible || valid_queen_side_castle_possible)
					&& chess_board.find_king_position(current_player)==initial_position) {
				const int row{ current_player==colour::white ? 7 : 0 };
				const auto disable_castling = [&]() {
				  if (current_player==colour::white) {
					  white_has_castled = true;
				  }
				  else {
					  black_has_castled = true;
				  }
				};
				if (valid_king_side_castle_possible && final_position==position{ std::pair<int, int>{ row, 6 }}) {
					// Player just king-side castled
					std::cout << current_player << " King King-side castles." << std::endl;
					move_piece(initial_position, final_position);
					// Move the rook to correct position
					const position rook_initial_position{ std::pair<int, int>{ row, 7 }};
					const position rook_final_position{ std::pair<int, int>{ row, 5 }};
					move_piece(rook_initial_position, rook_final_position);
					// Make sure the player can't castle again
					disable_castling();
					return;
				}
				else if (valid_king_side_castle_possible && final_position==position{ std::pair<int, int>{ row, 2 }}) {
					// Player just queen side castled
					std::cout << current_player << " King Queen-side castles." << std::endl;
					move_piece(initial_position, final_position);
					const position rook_initial_position{ std::pair<int, int>{ row, 0 }};
					const position rook_final_position{ std::pair<int, int>{ row, 3 }};
					move_piece(rook_initial_position, rook_final_position);
					// Make sure the player can't castle again
					disable_castling();
					return;
				}
			}
			// Stop loop if the move input by the user is valid
			asking_for_valid_move = !(valid_move_found && piece_belongs_to_player);
			if (asking_for_valid_move) {
				std::cerr << "Invalid move, try again." << std::endl;
			}
		}
		catch (std::invalid_argument& exception) {
			std::cerr << "Invalid input, try again." << std::endl;
			std::cin.clear();
			std::cin.ignore();
		}
		catch (std::out_of_range& exception) {
			std::cerr << "Invalid input, try again." << std::endl;
			std::cin.clear();
			std::cin.ignore();
		}
	}
	// They didn't castle, move as normal
	move_piece(initial_position, final_position);
}

// Check if the enemy can capture position
bool game::enemy_can_capture_position(const position& trial_position) const
{
	for (int row{ 0 }; row<8; row++) {
		for (int col{ 0 }; col<8; col++) {
			const position position_visiting{ std::pair<int, int>{ row, col }};
			if (chess_board.square_is_occupied(position_visiting)) {
				// Generate the legal moves for the piece being visited
				const std::shared_ptr<piece> piece_pointer{ chess_board.get_piece(position_visiting) };
				piece_pointer->load_possible_moves(chess_board);
				if (piece_pointer->is_possible_move(trial_position) && piece_pointer->get_colour()!=current_player) {
					return true;
				}
			}
		}
	}
	return false;
}

// Generate the moves of all the pieces on the board
void game::generate_moves() const
{
	for (int row{ 0 }; row<8; row++) {
		for (int col{ 0 }; col<8; col++) {
			const position position_visiting{ std::pair<int, int>{ row, col }};
			if (chess_board.square_is_occupied(position_visiting)) {
				// Generate the legal moves for the piece being visited
				const std::shared_ptr<piece> piece_pointer{ chess_board.get_piece(position_visiting) };
				piece_pointer->load_possible_moves(chess_board);
				piece_pointer->load_legal_moves(chess_board);
			}
		}
	}
}

// Count the number of legal moves the current player can make
int game::number_of_legal_moves() const
{
	int count{ 0 };
	for (int row{ 0 }; row<8; row++) {
		for (int col{ 0 }; col<8; col++) {
			const position position_visiting{ std::pair<int, int>{ row, col }};
			if (chess_board.square_is_occupied(position_visiting)) {
				const std::shared_ptr<piece> piece_pointer{ chess_board.get_piece(position_visiting) };
				if (piece_pointer->get_colour()==current_player) {
					count += piece_pointer->get_number_of_legal_moves();
				}
			}
		}
	}
	return count;
}

std::pair<bool, bool> game::can_validly_castle(const position& king_position) const
{
	const bool has_castling_rights{ current_player==colour::white ? !white_has_castled : !black_has_castled };
	const bool in_position{ (king_position==position(std::pair<int, int>{ 0, 4 })
			|| king_position==position(std::pair<int, int>{ 7, 4 })) };
	const std::string castle_icon{ current_player==colour::white ? "♖" : "♜" };
	bool can_king_side_castle{ false };
	bool can_queen_side_castle{ false };
	if (has_castling_rights && in_position) {
		// Check king-side
		bool searching{ true };
		int offset{ 0 };
		while (searching) {
			++offset;
			const position visiting{ king_position.get_position_with_offset(0, offset) };
			if (chess_board.position_in_range(visiting)) {
				if (!chess_board.square_is_occupied(visiting)) {
					if (!enemy_can_capture_position(visiting)) {
						// If safe and empty, keep searching
						continue;
					}
					else {
						searching = false;
					}
				}
				else if (chess_board.get_piece(visiting)->get_icon()==castle_icon
						&& visiting.get_position().second==7) {
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
			const position visiting{ king_position.get_position_with_offset(0, offset) };
			if (chess_board.position_in_range(visiting)) {
				if (!chess_board.square_is_occupied(visiting)) {
					if (!enemy_can_capture_position(visiting)) {
						// If safe and empty, keep searching
						continue;
					}
					else {
						searching = false;
					}
				}
				else if (chess_board.get_piece(visiting)->get_icon()==castle_icon
						&& visiting.get_position().second==0) {
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

void game::check_for_pawn_promotion()
{
	// Check if there is a pawn that can be promoted
	bool can_promote_pawn{ false };
	position promotable_pawn_position;
	for (int row{ 0 }; row<8 && !can_promote_pawn; row += 7) {
		for (int col{ 0 }; col<8 && !can_promote_pawn; ++col) {
			const position position_visiting{ std::pair<int, int>{ row, col }};
			if (chess_board.square_is_occupied(position_visiting)) {
				const std::string piece_icon{ chess_board.get_piece(position_visiting)->get_icon() };
				if (piece_icon=="♙" || piece_icon=="♟") {
					can_promote_pawn = true; // Stops the loop, no more than one pawn can be promoted
					promotable_pawn_position = position_visiting;
				}
			}
		}
	}
	if (can_promote_pawn) {
		std::cout << "Can promote pawn!" << std::endl;
		bool asking_for_piece{ true };
		while (asking_for_piece) {
			try {
				std::string promotion;
				std::cout
						<< "Input the piece you'd like to promote your pawn to; 'q' for Queen; 'r' for Rook; 'k' for Knight; and 'b' for Bishop: ";
				std::cin >> promotion;
				std::shared_ptr<piece> new_piece;
				if (promotion.length()!=1) {
					throw std::invalid_argument("More than one char given");
				}
				colour init_colour{ current_player };
				if (promotion=="q") {
					new_piece = std::make_shared<queen>(init_colour, promotable_pawn_position);
				}
				else if (promotion=="r") {
					new_piece = std::make_shared<rook>(init_colour, promotable_pawn_position);
				}
				else if (promotion=="k") {
					new_piece = std::make_shared<knight>(init_colour, promotable_pawn_position);
				}
				else if (promotion=="b") {
					new_piece = std::make_shared<bishop>(init_colour, promotable_pawn_position);
				}
				else {
					throw std::invalid_argument("Not a piece");
				}
				chess_board.place_piece(promotable_pawn_position, new_piece);
				asking_for_piece = false;
			}
			catch (std::invalid_argument& exception) {
				std::cerr << "Invalid input, try again." << std::endl;
				std::cin.clear();
				std::cin.ignore();
			}
		}
	}
}

// Trigger the core gameplay loop
void game::loop()
{
	while (game_is_active) {
		// Display chess board and game information
		print_chess_board();
		std::cout << current_player << "'s turn to play." << std::endl;
		// Find the location of the current player's king
		position king_position{ chess_board.find_king_position(current_player) };
		// See if the player's king is under attack and count number of legal moves to determine checkmate
		generate_moves();
		const bool in_check{ enemy_can_capture_position(king_position) };
		const int number_of_moves{ number_of_legal_moves() };
		// Check for castling
		std::tie(valid_king_side_castle_possible, valid_queen_side_castle_possible) = can_validly_castle(king_position);
		if (valid_king_side_castle_possible) {
			std::cout << "King-side castle possible!" << std::endl;
		}
		if (valid_queen_side_castle_possible) {
			std::cout << "Queen-side castle possible!" << std::endl;
		}
		if (number_of_moves==0) {
			std::cout << "Checkmate! " << next_player << " wins." << std::endl;
			game_is_active = false;
		}
		else {
			if (in_check) {
				std::cout << "Check! " << next_player << " is attacking " << current_player << "'s king." << std::endl;
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
	std::cout << "Game over." << std::endl;
}
