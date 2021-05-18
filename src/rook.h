// rook.h

#ifndef ROOK_H
#define ROOK_H

#include "piece.h"

namespace chess {
    class rook : public piece
    {
    public:
        rook(colour init_colour, const position& init_position);
        void load_possible_moves(const board& chess_board) override;
    };
}

#endif //ROOK_H
