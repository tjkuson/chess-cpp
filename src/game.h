// Copyright (C) 2021, Tom Kuson.
// This file is a part of Chess CLI which is released under the GPLv3.
// See LICENSE file in the project root or go to <https://www.gnu.org/licenses/> for full license details.

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
		bool game_active{ true };
		bool white_castled{ false };
		bool black_castled{ false };
		bool can_castle_king_side{ false };
		bool can_castle_queen_side{ false };
	public:
		// Prototype constructor and destructor
		game();
		~game();
		// Prototype functions
		void print_chess_board() const;
		void move_piece(const position& init_pos, const position& final_pos);
		void handle_move();
		[[nodiscard]] bool enemy_can_capture(const position& test_pos) const;
		void generate_moves() const;
		[[nodiscard]] int num_of_legal_moves() const;
		[[nodiscard]] std::pair<bool, bool> can_castle(const position& king_pos) const;
		void check_for_pawn_promotion();
		void loop();
	};
}

#endif //GAME_H
