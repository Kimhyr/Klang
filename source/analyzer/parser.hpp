#ifndef KC_PARSER_HPP
#define KC_PARSER_HPP

#include "../definitions.hpp"

namespace KC {

struct Syntax {
        
};

class Parser {
        const Sym *source;
        
public:
        Parser();

        ~Parser();

public:
        Syntax *parse();

};

} // namespace KC

#endif // KC_PARSER_HPP
