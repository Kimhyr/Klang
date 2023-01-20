#include "Compiler/Compiler.hpp"

#include <stdio.h>

using namespace Klang;
using namespace Klang::Compiler;

Int main() {
	FILE *f = fopen("/home/k/Projects/Klang/Tests/arithmetics.k", "r");
	if (!f)
		throw Error::UNKNOWN_TOKEN;
	Sym source[1024];
	Sym *it = source;
	while ((*it++ = fgetc(f)) != EOF)
		putchar(it[-1]);
	it[-1] = 0;
	Lexer lexer(source);
	Token token;
	try {
		do {
			token = lexer.lex();
			printf("%lu,%lu;%lu,%lu\t\t", token.span()->start.row, token.span()->start.column, token.span()->end.row, token.span()->end.column);
			switch (token.tag()) {
			case Token::Tag::IDENTIFIER: fputs("IDENTIFIER", stdout); break;
			case Token::Tag::NATURAL: fputs("NATURAL", stdout); break;
			case Token::Tag::INTEGER: fputs("INTEGER", stdout); break;
			case Token::Tag::DATUM: fputs("DATUM", stdout); break;
			case Token::Tag::END: fputs("END", stdout);
			default: printf("%c", (Sym)token.tag()); break;
			}
			putchar('\n');
		} while (token.tag() != Token::Tag::END);
	} catch (Error e) {
		switch (e) {
		case Error::UNKNOWN_TOKEN: puts("UNKNOWN_TOKEN"); break;
		default: puts("ERROR"); break;
		}
	}
	return 0;
}
