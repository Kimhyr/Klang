#pragma once

#include <fstream>
#include <stdexcept>
#include <algorithm>

#include "Syntax/Lexeme.hpp"
#include "Doctor.hpp"

namespace Klang {

class Lexer {
public:
	Lexer(char const* file);
	Lexer(std::ifstream&& file);

	~Lexer() = default;

public:
	constexpr std::ifstream const& source() const noexcept { return this->m_source; }
	constexpr char current() const noexcept { return this->m_current; }
	constexpr Position const& position() const noexcept { return this->m_position; }

public:
	void lex(Lexeme& out);

public:
	void load(char const* path);

private:
	std::ifstream m_source;
	char m_current;
	Position m_position;

private:
	inline char peek()
		{ return this->m_source.peek(); }

	void advance();
};

namespace Message {

inline std::string_view OUT_OF_RANGE(char const* from) {
	STRING.str("Out of range from ");
	STRING << from;
	return STRING.view();
}

inline std::string_view BUFFER_OVERFLOW(char const* action) {
	STRING.str("Buffer overflown when trying to ");
	STRING << action;
	return STRING.view();
};

inline std::string_view UNKNOWN_TOKEN(char token) {
	STRING.str("The string \"");
	STRING << token << "\" is not a token.";
	return STRING.view();
};

inline std::string_view LEX_FAILED(Lexeme::Tag tag, char const* cause) {
	STRING.str("Failed to lex ");
	STRING << to_string(tag) << " because " << cause;
	return STRING.view();
};

}

}
