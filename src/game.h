// game.h

#ifndef GAME_H
#define GAME_H

#include <iostream>

#include "board.h"
#include "position.h"
#include "colour.h"
#include "pawn.h"
#include "king.h"
#include "queen.h"
#include "rook.h"
#include "bishop.h"
#include "knight.h"

namespace chess {
	class game {
	private:
		board chess_board;
		colour current_player{ colour::white };
		colour next_player{ colour::black };
		bool game_is_active{ true };
		bool white_has_castled{ false };
		bool black_has_castled{ false };
		bool valid_king_side_castle_possible{ false };
		bool valid_queen_side_castle_possible{ false };
	public:
		// Prototype constructor and destructor
		game();
		~game();
		// Prototype functions
		void print_chess_board() const;
		void move_piece(const position& init_position, const position& final_position);
		void handle_move();
		[[nodiscard]] bool enemy_can_capture_position(const position& trial_position) const;
		void generate_moves() const;
		[[nodiscard]] int number_of_legal_moves() const;
		[[nodiscard]] std::pair<bool, bool> can_validly_castle(const position& king_position) const;
		void check_for_pawn_promotion();
		void loop();
	};
}

#endif //GAME_H
