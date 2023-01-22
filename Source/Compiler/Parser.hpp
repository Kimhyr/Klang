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
	constexpr
	Parser(const Sym *source)
		: _lexer(source) {}

	~Parser() = default;

public:
	inline
	const Lexer &lexer()
	const noexcept {return this->_lexer;}

public:
	template<class T = Expression, class ...Args_T>
	T *parse(Args_T ...args);

private:
	Token _token;
	Lexer _lexer;

private:
	inline
	Void lex() {
		this->_token = this->_lexer.lex();
	}
};

}

#endif // KLANG_COMPILER_PARSER_HPP
