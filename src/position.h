// position.h

#ifndef POSITION_H
#define POSITION_H

#include <utility>
#include <string>
#include <stdexcept>
#include <map>

namespace chess {
	class position {
	private:
		std::pair<int, int> position_value;
	public:
		// Prototype constructors and destructor
		position();
		explicit position(std::pair<int, int> init_pos);
		explicit position(const std::pair<std::string, std::string>& init_pos);
		~position();
		// Prototype functions
		[[nodiscard]] std::pair<int, int> get_position() const;
		[[nodiscard]] position get_offset(int row_offset, int col_offset) const;
		[[nodiscard]] bool operator==(const position& rhs) const;
	};
}

#endif //POSITION_H
