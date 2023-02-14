#pragma once

#include "Symbol_Tree.h"

namespace Klang {

Symbol_Tree_Node::~Node() {
	// Killing all the children.
	for (Node* child; this->child; this->child = child) {
		child = this->child->sibling;
		delete this->child;
	}
	Node* sibling = this->locate_prior_sibling();
	if (sibling)
		sibling->sibling = this->sibling;
}

Symbol_Tree_Node* Symbol_Tree_Node::locate_prior_sibling() {
	Node* sibling = this->parent->child;
	while (sibling->sibling != this || sibling->sibling == nullptr)
		sibling = sibling->sibling;
	return sibling;
}

}
