#ifndef KC_TOKEN_HPP
#define KC_TOKEN_HPP

#include "../doctor.hpp"

namespace KC {

struct Token {
        Location location;
        enum class Tag : Sym {
#include "token.defs"
        } tag;
        Sym *value;

public:
        Token(Location::Point start);
        ~Token();
};

} // namespace KC

#endif // KC_TOKEN_HPP
