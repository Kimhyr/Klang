#pragma once

#include <string_view>
#include <cstdint>

namespace std {

using float32_t = float;
using float64_t = double;

}

namespace Klang {

struct Position {
	std::size_t row;
	std::size_t column;
};

struct Span {
	Position start;
	Position end;
};

struct String {
	std::size_t length;
	char* string;

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
		string = new char[length];
		std::copy(view.begin(), view.end(), string);
		return *this;
	}
};

}
