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

#include "colour.h"

// Operator overloading works when namespace is declared as so
namespace chess {
    // Overload ++ operator such that ++white == black, and ++black == white
    // Usage: to increment the turns, for example, "++current_turn".
    auto operator++(Colour& c) noexcept -> Colour&
    {
        c = (c==Colour::black) ? Colour::white : Colour::black;
        return c;
    }
    // Overload << operator so that the current turn can be printed to string stream
    auto operator<<(std::ostream& os, const Colour& c) noexcept -> std::ostream&
    {
        std::string return_string{c==Colour::white ? "White" : "Black",
                                  std::allocator<char>()};
        os << return_string;
        return os;
    }
}  // namespace chess
