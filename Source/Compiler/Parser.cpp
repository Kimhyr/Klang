#include "Parser.hpp"

#include "Error.hpp"

namespace Klang::Compiler {

template<>
E::Datum *Parser::parse<>(Expression *under) {
	auto datum = new E::Datum {
		.under = under
	};
	this->lex();
	if (this->_token.tag() != Token::Tag::IDENTIFIER)
		throw Error::UNEXPECTED_TOKEN;
	// TODO: Add names to symbol table.
	datum->name = _token.value();
	this->lex();
	if (this->_token.tag() != Token::Tag::COLON)
		throw Error::UNEXPECTED_TOKEN;
	datum->type = this->parse<E::Primitive>();
	return datum;
}

template<>
E::Binary *Parser::parse<>(Expression *first, E::Binary::Operation operation) {
	auto binary = new E::Binary {
		.operation = operation,
		.first = first,
	};
	binary->second = this->parse<Expression>(binary);
	return binary;
}

template<>
Expression *Parser::parse<>(Expression *under) {
	this->lex();
	switch (_token.tag()) {
	case Token::Tag::DATUM: return this->parse<E::Datum>(under);
	case Token::Tag::PLUS:
	case Token::Tag::MINUS:
	case Token::Tag::ASTERISKS:
	case Token::Tag::SLASH:
	case Token::Tag::PERCENT:
		return this->parse<E::Binary>(under, (E::Binary::Operation)_token.tag());
	default:  return nil;
	}
}

}
