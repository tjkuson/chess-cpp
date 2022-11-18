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

#ifndef CHESS_CLI_COLOUR_H
#define CHESS_CLI_COLOUR_H

#include <sstream>

namespace chess {
enum class Colour {
    white,
    black
};
auto operator++(Colour& passed_colour) noexcept -> Colour&;
auto operator<<(std::ostream& str_stream,
                const Colour& passed_colour) noexcept -> std::ostream&;
}// namespace chess

#endif//CHESS_CLI_COLOUR_H
