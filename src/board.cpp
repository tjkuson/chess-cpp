#include "board.h"
#include "pawn.h"

// Default constructor
Board::Board()
{
    constexpr auto num_pieces{32};
    pieces.reserve(num_pieces);
    // Add the pawns
    constexpr auto white_pawn_rank{2};
    constexpr auto black_pawn_rank{7};
    for (auto file{1}; file <= files; ++file) {
        pieces.emplace_back(Pawn({white_pawn_rank, file}, Colour::white));
        pieces.emplace_back(Pawn({black_pawn_rank, file}, Colour::black));
    }
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