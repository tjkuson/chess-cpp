#include "board.h"
#include "bishop.h"
#include "king.h"
#include "knight.h"
#include "pawn.h"
#include "queen.h"
#include "rook.h"

// Default constructor
Board::Board()
{
    // We know precisely the number of pieces, so we can reserve memory manually
    pieces.reserve(num_pieces);
    // Add the pieces, starting with the pawns
    for (auto file{1}; file <= files; ++file) {
        pieces.emplace_back(Pawn({white_pawn_rank, file}, Colour::white));
        pieces.emplace_back(Pawn({black_pawn_rank, file}, Colour::black));
    }
    constexpr auto rook_left_file{1};
    constexpr auto rook_right_file{8};
    pieces.emplace_back(Rook({white_back_rank, rook_left_file}, Colour::white));
    pieces.emplace_back(
        Rook({white_back_rank, rook_right_file}, Colour::white));
    pieces.emplace_back(Rook({black_back_rank, rook_left_file}, Colour::black));
    pieces.emplace_back(
        Rook({black_back_rank, rook_right_file}, Colour::black));
    constexpr auto knight_left_file{2};
    constexpr auto knight_right_file{7};
    pieces.emplace_back(
        Knight({white_back_rank, knight_left_file}, Colour::white));
    pieces.emplace_back(
        Knight({white_back_rank, knight_right_file}, Colour::white));
    pieces.emplace_back(
        Knight({black_back_rank, knight_left_file}, Colour::black));
    pieces.emplace_back(
        Knight({black_back_rank, knight_right_file}, Colour::black));
    constexpr auto bishop_left_file{3};
    constexpr auto bishop_right_file{6};
    pieces.emplace_back(
        Bishop({white_back_rank, bishop_left_file}, Colour::white));
    pieces.emplace_back(
        Bishop({white_back_rank, bishop_right_file}, Colour::white));
    pieces.emplace_back(
        Bishop({black_back_rank, bishop_left_file}, Colour::black));
    pieces.emplace_back(
        Bishop({black_back_rank, bishop_right_file}, Colour::black));
    constexpr auto queen_file{4};
    pieces.emplace_back(Queen({white_back_rank, queen_file}, Colour::white));
    pieces.emplace_back(Queen({black_back_rank, queen_file}, Colour::black));
    constexpr auto king_file{5};
    pieces.emplace_back(King({white_back_rank, king_file}, Colour::white));
    pieces.emplace_back(King({black_back_rank, king_file}, Colour::black));
}

// Destructor
Board::~Board() = default;

// Overload the << operator to print the board
auto operator<<(std::ostream& output_stream, const Board& board) noexcept
    -> std::ostream&
{
    output_stream << "   a b c d e f g h  \n";
    for (auto rank{board.ranks}; rank >= 1; --rank) {
        output_stream << rank << " ";
        for (auto file{1}; file <= board.files; ++file) {
            output_stream << " ";
            // Check if there is a piece at this position, and if so, print it;
            // otherwise, print a dot
            for (const auto& piece: board.pieces) {
                // There should only be one piece at each position, so we break
                // after printing it
                if (piece.get_position() == std::pair<int, int>{rank, file}) {
                    output_stream << piece;
                    break;
                }
                if (&piece == &board.pieces.back()) { output_stream << "·"; }
            }
        }
        output_stream << "\n";
    }
    return output_stream;
}
auto Board::get_square_set(Colour colour) const noexcept
    -> std::vector<std::vector<bool>>
{
    std::vector<std::vector<bool>> square_set;
    square_set.reserve(ranks);
    for (auto rank{1}; rank <= files; ++rank) {
        std::vector<bool> rank_set;
        rank_set.reserve(files);
        for (auto file{1}; file <= files; ++file) {
            bool square{false};
            for (const auto& piece: pieces) {
                if (piece.get_position() == std::pair<int, int>{rank, file}
                    && piece.get_colour() == colour) {
                    square = true;
                    break;
                }
            }
            // Add rank_set to square_set if we are at the end of the rank
            rank_set.push_back(square);
        }
        square_set.push_back(rank_set);
    }
    return square_set;
}
auto Board::get_square_set(piece_type type) const noexcept
    -> std::vector<std::vector<bool>>
{
    std::vector<std::vector<bool>> square_set;
    square_set.reserve(ranks);
    for (auto rank{1}; rank <= files; ++rank) {
        std::vector<bool> rank_set;
        rank_set.reserve(files);
        for (auto file{1}; file <= files; ++file) {
            bool square{false};
            for (const auto& piece: pieces) {
                if (piece.get_position() == std::pair<int, int>{rank, file}
                    && piece.get_type() == type) {
                    square = true;
                    break;
                }
            }
            // Add rank_set to square_set if we are at the end of the rank
            rank_set.push_back(square);
        }
        square_set.push_back(rank_set);
    }
    return square_set;
}
