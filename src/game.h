// Copyright (C) 2021, Tom Kuson.
// This file is a part of Chess CLI which is released under the GPLv3.
// See LICENSE file in the project root or go to <https://www.gnu.org/licenses/> for full license details.

// game.h

#ifndef CHESS_CLI_GAME_H
#define CHESS_CLI_GAME_H

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
	class Game {
	private:
		Board chess_board;
		Colour current_player;
		Colour next_player;
		const int rows;
		const int cols;
		bool game_active;
		bool white_castled;
		bool black_castled;
		bool can_castle_king_side;
		bool can_castle_queen_side;
	public:
		// Prototype constructor and destructor
		Game();
		~Game();
		// Prototype functions
		void print_chess_board() const;
		void move_piece(const Position& init_pos, const Position& final_pos);
		void handle_move();
		[[nodiscard]] auto enemy_can_capture(const Position& test_pos) const -> bool;
		void generate_moves() const;
		[[nodiscard]] auto num_of_legal_moves() const -> int;
		[[nodiscard]] auto can_castle(const Position& king_pos) const -> std::pair<bool, bool>;
		void check_for_pawn_promotion();
		void loop();
	};
}  // namespace chess

#endif //CHESS_CLI_GAME_H
