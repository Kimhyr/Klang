#pragma once

#include <fstream>
#include <stdexcept>
#include <sstream>
#include <algorithm>

#include "../Syntax/Lexeme.h"
#include "../Doctor.h"

namespace Klang {

namespace Message {

static std::stringstream STRING;

constexpr std::string_view (*OUT_OF_RANGE)(S const* from) = [](S const* from) -> std::string_view {
	STRING.str("Out of range from ");
	STRING << from;
	return STRING.view();
};

constexpr std::string_view (*BUFFER_OVERFLOW)(S const* action) = [](S const* action) -> std::string_view {
	STRING.str("Buffer overflown when trying to ");
	STRING << action;
	return STRING.view();
};

constexpr std::string_view (*UNKNOWN_TOKEN)(S token) = [](S token) -> std::string_view {
	STRING.str("The string \"");
	STRING << token << "\" is not a token.";
	return STRING.view();
};

constexpr std::string_view (*LEX_FAILED)(Lexeme::Tag tag, S const* cause) = [](Lexeme::Tag tag, S const* cause) -> std::string_view {
	STRING.str("Failed to lex ");
	STRING << Lexeme::tag_to_string(tag) << " because " << cause;
	return STRING.view();
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
