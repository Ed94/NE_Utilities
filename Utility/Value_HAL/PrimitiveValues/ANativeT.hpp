/*
Title       : Abstract Native Template 
Author      : Edward R. Gonzalez
File Name   : ANativeT.hpp
Date Created: 11-3-2019

Description:
Defines the abstract interface for a Native template type.
*/

#pragma once

// Includes

// Notation Engine
#include "Objects/Value.hpp"
#include "APrimitiveValue.hpp"



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
	constant sfn IsIntOrFloat() -> bool
	{
		return IsInt<Type>() || IsFloat<Type>();
	}
}

SSource
{
	template<typename NType>
	class ANativeT : public APrimitiveValue<NType>
	{
		M_constraint(IsIntOrFloat<NType>(), "ANativeT requires a provided type of int or float fundamental type (Of any bit size).");

	public:
		virtual ~ANativeT(void) = NULL;

		implem sfn GetSign (void) ro -> ro     Sign   = NULL;
		implem sfn GetValue(void) ro -> ro Ref(NType) = NULL;

		implem sfn GetTypeID(void) ro -> ro Ref(TypeData) = NULL;

		implem sfn Reinitialize(void) -> void = NULL;

		implem sfn Str(void) ro -> ro string = NULL;

		implem sfn SetSign(ro Sign SignToSet) -> void = NULL;

		implem sfn SetZero(void) -> void = NULL;

		implem sfn SetValue(ro        uInt64      ValueToSet) -> void = NULL;
		implem sfn SetValue(ro ptr<ro AValue_HAL> ValueToSet) -> void = NULL;

		implem sfn SetValue(ro Ref(NType) ValueToSet) -> void = NULL;
	};
}

Context_End
