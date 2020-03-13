/*
*/

#pragma once

// Includes

// C++
#include "FundamentalLimits.hpp"

// Boost
// Note: Move these to a better spot if possible later.
#include <boost/multiprecision/cpp_int.hpp>
#include <boost/multiprecision/cpp_bin_float.hpp>

// Notation Engine
#include "Dev/DevMeta.hpp"
#include "Context/Context_Util.hpp"



Context(NotationEngine::Utility)

SAlias
{
	using uInt256   = boost::multiprecision::uint256_t       ;   // 128-bit unsigned integer.
	using sInt256   = boost::multiprecision::int256_t        ;   // 128-bit signed integer.
	using Float_P50 = boost::multiprecision::cpp_bin_float_50;   // 50-decimal place precision float.
}

SMeta
{
	template<typename Type>
	constant sfn IsBoostInt() -> bool
	{
		return IsSameType<Type, uInt256>() ||
			   IsSameType<Type, sInt256>()   ;
	}

	template<typename Type>
	constant sfn IsBoostFloat() -> bool
	{
		return IsSameType<Type, Float_P50>();
	}
}

SSource
{
	superpos ro Ref(Float_P50) FloatP50_Min       = NumLimits<Float_P50>::min          ();
	superpos ro Ref(Float_P50) FloatP50_MinNeg    = FloatP50_Min * -1.0                  ;
	superpos ro Ref(Float_P50) FloatP50_Max       = NumLimits<Float_P50>::max          ();
	superpos ro Ref(Float_P50) FloatP50_MaxNeg    = FloatP50_Max * -1.0                  ;
	superpos ro Ref(Float_P50) FloatP50_Precision = NumLimits<Float_P50>::epsilon      ();
	superpos ro Ref(Float_P50) FloatP50_Infinity  = NumLimits<Float_P50>::infinity     ();
	superpos ro Ref(Float_P50) FloatP50_QNaN      = NumLimits<Float_P50>::quiet_NaN    ();
	superpos ro Ref(Float_P50) FloatP50_SNaN      = NumLimits<Float_P50>::signaling_NaN();

	filter BInt
	{
		template<typename BInt>
		constant sfn Signum(ro Ref(BInt) _value) -> Where<IsBoostInt<BInt>(), ro Sign>
		{
			return Sign((BInt(0) < _value) - (_value < BInt(0)));
		}
	}

	filter BFloat
	{
		sfn ApproxEqual  (ro Ref(Float_P50) Subject, ro Ref(Float_P50) Reference) -> bool;
		sfn ApproxGreater(ro Ref(Float_P50) Subject, ro Ref(Float_P50) Reference) -> bool;
		sfn ApproxLess   (ro Ref(Float_P50) Subject, ro Ref(Float_P50) Reference) -> bool;

		template<typename BFloat>
		constant sfn Signum(ro Ref(BFloat) _value) -> Where<IsBoostFloat<BFloat>(), ro Sign>
		{
			return Sign( ApproxLess(Float_P50(0.0), _value) - ApproxLess(_value, Float_P50(0.0)) );
		}
	}
}

Context_End
