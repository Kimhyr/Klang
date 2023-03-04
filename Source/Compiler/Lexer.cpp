#include "Lexer.h"

namespace Klang {

Lexer::Lexer(S const* file)
	: source_(file), position_({.row = 1, .column = 0}) {
	this->current_ = this->source_.get();
}

void Lexer::load(S const* path) {
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
	I8 tag;
	switch (this->current()) {
	case Lexeme::SLOSH:
		if (this->peek() == '\\') {
			do {
				this->advance();
				if (this->source().eof())
					goto Return_EOT;
			} while (this->current() != '\n');
			goto Restart;
		}
	case Lexeme::PLUS:
	case Lexeme::MINUS:
	case Lexeme::COLON:
	case Lexeme::SEMICOLON:
	case Lexeme::EQUAL:
	case Lexeme::ASTERISKS:
	case Lexeme::SLASH:
	case Lexeme::PERCENT:
	case Lexeme::O_PAREN:
	case Lexeme::C_PAREN:
		tag = this->current();
		this->advance();
		break;
	default:
		if (std::isalpha(this->current())) {
			std::stringbuf buf;
			do {
				if (buf.view().length() >= Lexeme::MAX_VALUE_LENGTH)
					throw diagnose(Severity::ERROR, Message::BUFFER_OVERFLOW);
				buf.sputc(this->current());
				this->advance();
			} while (this->current() == '_' || std::isdigit(this->current()) ||
				 std::isalpha(this->current()));
			N len = buf.view().length();
			if (buf.view() == Lexeme::OBJECT_KEYWORD)
				tag = Lexeme::OBJECT;
			else {
				buf.sputc('\0');
				// NOTE: There's probably a bitwise formula to compute this elegantly.
				if (len >= 1 && len <= 3) {
					switch (buf.view()[0]) {
					case 'P': tag = Lexeme::P; break;
					case 'N': tag = Lexeme::N; break;
					case 'I': tag = Lexeme::I; break;
					case 'R': tag = Lexeme::R; break;
					default: goto Lex_Name;
					}
					if (buf.view()[1] == '\0')
						goto Finalize;
					switch (buf.view()[1] + buf.view()[2]) {
					if (tag != Lexeme::R) {
						case '8': tag += 4; break;
						case '1' + '6': tag += 3; break;
					}
					case '3' + '2': tag += 2; break;
					case '6' + '4': tag += 1; break;
					default: goto Lex_Name;
					}
					break;
				}
			Lex_Name:
				tag = Lexeme::NAME;
				// TODO: Instead of `std::stringbuf`, create a buffer that allows us to
				// take ownership of the underlying string.
				this->lexeme_.value.Name = new S[buf.view().length()];
				std::copy(buf.view().begin(), buf.view().end(),
					this->lexeme_.value.Name);
				goto Finalize;
			}
		} else if (std::isdigit(this->current())) {
			tag = Lexeme::NATURAL;
			std::stringstream ss;
			do {
				if (ss.view().length() >= Lexeme::MAX_VALUE_LENGTH)
					throw diagnose(Severity::ERROR, Message::BUFFER_OVERFLOW);
				if (this->current() == '.') {
					if (this->lexeme_.tag == Lexeme::REAL)
						throw diagnose(Severity::ERROR, Message::UNKNOWN_TOKEN);
					else this->lexeme_.tag = Lexeme::REAL;
				}
				if (this->current() != '_')
					ss.put(this->current());
				this->advance();
			} while (this->current() == '_' || std::isdigit(this->current()));
			if (tag == Lexeme::NATURAL)
				ss >> this->lexeme_.value.Natural;
			else ss >> this->lexeme_.value.Real;
		} else if (this->source_.eof())
		Return_EOT:
			tag = Lexeme::EOT;
		else {
			this->advance();
			throw diagnose(Severity::ERROR, Message::UNKNOWN_TOKEN);
		}
	}
Finalize:
	this->lexeme_.tag = static_cast<Lexeme::Tag>(tag);
	this->lexeme_.end = this->position();
	--this->lexeme_.end.column;
	return this->lexeme_;
}

char Lexer::peek() {
	I32 peek {this->source_.peek()};
	if (peek == EOF)
		throw std::out_of_range("Fialed to peek.");
	return peek;
}

void Lexer::advance() {
	if (!this->source().good())
		throw std::invalid_argument("The source is not good.");
	this->current_ = this->source_.get();
	if (this->current() == '\n') {
		++this->position_.row;
		this->position_.column = 0;
	}
	++this->position_.column;
}

}

