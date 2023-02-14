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
	switch (static_cast<Token_Tag>(this->current())) {
	case Token_Tag::SLOSH:
		do this->advance();
		while (this->current() != '\n');
		token.tag = Token_Tag::COMMENT;
		break;
	case Token_Tag::PLUS:
	case Token_Tag::MINUS:
	case Token_Tag::COLON:
	case Token_Tag::SEMICOLON:
	case Token_Tag::EQUAL:
	case Token_Tag::ASTERISKS:
	case Token_Tag::SLASH:
	case Token_Tag::PERCENT:
	case Token_Tag::OPAREN:
	case Token_Tag::CPAREN:
		token.tag = static_cast<Token_Tag>(this->current());
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
				token.tag = Token_Tag::OBJECT;
			else if (std::string("Int") == bucket.water())
				token.tag = Token_Tag::INT;
			else {
				token.value = bucket.flush();
				token.tag = Token_Tag::NAME;
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
			token.tag = Token_Tag::NATURAL;
		} else if (this->_source.eof())
			token.tag = Token_Tag::EOT;
		else {
			token.tag = Token_Tag::UNDEFINED;
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
