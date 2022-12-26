#ifndef _TOKEN_HPP
#define _TOKEN_HPP

#include "../doctor.hpp"

namespace KC {

struct Token {
        Location location;
        enum class Tag : Sym {
#include "token.defs"
        } tag;
        Sym *value;

        Token(Location::Point start);
        ~Token();
};

} // namespace KC

#endif // _TOKEN_HPP
