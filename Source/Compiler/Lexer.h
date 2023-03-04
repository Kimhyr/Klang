#pragma once

#include <fstream>
#include <stdexcept>
#include <sstream>
#include <algorithm>
#include <>

#include "../Syntax/Lexeme.h"
#include "../Doctor.h"

namespace Klang {

namespace Message {

constexpr S const* BUFFER_OVERFLOW = "Buffer overflow.";
constexpr S const* UNKNOWN_TOKEN = "Unkown token.";
constexpr S const* (*FAILED_TO_LEX)(Lexeme) = [](Lexeme l) {
	constexpr N8 prefix_length = 0;
	static std::string str = "Failed to lex ";
	str.resize(prefix_length);
	return "";
};

}

class Lexer {
public:
	Lexer(S const* file);

	~Lexer() = default;

public:
	constexpr std::ifstream const& source() const noexcept { return this->source_; }
	constexpr S current() const noexcept { return this->current_; }
	constexpr Position const& position() const noexcept { return this->position_; }

public:
	Lexeme lex();

public:
	V load(S const* path);

private:
	std::ifstream source_;
	S current_;
	Position position_;
	Lexeme lexeme_;

private:
	S peek();
	V advance();
};

}
