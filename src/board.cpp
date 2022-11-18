// Chess CLI: command-line chess
// Copyright (c) 2022 Tom Kuson
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.

#include "board.h"
#include <iostream>

using namespace chess;

// Parameterised constructor
Board::Board(int rows, int cols)
    : dimensions{rows, cols}
{
    // Use auto to avoid multiplication result conversions to a different (non-int) type
    auto number_of_squares = rows * cols;
    squares.resize(number_of_squares);
}

// Board destructor
Board::~Board() = default;

// Check position is in range on board
auto Board::in_range(const Position& pos) const -> bool
{
    int row{};
    int col{};
    std::tie(row, col) = pos.get_position();
    return pos.get_position().first < dimensions.first
            and pos.get_position().second < dimensions.second and row >= 0
            and col >= 0;
}

// Check position is occupied by piece on board
auto Board::occupied(const Position& pos) const -> bool
{
    int index{pos.get_index(dimensions)};
    return squares[index] != nullptr;
}

// Store pointer to new piece in squares vector
void Board::place_piece(const Position& pos, const std::shared_ptr<Piece>& piece_ptr)
{
    place_piece_no_update(pos, piece_ptr);
    // Tell the piece to update its position variable
    if (piece_ptr != nullptr) {
        piece_ptr->set_position(pos);
    }
}

// Store pointer to new piece in squares vector
// This is used when we don't want the piece to change its location e.g. testing possible moves for checks
void Board::place_piece_no_update(const Position& pos,
                                  const std::shared_ptr<Piece>& piece_ptr)
{
    int index{pos.get_index(dimensions)};
    squares[index] = piece_ptr;
}

// Return pointer corresponding to position
auto Board::get_piece(const Position& pos) const -> std::shared_ptr<Piece>
{
    int index{pos.get_index(dimensions)};
    return squares[index];
}

// Return position of king
auto Board::find_king(const Colour& king_colour) const -> Position
{
    const std::string king_icon{king_colour == Colour::white ? "♔" : "♚",
                                std::allocator<char>()};
    for (int row{0}; row < dimensions.first; row++) {
        for (int col{0}; col < dimensions.second; col++) {
            const Position visiting_pos{std::pair<int, int>{row, col}};
            if (occupied(visiting_pos)) {
                const std::shared_ptr<Piece> piece_ptr{get_piece(visiting_pos)};
                if (piece_ptr->get_icon() == king_icon) {
                    return visiting_pos;
                }
            }
        }
    }
    throw std::out_of_range("King not found");
}

// Check if pawn can be promoted
auto Board::promotable_pawn(const Colour& pawn_colour) const -> std::pair<bool, Position>
{
    const int row{pawn_colour == Colour::white ? 0 : 7};
    const std::string pawn_icon{pawn_colour == Colour::white ? "♙" : "♟"};
    for (int col{0}; col < dimensions.second; ++col) {
        const Position visiting_pos{std::pair<int, int>{row, col}};
        if (occupied(visiting_pos)) {
            const std::string piece_icon{get_piece(visiting_pos)->get_icon()};
            if (piece_icon == "♙" or piece_icon == "♟") {
                return std::pair<bool, Position>{true, visiting_pos};
            }
        }
    }
    return std::pair<bool, Position>{false, Position{}};
}
auto Board::get_icon(const Position& pos) const noexcept -> std::string
{
    int index{pos.get_index(dimensions)};
    return squares[index]->get_icon();
}
