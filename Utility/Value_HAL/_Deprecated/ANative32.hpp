/*
Title       : Abstract Native-32
Author      : Edward R. Gonzalez
File Name   : Native32.hpp
Date Created: 2-10-2019

Description:
Defines the Native-32 abstract interface.
*/

#pragma once

//Includes

//Notation Engine

#include "Dev/DevMeta.hpp"
#include "Objects/Value.hpp"
#include "DataTypes/FundamentalTypes.hpp"
#include "PrimitiveValues/PrimitiveValues.hpp"



Context(NotationEngine::Utility::Value)

SAlias
{
	// C++

	using std::string;

	// Notation Engine

	using NE_M::Value;

	using sInt32  = NE_U::sInt32 ;
	using uInt32  = NE_U::uInt32 ;
	using float32 = NE_U::float32;
}

SSource
{
	//Enum

	enum class N32_ID
	{
		SInteger,
		UInteger,
		Float   ,
	};


	//Class

	class ANative32 : Value
	{
	public:
		virtual ~ANative32(void) = NULL;

		virtual sfn GetID  (void) ro -> N32_ID = NULL;
		virtual sfn GetSign(void) ro -> Sign   = NULL;

		virtual sfn GetSInteger(void) ro -> sInt32  = NULL;
		virtual sfn GetUInteger(void) ro -> uInt32  = NULL;
		virtual sfn GetFloat   (void) ro -> float32 = NULL;

		implem sfn GetTypeID(void) ro -> ro Ref(TypeData) = NULL;

		implem sfn ReInitalize(void) -> void = NULL;

		implem sfn Str(void) ro -> string = NULL;

		virtual sfn SetSInteger(ro sInt32  IntToSet  ) -> void = NULL;
		virtual sfn SetUInteger(ro uInt32  IntToSet  ) -> void = NULL;
		virtual sfn SetFloat   (ro float32 FloatToSet) -> void = NULL;
	};
}

Context_End