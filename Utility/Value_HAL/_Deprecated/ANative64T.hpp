#pragma once

// Includes

#include "Objects/Value.hpp"

#include "PrimitiveValues/PrimitiveValues.hpp"



Context(NotationEngine::Utility::Value)

SAlias
{
	// C++

	using std::string;

	// Notation Engine

	using NE_M::Value;

	using NE_U::sInt64 ;
	using NE_U::uInt64 ;
	using NE_U::float64;

	using NE_U_R::IsSameType;
}

SMeta
{
	template<typename Type>
	constant sfn IsIntOrFloat64() -> bool
	{
		return IsSameType<Type, sInt64>() || IsSameType<Type, uInt64>() || IsSameType<Type, float64>();
	}
}

SSource
{
	template<typename N64>
	class ANative64T : Value
	{
		M_constraint(IsIntOrFloat64<N64>(), "ANative64T requires a provided type of sInt64, uInt64, or float64");

	public:
		virtual ~ANative64T(void) = NULL;

		virtual sfn GetSign (void) ro -> Sign = NULL;
		virtual sfn GetValue(void) ro -> N64  = NULL;

		implem sfn GetTypeID(void) ro -> ro Ref(TypeData) = NULL;

		implem sfn ReInitalize(void) -> void = NULL;

		implem sfn Str(void) ro -> string = NULL;

		virtual sfn SetValue(ro Ref(N64) ValueToSet) -> void = NULL;
	};
}

Context_End
