#include "Tokens.h"

std::ostream& operator<<(std::ostream& os, const Klang::Token& token) {
	os << "Token ";
	switch (token.tag) {
	case Klang::Token_Tag::UNDEFINED: os << "UNDEFINED";
	case Klang::Token_Tag::NAME: os << "NAME" << ' ' << token.value.Name; break;
	case Klang::Token_Tag::MACHINE_LITERAL: os << "MACHINE_LITERAL" << ' ' << token.value.Machine; break;
	case Klang::Token_Tag::NATURAL_LITERAL: os << "NATURAL_LITERAL" << ' ' << token.value.Natural; break;
	case Klang::Token_Tag::INTEGER_LITERAL: os << "INTEGER_LITERAL" << ' ' << token.value.Integer; break;
	case Klang::Token_Tag::REAL_LITERAL: os << "REAL_LITERAL" << ' ' << token.value.Real; break;
	case Klang::Token_Tag::TEXT_LITERAL: os << "TEXT_LITERAL" << ' ' << token.value.Text; break;
	case Klang::Token_Tag::PTR: os << "PTR"; break;
	case Klang::Token_Tag::NAT: os << "NAT"; break;
	case Klang::Token_Tag::NAT8: os << "NAT8"; break;
	case Klang::Token_Tag::NAT16: os << "NAT16"; break;
	case Klang::Token_Tag::NAT32: os << "NAT32"; break;
	case Klang::Token_Tag::NAT64: os << "NAT64"; break;
	case Klang::Token_Tag::INT: os << "INT"; break;
	case Klang::Token_Tag::INT8: os << "INT8"; break;
	case Klang::Token_Tag::INT16: os << "INT16"; break;
	case Klang::Token_Tag::INT32: os << "INT32"; break;
	case Klang::Token_Tag::INT64: os << "INT64"; break;
	case Klang::Token_Tag::REAL: os << "REAL"; break;
	case Klang::Token_Tag::REAL32: os << "REAL32"; break;
	case Klang::Token_Tag::REAL64: os << "REAL64"; break;
	case Klang::Token_Tag::COMMENT: os << "COMMENT"; break;
	case Klang::Token_Tag::OBJECT: os << "OBJECT"; break;
	case Klang::Token_Tag::EOT: os << "EOT"; break;
	case Klang::Token_Tag::SLOSH: os << "SLOSH"; break;
	case Klang::Token_Tag::COLON: os << "COLON"; break;
	case Klang::Token_Tag::SEMICOLON: os << "SEMICOLON"; break;
	case Klang::Token_Tag::EQUAL: os << "EQUAL"; break;
	case Klang::Token_Tag::PLUS: os << "PLUS"; break;
	case Klang::Token_Tag::MINUS: os << "MINUS"; break;
	case Klang::Token_Tag::ASTERISKS: os << "ASTERISKS"; break;
	case Klang::Token_Tag::SLASH: os << "SLASH"; break;
	case Klang::Token_Tag::PERCENT: os << "PERCENT"; break;
	case Klang::Token_Tag::OPAREN: os << "OPAREN"; break;
	case Klang::Token_Tag::CPAREN: os << "CPAREN"; break;
	}
	return os;
}
