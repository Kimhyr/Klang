#include "Analyzer/Lexer.h"

#include <utility>

using namespace Klang;

void test0() {
	Lexer lexer("/home/k/Projects/Klang/Tests/Test0");
	for (;;) {
		Token token;
		try {
			lexer.lex(token);
			std::cout << token << std::endl;
			if (token.kind == TokenKind::EOT)
				break;
		} catch (const std::exception& e) {
			std::cout << e.what() << '\n';
			break;
		}
	}
}

int main() {
	test0();
	return 0;
}
