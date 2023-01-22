#ifndef KLANG_COMPILER_TABLE_HPP
#define KLANG_COMPILER_TABLE_HPP

namespace Klang::Utilities {

template<class Key_T, class T>
class Table {
public:
	const T &get(const Key_T &key);
};

}

#endif // KLANG_COMPILER_TABLE_HPP
