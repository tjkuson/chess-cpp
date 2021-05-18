// Copyright (C) 2021, Tom Kuson.
// This file is a part of Chess CLI which is released under the GPLv3.
// See LICENSE file in the project root or go to <https://www.gnu.org/licenses/> for full license details.

// piece.h

#ifndef PIECE_H
#define PIECE_H

#include <algorithm>
#include <memory>
#include "board.h"
#include "colour.h"

namespace chess {

	// Forward declare to reference board class
	class board;

	class piece {
	protected:
		const colour piece_colour;
		position piece_pos;
		std::string piece_icon;
		std::vector<position> possible_moves;
		std::vector<position> legal_moves; // Moves that don't put own king in check
	public:
		// Prototype constructor and destructor
		piece(const colour init_colour, const position& init_pos);
		virtual ~piece();
		// Prototype functions
		[[nodiscard]] std::string get_icon() const;
		[[nodiscard]] colour get_colour() const;
		[[nodiscard]] int get_num_of_legal_moves() const;
		void set_position(const position& new_pos);
		[[nodiscard]] bool possible_move(const position& move) const;
		[[nodiscard]] bool attacking_enemy(const position& visiting_pos, const board& game_board) const;
		// Take chess board by value as the function will manipulate piece positions
		[[nodiscard]] bool legal_move(const position& init_pos, const position& final_pos,
				board chess_board) const;
		void load_legal_moves(const board& chess_board);
		[[nodiscard]] bool legal_move(const position& move) const;
		// Prototype virtual functions to be overridden by derived classes
		virtual void load_possible_moves(const board& chess_board) = 0;
	};
}

#endif //PIECE_H
