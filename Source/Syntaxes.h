#pragma once

#include "Syntax_Definitions.h"
#include "Syntax_Tree.h"

namespace Klang {

template<Syntax_Tree_Tag tag_T>
struct Syntax_Tree_Node_Base
	: public Syntax_Tree_Node {
public:
	const Syntax_Tree_Tag tag = tag_T;
};

struct Literal_Expression
	: public Syntax_Tree_Node_Base<Syntax_Tree_Tag::LITERAL_EXPRESSION>,
	  public Factor {
public:
	Literal_Type type;
	union Value {
		intptr Integer;
		natptr Natural;
		realptr Real;
		char Symbol;
		const char* Text;
	} value;
};

struct Unary_Expression
	: public Syntax_Tree_Node_Base<Syntax_Tree_Tag::UNARY_EXPRESSION>,
	  public Factor {
public:
	Syntax_Tree_Node* prior;
	Unary_Operation operation;
	Factor* expression;
	Syntax_Tree_Node* next;
};

struct Binary_Expression
	: public Syntax_Tree_Node_Base<Syntax_Tree_Tag::BINARY_EXPRESSION>,
	  public Factor {
public:
	Binary_Operation operation;
	Factor* first;
	Factor* second;
};

struct Ternary_Expression
	: public Syntax_Tree_Node_Base<Syntax_Tree_Tag::TERNARY_EXPRESSION>,
	  public Factor {
public:
	Ternary_Operation operation;
	Factor* first;
	Factor* second;
	Factor* third;
};

struct Scoped_Expression
	: public Syntax_Tree_Node_Base<Syntax_Tree_Tag::SCOPED_EXPRESSION>,
	  public Factor {
public:
	Scope_Type scope;
	Factor* root;
	Factor* head;
};

struct Simple_Expression
	: public Syntax_Tree_Node_Base<Syntax_Tree_Tag::SIMPLE_EXPRESSION> {
public:
	Simple_Operation operation;
	Factor* expression;
};

struct Primitive
	: public Type {
public:
	const Primitive_Type type;
};

constexpr const Primitive PTR_PRIMITIVE = { .type = Primitive_Type::PTR };
constexpr const Primitive NAT_PRIMITIVE = { .type = Primitive_Type::NAT };
constexpr const Primitive NAT8_PRIMITIVE = { .type = Primitive_Type::NAT8 };
constexpr const Primitive NAT16_PRIMITIVE = { .type = Primitive_Type::NAT16 };
constexpr const Primitive NAT32_PRIMITIVE = { .type = Primitive_Type::NAT32 };
constexpr const Primitive NAT64_PRIMITIVE = { .type = Primitive_Type::NAT64 };
constexpr const Primitive INT_PRIMITIVE = { .type = Primitive_Type::INT };
constexpr const Primitive INT8_PRIMITIVE = { .type = Primitive_Type::INT8 };
constexpr const Primitive INT16_PRIMITIVE = { .type = Primitive_Type::INT16 };
constexpr const Primitive INT32_PRIMITIVE = { .type = Primitive_Type::INT32 };
constexpr const Primitive INT64_PRIMITIVE = { .type = Primitive_Type::INT64 };
constexpr const Primitive REAL_PRIMITIVE = { .type = Primitive_Type::REAL };
constexpr const Primitive REAL32_PRIMITIVE = { .type = Primitive_Type::REAL32 };
constexpr const Primitive REAL64_PRIMITIVE = { .type = Primitive_Type::REAL64 };

struct Type_Composition {
public:
	natptr size = 0;
	Type* head;
	Type* root;
};

struct Object_Declaration
	: public Syntax_Tree_Node_Base<Syntax_Tree_Tag::OBJECT_DECLARATION>,
	  public Symbol {
public:
	Object_Flag flags = Object_Flag::CLEAR;
	Type_Composition type;
};

}
