#include "Token.H"

namespace KC {

Token::Token(Position start)
	: location_({.span = {.start = start}}), value_(nil) {}

Token::~Token() {
	if (this->value_)
		delete this->value_;
}

}
