// piece.cpp

#include "piece.h"

using namespace chess;

// Parameterised constructor
piece::piece(const colour init_colour, const position &init_position): piece_colour{init_colour}, piece_position{init_position} {}

// Default destructor
piece::~piece() {
    possible_moves.clear();
    legal_moves.clear();
}

std::string piece::get_icon() const {
    return piece_icon;
}

colour piece::get_colour() const {
    return piece_colour;
}

int piece::get_number_of_legal_moves() const {
    // .size() method returns size_type value
    return static_cast<int>(legal_moves.size());
}

void piece::set_position(const position& new_pos) {
    piece_position=new_pos;
}

// Check if move is in the possible moves vector
bool piece::is_possible_move(const position &position_visiting) const {
    return std::find(possible_moves.begin(),possible_moves.end(),position_visiting)!=possible_moves.end();
}

// Check is position points to enemy piece
bool piece::is_attacking_enemy(const position &position_visiting, const board &game_board) const {
    // Return false if no piece in square
    if (!game_board.square_is_occupied(position_visiting)||!game_board.position_in_range(position_visiting)) {
        return false;
    }
    // Return false if piece is of same colour
    const std::shared_ptr<piece> new_piece_pointer{game_board.get_piece(position_visiting)};
    return new_piece_pointer->get_colour()!=piece_colour;
}

// Return true if move does not put king in check
bool piece::is_possible_move_legal(const position &init_position, const position &final_position, board temp_chess_board) const {
    // Create a temp chess board to see what happens should the move be permitted
    temp_chess_board.place_piece_without_updating(final_position,temp_chess_board.get_piece(init_position));
    temp_chess_board.place_piece_without_updating(init_position,nullptr); // Empty vacated position
    // Find the location of the king after the proposed move
    const position king_position{temp_chess_board.find_king_position(piece_colour)};
    // Check if the enemy can attack the king after proposed move
    for (int row{0}; row<8; row++) {
        for (int col{0}; col < 8; col++) {
            const position position_visiting{std::pair<int, int>{row, col}};
            if (temp_chess_board.square_is_occupied(position_visiting)) {
                const std::shared_ptr<piece> piece_pointer{temp_chess_board.get_piece(position_visiting)};
                if (piece_pointer->get_colour() != piece_colour) {
                    // We don't check for *legal* moves for the opponent as it doesn't matter if they put their king in\
                    in check if it means ours can be capture. It would also create an infinite loop.
                    piece_pointer->load_possible_moves(temp_chess_board);
                    if (piece_pointer->is_possible_move(king_position)) {
                        return false;
                    }
                }
            }
        }
    }
    return true;
}

// Filter the possible moves vector for legal moves e.g. that don't put King in check and store in legal moves vector
void piece::load_legal_moves(const board &chess_board) {
    legal_moves.clear();
    std::copy_if(possible_moves.begin(),possible_moves.end(),std::back_inserter(legal_moves),
     [&](const auto &trial_move) {
        return is_possible_move_legal(piece_position,trial_move,chess_board);}
    );
}

// Check if move is in list of legal moves
bool piece::is_legal_move(const position &trial_move) const {
    return std::find(legal_moves.begin(),legal_moves.end(),trial_move)!=legal_moves.end();
}