#include <cctype>
#include <stdexcept>

#include "lexer.h"

namespace klang
{

token lexer::next()
{
    while (std::isspace(*m_pointer))
        consume();

    token token{
        .pointer = m_pointer,
        .length = 0
    };
    token_type type{static_cast<token_type>(*m_pointer)};
    switch (type) {
    case token_type::quatation_mark:
        do {
            consume();
            ++token.length;
        } while (*m_pointer != '"' && m_pointer[-1] != '\\');
        token.type = token_type::string;
        break;
    case token_type::end:
    case token_type::colon:
    case token_type::semicolon:
    case token_type::left_parenthesis:
    case token_type::right_parenthesis:
    case token_type::left_angle_bracket:
    case token_type::right_angle_bracket:
    case token_type::left_curly_bracket:
    case token_type::right_curly_bracket:
    case token_type::plus_sign:
    case token_type::minus_sign:
    case token_type::asterisk:
    case token_type::slash:
    case token_type::percent_sign:
        token.type = type;
        token.length = 1;
        break;
    default:
        if (std::isalpha(*m_pointer) || *m_pointer ==  '_') {
            do {
                consume();
                ++token.length;
            } while (std::isalpha(*m_pointer)
                    || *m_pointer == '_'
                    || std::isdigit(*m_pointer));
            token.type = token_type::identifier;
        } else if (std::isdigit(*m_pointer)) {
            do {
                consume();
                ++token.length;
            } while (std::isdigit(*m_pointer));
            token.type = token_type::number;
        }
        throw std::invalid_argument{"unknown token"};
    }

    return token;
}

}
