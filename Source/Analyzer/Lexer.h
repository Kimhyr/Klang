#pragma once

#include <fstream>

#include "Tokens.h"

namespace Klang {

class LexerError
	: public std::exception {
public:
	const char* what() const noexcept override {
	
	};

	UndefinedToken token;
};

class Lexer {
public:
	Lexer(const char* file);

	~Lexer() = default;

public:
	constexpr const std::ifstream& source() const noexcept { return this->_source; }
	constexpr char current() const noexcept { return this->_current; }
	constexpr const Position& position() const noexcept { return this->_position; }

public:
	void lex(Token& token);
	Token& lex();

public:
	void load(const char *path);

private:
	std::ifstream _source;
	char _current;
	Position _position;

public:
	char peek();
	void advance();
};

}
