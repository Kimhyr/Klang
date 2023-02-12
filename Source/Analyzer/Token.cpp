#include "Token.h"

std::ostream& operator<<(std::ostream& os, const Klang::Token& token) {
	os << "Token ";
	switch (token.tag) {
	case Klang::TokenTag::UNDEFINED: os << "UNDEFINED";
	case Klang::TokenTag::NAME: os << "NAME" << ' ' << token.value; break;
	case Klang::TokenTag::NATURAL: os << "NATURAL" << ' ' << token.value; break;
	case Klang::TokenTag::FLOAT: os << "FLOAT" << ' ' << token.value; break;
	case Klang::TokenTag::TEXT: os << "TEXT" << ' ' << token.value; break;
	case Klang::TokenTag::PTR: os << "PTR"; break;
	case Klang::TokenTag::NAT: os << "NAT"; break;
	case Klang::TokenTag::NAT8: os << "NAT8"; break;
	case Klang::TokenTag::NAT16: os << "NAT16"; break;
	case Klang::TokenTag::NAT32: os << "NAT32"; break;
	case Klang::TokenTag::NAT64: os << "NAT64"; break;
	case Klang::TokenTag::INT: os << "INT"; break;
	case Klang::TokenTag::INT8: os << "INT8"; break;
	case Klang::TokenTag::INT16: os << "INT16"; break;
	case Klang::TokenTag::INT32: os << "INT32"; break;
	case Klang::TokenTag::INT64: os << "INT64"; break;
	case Klang::TokenTag::REAL: os << "REAL"; break;
	case Klang::TokenTag::REAL32: os << "REAL32"; break;
	case Klang::TokenTag::REAL64: os << "REAL64"; break;
	case Klang::TokenTag::COMMENT: os << "COMMENT"; break;
	case Klang::TokenTag::OBJECT: os << "OBJECT"; break;
	case Klang::TokenTag::EOT: os << "EOT"; break;
	case Klang::TokenTag::SLOSH: os << "SLOSH"; break;
	case Klang::TokenTag::COLON: os << "COLON"; break;
	case Klang::TokenTag::SEMICOLON: os << "SEMICOLON"; break;
	case Klang::TokenTag::EQUAL: os << "EQUAL"; break;
	case Klang::TokenTag::PLUS: os << "PLUS"; break;
	case Klang::TokenTag::MINUS: os << "MINUS"; break;
	case Klang::TokenTag::ASTERISKS: os << "ASTERISKS"; break;
	case Klang::TokenTag::SLASH: os << "SLASH"; break;
	case Klang::TokenTag::PERCENT: os << "PERCENT"; break;
	case Klang::TokenTag::OPAREN: os << "OPAREN"; break;
	case Klang::TokenTag::CPAREN: os << "CPAREN"; break;
	}
	return os;
}
