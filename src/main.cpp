#include "board.h"
#include "colour.h"
#include "king.h"
#include "pawn.h"
#include "queen.h"
#include <iostream>
auto main() -> int
{
    // Create a board
    Board board;
    // Print the board
    std::cout << board;
    return 0;
}
