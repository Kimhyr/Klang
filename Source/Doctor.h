#pragma once

#include <string_view>
#include <iostream>
#include <utility>

#include "Klang.h"
#include "Types.h"

namespace Klang {

enum class Severity {
	ERROR,
	WARNING,
	NOTE,
};

Severity diagnose(Severity type, std::string_view&& note);
Severity diagnose(Severity type, Position const& position, std::string_view&& note);
Severity diagnose(Severity type, Position const& position, std::string_view&& view,
		  std::string_view&& note);
Severity diagnose(Severity type, Span const& span, std::string_view&& view,
		  std::string_view&& note);
}

std::ostream& operator<<(std::ostream& os, Klang::Severity x);
std::ostream& operator<<(std::ostream& os, Klang::Position const& x);
std::ostream& operator<<(std::ostream& os, Klang::Span const& x);
