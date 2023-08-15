#pragma once
#define KLANG_INCLUDED_SYNTAX_H

#include <klang/diagnostics.h>

namespace klang
{

enum class syntax_type
{
    parameters,  // '(' [<definition> +[',' <definition>]] ')'

    //
    // Types
    //
    primitive_type,  // TODO: Define syntax.
    function_type,   // <parameters> '->' <type>

    //
    // Statements
    //
    return_,     // 'return' <expression>
    definition,  // <identifier> ':' <type> (';'|'{' +[<statement>]'}')

    //
    // Expressions
    //

    // Factors
    binary,          // TODO: Define syntax.
    integer,         // TODO: Define syntax.
    floating_point,  // TODO: Define syntax.

    // Binary Expressions
    addition,        // <expression> '+' <expression>
    subtraction,     // <expression> '-' <expression>
    multiplication,  // <expression> '*' <expression>
    division,        // <expression> '/' <expression>
    modulo           // <expression> '%' <expression>
};

class syntax
{
public:
    syntax(syntax_type     type,
           location const& location,
           syntax*         prior
    ) noexcept
        : m_prior{prior}
        , m_type{type}
        , m_location{location}
    {}

    [[nodiscard]]
    syntax* prior() const noexcept
    { return m_prior;  }
        
    [[nodiscard]]
    syntax_type type() const noexcept
    { return m_type; }
        
    [[nodiscard]]
    location location() const noexcept
    { return m_location; }

private:
    syntax*         m_prior;
    syntax_type     m_type;
    klang::location m_location;
};

class expression
    : public syntax
{
public:
    using base_type = syntax;
        
    expression(syntax_type            type,
               klang::location const& location,
               syntax*                prior
    ) noexcept
        : base_type{type,
                    std::forward<klang::location const&>(location),
                    prior}
    {}

    [[nodiscard]]
    void* operator new(std::size_t, expression* prior) noexcept;
 };

}
