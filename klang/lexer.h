#pragma once
#define KLANG_INCLUDED_LEXER_H

#include <cstdint>
#include <string_view>
#include <limits>

#include <klang/diagnostics.h>

namespace klang
{

enum class token_type
{
    identifier = std::numeric_limits<int>::min(),

    // Literals
    number,
    string,

    // Words
    return_word,  // 'return'
    b8_word,      // 'b8',
    b16_word,     // 'b16',
    b32_word,     // 'b32',
    b64_word,     // 'b64',
    b128_word,    // 'b128'
    i8_word,      // 'i8',
    i16_word,     // 'i16',
    i32_word,     // 'i32',
    i64_word,     // 'i64',
    i128_word,    // 'i128'
    f16_word,     // 'f16',
    f32_word,     // 'f32',
    f64_word,     // 'f64',
    f128_word,    // 'f128'

    end = 0,

    // Punctuators
    apostrpohe          = '\'',
    quatation_mark      = '\"',
    colon               = ':',
    semicolon           = ';',
    left_parenthesis    = '(',
    right_parenthesis   = ')',
    left_angle_bracket  = '<',
    right_angle_bracket = '>',
    left_curly_bracket  = '{',
    right_curly_bracket = '}',
    plus_sign           = '+',
    minus_sign          = '-',
    asterisk            = '*',
    slash               = '/',
    percent_sign        = '%'
};

struct token
{
    char const* pointer;
    std::size_t length;
    token_type  type;
};

class lexer
{
public:
    lexer(char const* row) noexcept
        : m_pointer{row}
        , m_row{row}
        , m_row_number{1}
    {}
   
    [[nodiscard]]
    token next();

    [[nodiscard]]
    position position() const noexcept
    {
        return {
            .row    = m_row_number,
            .column = static_cast<std::size_t>(m_pointer - m_row)
        };
    }

private:
    char const* m_pointer;
    char const* m_row;
    std::size_t m_row_number;

    void consume() noexcept
    {
        if (*m_pointer == '\n')
            m_row = m_pointer;
        ++m_pointer;
    }
};

}
