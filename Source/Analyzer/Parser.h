#pragma once

#include "Expression.h"
#include "Lexer.h"

namespace Klang {

class Parser {

private:
	Lexer lexer;
	Program program;
};

}
