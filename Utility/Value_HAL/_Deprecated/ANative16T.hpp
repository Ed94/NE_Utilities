/*
Description:
Defines the Native-8 abstract interface.
*/

#pragma once

// Includes

#include "Objects/Value.hpp"
#include "Reflection/Meditate.hpp"
#include "PrimitiveValues/PrimitiveValues.hpp"



Context(NotationEngine::Utility::Value)

SAlias 
{
	// C++

	using std::string;

	// Notation Engine

	using NE_U_R::IsSameType;
	using NE_M  ::Value     ;
}

SMeta
{
	template<typename Type>
	constant sfn IsInt16() -> bool
	{
		return IsSameType<Type, sInt16>() || IsSameType<Type, uInt16>();
	}
}

SSource
{
	template<typename N16>
	class ANative16T : Value
	{
		M_constraint(IsInt16<N16>(), "ANative8_T requires a provided type of sInt8 or uInt16.");

	public:
		virtual ~ANative16T(void) = NULL;

		virtual sfn GetSign  (void) ro ->        Sign      = NULL;
		virtual sfn GetTypeID(void) ro -> ro Ref(TypeData) = NULL;
		virtual sfn GetValue (void) ro ->        N16       = NULL;

		implem sfn ReInitalize(void) -> void = NULL;

		implem sfn Str(void) ro -> string = NULL;

		virtual sfn SetValue(ro Ref(N16) ValueToSet) -> void = NULL;
	};
}

Context_End
