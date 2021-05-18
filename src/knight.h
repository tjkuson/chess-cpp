// knight.h

#ifndef KNIGHT_H
#define KNIGHT_H

#include "piece.h"

namespace chess {
    class knight : public piece
    {
    public:
        knight(colour init_colour, const position& init_position);
        void load_possible_moves(const board &chess_board) override;
    };
}

#endif //KNIGHT_H
