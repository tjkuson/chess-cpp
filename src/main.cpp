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

#include "game.h"

// Nasty compile command \
// g++ main.cpp game.cpp bishop.cpp board.cpp king.cpp knight.cpp pawn.cpp piece.cpp position.cpp queen.cpp rook.cpp colour.cpp -o ../bin/main.out

auto main() -> int
{
    chess::Game game;
    game.loop();
    return 0;
}
