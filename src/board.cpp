// Copyright (C) 2021, Tom Kuson.
// This file is a part of Chess CLI which is released under the GPLv3.
// See LICENSE file in the project root or go to <https://www.gnu.org/licenses/> for full license details.

// board.cpp

#include <iostream>
#include "board.h"

using namespace chess;

// Parameterised constructor
Board::Board(int rows, int cols)
		:dimensions{ rows, cols }
{
	squares.resize(rows*cols);
	std::cout << "Rows: " << rows << " Cols: " << cols << "\n";
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
	std::tie(row, col) = pos.get_position();
	return row<dimensions.first && col<dimensions.second && row>=0 && col>=0;
}

// Check position is occupied by piece on board
auto Board::occupied(const Position& pos) const -> bool
{
	int index{ pos.get_index(dimensions) };
	return squares[index]!=nullptr;
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
	int index{ pos.get_index(dimensions) };
	squares[index] = piece_ptr;
}

// Return pointer corresponding to position
auto Board::get_piece(const Position& pos) const -> std::shared_ptr<Piece>
{
	int index{ pos.get_index(dimensions) };
	return squares[index];
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
