// Copyright (C) 2021, Tom Kuson.
// This file is a part of Chess CLI which is released under the GPLv3.
// See LICENSE file in the project root or go to <https://www.gnu.org/licenses/> for full license details.

// colour.h

#ifndef CHESS_CLI_COLOUR_H
#define CHESS_CLI_COLOUR_H

#include <sstream>

namespace chess {
	enum class Colour {
		white,
		black
	};
	auto operator++(Colour& c) -> Colour&;
	auto operator<<(std::ostream& os, const Colour& c) -> std::ostream&;
}

#endif //CHESS_CLI_COLOUR_H
