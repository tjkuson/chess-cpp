// Chess CLI: command-line chess
// Copyright (c) 2022 Tom Kuson
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.

#ifndef CHESS_CLI_GAME_H
#define CHESS_CLI_GAME_H

#include <iostream>

#include "board.h"
#include "position.h"
#include "colour.h"
#include "pawn.h"
#include "king.h"
#include "queen.h"
#include "rook.h"
#include "bishop.h"
#include "knight.h"

namespace chess {
    class Game {
    private:
        Board chess_board;
        Colour current_player;
        Colour next_player;
        static constexpr int rows{8};
        static constexpr int cols{8};
        bool game_active;
        bool white_castled;
        bool black_castled;
        bool can_castle_king_side;
        bool can_castle_queen_side;
        bool pawn_doubled_pushed_last_turn; // Used for en passant
        int en_passant_col; // Read if pawn_doubled_pushed_last_turn is true
    public:
        // Prototype constructor and destructor
        Game();
        ~Game();
        // Prototype functions
        void print_chess_board() const;
        void move_piece(const Position& init_pos, const Position& final_pos);
        void handle_move();
        [[nodiscard]] auto enemy_can_capture(const Position& test_pos) const -> bool;
        void generate_moves() const;
        [[nodiscard]] auto num_of_legal_moves() const -> int;
        [[nodiscard]] auto
        can_castle(const Position& king_pos) const -> std::pair<bool, bool>;
        void check_for_pawn_promotion();
        void loop();
    };
}  // namespace chess

#endif //CHESS_CLI_GAME_H
