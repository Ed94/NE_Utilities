/*
Title       : PV_T_HAL
Author      : Edward R. Gonzalez
File Name   : Value.hpp
Date Created: 7-28-2019

Description:
Defines the the templated version of the primitive value hardware abstraction layer class and its associated concepts.

For a union version, see PV_HAL

PV_T_HAL acts a hardware abstraction layer of integer and float data types used generally in programming.

Note: This may not be usable...
*/

#pragma once

// Notation Engine

#include "Meta/Objects/Value.hpp"

#include "PrimitiveValues/PrimitiveValues.hpp"



Context(NotationEngine::Utility::Value)

SAlias
{
	using std::string;

	using NE_U::Sign;

	using NE_M::Value;

	using NE_U::sInt32;
	using NE_U::sInt64;

	using NE_U_R::IsSameType;
}

SMeta
{
	template<typename Type>
	constant sfn IsPrimitiveValueT() -> bool
	{
		if
		(
			IsSameType<Type, Native8_T<sInt8  > >() ||
			IsSameType<Type, Native8_T<uInt8  > >() ||
			IsSameType<Type, Native16T<sInt16 > >() ||
			IsSameType<Type, Native16T<uInt16 > >() ||
			IsSameType<Type, Native32T<sInt32 > >() ||
			IsSameType<Type, Native32T<uInt32 > >() ||
			IsSameType<Type, Native32T<float32> >() ||
			IsSameType<Type, Native64T<sInt64 > >() ||
			IsSameType<Type, Native64T<uInt64 > >() ||
			IsSameType<Type, Native64T<float32> >()
		)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
}

SSource 
{
	template<typename PV>
	class APV_THAL : public Value
	{
		M_constraint(IsPrimitiveValueT<PV>(), "APV_THAL requires a primitive value type to manage which is from the pv template family.");

	public:
		~APV_THAL(void) = NULL;

		virtual sfn GetSign (void) ro -> Sign = NULL;
		virtual sfn GetValue(void) ro -> PV   = NULL;

		implem sfn GetTypeID(void) ro -> ro Ref(TypeData) = NULL;
		
		implem sfn Str(void) ro -> string = NULL;

		virtual sfn SetValue(PV ValueToSet) -> void = NULL;
	};
}

Context_End
