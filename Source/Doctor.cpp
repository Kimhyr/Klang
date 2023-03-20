#include "Doctor.hpp"

std::ostream& operator<<(std::ostream& os, Klang::Severity x) {
	using namespace Klang;
	switch (x) {
	case Severity::ERROR: os << "\x1b[91mError"; break;
	case Severity::WARNING: os << "\x1b[93mWarning";break;
	case Severity::NOTE: os << "\x1b[92mNote"; break;
	}
	os << "\e[0m";
	return os;
}
std::ostream& operator<<(std::ostream& os, Klang::Position const& x) {
	os << x.row << ':' << x.column;
	return os;
}

std::ostream& operator<<(std::ostream& os, Klang::Span const& x) {
	os << x.start << "|" << x.end;
	return os;
}
