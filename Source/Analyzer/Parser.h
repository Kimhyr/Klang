#pragma once

#include "Expressions.h"
#include "Lexer.h"

namespace Klang {

class Parser {
public:
	Parser(const char* sourcePath)
		: _lexer(sourcePath) {};

private:
	Lexer _lexer;
};

}
