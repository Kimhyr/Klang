#include "Lexer.H"

#include "Error.H"

namespace KC {

Lexer::Lexer(const Sym *source)
	: source_(source), position_({.row = 1, .column = 1}) {}

Void Lexer::advance(Token *token) {
	while (this->isOnSpace())
		this->proceed();
	token->location_.span.start = this->position_;
	if (this->isOnAlphabetic()) {
		
	}
	if (this->isOnNumeric()) {
		
	} 
	switch ((Token::Tag)*this->source_) {
	case Token::Tag::OPEN_PAREN:
	case Token::Tag::CLOSE_PAREN:
	case Token::Tag::COLON: 
	case Token::Tag::SEMICOLON:
	case Token::Tag::SLOSH:
	case Token::Tag::EQUAL:
	case Token::Tag::PLUS:
	case Token::Tag::MINUS:
	case Token::Tag::ASTERISKS:
	case Token::Tag::SLASH:
	case Token::Tag::PERCENT:
		token->tag_ = (Token::Tag)*this->source_;
		this->proceed();
		goto Do_Epilogue;
	default: throw Error::UNKNOWN_TOKEN;
	}
Do_Epilogue:
	token->location_.span.end = this->position_;
}

Void Lexer::proceed() {
	++this->source_;
	if (*this->source_ == '\n') {
		++this->position_.row;
		this->position_.column = 0;
	}
	++this->position_.column;
}

}
