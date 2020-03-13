/*

*/
#pragma once

// Includes

#include "Dev/DevMeta.hpp"
#include "FundamentalTypes.hpp"
#include "Objects/Value.hpp"
#include "Reflection/Meditate.hpp"
#include "PrimitiveValues.hpp"



Context(NotationEngine::Utility::Value)

SAlias
{
	// C++

	using std::string;

	// Notation Engine

	using NE_M::Value;

	using NE_U::sInt32 ;
	using NE_U::uInt32 ;
	using NE_U::float32;

	using NE_U_R::IsSameType;
}

SMeta 
{
	template<typename Type>
	constant sfn IsIntOrFloat32() -> bool
	{
		return IsSameType<Type, sInt32>() || IsSameType<Type, uInt32>() || IsSameType<Type, float32>();
	}
}

SSource
{
	template<typename N32>
	class ANative32T : Value
	{
		M_constraint(IsIntOrFloat32<N32>(), "ANative32T requires a provided type of sInt32, uInt32 or float32.");

	public:
		virtual ~ANative32T(void) = NULL;

		virtual sfn GetSign (void) ro -> Sign = NULL;
		virtual sfn GetValue(void) ro -> N32  = NULL;

		implem sfn GetTypeID(void) ro -> ro Ref(TypeData) = NULL;

		implem sfn ReInitalize(void) -> void = NULL;

		implem sfn Str(void) ro -> string = NULL;

		virtual sfn SetValue(ro Ref(N32) ValueToSet) -> void = NULL;
	};
}

Context_End
