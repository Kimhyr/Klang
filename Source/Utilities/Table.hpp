#pragma once
#ifndef KLANG_COMPILER_TABLE_HPP
#define KLANG_COMPILER_TABLE_HPP

#include "../Types.hpp"

namespace Klang::Utilities {

class Hashable {
public:
	virtual constexpr Size hash() const noexcept = 0;
};

template<class T, class Key_T = Hashable>
class Table {
public:
	const T &get(const Key_T &key);
};

}

#endif // KLANG_COMPILER_TABLE_HPP
