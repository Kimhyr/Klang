#pragma once

#include "Types.h"
#include "Syntax_Definitions.h"

namespace Klang {

class Symbol_Table {
public:
	struct Entry {
		friend class Symbol_Table;
	
	public:
		constexpr Entry()
			: _determiner(Symbol_Determiner::UNDEFINED), _name(nullptr) {}
	
		~Entry() = default;

	public:
		constexpr Symbol_Determiner determiner() const noexcept { return this->_determiner; }
		constexpr const char* name() const noexcept { return this->_name; }
		constexpr Symbol* symbol() const noexcept { return this->_symbol; }

	private:
		Symbol_Determiner _determiner;
		const char* _name;
		Entry* _branches[27];
		Symbol* _symbol;
	};

public:
	constexpr Symbol_Table() {};

	~Symbol_Table() {}

public:
	void put(Entry& entry);
	void pop(Symbol_Determiner determiner, const char* name);
	void get(Symbol_Determiner determiner, const char* name);

private:
	Entry* _entries[27];
};

using Symbol_Table_Entry = Symbol_Table::Entry;

}
