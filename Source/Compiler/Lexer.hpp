#pragma once
#ifndef KLANG_COMPILER_LEXER_HPP
#define KLANG_COMPILER_LEXER_HPP

#include "Token.hpp"

namespace Klang::Compiler {

class Lexer {
public:
	constexpr
	Lexer(const Sym *source)
		: _source(source), _position({.row = 1, .column = 1}) {}

	~Lexer() = default;

public:
	inline constexpr
	const Sym *source()
	const noexcept { return this->_source; }

	inline constexpr
	const Position &position()
	const noexcept { return this->_position; }

	inline constexpr
	Sym current()
	const noexcept { return *this->_source; }

	inline constexpr
	Sym peek(Nat64 offset = 1)
	const noexcept { return this->_source[offset]; }

public:
	Token lex();

private:
	const Sym *_source;
	Position _position;

private:
	inline constexpr
	Bool isSpace(Sym sym)
	const noexcept { return (sym == ' ') || (sym >= '\t' && sym <= '\r'); }

	inline constexpr
	Bool isAlphabetic(Sym sym)
	const noexcept { return (sym >= 'a' && sym <= 'z') || (this->current() >= 'A' && this->current() <= 'Z'); }

	inline constexpr
	Bool isNumeric(Sym sym)
	const noexcept { return sym >= '0' && sym <= '9'; }

private:
	Void advance();

	Void lexNumeric(Token &token);
};

}

#endif // KLANG_COMPILER_LEXER_HPP
