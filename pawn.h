// pawn.h

#ifndef PAWN_H
#define PAWN_H

#include "piece.h"

namespace chess {
    class pawn : public piece
    {
    public:
        pawn(colour init_colour, const position& init_position);
        void load_possible_moves(const board& chess_board) override;
    };
}

#endif //PAWN_H