// Copyright (C) 2021, Tom Kuson.
// This file main.cpp is a part of Chess CLI which is released under the GPLv3.
// See LICENSE file in the project root or go to <https://www.gnu.org/licenses/> for full license details.

#include "game.h"

// Nasty compile command \
// g++ main.cpp game.cpp bishop.cpp board.cpp king.cpp knight.cpp pawn.cpp piece.cpp position.cpp queen.cpp rook.cpp colour.cpp -o ../bin/main.out

auto main() -> int
{
    chess::Game g_1;
    g_1.loop();
    return 0;
}
