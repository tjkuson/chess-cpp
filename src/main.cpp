// main.cpp

#include "game.h"

// Nasty compile command \
// g++ main.cpp game.cpp bishop.cpp board.cpp king.cpp knight.cpp pawn.cpp piece.cpp position.cpp queen.cpp rook.cpp colour.cpp -o ../bin/main.out

int main()
{
    chess::game g1;
    g1.loop();
    return 0;
}
