// Copyright (C) 2021, Tom Kuson.
// This file is a part of Chess CLI which is released under the GPLv3.
// See LICENSE file in the project root or go to <https://www.gnu.org/licenses/> for full license details.

// board.cpp
// Created by tjk on 30/04/2021.
//

#include "board.h"

using namespace chess;

// Board constructor
board::board()
		:dimensions{ 8, 8 }
{
	// Initialise vector of piece pointers
	std::vector<std::shared_ptr<piece>> squares_row;
	squares_row.resize(8);
	for (int i{ 0 }; i<dimensions.first; i++) {
		squares.push_back(squares_row);
	}
}

// Board destructor
board::~board()
{
	squares.clear();
}

// Check position is in range on board
bool board::in_range(const position& pos) const
{
	int row;
	int col;
	int board_rows;
	int board_cols;
	std::tie(row, col) = pos.get_position();
	std::tie(board_rows, board_cols) = dimensions;
	return row<board_rows && col<board_cols && row>=0 && col>=0;
}

// Check position is occupied by piece on board
bool board::occupied(const position& pos) const
{
	int row;
	int col;
	std::tie(row, col) = pos.get_position();
	return squares[row][col]!=nullptr;
}

// Store pointer to new piece in squares vector
void board::place_piece(const position& pos, const std::shared_ptr<piece>& piece_ptr)
{
	place_piece_no_update(pos, piece_ptr);
	// Tell the piece to update it's position variable
	if (piece_ptr!=nullptr) {
		piece_ptr->set_position(pos);
	}
}

// Store pointer to new piece in squares vector
// This is used when we don't want the piece to change its location e.g. testing possible moves for checks
void board::place_piece_no_update(const position& pos, const std::shared_ptr<piece>& piece_ptr)
{
	int row;
	int col;
	std::tie(row, col) = pos.get_position();
	squares[row][col] = piece_ptr;
}

// Return pointer corresponding to position
std::shared_ptr<piece> board::get_piece(const position& pos) const
{
	int row;
	int col;
	std::tie(row, col) = pos.get_position();
	return squares[row][col];
}

// Return position of king
position board::find_king(const colour& king_colour) const
{
	const std::string king_icon{ (king_colour==colour::white) ? "♔" : "♚" };
	for (int row{ 0 }; row<8; row++) {
		for (int col{ 0 }; col<8; col++) {
			const position visiting_pos{ std::pair<int, int>{ row, col }};
			if (occupied(visiting_pos)) {
				const std::shared_ptr<piece> piece_ptr{ get_piece(visiting_pos) };
				if (piece_ptr->get_icon()==king_icon) {
					return visiting_pos;
				}
			}
		}
	}
	throw std::out_of_range("King not found");
}
