#pragma once
#ifndef KLANG_COMPILER_PARSER_HPP
#define KLANG_COMPILER_PARSER_HPP

#include "Lexer.hpp"
#include "Expression.hpp"

namespace Klang::Compiler {

class Parser {
public:
	enum class State {
		DATUM,
		IDENTIFIER,
		TYPE,
		PRIMITIVE,
		ASSIGN,
	};
	
public:
	inline Parser(const Sym *source) noexcept
		: _lexer(source) {}

	~Parser() = default;

public:
	inline const Lexer &lexer() const noexcept { return this->_lexer; }
	inline const Sym *source() const noexcept { return this->_lexer.source(); }
	inline const Token &token() const noexcept { return this->_token; }

public:
	inline Void lex() noexcept { this->_lexer.lex(); }
	
	inline E::Program parse() {
		E::Program program;
		return program.parse(*this);
	}

private:
	Token _token;
	Lexer _lexer;

private:
	inline Void advance() { this->_token = this->_lexer.lex(); }
};

}

#endif // KLANG_COMPILER_PARSER_HPP
