#include "Lexer.h"

namespace Klang {

Lexer::Lexer(const char* path)
	: _source(path), _index(0), _position(1, 1) {
	if (!this->_source.is_open())
		throw std::invalid_argument("The source file failed to open.");
	this->_current = this->_source.get();
}

void Lexer::load(const char* path) {
	this->_source.close();
	this->_source.open(path);
	if (!this->_source.good())
		throw std::invalid_argument("The source file is not \"good\".");
	this->_current = this->_source.get();
	this->_position.row = 1;
	this->_position.column = 0;
	this->_index = 0;
}

void Lexer::lex(Token& token) {
	while (std::isspace(this->current()))
		this->advance();
	token.start = this->position();
	switch (static_cast<TokenKind>(this->current())) {
	case TokenKind::SLOSH:
		do this->advance();
		while (this->current() != '\n');
		token.end = this->position();
		token.kind = TokenKind::COMMENT;
		break;
	case TokenKind::PLUS:
	case TokenKind::MINUS:
		if (std::isdigit(this->peek())) {
			this->lexNumeric(token);
			token.kind = TokenKind::INTEGER;
			break;
		}
	case TokenKind::EOT:
	case TokenKind::COLON:
	case TokenKind::SEMICOLON:
	case TokenKind::EQUAL:
	case TokenKind::ASTERISKS:
	case TokenKind::SLASH:
	case TokenKind::PERCENT:
	case TokenKind::OPAREN:
	case TokenKind::CPAREN:
		token.kind = static_cast<TokenKind>(this->current());
		token.end = this->position();
		this->advance();
		break;
	default:
		if (std::isalpha(this->current())) {
			Bucket<char, Token::MAX_VALUE_LENGTH> bucket;
			do {
				if (bucket.weight() >= bucket.capacity())
					throw std::overflow_error(__FUNCTION__);
				bucket.put(this->current());
				this->advance();
			} while (this->current() == '_' || std::isdigit(this->current()) ||
				 std::isalpha(this->current()));
			token.value = bucket.flush();
			token.kind = TokenKind::NAME;
		} else if (std::isdigit(this->current())) {
			this->lexNumeric(token);
			token.kind = TokenKind::NATURAL;
		} else {
			std::cout << this->current() << '\n';
			throw std::invalid_argument("Unkown token.");
		}
		token.end = this->position();
	}
}

void Lexer::lexNumeric(Token& token) {
	Bucket<char, Token::MAX_VALUE_LENGTH> bucket;
	do {
		if (bucket.weight() >= bucket.capacity())
			throw std::overflow_error(__FUNCTION__);
		bucket.put(this->current());
		this->advance();
	} while (this->current() == '_' || std::isdigit(this->current()));
	token.value = bucket.flush();
}

char Lexer::peek() {
	int peek = this->_source.peek();
	if (peek == EOF)
		throw std::out_of_range(__FUNCTION__);
	return peek;
}

void Lexer::advance() {
	if (!this->source().good())
		throw std::invalid_argument("The source file is not \"good\".");
	this->_current = this->_source.get();
	if (this->current() == '\n') {
		++this->_position.row;
		this->_position.column = 0;
	}
	++this->_position.column;
	++this->_index;
}

}
