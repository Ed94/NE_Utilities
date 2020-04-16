#pragma once

// Includes

// Notation Engine
#include "MultiprecisionTypes.hpp"
#include "AValue_HAL.hpp"



Context(NotationEngine::Utility::Value)

SAlias
{
	using std::string;
}

SMeta
{
	template<typename Type>
	constant sfn IsPrimitiveType() -> bool
	{
		return IsInt<Type>() || IsFloat<Type>() || IsBoostInt<Type>() || IsBoostFloat<Type>();
	}
}

SSource
{
	template<typename PV_Type>
	class APrimitiveValue : public AValue_HAL
	{
		M_constraint(IsPrimitiveType<PV_Type>(), "APrimitiveValue requires a primitive type to properly use this interface.");

	public:
		virtual ~APrimitiveValue(void) {};

		implem  sfn GetSign (void) ro -> ro     Sign     = NULL;
		virtual sfn GetValue(void) ro -> ro Ref(PV_Type) = NULL;

		implem sfn GetTypeID(void) ro -> ro Ref(TypeData) = NULL;

		implem sfn Reinitialize(void) -> void = NULL;
		
		implem sfn Str(void) ro -> ro string = NULL;

		implem sfn SetSign(ro Sign SignToSet) -> void = NULL;

		implem sfn SetZero(void) -> void = NULL;

		implem sfn SetValue(ro        uInt64      ValueToSet) -> void = NULL;
		//implem sfn SetValue(ro        sInt64      ValueToSet) -> void = NULL;
		//implem sfn SetValue(ro        float32     ValueToSet) -> void = NULL;
		//implem sfn SetValue(ro        float64     ValueToSet) -> void = NULL;
		implem sfn SetValue(ro ptr<ro AValue_HAL> ValueToSet) -> void = NULL;

		virtual sfn SetValue(ro Ref(PV_Type) ValueToSet) -> void = NULL;
	};
}

Context_End
