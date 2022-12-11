#ifndef KPLC_SYNTAX_CAST_CPP
#define KPLC_SYNTAX_CAST_CPP

#include "Identifier.cpp"

namespace S  {
    struct Cast {
        Nat8 PointerCount;
        const S::Identifier *Identifier;
    };
} // S

#endif // KPLC_SYNTAX_CAST_CPP
