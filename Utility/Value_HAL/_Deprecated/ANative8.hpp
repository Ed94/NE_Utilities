/*
Title       : Abstract Native-8
Author      : Edward R. Gonzalez
File Name   : ANative8.hpp
Date Created: 9-30-2019

Description:
Defines the Native-8 abstract interface.
*/

#pragma once

// Includes

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
	enum class N8_ID : uInt8
	{
		Signed  ,
		Unsigned,
	};

	class ANative8 : public Value
	{
	public:
		virtual ~ANative8(void) = NULL;

		virtual sfn GetID  (void) ro -> N8_ID = NULL;
		virtual sfn GetSign(void) ro -> Sign  = NULL;

		virtual sfn GetSigned  (void) ro -> sInt8         = NULL;
		virtual sfn GetUnsigned(void) ro -> uInt8         = NULL;

		implem sfn GetTypeID(void) ro -> ro Ref(TypeData) = NULL;

		implem sfn ReInitalize(void) -> void = NULL;

		implem sfn Str(void) ro -> string = NULL;

		virtual sfn SetSigned  (ro sInt8 SignedIntToSet  ) -> void = NULL;
		virtual sfn SetUnsigned(ro uInt8 UnsignedIntToSet) -> void = NULL;
	};
}

Context_End
