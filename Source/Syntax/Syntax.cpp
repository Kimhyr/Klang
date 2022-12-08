#ifndef KPLC_SYNTAX_SYNTAX_CPP
#define KPLC_SYNTAX_SYNTAX_CPP

enum class SyntaxEnum {
#include "Defs/Identifiable.defs"
    Binary,
    Simple,
    Assignment,
};

// All are set to pointers to not waste space.
union SyntaxNode {
    S::Procedure *Procedure;
    S::Datum *Datum;
    S::Assignment *Assignment;
    S::Binary *Binary;
    S::Simple *Simple;
};

struct Syntax {
    SyntaxEnum Symbol;
    SyntaxNode Node;
};

#endif // KPLC_SYNTAX_SYNTAX_CPP
