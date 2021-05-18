// Copyright (C) 2021, Tom Kuson.
// This file is a part of Chess CLI which is released under the GPLv3.
// See LICENSE file in the project root or go to <https://www.gnu.org/licenses/> for full license details.

// colour.h

#ifndef COLOUR_H
#define COLOUR_H

#include <sstream>

namespace chess {
	enum class colour {
		white,
		black
	};
	colour& operator++(colour& c);
	std::ostream& operator<<(std::ostream& os, const colour& c);
}

#endif //COLOUR_H
