#include "Lexeme.h"

namespace Klang {

S const* Lexeme::tag_to_string(Tag tag) {
	switch (tag) {
	case Lexeme::UNDEFINED:	return Lexeme::String::UNDEFINED;
	case Lexeme::NAME:	return Lexeme::String::NAME;
	case Lexeme::NATURAL:	return Lexeme::String::NATURAL;
	case Lexeme::REAL:	return Lexeme::String::REAL;
	case Lexeme::STRING:	return Lexeme::String::STRING;
	case Lexeme::P:		return Lexeme::String::P;
	case Lexeme::N:		return Lexeme::String::N;
	case Lexeme::N64:	return Lexeme::String::N64;
	case Lexeme::N32:	return Lexeme::String::N32;
	case Lexeme::N16:	return Lexeme::String::N16;
	case Lexeme::N8:	return Lexeme::String::N8;
	case Lexeme::I:		return Lexeme::String::I;
	case Lexeme::I64:	return Lexeme::String::I64;
	case Lexeme::I32:	return Lexeme::String::I32;
	case Lexeme::I16:	return Lexeme::String::I16;
	case Lexeme::I8:	return Lexeme::String::I8;
	case Lexeme::R:		return Lexeme::String::R;
	case Lexeme::R64:	return Lexeme::String::R64;
	case Lexeme::R32:	return Lexeme::String::R32;
	case Lexeme::OBJECT:	return Lexeme::String::OBJECT;
	case Lexeme::EOT:	return Lexeme::String::EOT;
	case Lexeme::SLOSH:	return Lexeme::String::SLOSH;
	case Lexeme::COLON:	return Lexeme::String::COLON;
	case Lexeme::SEMICOLON:	return Lexeme::String::SEMICOLON;
	case Lexeme::EQUAL:	return Lexeme::String::EQUAL;
	case Lexeme::PLUS:	return Lexeme::String::PLUS;
	case Lexeme::MINUS:	return Lexeme::String::MINUS;
	case Lexeme::ASTERISKS:	return Lexeme::String::ASTERISKS;
	case Lexeme::SLASH:	return Lexeme::String::SLASH;
	case Lexeme::PERCENT:	return Lexeme::String::PERCENT;
	case Lexeme::O_PAREN:	return Lexeme::String::O_PAREN;
	case Lexeme::C_PAREN:	return Lexeme::String::C_PAREN;
	}
}

}

std::ostream& operator<<(std::ostream& os, const Klang::Lexeme& token) {
	using namespace Klang;
	os << "Token ";
	switch (token.tag) {
	case Lexeme::UNDEFINED:	os << Lexeme::String::UNDEFINED; break;
	case Lexeme::NAME:	os << Lexeme::String::NAME << ' ' << token.value.Name; break;
	case Lexeme::NATURAL:	os << Lexeme::String::NATURAL << ' ' << token.value.Natural; break;
	case Lexeme::REAL:	os << Lexeme::String::REAL << ' ' << token.value.Real; break;
	case Lexeme::STRING:	os << Lexeme::String::STRING << ' ' << token.value.String; break;
	case Lexeme::P:		os << Lexeme::String::P; break;
	case Lexeme::N:		os << Lexeme::String::N; break;
	case Lexeme::N64:	os << Lexeme::String::N64; break;
	case Lexeme::N32:	os << Lexeme::String::N32; break;
	case Lexeme::N16:	os << Lexeme::String::N16; break;
	case Lexeme::N8:	os << Lexeme::String::N8; break;
	case Lexeme::I:		os << Lexeme::String::I; break;
	case Lexeme::I64:	os << Lexeme::String::I64; break;
	case Lexeme::I32:	os << Lexeme::String::I32; break;
	case Lexeme::I16:	os << Lexeme::String::I16; break;
	case Lexeme::I8:	os << Lexeme::String::I8; break;
	case Lexeme::R:		os << Lexeme::String::R; break;
	case Lexeme::R64:	os << Lexeme::String::R64; break;
	case Lexeme::R32:	os << Lexeme::String::R32; break;
	case Lexeme::OBJECT:	os << Lexeme::String::OBJECT; break;
	case Lexeme::EOT:	os << Lexeme::String::EOT; break;
	case Lexeme::SLOSH:	os << Lexeme::String::SLOSH; break;
	case Lexeme::COLON:	os << Lexeme::String::COLON; break;
	case Lexeme::SEMICOLON:	os << Lexeme::String::SEMICOLON; break;
	case Lexeme::EQUAL:	os << Lexeme::String::EQUAL; break;
	case Lexeme::PLUS:	os << Lexeme::String::PLUS; break;
	case Lexeme::MINUS:	os << Lexeme::String::MINUS; break;
	case Lexeme::ASTERISKS:	os << Lexeme::String::ASTERISKS; break;
	case Lexeme::SLASH:	os << Lexeme::String::SLASH; break;
	case Lexeme::PERCENT:	os << Lexeme::String::PERCENT; break;
	case Lexeme::O_PAREN:	os << Lexeme::String::O_PAREN; break;
	case Lexeme::C_PAREN:	os << Lexeme::String::C_PAREN; break;
	}
	return os;
}
