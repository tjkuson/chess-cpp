// knight.cpp

#include "knight.h"

using namespace chess;

// Parameterised constructor
knight::knight(const colour init_colour, const position& init_position) : piece{init_colour, init_position} {
    piece_icon=(piece_colour==colour::white)?"♘":"♞";
}

// Find all possible "L-shaped" moves, not considering king check
void knight::load_possible_moves(const board &chess_board) {
    possible_moves.clear();
    const std::vector<position> temp_possible_moves{
            // Eight L-shaped moves
            piece_position.get_position_with_offset(2, -1),
            piece_position.get_position_with_offset(2, 1),
            piece_position.get_position_with_offset(-2, -1),
            piece_position.get_position_with_offset(-2, 1),
            piece_position.get_position_with_offset(1, -2),
            piece_position.get_position_with_offset(-1, -2),
            piece_position.get_position_with_offset(1, 2),
            piece_position.get_position_with_offset(-1, 2),
    };
    // Copy moves to possible  moves vector if they are empty or attacking enemy
    std::copy_if(temp_possible_moves.begin(),temp_possible_moves.end(),std::back_inserter(possible_moves),
         [&](const auto &possible_position){
             if (chess_board.position_in_range(possible_position)) {
                 return !chess_board.square_is_occupied(possible_position)||is_attacking_enemy(possible_position,chess_board);
             }
             return false;
    });
}
