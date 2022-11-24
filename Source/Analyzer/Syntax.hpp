#pragma once
#ifndef ANALYZER_SYNTAX_HPP
#define ANALYZER_SYNTAX_HPP

#include "../Core.hpp"
#include "Token.hpp"

namespace O {
  struct Expression {};

  struct Statement {};
}  // namespace O

namespace S {
  struct Structure : public O::Statement {};
}  // namespace S

namespace O {
  /*
    O:Identifier -> [_|A-Z|a-z][_|A-Z|a-z|0-9]*
  */
  struct Identifier {
    enum struct Flag {
    } flags;
    const Char8 *identifier;
  };

  /*
    O:Body -> '{' Statement* '}'
  */
  struct Body {
    UInt64 size;
    Statement *statements;
  };

  /*
    O:TypePath -> '::' T:Modifier {d | Declaration.kind $ O:Type}
  */
  struct TypePath {
    UInt8 pointerCount;
    enum struct Modifier {
      Mutable = 1 << 0,
    } modifiers;
  };
}  // namespace O

namespace S {
  /*
    S:Datum -> 'datum' O:Identifier O:TypePath O:Initializer
  */
  struct Datum : public O::Statement {
    O::TypePath type;
    O::Expression value;
  };
}  // namespace S

namespace E {
  struct Binary : public O::Expression {
    enum struct Operation {
      Add,
    } operation;
    O::Expression *first;
    O::Expression second;
  };

  struct Literal : public O::Expression {};

  struct Integer : public Literal {
    enum struct Flag : UInt8 {
      Bit8 = (1 << 0),
      Bit16 = (1 << 1),
      Bit32 = (1 << 2),
      Bit64 = (1 << 3),
      Signed = (1 << 4),
    } flags;
    UInt64 value;
  };

  // struct Float : public Literal {
  //     enum struct Flag : UInt8 {
  //         Bit32 = 0x01,
  //         Bit64 = 0x02,
  //         Bit128 = 0x04,
  //     } flags;
  //     Float128 value;
  // };

  // struct Character : public Literal {
  //     enum struct Flag : UInt8 {
  //         Bit8 = 0x01,
  //         Bit16 = 0x02,
  //         Cooked = 0x04,
  //     } flags;
  //     Char16 value;
  // };

  // struct String : public Literal {
  //     E::Character::Flag flags;
  //     UInt64 length;
  //     Char16 *value;
  // };

  // struct List : public Literal {
  //     UInt64 size;
  //     Expression *data;
  // };
};  // namespace E

namespace S {
  struct Assign : public O::Statement {
    S::Datum *datum;
    O::Expression value;
  };
}  // namespace S

namespace O {
  /*
    O:Initializer -> '{' [O:Accessor+|Literal] '}'
  */
  struct Initializer {
    union Object {
      E::Literal literal;
      S::Assign assignment;
    } object;
  };

  struct Parameter {
    UInt8 size;
    S::Datum items;
  };
};  // namespace O

namespace S {
  /*
    S::Procedure -> 'procedure' O::Identifier O::Parameter O::TypePath O::Body
  */
  struct Procedure : public O::Statement {
    O::Parameter parameter;
    O::TypePath type;
    O::Body body;
  };

  struct Return : public O::Statement {
    O::Expression value;
  };
};  // namespace S

namespace O {
  struct Declaration {
    enum struct Kind {
      Structure,
      Procedure,
      Datum,
    } kind;
    union Value {
      S::Structure *Structure;
      S::Procedure *Procedure;
      S::Datum *Datum;
    } value;
    O::Identifier identifier;

    Declaration(S::Procedure *value);
  };
}  // namespace O

#endif  // ANALYZER_SYNTAX_HPP
