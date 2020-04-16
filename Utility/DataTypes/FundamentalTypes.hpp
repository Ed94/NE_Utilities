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

#include <cmath>

// Notation Engine
#include "Dev/DevMeta.hpp"
#include "Context/Context_Util.hpp"
#include "Utility/Reflection/Meditate.hpp"

#ifdef __USE_TypeSafe__

	#include "type_safe/integer.hpp"
	#include "type_safe/floating_point.hpp"
	#include "type_safe/types.hpp"

#endif



Context(NotationEngine::Utility)

#ifdef __USE_TypeSafe__

	SSource
	{
		enum class Sign 
		{
			Positive =  1,
			Neutral  =  0,
			Negative = -1,
		};
	}

	Context(unsafe)
		
	SAlias
	{
		// C++

		// Integers

		// Signed
		using sInt8  = signed           char;
		using sInt16 = signed short     int ;
		using sInt32 = signed long      int ;
		using sInt64 = signed long long int ;

		// Unsigned

		using uInt8  = unsigned            char;
		using uInt16 = unsigned short      int ;
		using uInt32 = unsigned long       int ;
		using uInt64 = unsigned long long  int ;

		// Floats

		using float32 =      float ;
		using float64 =      double;
		using floatEP = long double;   // Not accessible in MSVC (Turns into regular doubles)

		using std::signbit;

		// Notation Engine

		using NE_U::Sign;

		using NE_U_R::IsSameType;
		using NE_U_R::Where     ;
	}

	SMeta
	{
		template<typename Type>
		constant sfn IsInt() -> bool
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
		constant sfn IsFloat() -> bool
		{
			return IsSameType<Type, float32>() || IsSameType<Type, float64>() || IsSameType<Type, floatEP>();
		}
	}

	SSource
	{
		filter Int
		{
			template<typename Int>
			constant sfn Signum(ro Int _value) -> Where<IsInt<Int>(), ro Sign>
			{
				//M_constraint(IsInt<Int>(), "Type for this function must be an sInt.");

				return Sign( (Int(0) < _value) - (_value < Int(0)) );
			}
		}
		
		filter Float
		{
			template<typename Float>
			constant sfn Signum(ro Float _value) -> Where<IsFloat<Float>(), ro Sign>
			{
				//M_constraint(IsFloat<Float>(), "Type for this function must be a float.");

				return Sign( ( Float(0.0) < _value ) - ( _value < Float(0.0) ) );
			}
		}
	}
	 
	Context_End



	SAlias
	{
		// TypeSafe

		namespace ts = type_safe;

		// Safe boolean...
		//using sBool = ts::boolean;

		// Integers

		// Signed

		using sInt8  = ts::integer<signed            char, ts::checked_arithmetic>;
		using sInt16 = ts::integer<signed      short int , ts::checked_arithmetic>;
		using sInt32 = ts::integer<signed      long  int , ts::checked_arithmetic>;
		using sInt64 = ts::integer<signed long long  int , ts::checked_arithmetic>;

		// Unsigned

		using uInt8  = ts::integer<unsigned            char, ts::checked_arithmetic>;
		using uInt16 = ts::integer<unsigned      short int , ts::checked_arithmetic>;
		using uInt32 = ts::integer<unsigned      long  int , ts::checked_arithmetic>;
		using uInt64 = ts::integer<unsigned long long  int , ts::checked_arithmetic>;

		// Floats

		using float32 = ts::floating_point<float >;
		using float64 = ts::floating_point<double>;

		using std::signbit;

		// Notation Engine

		using NE_U_R::IsSameType;
		using NE_U_R::TypeData  ;
		using NE_U_R::Where     ;
	}

	SMeta
	{
		template<typename Type>
		constant sfn IsInt() -> bool
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
		constant sfn IsFloat() -> bool
		{
			return IsSameType<Type, float32>() || IsSameType<Type, float64>() || IsSameType<Type, unsafe::floatEP>();
		}
	}

	SSource
	{
		filter Float
		{
			sfn ApproxEqual  (ro float32 First, ro float32 Second) -> bool;
			sfn ApproxGreater(ro float32 First, ro float32 Second) -> bool;
			sfn ApproxLess   (ro float32 First, ro float32 Second) -> bool;

			sfn ApproxEqual  (ro float64 First, ro float64 Second) -> bool;
			sfn ApproxGreater(ro float64 First, ro float64 Second) -> bool;
			sfn ApproxLess   (ro float64 First, ro float64 Second) -> bool;
		}

		template<typename Float> sfn ApproxEqual  (ro Float First, ro Float Second) -> Where<IsFloat<Float>(), bool>;
		template<typename Float> sfn ApproxGreater(ro Float First, ro Float Second) -> Where<IsFloat<Float>(), bool>;
		template<typename Float> sfn ApproxLess   (ro Float First, ro Float Second) -> Where<IsFloat<Float>(), bool>;
	}

#else

	SAlias
	{
		// C++

		// Integers

		// Signed

		using sInt8  = signed            char;
		using sInt16 = signed      short int ;
		using sInt32 = signed      long  int ;
		using sInt64 = signed long long  int ;

		// Unsigned

		using uInt8  = unsigned            char;
		using uInt16 = unsigned short      int ;
		using uInt32 = unsigned      long  int ;
		using uInt64 = unsigned long long  int ;

		// Floats

		using float32 =      float ;
		using float64 =      double;
		using floatEP = long double;   // Not accessible in MSVC (Turns into regular doubles)	

		// Notation Engine

		using NE_U_R::IsSameType;
		using NE_U_R::TypeData  ;
		using NE_U_R::Where     ;
	}

	SMeta
	{
		template<typename Type>
		constant sfn IsInt() -> bool
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
		constant sfn IsFloat() -> bool
		{
			return IsSameType<Type, float32>() || IsSameType<Type, float64>() || IsSameType<Type, floatEP>();
		}
	}

	SSource
	{
		enum class Sign
		{
			Positive =  1,
			Neutral  =  0,
			Negative = -1,
		};

		filter Int
		{
			template<typename Int>
			constant sfn Signum(ro Int _value) -> Where<IsInt<Int>(), ro Sign>
			{
				//M_constraint(IsInt<Int>(), "Type for this function must be an sInt.");

				return Sign( (Int(0) < _value) - (_value < Int(0)) );
			}
		}
		
		filter Float
		{
			template<typename Float>
			constant sfn Signum(ro Float _value) -> Where<IsFloat<Float>(), ro Sign>
			{
				//M_constraint(IsFloat<Float>(), "Type for this function must be a float.");

				return Sign( ( Float(0.0) < _value ) - ( _value < Float(0.0) ) );
			}

			sfn ApproxEqual  (ro float32 First, ro float32 Second) -> bool;
			sfn ApproxGreater(ro float32 First, ro float32 Second) -> bool;
			sfn ApproxLess   (ro float32 First, ro float32 Second) -> bool;

			sfn ApproxEqual  (ro float64 First, ro float64 Second) -> bool;
			sfn ApproxGreater(ro float64 First, ro float64 Second) -> bool;
			sfn ApproxLess   (ro float64 First, ro float64 Second) -> bool;
		}

		template<typename Float> sfn ApproxEqual  (ro Float First, ro Float Second) -> Where<IsFloat<Float>(), bool>;
		template<typename Float> sfn ApproxGreater(ro Float First, ro Float Second) -> Where<IsFloat<Float>(), bool>;
		template<typename Float> sfn ApproxLess   (ro Float First, ro Float Second) -> Where<IsFloat<Float>(), bool>;
	}

#endif

Context_End