#include "Parser.hpp"

namespace Klang::Compiler {

template<>
const E::Type *Parser::parse() {
	this->lexer_.lex();
	switch (this->token_.tag()) {
	case TokenTag::IDENTIFIER:
		
		break;
	case TokenTag::INT:
		break;
	default: throw Error::UNEXPECTED_TOKEN;
	}
	return 
}

template<>
const E::Identifier *Parser::parse(const E::Symbol *symbol) {
	auto identifier = new E::Identifier;
	identifier->tag = symbol->ETAG;
	this->lex(TokenTag::IDENTIFIER);
	identifier->name = this->token_.value();
	return identifier;
}

template<>
const E::Datum *Parser::parse() {
	auto datum = new E::Datum;
	datum->identifier = this->parse<E::Identifier>();
	this->lex(TokenTag::COLON);
	datum->type = this->parse<E::Type>();
	return datum;
}

template<>
const Expression *Parser::parse(const Expression *prior) {
	this->lexer_.lex();
	switch (this->token().tag()) {
	case TokenTag::SEMICOLON:
		if (!prior)
			throw Error::UNEXPECTED_TOKEN;
		return this->parse<E::Binary>(prior, E::Binary::STATEMENT);
	case TokenTag::DATUM: return this->parse<E::Datum>();
	case TokenTag::EQUAL: return this->parse<E::Binary>(prior, E::Binary::ASSIGN);
	default: throw Error::UNEXPECTED_TOKEN;
	}
}


}
