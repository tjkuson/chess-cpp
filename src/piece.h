// Copyright (C) 2021, Tom Kuson.
// This file is a part of Chess CLI which is released under the GPLv3.
// See LICENSE file in the project root or go to <https://www.gnu.org/licenses/> for full license details.

// piece.h

#ifndef CHESS_CLI_PIECE_H
#define CHESS_CLI_PIECE_H

#include <algorithm>
#include <memory>
#include "board.h"
#include "colour.h"

namespace chess {

	// Forward declare to reference board class
	class Board;

	class Piece {
	protected:
		const Colour piece_colour;
		Position piece_pos;
		std::string piece_icon;
		std::vector<Position> possible_moves;
		std::vector<Position> legal_moves; // Moves that don't put own king in check
	public:
		// Prototype constructor and destructor
		Piece(const Colour init_colour, const Position& init_pos);
		virtual ~Piece();
		// Prototype functions
		[[nodiscard]] std::string get_icon() const;
		[[nodiscard]] Colour get_colour() const;
		[[nodiscard]] int get_num_of_legal_moves() const;
		void set_position(const Position& new_pos);
		[[nodiscard]] bool possible_move(const Position& move) const;
		[[nodiscard]] bool attacking_enemy(const Position& visiting_pos, const Board& game_board) const;
		// Take chess board by value as the function will manipulate piece positions
		[[nodiscard]] bool legal_move(const Position& init_pos, const Position& final_pos,
				Board chess_board) const;
		void load_legal_moves(const Board& chess_board);
		[[nodiscard]] bool legal_move(const Position& move) const;
		// Prototype virtual functions to be overridden by derived classes
		virtual void load_possible_moves(const Board& chess_board) = 0;
	};
}

#endif //CHESS_CLI_PIECE_H
