#include "Lexer.h"

namespace Klang {

Lexer::Lexer(C const* file)
	: source_(file), position_({.row = 1, .column = 0}) {
	if (!this->source_.good())
		throw diagnose(Severity::ERROR, "File could not open.");
	this->current_ = this->source_.get();
}

Lexer::Lexer(std::ifstream&& file)
	: source_(std::move(file)), position_({.row = 1, .column = 0}) {
	this->current_ = this->source_.get();
}

V Lexer::load(C const* path) {
	this->source_.close();
	this->source_.open(path);
	this->current_ = this->source_.get();
	this->position_.row = 1;
	this->position_.column = 0;
}

V Lexer::lex(Lexeme& out) {
Restart:
	while (std::isspace(this->current()))
		this->advance();
	out.start = this->position();
	I8 tag;
	if (this->source_.eof()) {
	Return_EOT:
		tag = Lexeme::EOT;
		goto Finalize;
	}
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
	case Lexeme::ASTERISK:
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
					throw diagnose(Severity::ERROR, out.start, buf.view(),
						       Message::BUFFER_OVERFLOW("lex an identifier."));
				buf.sputc(this->current());
				this->advance();
			} while (this->current() == '_' || std::isdigit(this->current()) ||
				 std::isalpha(this->current()));
			N len = buf.view().length();
			if (buf.view() == Lexeme::String::LITERAL_OBJECT)
				tag = Lexeme::OBJECT;
			else {
				buf.sputc('\0');
				// NOTE: There's probably a bitwise formula to elegantly compute this.
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
				out.value.String = buf.view();
				goto Finalize;
			}
		} else if (std::isdigit(this->current())) {
			tag = Lexeme::NATURAL;
			std::stringstream ss;
			do {
				if (ss.view().length() >= Lexeme::MAX_VALUE_LENGTH)
					throw diagnose(Severity::ERROR, Message::BUFFER_OVERFLOW("lex a number."));
				if (this->current() == '.') {
					if (out.tag == Lexeme::REAL)
						throw diagnose(
							Severity::ERROR, out.start, ss.view(),
							Message::LEX_FAILED(Lexeme::REAL, "it has more than 1 `.` (dot lexeme)."));
					else out.tag = Lexeme::REAL;
				}
				if (this->current() != '_')
					ss.put(this->current());
				this->advance();
			} while (this->current() == '_' || std::isdigit(this->current()));
			if (tag == Lexeme::NATURAL)
				ss >> out.value.Natural;
			else ss >> out.value.Real;
		} else {
			this->advance();
			throw diagnose(Severity::ERROR, out.start,
				       Message::UNKNOWN_TOKEN(this->current()));
		}
	}
Finalize:
	out.tag = static_cast<Lexeme::Tag>(tag);
	out.end = this->position();
	--out.end.column;
}

V Lexer::advance() {
	if (!this->source().good())
		throw diagnose(Severity::ERROR, "The source is not good.");
	this->current_ = this->source_.get();
	if (this->current() == '\r' && this->peek() == '\n') {
		++this->position_.row;
		this->position_.column = 0;
	}
	++this->position_.column;
}

}

