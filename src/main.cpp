#include "board.h"
#include "colour.h"
#include "pawn.h"
#include <iostream>
auto main() -> int
{
    // Test printing pawn piece using overloaded << operator
    auto pawn = Pawn({0, 0}, Colour::black);
    std::cout << pawn << std::endl;
    return 0;
}
