#ifndef CHESS_CLI_BOARD_H
#define CHESS_CLI_BOARD_H

#include "piece.h"
#include <vector>

class Board {
private:
    std::vector<Piece> pieces;// vector of all 32 pieces
    constexpr static auto ranks{8};
    constexpr static auto files{8};

public:
    Board();// Construct with default pieces
    ~Board();
    // Overload the << operator to print the board
    friend auto operator<<(std::ostream& output_stream, const Board& board) noexcept -> std::ostream&;
};

#endif//CHESS_CLI_BOARD_H
