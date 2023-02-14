#pragma once

#include "Types.h"
#include "Syntax_Definitions.h"

namespace Klang {

// Family tree is a hashmap containing parents that hold children.
// If a parent gets killed, all the parent's children dies. 

class Family_Tree {
public:
	class Parent {
	public:

	};
};

class Symbol_Tree {
public:
	// Deleting a node:
	//	Kill all the node's children; then,
	// 	change the node's prior sibling to the node's `next` sibling.
	//	Do nothing with the symbol.
	class Node {
		friend class Symbol_Tree;

	public:
		constexpr Node() noexcept
			: determiner(static_cast<Symbol_Determiner>(0)), name(nullptr),
			  parent(nullptr), sibling(nullptr), child(nullptr), symbol(nullptr) {}
		constexpr Node(Symbol_Determiner determiner, char const* name, Node& parent,
			       Symbol* symbol) noexcept
			: determiner(determiner), name(name), parent(&parent), sibling(nullptr),
			  child(nullptr), symbol(symbol) {}

		~Node();

	private:
		Symbol_Determiner determiner;
		char const* name;
		Node* parent;
		Node* sibling;
		Node* child;
		Symbol* symbol;

	private:
		Node* locate_prior_sibling();
	};

public:
	Symbol_Tree() noexcept
		: tree(*new Node()) {};

	~Symbol_Tree() {}

public:
	void put_node(Symbol_Determiner determiner, char const* name, Node& parent, Symbol* symbol);
	void pop_node(Symbol_Determiner determiner, char const* name);
	
	Node* get_node(Symbol_Determiner determiner, char const* name);

private:
	Node& tree;

private:
	Node* locate_node(Symbol_Determiner, char const* name);
};

using Symbol_Tree_Node = Symbol_Tree::Node;

}
