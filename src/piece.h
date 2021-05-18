// piece.h

#ifndef PIECE_H
#define PIECE_H

#include <algorithm>
#include <memory>
#include "board.h"
#include "colour.h"

namespace chess {

    // Forward declare to reference board class
    class board;

    class piece
    {
    protected:
        const colour piece_colour;
        position piece_position;
        std::string piece_icon;
        std::vector<position> possible_moves;
        std::vector<position> legal_moves; // Moves that don't put own king in check
    public:
        // Prototype constructor and destructor
        piece(const colour init_colour, const position& init_position);
        virtual ~piece();
        // Prototype functions
        [[nodiscard]] std::string get_icon() const;
        [[nodiscard]] colour get_colour() const;
        [[nodiscard]] int get_number_of_legal_moves() const;
        void set_position(const position& new_pos);
        [[nodiscard]] bool is_possible_move(const position& position_visiting) const;
        [[nodiscard]] bool is_attacking_enemy(const position& position_visiting, const board& game_board) const;
        // Take chess board by value as the function will manipulate piece positions
        [[nodiscard]] bool is_possible_move_legal(const position &init_position, const position &final_position, board temp_chess_board) const;
        void load_legal_moves(const board& chess_board);
        [[nodiscard]] bool is_legal_move(const position& trial_move) const;
        // Prototype virtual functions to be overridden by derived classes
        virtual void load_possible_moves(const board& chess_board)=0;
    };
}

#endif //PIECE_H
