// Copyright (C) 2021, Tom Kuson.
// This file is a part of Chess CLI which is released under the GPLv3.
// See LICENSE file in the project root or go to <https://www.gnu.org/licenses/> for full license details.

// position.cpp

#include "position.h"

using namespace chess;

// Default constructor
position::position()
		:position_value{ 0, 0 } { }

// Parameterised integer pair constructor
position::position(const std::pair<int, int> init_pos)
		:position_value{ init_pos } { }

// Parameterised string pair constructor
// Makes code neater if string conversion occurs in position class constructor
position::position(const std::pair<std::string, std::string>& init_pos)
		:position_value{ [&]() {
  // Algebraic notation i.e. "xN" e.g. "e3"
  if (init_pos.first.length()!=1 || init_pos.second.length()!=1) {
	  throw std::invalid_argument("Position constructor string too large, should be single char");
  }
  const int row{ 8-std::stoi(init_pos.second) }; // This will throw std::invalid_argument on conversion fail
  const std::map<std::string, int> col_map{
		  { "a", 0 },
		  { "b", 1 },
		  { "c", 2 },
		  { "d", 3 },
		  { "e", 4 },
		  { "f", 5 },
		  { "g", 6 },
		  { "h", 7 }
  };
  const int col{ col_map.at(init_pos.first) }; // This will throw std::out_of_range on conversion fail
  return std::pair<int, int>{ row, col };
}() } { }

// Default destructor
position::~position() = default;

// Return position
std::pair<int, int> position::get_position() const
{
	return position_value;
}

// Return position, with offset
position position::get_offset(int row_offset, int col_offset) const
{
	std::pair<int, int> position_with_offset{ position_value.first+row_offset, position_value.second+col_offset };
	return position{ position_with_offset };
}

// Return true of positions point to same location
bool position::operator==(const position& rhs) const
{
	return rhs.get_position()==position_value;
}
