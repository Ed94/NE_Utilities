/*
Title       : Fundamental Limits
Author      : Edward R. Gonzalez
File Name   : FundamentalLimits.hpp
Date Created: 5-27-2019

Description:
Defines constants and functionality for the bounds of the fundamental numerical types.
*/

#pragma once

// Includes

// C++

#include <algorithm>
#include <cmath>
#include <limits>


// Notation Engine

#include "FundamentalTypes.hpp"



namespace NotationEngine::Utility
{
	SAlias
	{
		// C++

		using std::abs;
		using std::min;

		template<typename Type>
		using NumLimits = std::numeric_limits<Type>;
	}

	SSource
	{
		//Constants

		constexpr sInt8 SInt8Min  = NumLimits<sInt8>::min();
		constexpr sInt8 SInt8Max  = NumLimits<sInt8>::max();

		constexpr sInt16 SInt16Max = NumLimits<sInt16>::min();
		constexpr sInt16 SInt16Min = NumLimits<sInt16>::max();

		constexpr sInt32 SInt32Min = NumLimits<sInt32>::min();
		constexpr sInt32 SInt32Max = NumLimits<sInt32>::max();

		constexpr sInt64 SInt64Min = NumLimits<sInt64>::min();
		constexpr sInt64 SInt64Max = NumLimits<sInt64>::max();

		constexpr uInt8  UInt8Max  = NumLimits<uInt8 >::max();
		constexpr uInt16 UInt16Max = NumLimits<uInt16>::max();
		constexpr uInt32 UInt32Max = NumLimits<uInt32>::max();
		constexpr uInt64 UInt64Max = NumLimits<uInt64>::max();

		constexpr float32 Float32Min       = NumLimits<float32>::min          ()                 ;
		constexpr float32 Float32MinNeg    = NumLimits<float32>::min          () * float32(-1.0f);
		constexpr float32 Float32Max       = NumLimits<float32>::max          ()                 ;
		constexpr float32 Float32MaxNeg    = NumLimits<float32>::max          () * float32(-1.0f);
		constexpr float32 Float32Precision = NumLimits<float32>::epsilon      ()                 ;
		constexpr float32 Float32Infinity  = NumLimits<float32>::infinity     ()                 ;
		constexpr float32 Float32QNaN      = NumLimits<float32>::quiet_NaN    ()                 ;
		constexpr float32 Float32SNaN      = NumLimits<float32>::signaling_NaN()                 ;

		constexpr float64 Float64Min       = NumLimits<float64>::min          ()                ;
		constexpr float64 Float64MinNeg    = NumLimits<float64>::min          () * float64(-1.0);
		constexpr float64 Float64Max       = NumLimits<float64>::max          ()                ;
		constexpr float64 Float64MaxNeg    = NumLimits<float64>::max          () * float64(-1.0);
		constexpr float64 Float64Precision = NumLimits<float64>::epsilon      ()                ;
		constexpr float64 Float64Infinity  = NumLimits<float64>::infinity     ()                ;
		constexpr float64 Float64QNaN      = NumLimits<float64>::quiet_NaN    ()                ;
		constexpr float64 Float64SNaN      = NumLimits<float64>::signaling_NaN()                ;

		constexpr floatEP FloatEP_Min       = NumLimits<floatEP>::min          ()                 ;
		constexpr floatEP FloatEP_MinNeg    = NumLimits<floatEP>::min          () * floatEP(-1.0L);
		constexpr floatEP FloatEP_Max       = NumLimits<floatEP>::max          ()                 ;
		constexpr floatEP FloatEP_MaxNeg    = NumLimits<floatEP>::max          () * floatEP(-1.0L);
		constexpr floatEP FloatEP_Precision = NumLimits<floatEP>::epsilon      ()                 ;
		constexpr floatEP FloatEP_Infinity  = NumLimits<floatEP>::infinity     ()                 ;
		constexpr floatEP FloatEP_QNaN      = NumLimits<floatEP>::quiet_NaN    ()                 ;
		constexpr floatEP FloatEP_SNaN      = NumLimits<floatEP>::signaling_NaN()                 ;

		// Functions

		inline namespace SInt
		{
			template<typename SInt>
			constexpr bool AtBound(const SInt _value)
			{
				static_assert(IsInt<SInt>(), "Type must be a signed fundamental integer.");

				return _value == NumLimits<SInt>::max() || _value == NumLimits<SInt>::min();
			}
		}
		
		inline namespace Float
		{
			template<typename Float>
			constexpr bool AtBound(const Float _value)
			{
				static_assert(IsFloat<Float>(), "Type must be a fundamental float.");

				const Float floatMin  = NumLimits<Float>::min    ();
				const Float floatMax  = NumLimits<Float>::max    ();
				const Float precision = NumLimits<Float>::epsilon();

				const Float valueAbs = abs(_value           ),
							minAbs   = abs(floatMin         ),
							maxAbs   = abs(floatMax         ),
							diffMin  = abs(_value - floatMin),
							diffMax  = abs(_value - floatMax);

				bool exactlyEqualMin = (_value == floatMin),
					 exactlyEqualMax = (_value == floatMax),

					 closeToZeroMin  = (_value == 0 || diffMin < floatMin),
					 closeToZeroMax  = (_value == 0 || diffMax < floatMin) ;

				if (exactlyEqualMin || exactlyEqualMin)
				{
					return true;
				}
				else if (closeToZeroMin)
				{
					return (diffMin < (precision * floatMin));
				}
				else if (closeToZeroMax)
				{
					return (diffMax < (precision * floatMax));
				}
				else
				{
					return 
						(diffMin / min(valueAbs * floatMin, floatMax) < precision) || 
						(diffMax / min(valueAbs * floatMax, floatMax) < precision)   ;
				}
			}
		}
	}
}
