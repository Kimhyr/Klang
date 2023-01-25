#pragma once
#ifndef KLANG_COMPILER_PARSER_HPP
#define KLANG_COMPILER_PARSER_HPP

#include "Lexer.hpp"
#include "Expression.hpp"
#include "Error.hpp"

namespace Klang::Compiler {

using namespace Klang::Utilities;

const E::Type PRIMITIVES[] = {
	E::Type(E::Primitive::SYM),
	E::Type(E::Primitive::INT),
};

enum class ParserState {
	ANY,
	DATUM,
	IDENTIFIER,
	TYPE,
	PRIMITIVE,
	ASSIGN,
};

class Parser {
public:
	inline Parser(const Sym *source) noexcept
		: state_(ParserState::ANY), lexer_(source) {}

	~Parser() = default;

public:
	inline const Lexer &lexer() const noexcept { return this->lexer_; }
	inline const Sym *source() const noexcept { return this->lexer_.source(); }
	inline const Token &token() const noexcept { return this->token_; }

public:
	template<typename Expression_T = Expression, typename ...Args_T>
	const Expression_T *parse(Args_T...);

	// T::Identifier
	template<> const E::Identifier *parse(const E::Symbol *symbol);

	// 'datum' E::Identifier ':' E::Type (E ';')?
	template<> const E::Datum *parse(const Expression *prior);

	// E ['='|'+'|'-'|'*'|'/'|'%'] E
	template<> const E::Binary *parse(const Expression *lhs);

private:
	ParserState state_;
	Token token_;
	Lexer lexer_;
	Table<Expression *, E::Identifier> symbols_;

private:
	inline Void lex(TokenTag expected) {
		this->token_ = this->lexer_.lex();
		if (this->token_.tag() != expected)
			throw Compiler::Error::UNEXPECTED_TOKEN;
	}
};

}

#endif // KLANG_COMPILER_PARSER_HPP
