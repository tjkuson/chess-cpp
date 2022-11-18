// Copyright (C) 2021, Tom Kuson.
// This file position.h is a part of Chess CLI which is released under the GPLv3.
// See LICENSE file in the project root or go to <https://www.gnu.org/licenses/> for full license details.

#ifndef CHESS_CLI_POSITION_H
#define CHESS_CLI_POSITION_H

#include <utility>
#include <string>
#include <stdexcept>
#include <map>

namespace chess {
class Position {
private:
    std::pair<int, int> position_value;
    static const std::map<std::string,
                          int> col_map; // constexpr std::map not possible for some reason
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

#endif //CHESS_CLI_POSITION_H
