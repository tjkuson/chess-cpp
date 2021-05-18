// colour.cpp

#include "colour.h"

// Operator overloading works when namespace is declared as so
namespace chess {
    // Overload ++ operator such that ++white == black, and ++black == white
    // Usage: to increment the turns i.e. "++current_turn"
    colour &operator++(colour &c) {
        c=(c==colour::black)?colour::white:colour::black;
        return c;
    }
    // Overload << operator so that the current turn can be printed to string stream
    std::ostream &operator<<(std::ostream &os, const colour &c) {
        std::string return_string{c==colour::white?"White":"Black"};
        os<<return_string;
        return os;
    }
}