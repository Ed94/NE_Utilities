/*
Title       : A Value Hardware Abstraction Layer
Author      : Edward R. Gonzalez
File Name   : AValue_HAL.hpp
Date Created: 9-28-2019

Description:
Defines the Value Hardware Abstraction Layer class.

Used to further abstract away which variant of vHAL implementation being used in-case a non-native value implementation is being used,
that requires allocation management by the value manager. (For Example: Arbitrary-Precision numerics)

Note: The native or arbitrary precision only modes should only be restrictions handled by the value/object managers, not by the VHAL implementation.

Note: Do not use PVN_HAL for non-testing. A proper native template class should be used instead in the class within the engine that use VHAL in their structure.
*/

#pragma once

// Includes

// C++
#include <string>

// Notation Engine
#include "DevMeta.hpp"

#include "Meta/Objects/Value.hpp"

#include "FundamentalTypes.hpp"
#include "FundamentalLimits.hpp"



Context(NotationEngine::Utility::Value)

SSource
{
}

Context_End


// Sector: Flexible AValue_Hal
#ifdef __FLEX_VHAL__

	Context(NotationEngine::Utility::Value)

	SAlias
	{
		using std::string;

		using NE_M::Value;

		using NE_U  ::Sign    ;
		using NE_U_R::TypeData;

		using NE_U::uInt64;
		using NE_U::sInt64;
		using NE_U::float64;
		using NE_U::float32;
	}

	SMeta
	{
	}

	SSource
	{
		class AValue_HAL : public Value
		{
		public:
			~AValue_HAL(void) {};

			virtual sfn GetSign  (void) ro -> ro     Sign      = NULL;
			implem  sfn GetTypeID(void) ro -> ro Ref(TypeData) = NULL;

			implem sfn Reinitialize(void) -> void = NULL;

			implem sfn Str(void) ro -> ro string = NULL;

			virtual sfn SetZero(void) -> void = NULL;

			virtual sfn SetValue(ro        uInt64      ValueToSet) -> void = NULL;
			//virtual sfn SetValue(ro        sInt64      ValueToSet) -> void = NULL;
			//virtual sfn SetValue(ro        float32     ValueToSet) -> void = NULL;
			//virtual sfn SetValue(ro        float64     ValueToSet) -> void = NULL;
			virtual sfn SetValue(ro ptr<ro AValue_HAL> ValueToSet) -> void = NULL;
		};
	}

	Context_End

#endif
