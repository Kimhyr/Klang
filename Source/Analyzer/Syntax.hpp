#pragma once
#ifndef ANALYZER_SYNTAX_HPP
#define ANALYZER_SYNTAX_HPP

#include "../Core.hpp"

#include "Token.hpp"

namespace O {
    struct Expression {};

    struct Statement {};    
}

namespace O {
    struct Identifier {
        enum struct Flag {
        } flags;
        const Char8 *identifier;
    };

    struct Body {
        UInt64 size;
        Statement *statements;
    };

    struct Type {
        enum struct Kind {
            Structure,
            Enumerare,
            Unistruct,
        } kind;
        union Value {
            S::Structure *structure;
        } value;
    };

    struct TypePath {
        UInt8 pointerCount;
        enum struct Modifier {
            Mutable = 0x01,
        } modifiers;
        O::Type type;
    };
}

namespace S {
    struct Structure : public O::Statement {
    };

     struct Datum : public O::Statement {
        O::TypePath type;
        O::Expression value;
    };
}

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
    struct Assign : public O::Statement {
        S::Datum *datum;
        O::Expression value;
    };
}

namespace O {
    struct Parameter {
        UInt8 size;
        S::Datum items;
    };
};

namespace S {
    struct Procedure : public O::Statement {
        O::Parameter parameter;
        O::TypePath type;
        O::Body body;
    };

    struct Return : public O::Statement {
        O::Expression value;
    };
};

namespace O {
     struct Declaration {
        enum struct Kind {
            Structure,
            Procedure,
            Datum,
        } kind;
        union Value {
            S::Structure *structure;
            S::Procedure *procedure;
            S::Datum *datum;
        };
    };
}


#endif  // ANALYZER_SYNTAX_HPP
