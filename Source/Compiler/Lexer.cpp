#include "Lexer.hpp"

#include "../Utilities/Buffer.hpp"
#include "Error.hpp"

#include <string.h>

namespace Klang::Compiler {

using namespace Klang::Utilities;

Token Lexer::lex() {
	while (this->isSpace(this->current()))
		this->advance();
	Token token(this->position_);
	switch ((TokenTag)this->current()) {
	case TokenTag::PLUS:
	case TokenTag::MINUS:
		if (this->isNumeric(this->peek())) {
			this->lexNumeric(token);
			token.tag_ = TokenTag::INTEGER;
			goto No_Post_Advance; 
		}
	case TokenTag::OPEN_PAREN:
	case TokenTag::CLOSE_PAREN:
	case TokenTag::COLON: 
	case TokenTag::SEMICOLON:
	case TokenTag::SLOSH:
	case TokenTag::EQUAL:
	case TokenTag::ASTERISKS:
	case TokenTag::SLASH:
	case TokenTag::PERCENT:
	case TokenTag::END:
		token.tag_ = (TokenTag)this->current();
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
				token.tag_ = TokenTag::DATUM;
			else {
				token.value_ = buffer.flush();
				token.tag_= TokenTag::IDENTIFIER;
			}
			goto No_Post_Advance; 
		} else if (this->isNumeric(this->current())) {
			this->lexNumeric(token);
			token.tag_ = TokenTag::NATURAL;
				goto No_Post_Advance; 
		} else throw Error::UNKNOWN_TOKEN;
	}
	this->advance();
No_Post_Advance:
	token.span_.end = this->position_;
	--token.span_.end.column;
	return token;
}

constexpr Void Lexer::advance() noexcept {
	++this->source_;
	if (this->current() == '\n') {
		++this->position_.row;
		this->position_.column = 0;
	}
	++this->position_.column;
}

Void Lexer::lexNumeric(Token &token) {
	Buffer<Sym, Token::VALUE_SPACE> buffer;
	do {
		if (this->current() != '_')
			buffer.push(this->current());
		this->advance();
	} while (this->isNumeric(this->current()) || this->current() == '_');
	buffer.push(0);
	token.value_ = buffer.flush();
}

}
