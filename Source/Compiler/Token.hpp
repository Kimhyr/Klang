#pragma once
#ifndef KLANG_COMPILER_TOKEN_HPP
#define KLANG_COMPILER_TOKEN_HPP

#include "../Types.hpp"

namespace Klang::Compiler {

enum class TokenTag: Sym {
	DATUM = -128,
	INT,
	SYM,
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

struct Token {
public:
	friend class Lexer;

public:
	static constexpr Nat64 VALUE_SPACE = 1024;

public:
	inline Token() noexcept
		: value_(nil) {}

	inline Token(Position start) noexcept
		: span_({.start = start}), value_(nil) {}
	
	inline Token(Span span, TokenTag tag, const Sym *value = nil) noexcept
		: span_(span), tag_(tag), value_(value) {}

	~Token() = default;

public:
	inline const Span &span() const noexcept {return this->span_;}
	inline TokenTag tag() const noexcept {return this->tag_;}
	inline const Sym *value() const noexcept {return this->value_;}

private:
	Span span_;
	TokenTag tag_;
	const Sym *value_;
};

}

#endif // KLANG_COMPILER_TOKEN_HPP
