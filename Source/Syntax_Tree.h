#pragma once

#include "Types.h"
#include "Syntax_Definitions.h"

namespace Klang {

class Syntax_Tree {
public:
	enum class Tag {
		UNDEFINED = 0,
		UNARY_EXPRESSION,
		BINARY_EXPRESSION,
		TERNARY_EXPRESSION,
		SCOPED_EXPRESSION,
		SIMPLE_EXPRESSION,
		PRIMITIVE,
		LITERAL_EXPRESSION,
		TYPE_COMPOSITION,
		OBJECT_DECLARATION,
	};
	
	struct Node {
	public:
		const Tag tag = Tag::UNDEFINED;
		Node* prior;
		Node* next;
		Position start;
		Position end;

	public:
		virtual ~Node() = default;
	};
};

using Syntax_Tree_Tag = Syntax_Tree::Tag;
using Syntax_Tree_Node = Syntax_Tree::Node;

}
