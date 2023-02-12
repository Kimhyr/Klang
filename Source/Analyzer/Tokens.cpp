#include "Tokens.h"

std::ostream& operator<<(std::ostream& os, Klang::TokenTag tag) {
	std::cout << "Klang::TokenTag::";
	switch (tag) {
	case Klang::TokenTag::UNDEFINED: std::cout << "UNDEFINED"; break;
	case Klang::TokenTag::NAME: std::cout << "NAME"; break;
	case Klang::TokenTag::NATURAL: std::cout << "NATURAL"; break;
	case Klang::TokenTag::INTEGER: std::cout << "INTEGER"; break;
	case Klang::TokenTag::FLOAT: std::cout << "FLOAT"; break;
	case Klang::TokenTag::TEXT: std::cout << "TEXT"; break;
	case Klang::TokenTag::PTR: std::cout << "PTR"; break;
	case Klang::TokenTag::NAT: std::cout << "NAT"; break;
	case Klang::TokenTag::NAT8: std::cout << "NAT8"; break;
	case Klang::TokenTag::NAT16: std::cout << "NAT16"; break;
	case Klang::TokenTag::NAT32: std::cout << "NAT32"; break;
	case Klang::TokenTag::NAT64: std::cout << "NAT64"; break;
	case Klang::TokenTag::INT: std::cout << "INT"; break;
	case Klang::TokenTag::INT8: std::cout << "INT8"; break;
	case Klang::TokenTag::INT16: std::cout << "INT16"; break;
	case Klang::TokenTag::INT32: std::cout << "INT32"; break;
	case Klang::TokenTag::INT64: std::cout << "INT64"; break;
	case Klang::TokenTag::REAL: std::cout << "REAL"; break;
	case Klang::TokenTag::REAL32: std::cout << "REAL32"; break;
	case Klang::TokenTag::REAL64: std::cout << "REAL64"; break;
	case Klang::TokenTag::COMMENT: std::cout << "COMMENT"; break;
	case Klang::TokenTag::OBJECT: std::cout << "OBJECT"; break;
	case Klang::TokenTag::EOT: std::cout << "EOT"; break;
	case Klang::TokenTag::COLON: std::cout << "COLON"; break;
	case Klang::TokenTag::SEMICOLON: std::cout << "SEMICOLON"; break;
	case Klang::TokenTag::EQUAL: std::cout << "EQUAL"; break;
	case Klang::TokenTag::PLUS: std::cout << "PLUS"; break;
	case Klang::TokenTag::MINUS: std::cout << "MINUS"; break;
	case Klang::TokenTag::ASTERISKS: std::cout << "ASTERISKS"; break;
	case Klang::TokenTag::SLASH: std::cout << "SLASH"; break;
	case Klang::TokenTag::SLOSH: std::cout << "SLOSH"; break;
	case Klang::TokenTag::PERCENT: std::cout << "PERCENT"; break;
	case Klang::TokenTag::OPAREN: std::cout << "OPAREN"; break;
	case Klang::TokenTag::CPAREN: std::cout << "CPAREN"; break;
	}
	return os;
}
