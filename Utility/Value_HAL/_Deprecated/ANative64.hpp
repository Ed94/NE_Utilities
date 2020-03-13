/*
Title       : Abstract Native-64
Author      : Edward R. Gonzalez
File Name   : ANative64.hpp
Date Created: 2-10-2019

Description:
Defines the Abstract Interface for a Native-64 type.
*/

#pragma once

//Includes

//Notation Engine

#include "Objects/Value.hpp"
#include "PrimitiveValues.hpp"
#include "Utility/DataTypes/FundamentalTypes.hpp"



Context(NotationEngine::Utility::Value)

SAlias
{
	//C++

	using std::string;

	//Notation Engine

	using NE_M::Value;

	using NE_U::uInt64 ;
	using NE_U::float64;
}

SSource
{
	enum class N64_ID
	{
		SInteger,
		UInteger,
		Float   ,
	};


	class ANative64 : Value
	{
	public:
		virtual ~ANative64(void) = NULL;

		virtual sfn GetID  (void) ro -> N64_ID = NULL;
		virtual sfn GetSign(void) ro -> Sign   = NULL;

		virtual sfn GetSInteger(void) ro -> sInt64 = NULL;
		virtual sfn GetUInteger(void) ro -> uInt64  = NULL;
		virtual sfn GetFloat   (void) ro -> float64 = NULL;

		implem sfn GetTypeID(void) ro -> ro Ref(TypeData) = NULL;

		implem sfn ReInitalize(void) -> void = NULL;

		implem sfn Str(void) ro -> string = NULL;

		virtual sfn SetSInteger(ro sInt64  IntegerToSet) -> void = NULL;
		virtual sfn SetUInteger(ro uInt64  IntegerToSet) -> void = NULL;
		virtual sfn SetToFloat (ro float64 FloatToSet  ) -> void = NULL;
	};
}

Context_End