#include "Lexer.hpp"

#include "../Utilities/Buffer.hpp"
#include "Error.hpp"

#include <string.h>

namespace Klang::Compiler {

using namespace Klang::Utilities;

Token Lexer::lex() {
	while (this->isSpace(this->current()))
		this->advance();
	Token token(this->_position);
	switch ((Token::Tag)this->current()) {
	case Token::Tag::PLUS:
	case Token::Tag::MINUS:
		if (this->isNumeric(this->peek())) {
			this->lexNumeric(token);
			token._tag = Token::Tag::INTEGER;
			goto No_Post_Advance; 
		}
	case Token::Tag::OPEN_PAREN:
	case Token::Tag::CLOSE_PAREN:
	case Token::Tag::COLON: 
	case Token::Tag::SEMICOLON:
	case Token::Tag::SLOSH:
	case Token::Tag::EQUAL:
	case Token::Tag::ASTERISKS:
	case Token::Tag::SLASH:
	case Token::Tag::PERCENT:
	case Token::Tag::END:
		token._tag = (Token::Tag)this->current();
		break;
	default:
		if (this->isAlphabetic(this->current())) {
			Buffer<Sym, Token::VALUE_SPACE> buffer;
			do {
				buffer.push(this->current());
				this->advance();
			} while (this->isAlphabetic(this->current()) || this->current() == '_');
			buffer.push(0);
			if (strcmp(buffer.data(), "datum") == 0)
				token._tag = Token::Tag::DATUM;
			else {
				token._value = buffer.flush();
				token._tag = Token::Tag::IDENTIFIER;
			}
			goto No_Post_Advance; 
		} else if (this->isNumeric(this->current())) {
			this->lexNumeric(token);
			token._tag = Token::Tag::NATURAL;
				goto No_Post_Advance; 
		} else throw Error::UNKNOWN_TOKEN;
	}
	this->advance();
No_Post_Advance:
	token._span.end = this->_position;
	--token._span.end.column;
	return token;
}

constexpr Void Lexer::advance() noexcept {
	++this->_source;
	if (this->current() == '\n') {
		++this->_position.row;
		this->_position.column = 0;
	}
	++this->_position.column;
}

Void Lexer::lexNumeric(Token &token) {
	Buffer<Sym, Token::VALUE_SPACE> buffer;
	do {
		if (this->current() != '_')
			buffer.push(this->current());
		this->advance();
	} while (this->isNumeric(this->current()) || this->current() == '_');
	buffer.push(0);
	token._value = buffer.flush();
}

}
