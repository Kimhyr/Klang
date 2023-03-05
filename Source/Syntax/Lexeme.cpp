#include "Lexeme.h"

namespace Klang {

C const* to_string(Lexeme_Tag tag) {
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
	case Lexeme::DOT:	return Lexeme::String::DOT;
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

std::ostream& operator<<(std::ostream& os, Klang::Lexeme const& lexeme) {
	using namespace Klang;
	os << "Token " << to_string(lexeme.tag);
	switch (lexeme.tag) {
	case Lexeme::NAME:	os << ' ' << Lexeme::String::NAME << ' ' << lexeme.value.Name; break;
	case Lexeme::NATURAL:	os << ' ' << Lexeme::String::NATURAL << ' ' << lexeme.value.Natural; break;
	case Lexeme::REAL:	os << ' ' << Lexeme::String::REAL << ' ' << lexeme.value.Real; break;
	case Lexeme::STRING:	os << ' ' << Lexeme::String::STRING << ' ' << lexeme.value.String; break;
	default: break;
	}
	return os;
}
