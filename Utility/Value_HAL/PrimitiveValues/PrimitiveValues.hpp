/*
Title       : Primitive Values
Author      : Edward R. Gonzalez
File Name   : PrimitiveValues.hpp
Date Created: 2-10-2019

Description:
The main header for the primitive values supported within the Number Theory module of Notation Engine.
*/

#pragma once

//Includes

// C++

#include <typeinfo>

//Notation Engine
#include "Dev/DevMeta.hpp"

#include "DataTypes/FundamentalTypes.hpp"

#include "NativeT.hpp"
#include "BoostMP.hpp"



namespace NotationEngine::Utility::Value
{
	inline namespace Alias
	{
	}

	inline namespace Source
	{	
		/*
		The way type conversions work is essentially during dynamic operations is:

		Unsigned operated with signed integers will be casted to signs. 

		If one of the types is a float the integer term will be casted.

		If its arbitrary precision the native object will be casted to a arbitrary precision. (Integer or float depending on what the type was [with float naturally taking priority])

		Casts show throw if the previous type is not within bounds.

		// TODO: Bounds check of type casted to float not done yet.
		// TODO: Native64 is unsafe in operations.
		*/
		enum class ValueType
		{
			uInt8   ,
			sInt8   ,
			uInt16  ,
			sInt16  ,
			uInt32  ,
			sInt32  ,
			uInt64  ,
			sInt64  ,
			float32 ,
			float64 ,
			uInt256 ,
			sInt256 ,
			FloatP50
		};

		inline ValueType GetValueType(const AValue_HAL* const _value)
		{
			const TypeData& typeID = _value->GetTypeID();

			if      (typeID == NativeT_TypeID<uInt8    >) return ValueType::uInt8   ;
			else if (typeID == NativeT_TypeID<sInt8    >) return ValueType::sInt8   ;
			else if (typeID == NativeT_TypeID<uInt16   >) return ValueType::uInt16  ;
			else if (typeID == NativeT_TypeID<sInt16   >) return ValueType::sInt16  ;
			else if (typeID == NativeT_TypeID<uInt32   >) return ValueType::uInt32  ;
			else if (typeID == NativeT_TypeID<sInt32   >) return ValueType::sInt32  ;
			else if (typeID == NativeT_TypeID<uInt64   >) return ValueType::uInt64  ;
			else if (typeID == NativeT_TypeID<sInt64   >) return ValueType::sInt64  ; 
			else if (typeID == NativeT_TypeID<float32  >) return ValueType::float32 ;
			else if (typeID == NativeT_TypeID<float64  >) return ValueType::float64 ;
			else if (typeID == BoostMP_TypeID<uInt256  >) return ValueType::uInt256 ;
			else if (typeID == BoostMP_TypeID<sInt256  >) return ValueType::sInt256 ;
			else if (typeID == BoostMP_TypeID<Float_P50>) return ValueType::FloatP50;
		}
	}
}