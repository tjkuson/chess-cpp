// Copyright (C) 2021, Tom Kuson.
// This file is a part of Chess CLI which is released under the GPLv3.
// See LICENSE file in the project root or go to <https://www.gnu.org/licenses/> for full license details.

// colour.cpp

#include "colour.h"

// Operator overloading works when namespace is declared as so
namespace chess {
	// Overload ++ operator such that ++white == black, and ++black == white
	// Usage: to increment the turns i.e. "++current_turn"
	auto operator++(Colour& c) -> Colour&
	{
		c = (c==Colour::black) ? Colour::white : Colour::black;
		return c;
	}
	// Overload << operator so that the current turn can be printed to string stream
	auto operator<<(std::ostream& os, const Colour& c) -> std::ostream&
	{
		std::string return_string{ c==Colour::white ? "White" : "Black", std::allocator<char>() };
		os << return_string;
		return os;
	}
}  // namespace chess
