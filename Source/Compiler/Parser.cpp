#include "Parser.hpp"

namespace Klang::Compiler {

template<>
Object *Parser::parse<>(Object *under) {
	
	return nil;
}

template<>
O::Binary *Parser::parse<>(Object *under, O::Binary::Operation operation) {
	auto binary = new O::Binary {
		.operation = operation,
	};
	binary->under = under;
	binary->second = this->parse<Object>(binary);
	return nil;
}

template<>
O::Datum *Parser::parse<O::Datum>(Object *under) {
	const Sym *name = this->parse<O::Name>(under);
	const O::Type &type = this->_structure.symbols.get(name->string());

	auto datum = new O::Datum {
	};
}

}

