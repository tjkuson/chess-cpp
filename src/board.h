#ifndef CHESS_CLI_BOARD_H
#define CHESS_CLI_BOARD_H

#include "piece.h"
#include <vector>

class Board {
private:
    constexpr static auto ranks{8};
    constexpr static auto files{8};
    constexpr static auto white_back_rank{1};
    constexpr static auto black_back_rank{8};
    constexpr static auto white_pawn_rank{2};
    constexpr static auto black_pawn_rank{7};
    constexpr static auto num_pieces{32};
    std::vector<Piece> pieces;
public:
    Board(); // Construct with default pieces
    ~Board();
    // Overload the << operator to print the board
    friend auto operator<<(std::ostream& output_stream,
                           const Board& board) noexcept -> std::ostream&;
    // Generate square-set from piece list
    // Check if square matches a given colour
    auto get_square_set(Colour colour) const noexcept
        -> std::vector<std::vector<bool>>;
    // Check if square matches a given piece type
    auto get_square_set(piece_type type) const noexcept
        -> std::vector<std::vector<bool>>;
};

#endif // CHESS_CLI_BOARD_H
