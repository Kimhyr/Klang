#include "Token.h"

namespace Klang {

}

std::ostream& operator<<(std::ostream& os, Klang::TokenKind kind) {
	const char*  str;
	os << "TokenKind::";
	switch (kind) {
	case Klang::TokenKind::NAME: str = "NAME"; break; 
	case Klang::TokenKind::COMMENT: str = "COMMENT"; break; 
	case Klang::TokenKind::NATURAL: str = "NATURAL"; break; 
	case Klang::TokenKind::INTEGER: str = "INTEGER"; break; 
	case Klang::TokenKind::EOT: str = "EOT"; break; 
	case Klang::TokenKind::COLON: str = "COLON"; break; 
	case Klang::TokenKind::SEMICOLON: str = "SEMICOLON"; break; 
	case Klang::TokenKind::EQUAL: str = "EQUAL"; break; 
	case Klang::TokenKind::PLUS: str = "PLUS"; break; 
	case Klang::TokenKind::MINUS: str = "MINUS"; break; 
	case Klang::TokenKind::ASTERISKS: str = "ASTERISKS"; break; 
	case Klang::TokenKind::SLASH: str = "SLASH"; break; 
	case Klang::TokenKind::SLOSH: str = "SLOSH"; break; 
	case Klang::TokenKind::PERCENT: str = "PERCENT"; break; 
	case Klang::TokenKind::OPAREN: str = "OPAREN"; break; 
	case Klang::TokenKind::CPAREN: str = "CPAREN"; break; 
	}
	os << str;
	return os;
}

std::ostream& operator<<(std::ostream& os, const Klang::Token& token) {
	os << "Token{.start=" << token.start <<
		",.end=" << token.end <<
		",.kind=" << token.kind;
	switch (token.kind) {
	case Klang::TokenKind::NAME:
	case Klang::TokenKind::NATURAL:
	case Klang::TokenKind::INTEGER: os << ",.value=" << token.value;
	default: os << '}'; break;
	}
	return os;
}
