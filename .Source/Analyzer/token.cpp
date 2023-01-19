#include "token.h"

namespace KC::Analyzer {

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
	PRINTC(KC::Analyzer::Token::Tag::DATUM);
	PRINTC(KC::Analyzer::Token::Tag::END);
	PRINTV(KC::Analyzer::Token::Tag::IDENTIFIER);
	PRINTV(KC::Analyzer::Token::Tag::MACHINE);
	PRINTV(KC::Analyzer::Token::Tag::NATURAL);
	PRINTV(KC::Analyzer::Token::Tag::INTEGER);
	PRINTV(KC::Analyzer::Token::Tag::REAL);
	PRINTV(KC::Analyzer::Token::Tag::TEXT);
	PRINTC(KC::Analyzer::Token::Tag::OPEN_PAREN);
	PRINTC(KC::Analyzer::Token::Tag::CLOSE_PAREN);
	PRINTC(KC::Analyzer::Token::Tag::COLON );
	PRINTC(KC::Analyzer::Token::Tag::SEMICOLON);
	PRINTC(KC::Analyzer::Token::Tag::SLOSH);
	PRINTC(KC::Analyzer::Token::Tag::EQUAL);
	PRINTC(KC::Analyzer::Token::Tag::PLUS);
	PRINTC(KC::Analyzer::Token::Tag::MINUS);
	PRINTC(KC::Analyzer::Token::Tag::ASTERISKS);
	PRINTC(KC::Analyzer::Token::Tag::SLASH);
	PRINTC(KC::Analyzer::Token::Tag::PERCENT);
	}
}

} // namespace KC
