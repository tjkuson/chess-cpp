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

#ifndef CHESS_CLI_POSITION_H
#define CHESS_CLI_POSITION_H

#include <map>
#include <stdexcept>
#include <string>
#include <utility>

namespace chess {
    class Position {
    private:
        std::pair<int, int> position_value;
        static const std::map<std::string, int> col_map; // constexpr std::map not possible for some reason
    public:
        // Prototype constructors and destructor
        Position();
        explicit Position(std::pair<int, int> init_pos);
        explicit Position(const std::pair<std::string, std::string>& init_pos);
        ~Position();
        // Prototype functions
        [[nodiscard]] auto get_position() const noexcept -> std::pair<int, int>;
        [[nodiscard]] auto
        get_offset(int row_offset, int col_offset) const noexcept -> Position;
        [[nodiscard]] auto operator==(const Position& rhs) const noexcept -> bool;
        [[nodiscard]] auto get_index(std::pair<int, int> pair) const noexcept -> int;
    };
}  // namespace chess

}// namespace chess

#endif//CHESS_CLI_POSITION_H
