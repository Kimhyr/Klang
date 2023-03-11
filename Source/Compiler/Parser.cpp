#include "Parser.h"

namespace Klang {

Parser::Parser(C const* file)
	: file_(file), lexer_(file) {
	this->lexer_.lex(this->lexeme_);
	if (this->lexeme_.tag == Lexeme::EOT)
		throw diagnose(Severity::ERROR, "File is empty.");
} 

Syntax* Parser::parse() {
	switch (this->lexeme_.tag) {
	case Lexeme::O_PAREN:
	case Lexeme::
	default: break;
	}
	return nullptr;
}

}
