// position.cpp

#include "position.h"

using namespace chess;

// Default constructor
position::position()
		:position_value{ 0, 0 } { }

// Parameterised integer pair constructor
position::position(const std::pair<int, int> initial_position)
		:position_value{ initial_position } { }

// Parameterised string pair constructor
// Makes code neater if string conversion occurs in position class constructor
position::position(const std::pair<std::string, std::string>& initial_position)
		:position_value{ [&]() {
  // Algebraic notation i.e. "xN" e.g. "e3"
  if (initial_position.first.length()!=1 || initial_position.second.length()!=1) {
	  throw std::invalid_argument("Position constructor string too large, should be single char");
  }
  const int row{ 8-std::stoi(initial_position.second) }; // This will throw std::invalid_argument on conversion fail
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
  const int col{ col_map.at(initial_position.first) }; // This will throw std::out_of_range on conversion fail
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
position position::get_position_with_offset(int row_offset, int col_offset) const
{
	std::pair<int, int> position_with_offset{ position_value.first+row_offset, position_value.second+col_offset };
	return position{ position_with_offset };
}

// Return true of positions point to same location
bool position::operator==(const position& rhs) const
{
	return rhs.get_position()==position_value;
}
