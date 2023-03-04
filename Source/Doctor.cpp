#include "Doctor.h"

namespace Klang {

void diagnose(Diagnosis_Type severity, Span span, std::string_view&& view,
	      std::string_view&& note) {
	std::cout << "\e[" << static_cast<I>(severity) << 'm'
		  << severity << " at " << span << ":\e[0m\n"
		  << view << "\n"
		  << note << '\n';
}
	
};

std::ostream& operator<<(std::ostream& os, Klang::Diagnosis_Type x) {
	using namespace Klang;
	switch (x) {
	case Diagnosis_Type::ERROR: os << "Error"; break;
	case Diagnosis_Type::WARNING: os << "Warning";break;
	case Diagnosis_Type::NOTE: os << "Note"; break;
	}
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
