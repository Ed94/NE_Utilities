/*
Title       : Abstract Native-16
Author      : Edward R. Gonzalez
File Name   : ANative16.hpp
Date Created: 9-30-2019

Description:
Defines the Native-16 abstract interface.
*/

#pragma once

// Includes

// Notation Engine
#include "Objects/Value.hpp"

#include "PrimitiveValues/PrimitiveValues.hpp"



Context(NotationEngine::Utility::Value)

SAlias
{
	// C++

	using std::string;

	// Notation Engine

	using NE_M::Value;
}

SSource
{
	enum class N16_ID
	{
		Signed  ,
		Unsigned,
	};

	class ANative16 : Value
	{
	public:
		virtual ~ANative16(void) = NULL;

		virtual sfn GetID  (void) ro -> N16_ID = NULL;
		virtual sfn GetSign(void) ro -> Sign   = NULL;

		virtual sfn GetSigned  (void) ro -> sInt16 = NULL;
		virtual sfn GetUnsigned(void) ro -> uInt16 = NULL;

		implem sfn GetTypeID(void) ro -> ro Ref(TypeData) = NULL;

		implem sfn ReInitalize(void) -> void = NULL;

		implem sfn Str(void) ro -> string = NULL;

		virtual sfn SetSigned  (ro sInt16 SignedIntToSet  ) -> void = NULL;
		virtual sfn SetUnsigned(ro uInt16 UnsignedIntToSet) -> void = NULL;
	};
}

Context_End
