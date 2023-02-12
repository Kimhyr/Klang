#include "Lexer.h"

namespace Klang {

// `file` is already validated.
Lexer::Lexer(const char* file)
	: _source(file), _position(1, 0) {
	this->_current = this->_source.get();
}

void Lexer::load(const char* path) {
	this->_source.close();
	this->_source.open(path);
	this->_current = this->_source.get();
	this->_position.row = 1;
	this->_position.column = 0;
}

void Lexer::lex(Token& token) {
	while (std::isspace(this->current()))
		this->advance();
	token.start = this->position();
	switch (static_cast<TokenTag>(this->current())) {
	case TokenTag::SLOSH:
		do this->advance();
		while (this->current() != '\n');
		token.tag = TokenTag::COMMENT;
		break;
	case TokenTag::PLUS:
	case TokenTag::MINUS:
	case TokenTag::COLON:
	case TokenTag::SEMICOLON:
	case TokenTag::EQUAL:
	case TokenTag::ASTERISKS:
	case TokenTag::SLASH:
	case TokenTag::PERCENT:
	case TokenTag::OPAREN:
	case TokenTag::CPAREN:
		token.tag = static_cast<TokenTag>(this->current());
		this->advance();
		break;
	default:
		if (std::isalpha(this->current())) {
			Bucket<char, Token::MAX_VALUE_LENGTH + 1> bucket;
			do {
				if (bucket.weight() >= Token::MAX_VALUE_LENGTH)
					throw std::overflow_error(__FUNCTION__);
				bucket.put(this->current());
				this->advance();
			} while (this->current() == '_' || std::isdigit(this->current()) ||
				 std::isalpha(this->current()));
			bucket.put('\0');
			if (std::string("object") == bucket.water())
				token.tag = TokenTag::OBJECT;
			else if (std::string("Int") == bucket.water())
				token.tag = TokenTag::INT;
			else {
				token.value = bucket.flush();
				token.tag = TokenTag::NAME;
			}
		} else if (std::isdigit(this->current())) {
			Bucket<char, Token::MAX_VALUE_LENGTH + 1> bucket;
			do {
				if (bucket.weight() >= Token::MAX_VALUE_LENGTH)
					throw std::overflow_error(__FUNCTION__);
				if (this->current() != '_')
					bucket.put(this->current());
				this->advance();
			} while (this->current() == '_' || std::isdigit(this->current()));
			bucket.put('\0');
			token.value = bucket.flush();
			token.tag = TokenTag::NATURAL;
		} else if (this->_source.eof())
			token.tag = TokenTag::EOT;
		else {
			token.tag = TokenTag::UNDEFINED;
			this->advance();
		}
	}
	token.end = this->position();
	--token.end.column;
}

char Lexer::peek() {
	int peek {this->_source.peek()};
	if (peek == EOF)
		throw std::out_of_range(__FUNCTION__);
	return peek;
}

void Lexer::advance() {
	if (!this->source().good())
		throw std::invalid_argument(__FUNCTION__);
	this->_current = this->_source.get();
	if (this->current() == '\n') {
		++this->_position.row;
		this->_position.column = 0;
	}
	++this->_position.column;
}

}
