#include "Expression.hpp"

#include "Parser.hpp"
#include "Error.hpp"

namespace Klang::Compiler {

namespace E {

const Program &Program::parse(Parser &parser) {
	auto program = new Program();
	parser.lex();
	switch (parser.token().kind()) {
	case Token::Kind::DATUM:
		this->_root = (Void **)new Datum;
		((E::Datum*)this->_root)->parse(parser);
		break;
	default: throw Compiler::Error::UNEXPECTED_TOKEN;
	}
	return *program;
}

const Datum &Datum::parse(Parser &parser) {
	this->_identifier.parse(parser);
}

}

}
