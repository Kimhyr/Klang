#pragma once

#include <fstream>
#include <stdexcept>
#include <algorithm>

#include "../Syntax/Lexeme.h"
#include "../Doctor.h"

namespace Klang {

class Lexer {
public:
	Lexer(C const* file);

	~Lexer() = default;

public:
	constexpr std::ifstream const& source() const noexcept { return this->source_; }
	constexpr C current() const noexcept { return this->current_; }
	constexpr Position const& position() const noexcept { return this->position_; }

public:
	Lexeme lex();

public:
	V load(C const* path);

private:
	std::ifstream source_;
	C current_;
	Position position_;
	Lexeme lexeme_;

private:
	C peek();
	V advance();
};

namespace Message {

constexpr std::string_view (*OUT_OF_RANGE)(C const* from) = [](C const* from) -> std::string_view {
	STRING.str("Out of range from ");
	STRING << from;
	return STRING.view();
};

constexpr std::string_view (*BUFFER_OVERFLOW)(C const* action) = [](C const* action) -> std::string_view {
	STRING.str("Buffer overflown when trying to ");
	STRING << action;
	return STRING.view();
};

constexpr std::string_view (*UNKNOWN_TOKEN)(C token) = [](C token) -> std::string_view {
	STRING.str("The string \"");
	STRING << token << "\" is not a token.";
	return STRING.view();
};

constexpr std::string_view (*LEX_FAILED)(Lexeme::Tag tag, C const* cause) = [](Lexeme::Tag tag, C const* cause) -> std::string_view {
	STRING.str("Failed to lex ");
	STRING << to_string(tag) << " because " << cause;
	return STRING.view();
};

}
}
