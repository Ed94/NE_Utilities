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



namespace NotationEngine::Utility
{
	inline namespace Alias
	{
		using uInt256   = boost::multiprecision::uint256_t       ;   // 128-bit unsigned integer.
		using sInt256   = boost::multiprecision::int256_t        ;   // 128-bit signed integer.
		using Float_P50 = boost::multiprecision::cpp_bin_float_50;   // 50-decimal place precision float.
	}

	inline namespace Meta
	{
		template<typename Type>
		constexpr bool IsBoostInt()
		{
			return IsSameType<Type, uInt256>() ||
				   IsSameType<Type, sInt256>()   ;
		}

		template<typename Type>
		constexpr bool IsBoostFloat()
		{
			return IsSameType<Type, Float_P50>();
		}
	}

	inline namespace Source
	{
		inline const Float_P50& FloatP50_Min       = NumLimits<Float_P50>::min          ();
		inline const Float_P50& FloatP50_MinNeg    = FloatP50_Min * -1.0                  ;
		inline const Float_P50& FloatP50_Max       = NumLimits<Float_P50>::max          ();
		inline const Float_P50& FloatP50_MaxNeg    = FloatP50_Max * -1.0                  ;
		inline const Float_P50& FloatP50_Precision = NumLimits<Float_P50>::epsilon      ();
		inline const Float_P50& FloatP50_Infinity  = NumLimits<Float_P50>::infinity     ();
		inline const Float_P50& FloatP50_QNaN      = NumLimits<Float_P50>::quiet_NaN    ();
		inline const Float_P50& FloatP50_SNaN      = NumLimits<Float_P50>::signaling_NaN();

		inline namespace BInt
		{
			template<typename BInt> constexpr Where<IsBoostInt<BInt>(), const Sign> 
			Signum(const BInt& _value)
			{
				return Sign((BInt(0) < _value) - (_value < BInt(0)));
			}
		}

		inline namespace BFloat
		{
			bool ApproxEqual  (const Float_P50& Subject, const Float_P50& Reference);
			bool ApproxGreater(const Float_P50& Subject, const Float_P50& Reference);
			bool ApproxLess   (const Float_P50& Subject, const Float_P50& Reference);

			template<typename BFloat> constexpr Where<IsBoostFloat<BFloat>(), const Sign> 
			Signum(const BFloat& _value)
			{
				return Sign( ApproxLess(Float_P50(0.0), _value) - ApproxLess(_value, Float_P50(0.0)) );
			}
		}
	}
}
