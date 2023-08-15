#pragma once
#define KLANG_INCLUDED_DIAGNOSTICS_H

#include <string_view>

namespace klang
{

struct position
{
    std::size_t row;
    std::size_t column;
};

struct location
{
    std::string_view file_path;
    position         position;
};

}
