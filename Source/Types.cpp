#include "Types.h"

std::ostream& operator<<(std::ostream& os, const Klang::Position& pos) {
	os << "Position{.row=" << pos.row << ",.column=" << pos.column << '}';
	return os;
}
