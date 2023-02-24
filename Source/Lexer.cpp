#include "Lexer.h"

#include <vector>

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
Restart:
	while (std::isspace(this->current()))
		this->advance();
	token.start = this->position();
	switch (static_cast<Token_Tag>(this->current())) {
	case Token_Tag::QUOTE: this->lex_text(token); break;
	case Token_Tag::SLOSH:
		if (this->peek() == '"') {
			this->lex_text(token, true);
			break;
		}
		do {
			this->advance();
			if (this->source().eof())
				break;
		} while (this->current() != '\n');
		goto Restart;
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
			if (std::string_view("object") == bucket.water())
				token.tag = Token_Tag::OBJECT;
			else if (std::string_view("Int") == bucket.water())
				token.tag = Token_Tag::INT;
			else {
				token.value.Name = bucket.flush();
				token.tag = Token_Tag::NAME;
			}
		} else if (std::isdigit(this->current())) {
			token.tag = Token_Tag::NATURAL_LITERAL;
			this->lex_numeric(token);
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

void Lexer::lex_text(Token& token, bool is_escaped) {
	std::vector<char> text;
	do {
		char c = this->current();
		if (this->current() == '\\' && is_escaped) {
			this->advance();
			switch (this->current()) {
			case 'a':
			case 'b':
			case 'f':
			case 'n':
			case 'r':
			case 't':
			case 'v':
			case 'e':
			case '"':
			case '?':
			case '\\':
			case 'o': // Octal
			case 'x': // Hexadecimal
			case 'u': // Unicode
			case 'N': // Character named by name
			case 'B': // Binary
			default: c = this->current(); break;
			}
		}
		text.push_back(c);
		this->advance();
	} while (this->current() != '"');
	if (text.empty())
		throw std::invalid_argument(__FUNCTION__);
	token.tag = Token_Tag::TEXT_LITERAL;
	
}

void Lexer::lex_numeric(Token& token) {
	Bucket<char, Token::MAX_VALUE_LENGTH + 1> bucket;
	do {
		if (bucket.weight() >= Token::MAX_VALUE_LENGTH)
			throw std::overflow_error(__FUNCTION__);
		if (this->current() == '.') {
			if (token.tag == Token_Tag::REAL_LITERAL)
				throw std::invalid_argument(__FUNCTION__);
			else token.tag = Token_Tag::REAL_LITERAL;
		}
		if (this->current() != '_')
			bucket.put(this->current());
		this->advance();
	} while (this->current() == '_' || std::isdigit(this->current()));
	bucket.put('\0');
	std::stringstream ss(bucket.water());
	if (token.tag == Token_Tag::NATURAL_LITERAL)
		ss >> token.value.Natural;
	else ss >> token.value.Real;
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
