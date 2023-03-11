#pragma once

#include <string_view>

namespace Klang {

using V = void;

using I8 = signed char;
using I16 = signed short int;
using I32 = signed int;
using I64 = signed long int;

using N8 = unsigned char;
using N16 = unsigned short int;
using N32 = unsigned int;
using N64 = unsigned long int;

using R32 = float;
using R64 = double;

using B = bool;
using B8 =  N8;
using B16 = N16;
using B32 = N32;
using B64 = N64;

using C = char;
using C8 = char;
using C16  = char16_t;
using C32 = char32_t;

#if defined(__x86_64__)
	using I = I64;
	using N = N64;
	using R = R64;
#else
	using I = I32;
	using N = N32;
	using R = Rl32;
#endif

struct Position {
	N row;
	N column;
};

struct Span {
	Position start;
	Position end;
};

struct String {
	N length;
	C* string;

	constexpr String() noexcept
		: length(0), string(nullptr) {}

	constexpr String(String&& other) noexcept
		: length(other.length), string(other.string) {
		other.string = nullptr;
	}

	constexpr String& operator=(String&& other) noexcept {
		this->length = other.length;
		this->string = other.string;
		other.string = nullptr;
		return *this;
	}

	String& operator=(std::string_view const& view) {
		length = view.length();
		string = new C[length];
		std::copy(view.begin(), view.end(), string);
		return *this;
	}
};

}
