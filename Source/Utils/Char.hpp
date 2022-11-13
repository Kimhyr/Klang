#pragma once
#ifndef UTILS_CHAR_HPP
#define UTILS_CHAR_HPP

#include "../Core.hpp"

struct Char {
  constexpr static Bool IsWhitespace(Char8 chr) {
    return (chr == ' ') || (chr >= '\t' && chr <= '\r');
  }
  constexpr static Bool IsNumeric(Char8 chr) {
    return chr >= '0' && chr <= '9';
  }
  constexpr static Bool IsAlphabetic(Char8 chr) {
    return (chr >= 'A' && chr <= 'Z') || (chr >= 'a' && chr <= 'z');
  }
};

#endif  // UTILS_CHAR_HPP
