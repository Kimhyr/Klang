#pragma once
#ifndef ANALYZER_PARSER_HPP
#define ANALYZER_PARSER_HPP

#include "../Utils/Vector.hpp"
#include "Syntax.hpp"
#include "Token.hpp"


struct Parser {
    Vector<O::Declaration> identifiers;

};

#endif  // ANALYZER_PARSER_HPP
