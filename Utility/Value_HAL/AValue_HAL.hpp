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



namespace NotationEngine::Utility::Value
{
	inline namespace Source
	{
	}
}



// Sector: Flexible AValue_Hal
#ifdef __FLEX_VHAL__

	namespace NotationEngine::Utility::Value
	{
		inline namespace Alias
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

		inline namespace Meta
		{
		}

		inline namespace Source
		{
			class AValue_HAL : public Value
			{
			public:
				~AValue_HAL(void) {};

				virtual const Sign      GetSign  (void) ro = NULL;
				virtual const TypeData* GetTypeID(void) ro = NULL;

				virtual void Reinitialize(void)= NULL;

				virtual const string Str(void) const = NULL;

				virtual void SetZero(void) = NULL;

				virtual void SetValue(const uInt64            ValueToSet) = NULL;
				virtual void SetValue(const AValue_HAL* const ValueToSet) = NULL;
			};
		}
	}

#endif
