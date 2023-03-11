#pragma once

#include <stack>
#include <iostream>

#include "../Syntax/Syntax.h"
#include "Lexer.h"

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
	Parser(C const* file);

public:
	constexpr C const* file() const noexcept { return this->file_; }
	constexpr Lexer const& lexer() const noexcept { return this->lexer_; }
	constexpr Lexeme const& lexeme() const noexcept { return this->lexeme_; }
	constexpr std::stack<Syntax_Tag> const& states() const noexcept { return this->states_; };

public:
	Syntax* parse();
	
	Parser& operator<<(Parser& parser);

private:
	C const* file_;
	Lexer lexer_;
	Lexeme lexeme_;
	std::stack<Syntax_Tag> states_;
	Syntax* ast_;

private:
	inline V eat_until(Lexeme_Tag tag) {
		do {
			this->lex();
			if (this->lexeme().tag == Lexeme::EOT)
				throw EOT {};
		} while (this->lexeme().tag != tag);
	}

private:
	inline B lex() {
		try {this->lexer_.lex(this->lexeme_);}
		catch (Severity) {return false;}
		return true;
	}

	inline B lex(Lexeme_Tag tag) {
		try {
			this->lexer_.lex(this->lexeme_);
			if (this->lexeme_.tag != tag) {
				diagnose(Severity::ERROR, this->lexer_.position(),
					 Message::UNEXPECTED_LEXEME(tag, this->lexeme_.tag));
				return false;
			}
		} catch (Severity) {return false;}
		return true;
	}
};

}
