#include "board.h"
#include "pawn.h"

// Default constructor
Board::Board()
{
    constexpr auto num_pieces{32};
    pieces = std::vector<std::vector<Piece>>(num_pieces);
    // Add the pawns to the board
    for (auto i{0}; i < 8; ++i) {
        pieces[i].emplace_back(Pawn({i, 1}, Colour::white));
        pieces[i].emplace_back(Pawn({i, 6}, Colour::black));
    }
}

// Destructor
Board::~Board() = default;

// Overload the << operator to print the board
auto operator<<(std::ostream& output_stream, const Board& board) noexcept -> std::ostream&
{
    // Print the board
    // TODO: Print the board in a more readable format
    for (const auto& row : board.pieces) {
        for (const auto& piece : row) {
            output_stream << piece;
        }
        output_stream << std::endl;
    }
    return output_stream;
}