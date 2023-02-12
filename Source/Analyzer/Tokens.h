#pragma once

#include "../Types.h"

namespace Klang {

enum class TokenTag: char {
	UNDEFINED = -128,
	NAME,
	NATURAL,
	INTEGER,
	FLOAT,
	TEXT,
	PTR,
	NAT,
	NAT8,
	NAT16,
	NAT32,
	NAT64,
	INT,
	INT8,
	INT16,
	INT32,
	INT64,
	REAL,
	REAL32,
	REAL64,
	COMMENT,
	OBJECT,
	EOT = 0,
	COLON = ':',
	SEMICOLON = ';',
	EQUAL = '=',
	PLUS = '+',
	MINUS = '-',
	ASTERISKS = '*',
	SLASH = '/',
	SLOSH = '\\',
	PERCENT = '%',
	OPAREN = '(',
	CPAREN = ')',
};

struct Token {
	friend class Lexer;

public:
	virtual ~Token() = default;

public:
	virtual constexpr TokenTag tag() const noexcept = 0;
	constexpr const Position& start() const noexcept { return this->_start; }
	constexpr const Position& end() const noexcept { return this->_end; }

private:
	Position _start;
	Position _end;
};

template<TokenTag tag_T>
struct TokenBase
	: public Token {
public:
	constexpr TokenTag tag() const noexcept override { return tag_T; }
};

template<TokenTag tag_T, typename Value_T>
struct ValuableTokenBase
	: public TokenBase<tag_T> {
public:
	constexpr Value_T value() const noexcept { return this->_value; }

private:
	Value_T _value;
};

// Literal tokens.
using NameToken = ValuableTokenBase<TokenTag::NAME, const char*>;
using NaturalToken = ValuableTokenBase<TokenTag::NATURAL, nat64>;
using IntegerToken = ValuableTokenBase<TokenTag::INTEGER, int64>;
using FloatToken = ValuableTokenBase<TokenTag::FLOAT, real64>;
using TextToken = ValuableTokenBase<TokenTag::TEXT, const char*>;

// Primitive tokens.
using PtrToken = TokenBase<TokenTag::PTR>;
using NatToken = TokenBase<TokenTag::NAT>;
using Nat8Token = TokenBase<TokenTag::NAT8>;
using Nat16Token = TokenBase<TokenTag::NAT16>;
using Nat32Token = TokenBase<TokenTag::NAT32>;
using Nat64Token = TokenBase<TokenTag::NAT64>;
using IntToken = TokenBase<TokenTag::INT>;
using Int8Token = TokenBase<TokenTag::INT8>;
using Int16Token = TokenBase<TokenTag::INT16>;
using Int32Token = TokenBase<TokenTag::INT32>;
using Int64Token = TokenBase<TokenTag::INT64>;
using RealToken = TokenBase<TokenTag::REAL>;
using Real32Token = TokenBase<TokenTag::REAL32>;
using Real64Token = TokenBase<TokenTag::REAL64>;

// Determiner tokens.
using ObjectToken = TokenBase<TokenTag::OBJECT>;

// Operational tokens.

// Unary tokens.
using EOTToken = TokenBase<TokenTag::EOT>;

// Binary Tokens.
using ColonToken = TokenBase<TokenTag::COLON>;
using SemicolonToken = TokenBase<TokenTag::SEMICOLON>;
using EqualToken = TokenBase<TokenTag::EQUAL>;
using PlusToken = TokenBase<TokenTag::PLUS>;
using MinusToken = TokenBase<TokenTag::MINUS>;
using AsterisksToken = TokenBase<TokenTag::ASTERISKS>;
using SlashToken = TokenBase<TokenTag::SLASH>;
using SloshToken = TokenBase<TokenTag::SLOSH>;
using PercentToken = TokenBase<TokenTag::PERCENT>;

// Scope tokens.
using OParenToken = TokenBase<TokenTag::OPAREN>;
using CParenToken = TokenBase<TokenTag::CPAREN>;

// Other tokens.
using UndefinedToken = ValuableTokenBase<TokenTag::UNDEFINED, char>;
using CommentToken = TokenBase<TokenTag::COMMENT>;

template<typename> struct IsLiteralToken { static constexpr const bool value = true; };
template<> struct IsLiteralToken<NameToken> {};
template<> struct IsLiteralToken<NaturalToken> {};
template<> struct IsLiteralToken<IntegerToken> {};
template<> struct IsLiteralToken<FloatToken> {};
template<> struct IsLiteralToken<TextToken> {};

template<typename> struct IsPrimitiveToken { static constexpr const bool value = true; };
template<> struct IsPrimitiveToken<PtrToken> {};
template<> struct IsPrimitiveToken<NatToken> {};
template<> struct IsPrimitiveToken<Nat8Token> {};
template<> struct IsPrimitiveToken<Nat16Token> {};
template<> struct IsPrimitiveToken<Nat32Token> {};
template<> struct IsPrimitiveToken<Nat64Token> {};
template<> struct IsPrimitiveToken<IntToken> {};
template<> struct IsPrimitiveToken<Int8Token> {};
template<> struct IsPrimitiveToken<Int16Token> {};
template<> struct IsPrimitiveToken<Int32Token> {};
template<> struct IsPrimitiveToken<Int64Token> {};
template<> struct IsPrimitiveToken<RealToken> {};
template<> struct IsPrimitiveToken<Real32Token> {};
template<> struct IsPrimitiveToken<Real64Token> {};

template<typename> struct IsDeterminerToken { static constexpr const bool value = true; };
template<> struct IsDeterminerToken<ObjectToken> {};

template<typename> struct IsOperationalToken { static constexpr const bool value = true; };

template<typename> struct IsUnaryToken { static constexpr const bool value = true; };
template<> struct IsUnaryToken<EOTToken> {};

template<typename> struct IsBinaryToken { static constexpr const bool value = true; };
template<> struct IsBinaryToken<ColonToken> {};
template<> struct IsBinaryToken<SemicolonToken> {};
template<> struct IsBinaryToken<EqualToken> {};
template<> struct IsBinaryToken<PlusToken> {};
template<> struct IsBinaryToken<MinusToken> {};
template<> struct IsBinaryToken<AsterisksToken> {};
template<> struct IsBinaryToken<SlashToken> {};
template<> struct IsBinaryToken<SloshToken> {};
template<> struct IsBinaryToken<PercentToken> {};

template<typename> struct IsScopeToken { static constexpr const bool value = true; };
template<> struct IsScopeToken<OParenToken> {};
template<> struct IsScopeToken<CParenToken> {};

}

std::ostream& operator<<(std::ostream& os, Klang::TokenTag& tag);
std::ostream& operator<<(std::ostream& os, Klang::Token& token);
