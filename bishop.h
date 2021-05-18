// bishop.h

#ifndef BISHOP_H
#define BISHOP_H

#include "piece.h"

namespace chess {
    class bishop : public piece
    {
    public:
        bishop(colour init_colour, const position& init_position);
        void load_possible_moves(const board &chess_board) override;
    };
}


#endif //BISHOP_H
