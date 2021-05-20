// Copyright (C) 2021, Tom Kuson.
// This file is a part of Chess CLI which is released under the GPLv3.
// See LICENSE file in the project root or go to <https://www.gnu.org/licenses/> for full license details.

// board.h

#ifndef CHESS_CLI_BOARD_H
#define CHESS_CLI_BOARD_H

#include "main.h"
#include "position.h"
#include "piece.h"
#include "colour.h"

namespace chess {
	// Forward declare piece class to resolve circular dependency \
    This allows the board class to store piece class pointers before piece class has been defined
	class Piece;

	class Board {
	private:
		const std::pair<int, int> dimensions; // row, col
		std::vector<std::shared_ptr<Piece>> squares;
	public:
		// Prototype constructor and destructor
		Board(int rows, int cols);
		~Board();
		// Prototype functions
		[[nodiscard]] bool in_range(const Position& pos) const;
		[[nodiscard]] bool occupied(const Position& pos) const;
		void place_piece(const Position& pos, const std::shared_ptr<Piece>& piece_ptr);
		void place_piece_no_update(const Position& pos, const std::shared_ptr<Piece>& piece_ptr);
		[[nodiscard]] std::shared_ptr<Piece> get_piece(const Position& pos) const;
		[[nodiscard]] Position find_king(const Colour& king_colour) const;
	};
}

#endif //CHESS_CLI_BOARD_H
