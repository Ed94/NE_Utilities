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



namespace NotationEngine::Utility::Value
{
	inline namespace Alias
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

	inline namespace Meta
	{
		template<typename Type>
		constexpr bool IsIntOrFloat()
		{
			return IsInt<Type>() || IsFloat<Type>();
		}
	}

	inline namespace Source
	{
		template<typename NType>
		class ANativeT : public APrimitiveValue<NType>
		{
			M_constraint(IsIntOrFloat<NType>(), "ANativeT requires a provided type of int or float fundamental type (Of any bit size).");

		public:
			virtual ~ANativeT(void) = NULL;

			virtual const Sign   GetSign (void) const = NULL;
			virtual const NType& GetValue(void) const = NULL;

			virtual const TyepData& GetTypeID(void) const = NULL;

			virtual void Reinitialize(void) = NULL;

			virtual const string Str(void) const = NULL;

			virtual void SetZero(void) -> void = NULL;

			virtual void SetValue(const uInt64            ValueToSet) -> void = NULL;
			virtual void SetValue(const AValue_HAL* const ValueToSet) -> void = NULL;

			virtual void SetValue(const NType& ValueToSet) -> void = NULL;
		};
	}
}
