#include "Analyzer/Lexer.h"

#include <utility>

using namespace Klang;

void test0() {
	Lexer lexer("/home/k/Projects/Klang/Tests/arithmetics.k");
	for (;;) {
		Token token = lexer.lex();
		std::cout << token << std::endl;
		if (token.kind == TokenKind::EOT)
			break;
	}
}

void test1() {
	Lexer lexer("/home/k/Projects/Klang/Tests/arithmetics.k");
	Token token = lexer.lex();
	std::cout << token << '\n';
	token = lexer.lex();
	std::cout << token << '\n';
	token = lexer.lex();
	std::cout << token << '\n';
}

int main() {
	test1();
	return 0;
}
