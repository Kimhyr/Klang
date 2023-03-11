#include <string>
#include <iostream>
#include <sstream>

#include "Compiler/Lexer.h"

void test0() {
	using namespace Klang;
	std::ifstream file("/home/k/Projects/Klang/Tests/Test0");
	Lexer lexer(std::move(file));
	for (;;) {
		Lexeme lexeme;
		lexer.lex(lexeme);
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
