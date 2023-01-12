#ifndef KC_ANALYZER_TOKEN_H
#define KC_ANALYZER_TOKEN_H

#include "../doctor.h"

namespace KC::Analyzer {

struct Token {
        Location location;
        enum class Tag : Sym {
#include "token.defs"
        } tag;
        Sym *value;

public:
        Token() = default;
        Token(Location::Point start);
        ~Token();
public:
        Void print();
};

}

#endif // KC_ANALYZER_TOKEN_H
