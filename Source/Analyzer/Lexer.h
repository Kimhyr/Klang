#pragma once

#include <fstream>
#include <string>

#include "../Bucket.h"
#include "Token.h"

namespace Klang {

class Lexer {
public:
	Lexer(const char* path);
	
	void load(const char *path);

	~Lexer() = default;

public:
	constexpr const std::ifstream& source() const noexcept { return this->_source; }
	constexpr char current() const noexcept { return this->_current; }
	constexpr natptr index() const noexcept { return this->_index; }
	constexpr const Position& position() const noexcept { return this->_position; }

public:
	Token lex();

private:
	std::ifstream _source;
	char _current;
	natptr _index;
	Position _position;

private:
	void lexNumeric(Token& token);
	char peek();
	void advance();
};

}
