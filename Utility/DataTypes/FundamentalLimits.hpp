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



Context(NotationEngine::Utility)

SAlias
{
	// C++

	using std::abs;
	using std::min;

	GUsing(NumLimits) = std::numeric_limits<Type>;
}

SSource
{
	//Constants


	#ifdef __USE_TypeSafe__

		constant sInt8 SInt8Min  = NumLimits<unsafe::sInt8>::min();
		constant sInt8 SInt8Max  = NumLimits<unsafe::sInt8>::max();

		constant sInt16 SInt16Max = NumLimits<unsafe::sInt16>::min();
		constant sInt16 SInt16Min = NumLimits<unsafe::sInt16>::max();

		constant sInt32 SInt32Min = NumLimits<unsafe::sInt32>::min();
		constant sInt32 SInt32Max = NumLimits<unsafe::sInt32>::max();

		constant sInt64 SInt64Min = NumLimits<unsafe::sInt64>::min();
		constant sInt64 SInt64Max = NumLimits<unsafe::sInt64>::max();

		constant uInt8  UInt8Max  = NumLimits<unsafe::uInt8 >::max();
		constant uInt16 UInt16Max = NumLimits<unsafe::uInt16>::max();
		constant uInt32 UInt32Max = NumLimits<unsafe::uInt32>::max();
		constant uInt64 UInt64Max = NumLimits<unsafe::uInt64>::max();

		constant float32 Float32Min       = NumLimits<unsafe::float32>::min          ()                 ;
		constant float32 Float32MinNeg    = NumLimits<unsafe::float32>::min          () * float32(-1.0f);
		constant float32 Float32Max       = NumLimits<unsafe::float32>::max          ()                 ;
		constant float32 Float32MaxNeg    = NumLimits<unsafe::float32>::max          () * float32(-1.0f);
		constant float32 Float32Precision = NumLimits<unsafe::float32>::epsilon      ()                 ;
		constant float32 Float32Infinity  = NumLimits<unsafe::float32>::infinity     ()                 ;
		constant float32 Float32QNaN      = NumLimits<unsafe::float32>::quiet_NaN    ()                 ;
		constant float32 Float32SNaN      = NumLimits<unsafe::float32>::signaling_NaN()                 ;

		constant float64 Float64Min       = NumLimits<unsafe::float64>::min          ()                ;
		constant float64 Float64MinNeg    = NumLimits<unsafe::float64>::min          () * float64(-1.0);
		constant float64 Float64Max       = NumLimits<unsafe::float64>::max          ()                ;
		constant float64 Float64MaxNeg    = NumLimits<unsafe::float64>::max          () * float64(-1.0);
		constant float64 Float64Precision = NumLimits<unsafe::float64>::epsilon      ()                ;
		constant float64 Float64Infinity  = NumLimits<unsafe::float64>::infinity     ()                ;
		constant float64 Float64QNaN      = NumLimits<unsafe::float64>::quiet_NaN    ()                ;
		constant float64 Float64SNaN      = NumLimits<unsafe::float64>::signaling_NaN()                ;

		constant unsafe::floatEP FloatEP_Min       = NumLimits<unsafe::floatEP>::min          ()                         ;
		constant unsafe::floatEP FloatEP_MinNeg    = NumLimits<unsafe::floatEP>::min          () * unsafe::floatEP(-1.0L);
		constant unsafe::floatEP FloatEP_Max       = NumLimits<unsafe::floatEP>::max          ()                         ;
		constant unsafe::floatEP FloatEP_MaxNeg    = NumLimits<unsafe::floatEP>::max          () * unsafe::floatEP(-1.0L);
		constant unsafe::floatEP FloatEP_Precision = NumLimits<unsafe::floatEP>::epsilon      ()                         ;
		constant unsafe::floatEP FloatEP_Infinity  = NumLimits<unsafe::floatEP>::infinity     ()                         ;
		constant unsafe::floatEP FloatEP_QNaN      = NumLimits<unsafe::floatEP>::quiet_NaN    ()                         ;
		constant unsafe::floatEP FloatEP_SNaN      = NumLimits<unsafe::floatEP>::signaling_NaN()                         ;

	#else
		
		constant sInt8 SInt8Min  = NumLimits<sInt8>::min();
		constant sInt8 SInt8Max  = NumLimits<sInt8>::max();

		constant sInt16 SInt16Max = NumLimits<sInt16>::min();
		constant sInt16 SInt16Min = NumLimits<sInt16>::max();

		constant sInt32 SInt32Min = NumLimits<sInt32>::min();
		constant sInt32 SInt32Max = NumLimits<sInt32>::max();

		constant sInt64 SInt64Min = NumLimits<sInt64>::min();
		constant sInt64 SInt64Max = NumLimits<sInt64>::max();

		constant uInt8  UInt8Max  = NumLimits<uInt8 >::max();
		constant uInt16 UInt16Max = NumLimits<uInt16>::max();
		constant uInt32 UInt32Max = NumLimits<uInt32>::max();
		constant uInt64 UInt64Max = NumLimits<uInt64>::max();

		constant float32 Float32Min       = NumLimits<float32>::min          ()                 ;
		constant float32 Float32MinNeg    = NumLimits<float32>::min          () * float32(-1.0f);
		constant float32 Float32Max       = NumLimits<float32>::max          ()                 ;
		constant float32 Float32MaxNeg    = NumLimits<float32>::max          () * float32(-1.0f);
		constant float32 Float32Precision = NumLimits<float32>::epsilon      ()                 ;
		constant float32 Float32Infinity  = NumLimits<float32>::infinity     ()                 ;
		constant float32 Float32QNaN      = NumLimits<float32>::quiet_NaN    ()                 ;
		constant float32 Float32SNaN      = NumLimits<float32>::signaling_NaN()                 ;

		constant float64 Float64Min       = NumLimits<float64>::min          ()                ;
		constant float64 Float64MinNeg    = NumLimits<float64>::min          () * float64(-1.0);
		constant float64 Float64Max       = NumLimits<float64>::max          ()                ;
		constant float64 Float64MaxNeg    = NumLimits<float64>::max          () * float64(-1.0);
		constant float64 Float64Precision = NumLimits<float64>::epsilon      ()                ;
		constant float64 Float64Infinity  = NumLimits<float64>::infinity     ()                ;
		constant float64 Float64QNaN      = NumLimits<float64>::quiet_NaN    ()                ;
		constant float64 Float64SNaN      = NumLimits<float64>::signaling_NaN()                ;

		constant floatEP FloatEP_Min       = NumLimits<floatEP>::min          ()                 ;
		constant floatEP FloatEP_MinNeg    = NumLimits<floatEP>::min          () * floatEP(-1.0L);
		constant floatEP FloatEP_Max       = NumLimits<floatEP>::max          ()                 ;
		constant floatEP FloatEP_MaxNeg    = NumLimits<floatEP>::max          () * floatEP(-1.0L);
		constant floatEP FloatEP_Precision = NumLimits<floatEP>::epsilon      ()                 ;
		constant floatEP FloatEP_Infinity  = NumLimits<floatEP>::infinity     ()                 ;
		constant floatEP FloatEP_QNaN      = NumLimits<floatEP>::quiet_NaN    ()                 ;
		constant floatEP FloatEP_SNaN      = NumLimits<floatEP>::signaling_NaN()                 ;
		
	#endif

	// Functions

	filter SInt
	{
		template<typename SInt>
		constant sfn AtBound(ro SInt _value) -> bool
		{
			M_constraint(IsInt<SInt>(), "Type must be a signed fundamental integer.");

			return _value == NumLimits<SInt>::max() || _value == NumLimits<SInt>::min();
		}
	}
	
	filter Float
	{
		template<typename Float>
		constant sfn AtBound(ro Float _value) -> bool
		{
			M_constraint(IsFloat<Float>(), "Type must be a fundamental float.");

			ro stack<Float> floatMin  = NumLimits<Float>::min    ();
			ro stack<Float> floatMax  = NumLimits<Float>::max    ();
			ro stack<Float> precision = NumLimits<Float>::epsilon();

			ro stack<Float> valueAbs = abs(_value           ),
					        minAbs   = abs(floatMin         ),
					        maxAbs   = abs(floatMax         ),
					        diffMin  = abs(_value - floatMin),
					        diffMax  = abs(_value - floatMax);

			stack<bool> exactlyEqualMin = (_value == floatMin),
				        exactlyEqualMax = (_value == floatMax),

				        closeToZeroMin  = (_value == 0 || diffMin < floatMin),
				        closeToZeroMax  = (_value == 0 || diffMax < floatMin);

			// TODO: I don't remember if it was exactly equal min or max....
			if (exactlyEqualMin || exactlyEqualMax)
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

Context_End