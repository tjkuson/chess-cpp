// queen.cpp

#include "queen.h"

using namespace chess;

// Parameterised constructor
queen::queen(const colour init_colour, const position& init_position) : piece{init_colour, init_position} {
    piece_icon=(piece_colour==colour::white)?"♕":"♛";
}

// Find all possible horizontal, vertical, and diagonal moves, not considering king check
void queen::load_possible_moves(const board &chess_board) {
    possible_moves.clear();
    // Lambda expression to search in a direction
    const auto generate_moves=[&](const int row_offset,const int col_offset){
        bool searching{true};
        for (int offset{1}; searching; ++offset) {
            const position visiting{piece_position.get_position_with_offset(offset*row_offset, offset*col_offset)};
            // Stop searching when another piece is encountered
            if (chess_board.position_in_range(visiting)) {
                if (!chess_board.square_is_occupied(visiting)) {
                    possible_moves.push_back(visiting);
                    continue;
                } else if (is_attacking_enemy(visiting, chess_board)) {
                    // If piece is enemy, then it can be captured
                    possible_moves.push_back(visiting);
                }
            }
            searching=false;
        }
    };
    generate_moves(1, 0); // Move vertically down
    generate_moves(-1, 0); // Move vertically up
    generate_moves(0, 1); // Move vertically right
    generate_moves(0, -1); // Move vertically left
    generate_moves(1,1); // Move down and to the right
    generate_moves(1,-1); // Move down and to the left
    generate_moves(-1,1); // Move up and to the right
    generate_moves(-1,-1); // Move up and to the left
}
