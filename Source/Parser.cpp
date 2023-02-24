#include "Parser.h"

#include <type_traits>

namespace Klang {

template<>
void Parser::parse(E::Program& out) {
	switch (this->token().tag) {
	case Token_Tag::OBJECT:
		this->parse(dynamic_cast<E::Object&>(*out.next));
		break;
	default: throw std::invalid_argument("Invalid start symbol.");
	}
}

template<>
void Parser::parse(E::Object& out) {
	this->lex();
	out.identifier.determiner = O::Determiner::OBJECT;
	this->parse<O::Identifier>(out.identifier);
	this->lex();
	if (this->token().tag != Token_Tag::COLON)
		throw std::invalid_argument("Expected a COLON token when trying to parse an E::Object.");
	this->parse<O::Type_Composition>(out.type);

}

template<>
void Parser::parsed(O::Type_Composition& out) {
	for (;;) {
		this->lex();
		if (this->token().is_primitive()) {
			
		}
		// throw std::invalid_argument("Unexpected token when trying to parse an O::Type_Composition.");
	}
}

template<>
void Parser::parse(O::Identifier& out) {
	for (;;) {
		this->lex();
		switch (this->token().tag) {
		case Token_Tag::NAME:
			out.name = this->token().value.Name;
			return;
		default: throw std::invalid_argument("Unexpected token when trying to parse an O::Identifier.");
		}
	}
}

}
