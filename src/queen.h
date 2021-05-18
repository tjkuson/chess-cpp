// queen.h

#ifndef QUEEN_H
#define QUEEN_H

#include "piece.h"

namespace chess {
	class queen : public piece {
	public:
		queen(colour init_colour, const position& init_pos);
		void load_possible_moves(const board& chess_board) override;
	};
}

#endif //QUEEN_H
