#include "parser.h"

namespace KC::Analyzer {

Parser::Parser(const Sym *source)
	: source(source), lexer(source), token() {}

Parser::~Parser() {
	
}

Expression *Parser::parse() {
	auto expression = new Expression;
	for (Token token = this->lexer.lex(); token.tag != Token::Tag::END; token = this->lexer.lex()) {
		Nat64 stateIndex;
		const State *state;

		switch (token.tag) {
		case Token::Tag::DATUM:
			stateIndex = this->states.search(State::compareTag, State::Tag::DATUM);
			if (stateIndex != -1)
				throw Diagnosis();
			this->states.put(State(State::Tag::DATUM));
			break;
		case Token::Tag::IDENTIFIER:
			stateIndex = this->states.search(State::compareTag, State::Tag::);
		default:
			break;
		}
	}
	return expression;
}

} // namespace KC::Analyzer
