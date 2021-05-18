// board.cpp
// Created by tjk on 30/04/2021.
//

#include "board.h"

using namespace chess;

// Board constructor
board::board(): dimensions{8,8} {
    // Initialise vector of piece pointers
    std::vector<std::shared_ptr<piece>> squares_row;
    squares_row.resize(8);
    for (int i{0}; i<dimensions.first; i++) {
        squares.push_back(squares_row);
    }
}

// Board destructor
board::~board() {
    squares.clear();
}

// Check position is in range on board
bool board::position_in_range(const position& pos) const {
    int row;
    int col;
    int board_rows;
    int board_cols;
    std::tie(row,col)=pos.get_position();
    std::tie(board_rows,board_cols)=dimensions;
    return row<board_rows && col<board_cols && row>=0 && col>=0;
}

// Check position is occupied by piece on board
bool board::square_is_occupied(const position& pos) const {
    int row;
    int col;
    std::tie(row,col)=pos.get_position();
    return squares[row][col]!=nullptr;
}

// Store pointer to new piece in squares vector
void board::place_piece(const position& pos, const std::shared_ptr<piece>& piece_pointer) {
    place_piece_without_updating(pos, piece_pointer);
    // Tell the piece to update it's position variable
    if (piece_pointer!=nullptr) {
        piece_pointer->set_position(pos);
    }
}

// Store pointer to new piece in squares vector
// This is used when we don't want the piece to change its location e.g. testing possible moves for checks
void board::place_piece_without_updating(const position &pos, const std::shared_ptr<piece> &piece_pointer) {
    int row;
    int col;
    std::tie(row,col)=pos.get_position();
    squares[row][col]=piece_pointer;
}

// Return pointer corresponding to position
std::shared_ptr<piece> board::get_piece(const position& pos) const {
    int row;
    int col;
    std::tie(row,col)=pos.get_position();
    return squares[row][col];
}

// Return position of king
position board::find_king_position(const colour& king_colour) const {
    const std::string king_icon{(king_colour == colour::white) ? "♔" : "♚"};
    for (int row{0}; row<8; row++) {
        for (int col{0}; col<8; col++) {
            const position position_visiting{std::pair<int,int>{row,col}};
            if (square_is_occupied(position_visiting)) {
                const std::shared_ptr<piece> piece_pointer{get_piece(position_visiting)};
                if (piece_pointer->get_icon()==king_icon) {
                    return position_visiting;
                }
            }
        }
    }
    throw std::out_of_range("King not found");
}
