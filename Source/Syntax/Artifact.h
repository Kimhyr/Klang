#pragma once

#include "Syntax.h"

namespace Klang {

namespace S {

class Artifact: public Syntax {
public:
	enum Determiner: I8 {
		OBJECT = -127,
		PROCEDURE,
		P = 'P' + 3,
		N = 'N', N64, N32, N16, N8,
		I = 'I', I64, I32, I16, I8,
		R = 'R' + 2, R64, R32,
	};

public:
	Tag const tag = ARTIFACT;
	Syntax* prior;
	Syntax* next;
	Determiner determiner;
	Identifier* identifier;
	Parameter parameter;
	Type_Composition type;
	Body body;

public:
	constexpr Artifact(Determiner determiner, Syntax* prior = nullptr) noexcept
		: prior(prior), next(nullptr), determiner(determiner){}
};

}

namespace Primitive {

S::Artifact const P(S::Artifact::P);
S::Artifact const N(S::Artifact::N);
S::Artifact const N8(S::Artifact::N8);
S::Artifact const N16(S::Artifact::N16);
S::Artifact const N32(S::Artifact::N32);
S::Artifact const N64(S::Artifact::N64);
S::Artifact const I(S::Artifact::I);
S::Artifact const I8(S::Artifact::I8);
S::Artifact const I16(S::Artifact::I16);
S::Artifact const I32(S::Artifact::I32);
S::Artifact const I64(S::Artifact::I64);
S::Artifact const R32(S::Artifact::R32);
S::Artifact const R64(S::Artifact::R64);

}

}
