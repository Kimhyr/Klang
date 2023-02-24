#pragma once

#include "Lexer.h"
#include "Symbol_Table.h"
#include "Syntax.h"

#include <stack>

namespace Klang {

template<typename T>
struct Is_Parsable { static constexpr bool const value = true; };
template<> struct Is_Parsable<O::This> {};
template<> struct Is_Parsable<E::This> {};
template<typename T>
concept Parsable = Is_Parsable<T>::value;

class Parser {
public:
	using This_Type = Parser;
	using Symbol_Table_Type = Symbol_Table<O::Identifier, E::This&>;
	using Symbol_Type = Symbol_Table_Type::Symbol_Type;

public:
	Parser(char const* file_path)
		: lexer_(file_path) {
		this->lex();
	}

public:
	constexpr Lexer const& lexer() const noexcept { return this->lexer_; }
	constexpr Token const& token() const noexcept { return this->token_; }
	
	constexpr Symbol_Table_Type const& symbols() const noexcept { return this->symbols_; }

	constexpr std::stack<Token*> const& token_stack() const noexcept { return this->token_stack_; }
	constexpr std::stack<E::This*> const& expression_stack() const noexcept { return this->expression_stack_; }

public:
	template<Parsable E_T>
	void parse(E_T& out);

private:
	Lexer lexer_;
	Token token_;
	Symbol_Table_Type symbols_;
	E::This* root_e_ = nullptr;
	std::stack<Token*> token_stack_;
	std::stack<E::This*> expression_stack_;

private:
	inline void lex() {
		this->token_.reset();
		this->lexer_.lex(this->token_);
		this->token_stack_.push(&this->token_);
	}

private:
	template<>
	void parse(E::Program&);

	template<>
	void parse(E::Object&);

	template<>
	void parse(O::Identifier&);
};

}
