#include "Compiler/Parser.hpp"

namespace Klang {

Parser::Parser(char const* file)
	: m_file(file), m_lexer(file) {
	this->m_lexer.lex(this->lexeme_);
	if (this->lexeme_.tag == Lexeme::EOT)
		throw diagnose(Severity::ERROR, "File is empty.");
}

Syntax* Parser::parse() {
	switch (this->lexeme_.tag) {
	case Lexeme::LPAREN:
	case Lexeme::
	default: break;
	}
	return nullptr;
}

}
