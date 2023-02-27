#include <string>
#include <iostream>
#include <sstream>

#include "Compiler/Lexer.h"

void test0() {
	using namespace Klang;
	Lexer lexer("/home/k/Projects/Klang/Tests/Test0");
	for (;;) {
		Lexeme lexeme = lexer.lex();
		std::cout << lexeme << std::endl;
		if (lexeme.tag == Lexeme::EOT)
			break;
	}
}

int main() {
	using namespace Klang;
	test0();
	return 0;
}
