#pragma once

#include <fstream>
#include <stdexcept>
#include <sstream>

#include "Bucket.h"
#include "Tokens.h"

namespace Klang {

class Lexer {
public:
	Lexer(const char* file);

	~Lexer() = default;

public:
	constexpr const std::ifstream& source() const noexcept { return this->_source; }
	constexpr char current() const noexcept { return this->_current; }
	constexpr const Position& position() const noexcept { return this->_position; }

public:
	void lex(Token& out);

public:
	void load(const char *path);

private:
	std::ifstream _source;
	char _current;
	Position _position;

private:
	char peek();
	void advance();

	void lex_numeric(Token& token);
	void lex_text(Token& token, bool is_escaped = false);
};

}
