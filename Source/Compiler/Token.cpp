#include "Token.hpp"

namespace Klang::Compiler {

Token::Token()
	: _value(nil) {}

Token::Token(Position position)
	: _span({.start = position}), _value(nil) {}

Token::~Token() {
	if (_value)
		delete this->_value;
}

}
