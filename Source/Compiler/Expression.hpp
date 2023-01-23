#pragma once
#ifndef KLANG_COMPILER_EXPRESSION_HPP
#define KLANG_COMPILER_EXPRESSION_HPP

#include "../Types.hpp"
#include "../Utilities/Table.hpp"

namespace Klang::Compiler {

class Parser;

template<class T>
class Expression {
public:
	virtual ~Expression() = 0;

public:
	virtual const T &parse(Parser &parser) = 0;
};

namespace E {

using namespace Klang::Utilities;

template<class T>
class Identifier: public Expression<Identifier<T>>, public Hashable {
public:
	enum class Type {
		DATUM,
		TYPE,
	};

public:
	inline Identifier(const T &person, Type type)
		: _person(person), _type(type) {}
	
	inline Identifier(const T &person, Type type, const Sym *name)
		: _person(person), _type(type), _name(name) {}

	~Identifier() = default;

public:
	inline const T &person() const noexcept { return this->_person; }
	inline Type type() const noexcept { return this->_type; }
	inline const Sym *name() const noexcept { return this->_name; }

public:
	const Identifier &parse(Parser &parser) override;

	constexpr Size hash() override {
		Size result = 0;
		for (Nat16 i = 0; this->_name[i]; ++i)
			result += this->_name[i];
		return result;
	};

public:
	constexpr Bool operator ==(const Identifier &rhs) const noexcept {
		return this->_type == rhs._type && strcmp(this->_name, rhs._name) == 0;
	}

public:
	const T &_person;
	Type _type;
	const Sym *_name;
};

// '-'? ['64'|'32'|'16'|'8'|'0'] '.'?
class Primitive: public Expression<Primitive> {
public:
	enum class Type {
		INT32,
	};
	
public:
	inline Primitive(Type type)
		: _type(type) {}

	~Primitive() = default;

public:
	inline Type type() const noexcept { return this->_type; }

public:
	const Primitive &parse(Parser &parser) override;

private:
	Type _type;
};

// 'datum' Identifier ':' Type '=' E ';'
class Datum: public Expression<Datum> {
public:
	inline Datum()
		: _identifier(*this, Identifier<Datum>::Type::DATUM) {}

	~Datum() = default;

public:
	inline const Identifier<Datum> &_name() const noexcept { return this->_identifier; }
	inline const Expression &type() const noexcept { return *this->_type; }

public:
	const Datum &parse(Parser &parser) override;

private:
	Identifier<Datum> _identifier;
	Identifier &_type;
};

// [Literal|Datum] 
class Factor: public Expression<Factor> {
public:
	enum class Kind {
		INTEGER,
		NATURAL,
		REAL,
		TEXT,
		DATUM,
	};

	union Value {
		Nat64 natural;
		Int64 integer;
		Real64 real;
		const Sym *text;
	};
	
public:
	inline Factor(Kind type, Nat64 natural) noexcept
		: _type(type), _value({.natural = natural}) {}

	inline Factor(Kind type, Int64 integer) noexcept 
		: _type(type), _value({.integer = integer}) {}

	inline Factor(Kind type, Real64 real) noexcept
		: _type(type), _value({.real = real}) {}
	
	inline Factor(Kind type, const Sym *text) noexcept
		: _type(type), _value({.text = text}) {}

	~Factor() = default;

public:
	const Factor &parse(Parser &parser) override;

public:
	inline Kind type() const noexcept { return this->_type; }
	inline const Value &value() const noexcept { return this->_value; }

private:
	Kind _type;
	Value _value;
};

// E ['='|'+'|'-'|'*'|'/'|'%'] E
class Binary: public Expression<Binary> {
public:
	enum class Operation: Sym {
		ASSIGN,
		ADD,
		SUBTRACT,
		MULTIPLY,
		DIVIDE,
		MOD,
	};

public:
	inline Binary(Operation operation, Expression &left) noexcept
		: _operation(operation), _left(left) {}

	~Binary() = default;

public:
	inline Operation operation() const noexcept { return this->_operation; }
	inline const Expression &left() const noexcept { return this->_left; }
	inline const Expression &right() const noexcept { return *this->_right; }

public:
	const Binary &parse(Parser &parser) override;
	
private:
	Operation _operation;
	Expression &_left;
	Expression *_right;
};

class Program: public Expression<Program> {
public:
	inline Program() noexcept {}

	~Program() = default;

public:
	const Program &parse(Parser &parser) override;

private:
	Table<Expression &, Identifier<Expression>> _identifiers;
	Void **_root;
};

}

}
#endif // KLANG_COMPILER_EXPRESSION_HPP
