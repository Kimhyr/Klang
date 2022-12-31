#ifndef KC_ANALYZER_TOKEN_HPP
#define KC_ANALYZER_TOKEN_HPP

#include "../doctor.hpp"

namespace KC {

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

} // namespace KC

#endif // KC_ANALYZER_TOKEN_HPP
