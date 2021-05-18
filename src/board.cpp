// Copyright (C) 2021, Tom Kuson.
// This file is a part of Chess CLI which is released under the GPLv3.
// See LICENSE file in the project root or go to <https://www.gnu.org/licenses/> for full license details.

// board.cpp

#include "board.h"

using namespace chess;

// Board constructor
Board::Board()
		:dimensions{ 8, 8 }
{
	// Initialise vector of piece pointers
	// We push back this vector to the squares vector such that squares[std::vector squares_row]
	// Hence squares_row must be size must be the number of columns such that squares[row][col]
	std::vector<std::shared_ptr<Piece>> squares_row;
	squares_row.resize(dimensions.second);
	// Push back squares row n times, where squares[n][cols] i.e. n = rows
	for (int i{ 0 }; i<dimensions.first; i++) {
		squares.push_back(squares_row);
	}
}

// Board destructor
Board::~Board()
{
	squares.clear();
}

// Check position is in range on board
auto Board::in_range(const Position& pos) const -> bool
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
auto Board::occupied(const Position& pos) const -> bool
{
	int row;
	int col;
	std::tie(row, col) = pos.get_position();
	return squares[row][col]!=nullptr;
}

// Store pointer to new piece in squares vector
void Board::place_piece(const Position& pos, const std::shared_ptr<Piece>& piece_ptr)
{
	place_piece_no_update(pos, piece_ptr);
	// Tell the piece to update its position variable
	if (piece_ptr!=nullptr) {
		piece_ptr->set_position(pos);
	}
}

// Store pointer to new piece in squares vector
// This is used when we don't want the piece to change its location e.g. testing possible moves for checks
void Board::place_piece_no_update(const Position& pos, const std::shared_ptr<Piece>& piece_ptr)
{
	int row;
	int col;
	std::tie(row, col) = pos.get_position();
	squares[row][col] = piece_ptr;
}

// Return pointer corresponding to position
auto Board::get_piece(const Position& pos) const -> std::shared_ptr<Piece>
{
	int row;
	int col;
	std::tie(row, col) = pos.get_position();
	return squares[row][col];
}

// Return position of king
auto Board::find_king(const Colour& king_colour) const -> Position
{
	const std::string king_icon{ king_colour==Colour::white ? "♔" : "♚", std::allocator<char>() };
	for (int row{ 0 }; row<dimensions.first; row++) {
		for (int col{ 0 }; col<dimensions.second; col++) {
			const Position visiting_pos{ std::pair<int, int>{ row, col }};
			if (occupied(visiting_pos)) {
				const std::shared_ptr<Piece> piece_ptr{ get_piece(visiting_pos) };
				if (piece_ptr->get_icon()==king_icon) {
					return visiting_pos;
				}
			}
		}
	}
	throw std::out_of_range("King not found");
}
