#include "token.hpp"

namespace KC {

Token::Token(Location::Point start)
	: location({.start = start}){}

Token::~Token() {
        delete this->value;
}

} // namespace KC
