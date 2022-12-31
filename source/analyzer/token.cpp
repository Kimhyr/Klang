#include "token.hpp"

namespace KC {

Token::Token(Location::Point start)
	: location({.start = start}) {}

Token::~Token() {
	if (this->tag >= Tag::IDENTIFIER && this->tag <= Tag::TEXT)
        	delete this->value;
}

#define PRINTC(TAG) case TAG: puts(#TAG); break
#define PRINTV(TAG) case TAG: printf(#TAG " %s\n", this->value); break

Void Token::print() {
	switch (this->tag) {
	PRINTC(KC::Token::Tag::DATUM);
	PRINTC(KC::Token::Tag::END);
	PRINTV(KC::Token::Tag::IDENTIFIER);
	PRINTV(KC::Token::Tag::MACHINE);
	PRINTV(KC::Token::Tag::NATURAL);
	PRINTV(KC::Token::Tag::INTEGER);
	PRINTV(KC::Token::Tag::REAL);
	PRINTV(KC::Token::Tag::TEXT);
	PRINTC(KC::Token::Tag::OPEN_PAREN);
	PRINTC(KC::Token::Tag::CLOSE_PAREN);
	PRINTC(KC::Token::Tag::COLON );
	PRINTC(KC::Token::Tag::SEMICOLON);
	PRINTC(KC::Token::Tag::SLOSH);
	PRINTC(KC::Token::Tag::EQUAL);
	PRINTC(KC::Token::Tag::PLUS);
	PRINTC(KC::Token::Tag::MINUS);
	PRINTC(KC::Token::Tag::ASTERISKS);
	PRINTC(KC::Token::Tag::SLASH);
	PRINTC(KC::Token::Tag::PERCENT);
	}
}

} // namespace KC
