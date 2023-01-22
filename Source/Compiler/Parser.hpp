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
	T *parse(Expression *under, Args_T ...args);

private:
	Lexer _lexer;
};

}

#endif // KLANG_COMPILER_PARSER_HPP
