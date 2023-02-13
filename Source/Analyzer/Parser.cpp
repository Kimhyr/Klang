#include "Parser.h"

namespace Klang {

template<>
SyntaxTree *Parser::parse() {
	this->lex();
	switch (this->token().tag) {
	case TokenTag::OBJECT:
		this->parse<Identifier>(id);
		break;
	default: throw std::invalid_argument(__FUNCTION__);
	}
}

template<>
Identifier* Parser::parse() {
	Identifier identifier;
	identifier.determiner = static_cast<IdentifierDeterminer>(this->token().tag);
	this->lex();
	if (this->token().tag != TokenTag::NAME)
		throw std::invalid_argument(__FUNCTION__);
	identifier.name = this->token().value.Name;
	>
	return nullptr;
}

}
