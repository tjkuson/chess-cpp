// Copyright (C) 2021, Tom Kuson.
// This file position.cpp is a part of Chess CLI which is released under the GPLv3.
// See LICENSE file in the project root or go to <https://www.gnu.org/licenses/> for full license details.

#include "position.h"

using namespace chess;

const std::map<std::string, int> Position::col_map{
        {"a", 0},
        {"b", 1},
        {"c", 2},
        {"d", 3},
        {"e", 4},
        {"f", 5},
        {"g", 6},
        {"h", 7}
};

// Default constructor
Position::Position()
        :position_value{0, 0} { }

// Parameterised integer pair constructor
Position::Position(const std::pair<int, int> init_pos)
        :position_value{init_pos} { }

// Parameterised string pair constructor
// Makes code neater if string conversion occurs in position class constructor
Position::Position(const std::pair<std::string, std::string>& init_pos)
        :position_value{[&]() {
  // Algebraic notation i.e. "xN" e.g. "e3"
  if (init_pos.first.length() != 1 or init_pos.second.length() != 1) {
      throw std::invalid_argument(
              "Position constructor string too large, should be single char");
  }
  const int row{8 - std::stoi(
          init_pos.second)}; // This will throw std::invalid_argument on conversion fail
  // std::allocator<std::pair<std::string, int>>()
  const int col{col_map.at(
          init_pos.first)}; // This will throw std::out_of_range on conversion fail
  return std::pair<int, int>{row, col};
}()} { }

// Default destructor
Position::~Position() = default;

// Return position
auto Position::get_position() const noexcept -> std::pair<int, int>
{
    return position_value;
}

// Return position, with offset
auto Position::get_offset(int row_offset, int col_offset) const noexcept -> Position
{
    std::pair<int, int> position_with_offset{position_value.first + row_offset,
                                             position_value.second + col_offset};
    return Position{position_with_offset};
}

// Return true of positions point to same location
auto Position::operator==(const Position& rhs) const noexcept -> bool
{
    return rhs.get_position() == position_value;
}

auto Position::get_index(const std::pair<int, int> dimensions) const noexcept -> int
{
    return dimensions.second * position_value.first + position_value.second;
}
