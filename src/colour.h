// colour.h

#ifndef COLOUR_H
#define COLOUR_H

#include <sstream>

namespace chess {
    enum class colour
    {
        white,
        black
    };
    colour& operator++(colour& col);
    std::ostream &operator<<(std::ostream &os, const colour &c);
}


#endif //COLOUR_H
