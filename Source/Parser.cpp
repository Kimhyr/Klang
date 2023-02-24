#include "Parser.h"

namespace Klang {

template<>
void Parser::parse_out_a(O::Identifier& out, O::Determiner determiner) {
	auto sym = new This_Type::Symbol_Type;
	for (;;) {
		this->lex();
		if (this->token().tag == Token_Tag::NAME) {
			break;
		}
	}
	this->symbols_.enter(*sym);
}

template<>
E::Object* Parser::parse_a() {
	auto e = new E::Object;
	this->parse_out_a(e->identifier, O::Determiner::OBJECT);
	if (this->token().tag != Token_Tag::COLON)
		throw std::invalid_argument(__FUNCTION__);
	this->parse_out_a(e->type);
	return e;
}

}
