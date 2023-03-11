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
    auto square_set{board.get_square_set(piece_type::king)};
    return 0;
}
