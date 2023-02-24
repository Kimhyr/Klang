#pragma once

#include "Lexer.h"
#include "Symbol_Table.h"
#include "Syntax.h"

namespace Klang {

class Parser {
public:
	using This_Type = Parser;
	using Symbol_Table_Type = Symbol_Table<O::Identifier, E::E*>;
	using Symbol_Type = Symbol_Table_Type::Symbol_Type;
	
public:
	Parser(char const* file_path)
		: lexer_(file_path) {}

public:
	constexpr Lexer const& lexer() const noexcept { return this->lexer_; }
	constexpr Token const& token() const noexcept { return this->token_; }
	
	constexpr Symbol_Table_Type const& symbols() const noexcept { return this->symbols_; }
	constexpr E::E const* root_e() const noexcept { return this->root_e_; }  

public:
	E::E* parse();

private:
	Lexer lexer_;
	Token token_;
	Symbol_Table_Type symbols_;
	E::E* root_e_ = nullptr;

private:
	template<typename E_T = E::E>
	E_T* parse_a();
	
	template<typename O_T = O::O, typename... Args_T>
	void parse_out_a(O_T& out, Args_T...);

private:
	inline void lex() {
		this->token_.reset();
		this->lexer_.lex(this->token_);
	}
};

}
