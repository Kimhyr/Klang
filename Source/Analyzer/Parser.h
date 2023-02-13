#pragma once

#include "Syntax.h"
#include "Lexer.h"

namespace Klang {

class Parser {
public:
	Parser(const char* sourcePath) noexcept
		: _lexer(sourcePath) {};

	~Parser() = default;

public:
	constexpr const Token& token() const noexcept { return this->_token; }

public:
	template<typename T = Syntax>
	T* parse();

	template<typename T = Syntax>
	void parse(T& out);


	template<> SyntaxTree* parse();
	template<> Identifier* parse();

private:
	Lexer _lexer;
	SyntaxTree* _tree;
	Token _token;

private:
	constexpr SyntaxTree& tree() noexcept { return *this->_tree; }
	constexpr Syntax* syntax() noexcept { return this->_tree->head; }
	
	inline void lex() noexcept {
		this->_lexer.lex(this->_token);
	}
};

}
