#pragma once
#ifndef KC_Lexer_H
#define KC_Lexer_H

#include "Token.H"

namespace KC {

class Lexer {
public:
	Lexer(const Sym *source);

	~Lexer() = default;

public:
	constexpr
	const Sym *source()
	const noexcept { return this->source_; }

	constexpr
	const Position *position()
	const noexcept { return &this->position_; }

public:
	Void advance(Token *out);

private:
	const Sym *source_;
	Position position_;

private:
	constexpr
	Bool isOnSpace()
	const noexcept { return (*this->source_ == ' ') || *this->source_ >= '\t' && *this->source_ <= '\r'; }

	constexpr
	Bool isOnAlphabetic()
	const noexcept { return (*this->source_ >= 'a' && *this->source_ <= 'z') || (*this->source_ >= 'A' && *this->source_ <= 'Z'); }

	constexpr
	Bool isOnNumeric()
	const noexcept { return *this->source_ >= '0' && *this->source_ <= '9'; }

private:
	Void proceed();
};

}

#endif // KC_Lexer_H
