//
// Created by tjk on 02/05/2021.
//

#ifndef KING_H
#define KING_H


#include "piece.h"

namespace chess {
    class king : public piece
    {
    public:
        king(colour init_colour, const position& init_position);
        void load_possible_moves(const board &chess_board) override;
    };
}


#endif //KING_H
