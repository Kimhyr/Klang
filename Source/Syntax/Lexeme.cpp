#include "Lexeme.h"

std::ostream& operator<<(std::ostream& os, const Klang::Lexeme& token) {
	using namespace Klang;
	os << "Token ";
	switch (token.tag) {
	case Lexeme::UNDEFINED: os << "UNDEFINED"; break;
	case Lexeme::NAME: os << "NAME " << token.value.Name; break;

	case Lexeme::NATURAL: os << "NATURAL " << token.value.Natural; break;
	case Lexeme::REAL: os << "REAL " << token.value.Real; break;
	case Lexeme::STRING: os << "STRING " << token.value.String; break;

	case Lexeme::P: os << "P"; break;
	case Lexeme::N: os << "N"; break;
	case Lexeme::N64: os << "N64"; break;
	case Lexeme::N32: os << "N32"; break;
	case Lexeme::N16: os << "N16"; break;
	case Lexeme::N8: os << "N8"; break;
	case Lexeme::I: os << "I"; break;
	case Lexeme::I64: os << "I64"; break;
	case Lexeme::I32: os << "I32"; break;
	case Lexeme::I16: os << "I16"; break;
	case Lexeme::I8: os << "I8"; break;
	case Lexeme::R: os << "R"; break;
	case Lexeme::R64: os << "R64"; break;
	case Lexeme::R32: os << "R32"; break;
	
	case Lexeme::OBJECT: os << "OBJECT"; break;
	
	case Lexeme::EOT: os << "EOT"; break;
	case Lexeme::SLOSH: os << "SLOSH"; break;
	case Lexeme::COLON: os << "COLON"; break;
	case Lexeme::SEMICOLON: os << "SEMICOLON"; break;
	case Lexeme::EQUAL: os << "EQUAL"; break;
	case Lexeme::PLUS: os << "PLUS"; break;
	case Lexeme::MINUS: os << "MINUS"; break;
	case Lexeme::ASTERISKS: os << "ASTERISKS"; break;
	case Lexeme::SLASH: os << "SLASH"; break;
	case Lexeme::PERCENT: os << "PERCENT"; break;
	case Lexeme::O_PAREN: os << "O_PAREN"; break;
	case Lexeme::C_PAREN: os << "C_PAREN"; break;
	}
	return os;
}
