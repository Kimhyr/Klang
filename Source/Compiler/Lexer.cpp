#include "Lexer.h"

#include <sstream>
#include <algorithm>

namespace Klang {

// `file` is already validated.
Lexer::Lexer(char const* file)
	: source_(file), position_(1, 0) {
	this->current_ = this->source_.get();
}

void Lexer::load(char const* path) {
	this->source_.close();
	this->source_.open(path);
	this->current_ = this->source_.get();
	this->position_.row = 1;
	this->position_.column = 0;
}

Lexeme Lexer::lex() {
Restart:
	while (std::isspace(this->current()))
		this->advance();
	this->lexeme_.start = this->position();
	nat8 tag = Lexeme::NAME;
	switch (static_cast<Lexeme::Tag>(this->current())) {
	case Lexeme::SLOSH:
		do {
			this->advance();
			if (this->source().eof())
				goto Return_EOT;
		} while (this->current() != '\n');
		goto Restart;
	case Lexeme::PLUS:
	case Lexeme::MINUS:
	case Lexeme::COLON:
	case Lexeme::SEMICOLON:
	case Lexeme::EQUAL:
	case Lexeme::ASTERISKS:
	case Lexeme::SLASH:
	case Lexeme::PERCENT:
	case Lexeme::OPAREN:
	case Lexeme::CPAREN:
		tag = static_cast<Lexeme::Tag>(this->current());
		this->advance();
		break;
	default:
		if (std::isalpha(this->current())) {
			std::stringbuf buf;
			do {
				if (buf.view().length() >= Lexeme::MAX_VALUE_LENGTH)
					throw std::overflow_error(__FUNCTION__);
				buf.sputc(this->current());
				this->advance();
			} while (this->current() == '_' || std::isdigit(this->current()) ||
				 std::isalpha(this->current()));
			natptr len = buf.view().length();
			if (len >= 1 && len <= 3) {
				buf.sputc(0);
				switch (buf.view()[0]) {
				case 'P': tag = Lexeme::P; break;
				case 'N': tag = Lexeme::N; break;
				case 'I': tag = Lexeme::I; break;
				case 'R': tag = Lexeme::R; break;
				default: goto Lex_Name;
				}
				if (len == 1)
					goto Finalize;
				switch (buf.view()[1] + buf.view()[2]) {
				case '6' + '4': tag += 1;
				case '3' + '2': tag += 2;
				case '1' + '6': tag += 3;
				case '8':	tag += 4;
				default: goto Lex_Name;
				}
			}
			if (buf.view() == Lexeme::OBJECT_KEYWORD)
				tag = Lexeme::OBJECT;
			else {
				buf.sputc('\0');
			Lex_Name:
				std::copy(buf.view().begin(), buf.view().end(),
					this->lexeme_.value.Name);
			}
		} else if (std::isdigit(this->current())) {
			tag = Lexeme::BINARY;
			this->lex_numeric();
		} else if (this->source_.eof())
		Return_EOT:
			tag = Lexeme::EOT;
		else {
			tag = Lexeme::UNDEFINED;
			this->advance();
		}
	}
Finalize:
	this->lexeme_.tag = static_cast<Lexeme::Tag>(tag);
	this->lexeme_.end = this->position();
	--this->lexeme_.end.column;
	return this->lexeme_;
}

void Lexer::lex_numeric() {
	std::stringstream ss;
	do {
		if (ss.view().length() >= Lexeme::MAX_VALUE_LENGTH)
			throw std::overflow_error(__FUNCTION__);
		if (this->current() == '.') {
			if (this->lexeme_.tag == Lexeme::FLOAT)
				throw std::invalid_argument(__FUNCTION__);
			else this->lexeme_.tag = Lexeme::FLOAT;
		}
		if (this->current() != '_')
			ss.put(this->current());
		this->advance();
	} while (this->current() == '_' || std::isdigit(this->current()));
	ss.put('\0');
	if (this->lexeme_.tag == Lexeme::BINARY)
		ss >> this->lexeme_.value.Natural;
	else ss >> this->lexeme_.value.Float;
}

char Lexer::peek() {
	int peek {this->source_.peek()};
	if (peek == EOF)
		throw std::out_of_range(__FUNCTION__);
	return peek;
}

void Lexer::advance() {
	if (!this->source().good())
		throw std::invalid_argument(__FUNCTION__);
	this->current_ = this->source_.get();
	if (this->current() == '\n') {
		++this->position_.row;
		this->position_.column = 0;
	}
	++this->position_.column;
}

}

