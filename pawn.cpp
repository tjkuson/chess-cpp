// pawn.cpp

#include "pawn.h"

using namespace chess;

// Parameterised constructor
pawn::pawn(const colour init_colour, const position& init_position) : piece{init_colour, init_position} {
    piece_icon=(piece_colour==colour::white)?"♙":"♟";
}

// Find all possible pawn moves, not considering king check
void pawn::load_possible_moves(const board& chess_board) {
    possible_moves.clear();
    const int direction{piece_colour==colour::white?-1:1};
    const position one_step_position{piece_position.get_position_with_offset(direction, 0)};
    if (chess_board.position_in_range(one_step_position)) {
        if (!chess_board.square_is_occupied(one_step_position)) {
            possible_moves.push_back(one_step_position);
            int row{piece_position.get_position().first};
            if ((row==6&&piece_colour==colour::white) || (row==1&&piece_colour==colour::black)) {
                // Can move up by two squares if pawn has not yet moved
                const position two_step_position{piece_position.get_position_with_offset(2*direction,0)};
                if (!chess_board.square_is_occupied(two_step_position)) {
                    possible_moves.push_back(two_step_position);
                }
            }
        }
    }
    // Pawn can move up diagonally only if attacking
    const auto generate_attack_moves=[&](const int col_offset){
        const position attack_position{piece_position.get_position_with_offset(direction,col_offset)};
        if (chess_board.position_in_range(attack_position)) {
            if (is_attacking_enemy(attack_position,chess_board)) {
                possible_moves.push_back(attack_position);
            }
        }
    };
    generate_attack_moves(-1); // Check forward and to the left
    generate_attack_moves(1); // Check forward and to the right
}