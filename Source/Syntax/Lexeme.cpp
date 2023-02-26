#include "Lexeme.h"

std::ostream& operator<<(std::ostream& os, const Klang::Lexeme& token) {
	os << "Token ";
	switch (token.tag) {
	case Klang::Lexeme::UNDEFINED: os << "UNDEFINED";
	case Klang::Lexeme::NAME: os << "NAME" << ' ' << token.value.Name; break;
	case Klang::Lexeme::NATURAL: os << "NATURAL" << ' ' << token.value.Natural; break;
	case Klang::Lexeme::FLOAT: os << "FLOAT" << ' ' << token.value.Float; break;
	case Klang::Lexeme::STRING: os << "STRING" << ' ' << token.value.String; break;
	case Klang::Lexeme::PTR: os << "PTR"; break;
	case Klang::Lexeme::NAT: os << "NAT"; break;
	case Klang::Lexeme::NAT8: os << "NAT8"; break;
	case Klang::Lexeme::NAT16: os << "NAT16"; break;
	case Klang::Lexeme::NAT32: os << "NAT32"; break;
	case Klang::Lexeme::NAT64: os << "NAT64"; break;
	case Klang::Lexeme::INT: os << "INT"; break;
	case Klang::Lexeme::INT8: os << "INT8"; break;
	case Klang::Lexeme::INT16: os << "INT16"; break;
	case Klang::Lexeme::INT32: os << "INT32"; break;
	case Klang::Lexeme::INT64: os << "INT64"; break;
	case Klang::Lexeme::REAL: os << "REAL"; break;
	case Klang::Lexeme::REAL32: os << "REAL32"; break;
	case Klang::Lexeme::REAL64: os << "REAL64"; break;
	case Klang::Lexeme::OBJECT: os << "OBJECT"; break;
	case Klang::Lexeme::EOT: os << "EOT"; break;
	case Klang::Lexeme::SLOSH: os << "SLOSH"; break;
	case Klang::Lexeme::COLON: os << "COLON"; break;
	case Klang::Lexeme::SEMICOLON: os << "SEMICOLON"; break;
	case Klang::Lexeme::EQUAL: os << "EQUAL"; break;
	case Klang::Lexeme::PLUS: os << "PLUS"; break;
	case Klang::Lexeme::MINUS: os << "MINUS"; break;
	case Klang::Lexeme::ASTERISKS: os << "ASTERISKS"; break;
	case Klang::Lexeme::SLASH: os << "SLASH"; break;
	case Klang::Lexeme::PERCENT: os << "PERCENT"; break;
	case Klang::Lexeme::OPAREN: os << "OPAREN"; break;
	case Klang::Lexeme::CPAREN: os << "CPAREN"; break;
	}
	return os;
}
