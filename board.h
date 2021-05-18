// board.h

#ifndef BOARD_H
#define BOARD_H

#include "main.h"
#include "position.h"
#include "piece.h"
#include "colour.h"

namespace chess {
    // Forward declare piece class to resolve circular dependency \
    This allows the board class to store piece class pointers before piece class has been defined
    class piece;

    class board
    {
    private:
        const std::pair<int, int> dimensions; // row, col
        std::vector<std::vector<std::shared_ptr<piece>>> squares;
    public:
        // Prototype constructor and destructor
        board();
        ~board();
        // Prototype functions
        [[nodiscard]] bool position_in_range(const position& pos) const;
        [[nodiscard]] bool square_is_occupied(const position& pos) const;
        void place_piece(const position& pos, const std::shared_ptr<piece>& piece_pointer);
        void place_piece_without_updating(const position& pos, const std::shared_ptr<piece>& piece_pointer);
        [[nodiscard]] std::shared_ptr<piece> get_piece(const position& pos) const;
        [[nodiscard]] position find_king_position(const colour& king_colour) const;
    };
}

#endif //BOARD_H