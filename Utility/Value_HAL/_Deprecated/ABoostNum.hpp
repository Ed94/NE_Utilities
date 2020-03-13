/*
Title       : Abstract Interface Boost Number
Author      : Edward R. Gonzalez
File Name   : ABoostNum.hpp
Date Created: 11-10-2019

Description:
Defines the abstract interface for the BoostNum type.

*/

#pragma once

// Includes

// Notation Engine
#include "Dev/DevMeta.hpp"

#include "Meta/Objects/Value.hpp"

#include "DataTypes/FundamentalTypes.hpp"
#include "DataTypes/MultiprecisionTypes.hpp"



Context(NotationEngine::Utility::Value)

SAlias
{
	// C++

	using std::string;

	// Notation Engine

	using NE_M::Value;

	using NE_U_R::TypeData;
}

SSource 
{
	enum class BN_ID
	{
		BoostUInt ,
		BoostSInt ,
		BoostFloat
	};

	class ABoostNum : Value
	{
	public:

		virtual ~ABoostNum(void) = NULL;

		virtual sfn GetID  (void) ro -> BN_ID = NULL;
		virtual sfn GetSign(void) ro -> Sign  = NULL;

		virtual sfn GetSInteger(void) ro -> ro Ref(sInt256  ) = NULL;
		virtual sfn GetUInteger(void) ro -> ro Ref(uInt256  ) = NULL;
		virtual sfn GetFloat   (void) ro -> ro Ref(Float_P50) = NULL;

		implem sfn GetTypeID(void) ro -> ro Ref(TypeData) = NULL;

		implem sfn ReInitalize(void) -> void = NULL;

		implem sfn Str(void) ro -> string = NULL;

		virtual sfn SetToSInteger(ro Ref(sInt256  ) IntegerToSet) -> void = NULL;
		virtual sfn SetToUInteger(ro Ref(uInt256  ) IntegerToSet) -> void = NULL;
		virtual sfn SetToFloat   (ro Ref(Float_P50) FloatToSet  ) -> void = NULL;
	};
}

Context_End
