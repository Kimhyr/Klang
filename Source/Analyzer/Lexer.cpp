#include "Lexer.h"

namespace Klang {

// `file` is already validated.
Lexer::Lexer(const char* file)
	: _source(file), _position(1, 0) {
	this->_current = this->_source.get();
}

void Lexer::lex(TokenBase& token) {
	while (std::isspace(this->current()))
		this->advance();
}

char Lexer::peek() {
	
}

}
