#pragma once

#include <fstream>
#include <stdexcept>

#include "../Syntax/Lexeme.h"

namespace Klang {

class Lexer {
public:
	Lexer(char const* file);

	~Lexer() = default;

public:
	constexpr std::ifstream const& source() const noexcept { return this->source_; }
	constexpr char current() const noexcept { return this->current_; }
	constexpr Position const& position() const noexcept { return this->position_; }

public:
	Lexeme lex();

public:
	void load(char const* path);

private:
	std::ifstream source_;
	char current_;
	Position position_;
	Lexeme lexeme_;

private:
	char peek();
	void advance();

	void lex_numeric();
};

}
