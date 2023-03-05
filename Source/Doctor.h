#pragma once

#include <sstream>
#include <utility>
#include <iostream>

#include "Klang.h"
#include "Types.h"

namespace Klang {

namespace Message {

static std::stringstream STRING;

}

enum class Severity {
	ERROR,
	WARNING,
	NOTE,
};

}

std::ostream& operator<<(std::ostream& os, Klang::Severity x);
std::ostream& operator<<(std::ostream& os, Klang::Position const& x);
std::ostream& operator<<(std::ostream& os, Klang::Span const& x);

namespace Klang {

inline Severity diagnose(Severity type, std::string_view&& note) {
	std::cerr << '['<< type << "] " << note;
	return type;
}

inline Severity diagnose(Severity type, Position const& position,
			 std::string_view&& note) {
	std::cerr << '['<< type << " at " << position << "] " << note;
	return type;
}

inline Severity diagnose(Severity type, Position const& position,
			 std::string_view&& view, std::string_view&& note) {
	std::cerr << '[' << type << " at " << position << "] " << note << '\n' << view;
	return type;
}

}
