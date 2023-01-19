#ifndef KC_ANALYZER_PARSER_H
#define KC_ANALYZER_PARSER_H

#include "../utilities/dynamic.h"
#include "lexer.h"
#include "expression.h"

namespace KC::Analyzer {

using namespace KC::Utilities;

class Parser {
public:
        Parser(const Sym *source);

        ~Parser();

public:
        Expression *parse();

private:

        struct State {
                const enum class Tag {
#include "state.defs"
                } tag;
                Nat8 step;

        public:
                State()
                        : tag((Tag)-1), step(0) {};

                State(Tag tag)
                        : tag(tag), step(0) {}
       

                static constexpr
                Bool compareTag(const State *self, State::Tag tag) noexcept {
                        return self->tag == tag;
                }
        };

private:
        const Sym *source;
        Lexer lexer;
        Token token;
        Dynamic<State> states;
};

}

#endif // KC_ANALYZER_PARSER_HPP
