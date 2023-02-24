#pragma once

#include "Lexer.h"
#include "Symbol_Table.h"
#include "Syntax.h"

#include <stack>

namespace Klang {

class Parser {
public:
	using This_Type = Parser;
	using Symbol_Table_Type = Symbol_Table<O::Identifier, E::E&>;
	using Symbol_Type = Symbol_Table_Type::Symbol_Type;

public:
	Parser(char const* file_path)
		: lexer_(file_path) {}

public:
	constexpr Lexer const& lexer() const noexcept { return this->lexer_; }
	constexpr Token const& token() const noexcept { return this->token_; }
	
	constexpr Symbol_Table_Type const& symbols() const noexcept { return this->symbols_; }

	constexpr std::stack<Token*> const& token_stack() const noexcept { return this->token_stack_; }
	constexpr std::stack<E::E*> const& expression_stack() const noexcept { return this->expression_stack_; }

public:
	Program& parse();

private:
	Lexer lexer_;
	Token token_;
	Symbol_Table_Type symbols_;
	E::E* root_e_ = nullptr;
	std::stack<Token*> token_stack_;
	std::stack<E::E*> expression_stack_;
	
public:
	template<typename E_T = E::E>
	E_T* parse_a();

private:
	inline void lex() {
		this->token_.reset();
		this->lexer_.lex(this->token_);
		this->token_stack_.push(&this->token_);
	}
};

}
