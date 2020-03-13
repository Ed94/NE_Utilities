#pragma once

// Includes

// Notation Engine
#include "APrimitiveValue.hpp"



Context(NotationEngine::Utility::Value)

SMeta
{
	template<typename Type>
	constant sfn IsMultiprecisionType() -> bool
	{
		return IsBoostInt<Type>() || IsBoostFloat<Type>();
	}
}

SSource
{
	template<typename MP_Type>
	class ABoostMP : APrimitiveValue<MP_Type>
	{
		M_constraint(IsMultiprecisionType<MP_Type>(), "ABoostMP requires a multi-precision primitive.");

	public:
		virtual ~ABoostMP(void) = NULL;

		virtual sfn GetSign (void) ro -> ro     Sign     = NULL;
		virtual sfn GetValue(void) ro -> ro Ref(MP_Type) = NULL;

		implem sfn GetTypeID(void) ro->ro Ref(TypeData) = NULL;

		implem sfn Reinitialize(void) -> void = NULL;

		implem sfn Str(void) ro -> ro string = NULL;

		virtual sfn SetValue(ro Ref(MP_Type) ValueToSet) -> void = NULL;
	};
}

Context_End
