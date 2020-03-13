/*
Title       : Fundamental Types
Author      : Edward R. Gonzalez
File Name   : FundamentalTypes.hpp
Date Created: 2-10-2019

Description:
Contains Aliases and other helpful definitions for the fundamental types supported by C++.
*/

#pragma once

// Includes

// Notation Engine
#include "Dev/DevMeta.hpp"
#include "Utility/Reflection/Meditate.hpp"



namespace NotationEngine::Utility
{
	inline namespace Alias
	{
		// C++

		//Integers

		//Signed

		using sInt8  = signed           char;
		using sInt16 = signed short     int ;
		using sInt32 = signed           int ;
		using sInt64 = signed long long int ;

		//Unsigned

		using uInt8  = unsigned            char;
		using uInt16 = unsigned      short int ;
		using uInt32 = unsigned            int ;
		using uInt64 = unsigned long long  int ;

		//Floats

		using float32 =      float ;
		using float64 =      double;
		using floatEP = long double;   // Not accessible in MSVC (Turns into regular doubles)

		// Notation Engine

		using NE_U_R::IsSameType;
		using NE_U_R::TypeData  ;
		using NE_U_R::Where     ;
	}

	inline namespace Meta
	{
		template<typename Type>
		constexpr bool IsInt()
		{
			return IsSameType<Type, sInt8 >() || 
				   IsSameType<Type, sInt16>() || 
				   IsSameType<Type, sInt32>() || 
				   IsSameType<Type, sInt64>() ||
				   IsSameType<Type, uInt8 >() ||
				   IsSameType<Type, uInt16>() ||
				   IsSameType<Type, uInt32>() ||
				   IsSameType<Type, uInt64>()   ;
		}

		template<typename Type>
		constexpr bool IsFloat()
		{
			return IsSameType<Type, float32>() || IsSameType<Type, float64>() || IsSameType<Type, floatEP>();
		}
	}

	inline namespace Source
	{
		enum class Sign
		{
			Positive =  1,
			Neutral  =  0,
			Negative = -1,
		};

		inline namespace Int
		{
			template<typename Int>
			constexpr Where<IsInt<Int>(), const Sign> 
			Signum(const Int _value)
			{
				return Sign( (Int(0) < _value) - (_value < Int(0)) );
			}
		}
		
		inline namespace Float
		{
			template<typename Float> 
			constexpr Where<IsFloat<Float>(), const Sign> 
			Signum(const Float _value)
			{
				return Sign( ( Float(0.0) < _value ) - ( _value < Float(0.0) ) );
			}

			bool ApproxEqual  (const float32 First, const float32 Second);
			bool ApproxGreater(const float32 First, const float32 Second);
			bool ApproxLess   (const float32 First, const float32 Second);

			bool ApproxEqual  (const float64 First, const float64 Second);
			bool ApproxGreater(const float64 First, const float64 Second);
			bool ApproxLess   (const float64 First, const float64 Second);

			template<typename Float> Where<IsFloat<Float>(), bool> ApproxEqual  (const Float First, const Float Second);
			template<typename Float> Where<IsFloat<Float>(), bool> ApproxGreater(const Float First, const Float Second);
			template<typename Float> Where<IsFloat<Float>(), bool> ApproxLess   (const Float First, const Float Second);
		}
	}
}
