#include "Lexer.h"

namespace Klang {

Lexer::Lexer(const char* path)
	: _source(path), _index(0), _position(1, 1) {
	if (!this->_source.is_open())
		throw std::invalid_argument("The source file failed to open.");
}

void Lexer::load(const char* path) {
	this->_source.close();
	this->_source.open(path);
	if (!this->_source.good())
		throw std::invalid_argument("The source file is not \"good\".");
	this->_current = this->_source.get();
	this->_position.row = 1;
	this->_position.column = 1;
	this->_index = 0;
}

Token Lexer::lex() {
	while (std::isspace(this->current()))
		this->advance();
	Token token = { .start = this->position() };
	switch (static_cast<TokenKind>(this->current())) {
	case TokenKind::EOT:
	case TokenKind::COLON:
	case TokenKind::SEMICOLON:
	case TokenKind::EQUAL:
	case TokenKind::PLUS:
	case TokenKind::MINUS:
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
			std::vector<char> buf(8);
			do {
				if (buf.size() >= Token::MAX_VALUE_LENGTH)
					throw std::overflow_error(
						"The token's value's length is trying to exceed over Token::MAX_VALUE_LENGTH.");
				buf.push_back(this->current());
				this->advance();
			} while (this->current() == '_' || std::isdigit(this->current()) ||
				 std::isalpha(this->current()));
			buf.shrink_to_fit();
		} else if (std::isdigit(this->current())) {
			
		} else {
			
		}
	}
	return token;
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
