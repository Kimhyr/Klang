#pragma once
#ifndef KLANG_COMPILER_ERROR_HPP
#define KLANG_COMPILER_ERROR_HPP

namespace Klang::Compiler {
	enum class Error {
		UNKNOWN_TOKEN,
		UNEXPECTED_TOKEN,
	};
}

#endif // KLANG_COMPILER_ERROR_HPP
