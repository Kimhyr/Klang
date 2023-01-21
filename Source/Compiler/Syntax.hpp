#ifndef KLANG_COMPILER_SYNTAX_HPP
#define KLANG_COMPILER_SYNTAX_HPP

#include "../Types.hpp"

namespace Klang::Compiler {

class Syntax {
public:
	enum class Tag {
		DATUM,
		
		// Operations
		BINARY,
	};
	
	class Node {
	public:
		virtual inline constexpr
		Tag tag()
		const noexcept = 0;

		virtual inline constexpr
		const Node *under()
		const noexcept = 0;

		virtual inline constexpr
		const Node *above()
		const noexcept = 0;
	
	protected:
		Node *_under;
		Node *_above;
	};

private:

};

class Type: Syntax::Node {
public:
	enum class Kind {
		PTR,
		NAT8,
		NAT16,
		NAT32,
		NAT64,
		INT8,
		INT16,
		INT32,
		INT64,
		REAL32,
		REAL64,
	};

private:
};

class Datum: Syntax::Node {
public:
	inline constexpr
	Syntax::Tag tag()
	const noexcept override {return Syntax::Tag::DATUM;}

	inline constexpr
	const Node *under()
	const noexcept override {return this->_under;}

	inline constexpr
	const Node *above()
	const noexcept override {return this->_above;}

private:
	Type _type;
};

class Binary: Syntax::Node {
public:
	enum class Operation {
		ASSIGN,
		ADD,
		SUBTRACT,
		MULITPLY,
		DIVIDE,
		MOD,
	};

public:	
	Operation operation;
	Syntax::Node *first;
	Syntax::Node *second;

public:
	inline constexpr
	Syntax::Tag tag()
	const noexcept override {return Syntax::Tag::BINARY;} 

	inline constexpr
	const Node *under()
	const noexcept override {return this->_under;}

	inline constexpr
	const Node *above()
	const noexcept override {return this->_above;}
};

}

#endif // KLANG_COMPILER_SYNTAX_HPP
