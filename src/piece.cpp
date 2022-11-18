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

#include "piece.h"

using namespace chess;

// Parameterised constructor
Piece::Piece(const Colour init_colour, const Position& init_pos)
        :piece_colour{init_colour}, piece_pos{init_pos} { }

// Default destructor
Piece::~Piece() = default;

auto Piece::get_icon() const -> std::string
{
    return piece_icon;
}

auto Piece::get_colour() const -> Colour
{
    return piece_colour;
}

auto Piece::get_num_of_legal_moves() const -> int
{
    // .size() method returns size_type value
    return static_cast<int>(legal_moves.size());
}

void Piece::set_position(const Position& new_pos)
{
    piece_pos = new_pos;
}

// Check if move is in the possible moves vector
auto Piece::possible_move(const Position& move) const -> bool
{
    return std::find(possible_moves.begin(), possible_moves.end(), move)
            != possible_moves.end();
}

// Check is position points to enemy piece
auto Piece::attacking_enemy(const Position& visiting_pos,
        const Board& game_board) const -> bool
{
    // Return false if no piece in square
    if (not game_board.occupied(visiting_pos)
            or not game_board.in_range(visiting_pos)) {
        return false;
    }
    // Return false if piece is of same colour
    const std::shared_ptr<Piece> piece_ptr{game_board.get_piece(visiting_pos)};
    return piece_ptr->get_colour() != piece_colour;
}

// Return true if move does not put king in check
auto Piece::legal_move(const Position& init_pos, const Position& final_pos,
        Board chess_board) const -> bool
{
    // Create a temp chess board to see what happens should the move be permitted
    chess_board.place_piece_no_update(final_pos, chess_board.get_piece(init_pos));
    chess_board.place_piece_no_update(init_pos, nullptr); // Empty vacated position
    // Find the location of the king after the proposed move
    const Position king_pos{chess_board.find_king(piece_colour)};
    // Check if the enemy can attack the king after proposed move
    for (int row{0}; row < 8; row ++) {
        for (int col{0}; col < 8; col ++) {
            const Position visiting_pos{std::pair<int, int>{row, col}};
            if (chess_board.occupied(visiting_pos)) {
                const std::shared_ptr<Piece> piece_ptr{
                        chess_board.get_piece(visiting_pos)};
                if (piece_ptr->get_colour() != piece_colour) {
                    // We don't check for *legal* moves for the opponent as it doesn't matter if they put their king in\
                    in check if it means ours can be capture. It would also create an infinite loop.
                    piece_ptr->load_possible_moves(chess_board);
                    if (piece_ptr->possible_move(king_pos)) {
                        return false;
                    }
                }
            }
        }
    }
    return true;
}

// Filter the possible moves vector for legal moves e.g. that don't put King in check and store in legal moves vector
void Piece::load_legal_moves(const Board& chess_board)
{
    legal_moves.clear();
    std::copy_if(
            possible_moves.begin(), possible_moves.end(),
            std::back_inserter(legal_moves),
            [&](const auto& trial_move) {
              return legal_move(piece_pos, trial_move, chess_board);
            }
    );
}

// Check if move is in list of legal moves
auto Piece::legal_move(const Position& move) const -> bool
{
    return std::find(legal_moves.begin(), legal_moves.end(), move) != legal_moves.end();
}
