#pragma once

#include <stack>
#include <iostream>

#include "Syntax/Syntax.hpp"
#include "Lexer.hpp"

namespace Klang {

namespace Message {

inline std::string_view UNEXPECTED_LEXEME(Lexeme_Tag expected, Lexeme_Tag recieved) {
	STRING.str("Expected a ");
	STRING << to_string(expected) << " but recieved a " << to_string(recieved) << '.';
	return STRING.view();
}

}

class EOT {};

class Parser {
public:
	Parser(char const* file);

public:
	constexpr char const* file() const noexcept { return this->m_file; }
	constexpr Lexer const& lexer() const noexcept { return this->m_lexer; }
	constexpr Lexeme const& lexeme() const noexcept { return this->lexeme_; }
	constexpr std::stack<Syntax_Tag> const& states() const noexcept { return this->m_states; };

public:
	Syntax* parse();

	Parser& operator<<(Parser& parser);

private:
	char const* m_file;
	Lexer m_lexer;
	Lexeme lexeme_;
	std::stack<Syntax_Tag> m_states;
	Syntax* m_ast;

private:
	inline void eat_until(Lexeme_Tag tag) {
		do {
			this->lex();
			if (this->lexeme().tag == Lexeme::EOT)
				throw EOT {};
		} while (this->lexeme().tag != tag);
	}

private:
	constexpr bool lex() {
		try {this->m_lexer.lex(this->lexeme_);}
		catch (Severity) {return false;}
		return true;
	}

	constexpr bool lex(Lexeme_Tag tag) {
		try {
			this->m_lexer.lex(this->lexeme_);
			if (this->lexeme_.tag != tag) {
				diagnose(Severity::ERROR, this->m_lexer.position(),
					 Message::UNEXPECTED_LEXEME(tag, this->lexeme_.tag));
				return false;
			}
		} catch (Severity) {return false;}
		return true;
	}
};

}
