#pragma once
#ifndef ANALYZER_PARSER_HPP
#define ANALYZER_PARSER_HPP

#include "../Utils/Dynarray.hpp"
#include "Lexer.hpp"
#include "Syntax.hpp"

struct Parser {
  ErrorBuffer *errBuf;
  Lexer lexer;
  Dynarray<O::Declaration> declarations;
  enum struct Flag {
    EoF = (1 << 0),
    Done = (1 << 1),
    SkipToTerminator = (1 << 2),
  } flags;
  enum struct State {
    Done,
    Procedure,
    Datum,
  } state;
  Dynarray<State> stateBuffer;  // TODO Give this set a static cardinality.
  Token token;

  Parser(ErrorBuffer *errBuf, const Char8 *source);

  template<typename TStatement>
  Bool Parse(TStatement *out);

  Void Destroy();

  Bool Advance();
};

#endif  // ANALYZER_PARSER_HPP
