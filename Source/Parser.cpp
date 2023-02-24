#include "Parser.h"

namespace Klang {

Program& Parser::parse() {
	auto program = new Program;
	for (;;) {
		this->lex();
		E::E* e;
		switch (this->token().tag) {
		case Token_Tag::OBJECT: e = this->parse_a<E::Object>(); break;
		case Token_Tag::EQUAL:
		case Token_Tag::SEMICOLON: e = this->parse_a<E::Separator>(); break;
		case Token_Tag::PLUS:
		case Token_Tag::MINUS:
		case Token_Tag::ASTERISKS:
		case Token_Tag::SLASH:
		case Token_Tag::PERCENT: e = this->parse_a<E::Binary>(); break;
		case Token_Tag::OPAREN: e = this->parse_a<E::Scoped>(); break;
		case Token_Tag::MACHINE_LITERAL:
		case Token_Tag::NATURAL_LITERAL:
		case Token_Tag::REAL_LITERAL:
		case Token_Tag::TEXT_LITERAL: e = this->parse_a<E::Literal>(); break;
		case Token_Tag::EOT: goto Escape;
		default: throw std::invalid_argument("Unexpected token.");
		}
		this->expression_stack_.push(e);
	}
Escape:
	return *program;
}

}
