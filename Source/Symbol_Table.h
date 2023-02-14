#pragma once

#include "Types.h"
#include "Syntax_Definitions.h"

namespace Klang {

class Symbol_Table {
private:
	struct Entry {
	public:
		Symbol_Determiner determiner;
		const char* name;
		Entry* branches[27];
		Symbol* symbol;

	public:
		constexpr Entry()
			: determiner(Symbol_Determiner::UNDEFINED), name(nullptr) {}
	
		~Entry() = default;
	};

public:
	constexpr Symbol_Table() {};

	~Symbol_Table() {}

private:
	Entry* _entries[27];
};

}
