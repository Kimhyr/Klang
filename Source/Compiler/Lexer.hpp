#pragma once
#ifndef KLANG_COMPILER_LEXER_HPP
#define KLANG_COMPILER_LEXER_HPP

#include "../Types.hpp"

namespace Klang::Compiler {

class Token {
public:
	friend class Lexer;
	
public:
	enum class Tag: Sym {
		DATUM = -128,

		END = 0,

		IDENTIFIER,
		MACHINE,
		NATURAL,
		INTEGER,
		REAL,
		TEXT,

		OPEN_PAREN = '(',
		CLOSE_PAREN = ')',

		COLON = ':', 
		SEMICOLON = ';',

		SLOSH = '\\',

		EQUAL = '=',
		PLUS = '+',
		MINUS = '-',
		ASTERISKS = '*',
		SLASH = '/',
		PERCENT = '%',
	};

public:
	static constexpr
	Nat64 VALUE_SPACE = 1024;

public:
	Token();
	Token(Position position);

	~Token();

public:
	inline constexpr
	const Span *span()
	const noexcept {return &this->_span;}

	inline constexpr
	Tag tag()
	const noexcept {return this->_tag;}

	inline constexpr
	const Sym *value()
	const noexcept {return this->_value;}

private:
	Span _span;
	Tag _tag;
	Sym *_value;
};

class Lexer {
public:
	Lexer(const Sym *source);

	~Lexer() = default;

public:
	inline constexpr
	const Sym *source()
	const noexcept { return this->_source; }

	inline constexpr
	const Position *position()
	const noexcept { return &this->_position; }

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

	Void lexNumeric(Token *token);
};

}

#endif // KLANG_COMPILER_LEXER_HPP
