#pragma once
#ifndef KLANG_COMPILER_TABLE_HPP
#define KLANG_COMPILER_TABLE_HPP

#include "../Types.hpp"
#include "Error.hpp"

namespace Klang::Utilities {

class Hashable {
public:
	virtual Size hash() = 0;
};

template<class T, class Key_T = Hashable, Size Space_T = 1024>
class Table {
public:
private:
	struct Entry {
	public:
		const Key_T key;
		T value;
		Entry *next;

	public:
		inline Entry(Key_T key, T value)
			: key(key), value(value), next(nil) {}

		inline ~Entry() {
			key.~Key_T();
			value.~T();
		}
	};

public:
	inline Table()
		: _size(0) {}

	~Table() {
		for (auto &e : _entries) {
			for (Entry *entry; e.next; e.next = entry) {
				entry = e.next.next;
				delete e.next;
			}
		}
	}

public:
	Void put(Key_T key, T value) {
		Entry *entry = this->getEntry(key);
		if (entry)
			throw Error::INVALID_ARGUEMENT;
		entry = new Entry(key, value);
	}

	Void pop(const Key_T &key) {
		Entry *entry = _entries[key.hash()];
		if (!entry)
			throw Error::INVALID_ARGUEMENT;
		for (; entry->next; entry = entry->next)
			if (entry->next->key == key)
				goto On_Found;
		throw Error::INVALID_ARGUEMENT;
	On_Found:
		Entry *next = entry->next;
		entry->next = entry->next->next;
		delete next;
	}

	T &get(const Key_T &key) {
		Entry *entry = this->getEntry(key);
		if (!entry)
			throw Error::INVALID_ARGUEMENT;
		return entry->value;
	}

private:
	Size _size;
	Entry _entries[Space_T];

private:
	Entry *getEntry(const Key_T &key) {
		Entry *entry = _entries[key.hash()];
		for (; entry; entry = entry->next)
			if (entry->key == key)
				break;
		return entry;
	}
};

}

#endif // KLANG_COMPILER_TABLE_HPP
