#pragma once
#ifndef ANALYZER_SYNTAX_HPP
#define ANALYZER_SYNTAX_HPP

#include "../Core.hpp"

#include "Token.hpp"

struct Object {};

struct Expression {};

struct Statement {};

namespace O {
    struct Identifier {
        const Char8 *identifier;
    };

    struct Body {
        UInt64 size;
        Statement *statements;
    };

    struct Type {};

    struct TypePath {
        UInt8 pointerCount;
        enum struct Modifier {
            Mutable = 0x01,
        } modifiers;
        O::Type *type;
    };
}


namespace S {
    struct Datum : public Statement {
        O::Identifier identifier;
        O::TypePath type;
        Expression value;
    };
}

namespace O {
    struct DatumPath {
        S::Datum *datum;
    };
};

namespace E {
    struct Binary : public Expression {
        enum struct Operation {
            Add,
        } operation;
        Expression *first;
        Expression second;
    };

    struct Literal : public Expression {};

    struct Integer : public Literal {
        enum struct Flag : UInt8 {
            Bit8 = 0x01,
            Bit16 = 0x02,
            Bit32 = 0x04,
            Bit64 = 0x08,
            Signed = 0x10,
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
};

namespace S {
    struct Assign : public Statement {
        O::DatumPath datum;
        Expression value;
    };
}

namespace O {
    struct Parameter {
        UInt8 size;
        S::Datum items;
    };
};

namespace S {
    struct Procedure : public Statement {
        O::Identifier identifier;
        O::Parameter parameter;
        O::TypePath type;
        O::Body body;
    };

    struct Return : public Statement {
        Expression value;
    };
};

#endif  // ANALYZER_SYNTAX_HPP
