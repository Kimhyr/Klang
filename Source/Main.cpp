#include "Lexer.h"
#include "Syntax.h"

using namespace Klang;

void test0() {
	Lexer lexer("/home/k/Projects/Klang/Tests/Test0");
	for (;;) {
		Token token;
		lexer.lex(token);
		std::cout << token << std::endl;
		if (token.tag == Token_Tag::EOT)
			break;
		token.reset();
	}
}

int main() {
	test0();
	return 0;
}
