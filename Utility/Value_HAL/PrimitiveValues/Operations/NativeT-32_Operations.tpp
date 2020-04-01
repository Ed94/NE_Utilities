/*
Title       : Native Template 32-bit Operations Implementation
Author      : Edward R. Gonzalez
File Name   : NativeT_Operations.tpp
Date Created: 11-10-2019

Description:
Implements the Native Template operations for 32-bit fundamental types.
*/

#pragma once

// Parent Header
//#include "NativeT_Operations.hpp"

#include "FundamentalLimits.hpp"



namespace NotationEngine::Utility::Value
{
	SSource
	{
	// Comparison

		// Operator==

		bool operator==(const NativeT<uInt32> _subject, const NativeT<sInt32> _reference)
		{
			return _subject.GetValue() <= SInt32Max ? sInt32(_subject.GetValue()) == _reference.GetValue() : false;
		}

		bool operator==(const NativeT<sInt32> _subject, const NativeT<uInt32> _reference)
		{
			return _reference.GetValue() <= SInt32Max ? _subject.GetValue() == sInt32(_reference.GetValue()) : false;
		}

		template<typename N32>
		bool operator== (const NativeT<float32> _subject, const NativeT<N32> _reference)
		{
			return Float::ApproxEqual(_subject, float32(_reference));
		}

		template<typename N32>
		bool operator== (const NativeT<N32> _subject, const NativeT<float32> _reference)
		{
			return Float::ApproxEqual(float32(_subject.GetValue()), _reference.GetValue());
		}
		
		bool operator== (const NativeT<float32> _subject, const NativeT<float32> _reference)
		{
			return Float::ApproxEqual(_subject.GetValue(), _reference.GetValue());
		}

		// Operator !=

		bool operator!=(const NativeT<uInt32> _subject, const NativeT<sInt32> _reference)
		{
			return _subject.GetValue() <= SInt32Max ? sInt32(_subject.GetValue()) != _reference.GetValue() : true;
		}

		bool operator!=(const NativeT<sInt32> _subject, const NativeT<uInt32> _reference)
		{
			return _reference.GetValue() <= SInt32Max ? _subject.GetValue() != sInt32(_reference.GetValue()) : true;
		}

		template<typename N32>
		bool operator!= (const NativeT<float32> _subject, const NativeT<N32> _reference)
		{
			return !Float::ApproxEqual(_subject, float32(_reference));
		}

		template<typename N32>
		bool operator!= (const NativeT<N32> _subject, const NativeT<float32> _reference)
		{
			return !Float::ApproxEqual(float32(_subject.GetValue()), _reference.GetValue());
		}

		bool operator!= (const NativeT<float32> _subject, const NativeT<float32> _reference)
		{
			return !Float::ApproxEqual(_subject.GetValue(), _reference.GetValue());
		}

		// Operator <

		bool operator<(const NativeT<uInt32> _subject, const NativeT<sInt32> _reference)
		{
			return _subject.GetValue() <= SInt32Max ? sInt32(_subject.GetValue()) < _reference.GetValue() : false;
		}

		bool operator<(const NativeT<sInt32> _subject, const NativeT<uInt32> _reference)
		{
			return _reference.GetValue() <= SInt32Max ? _subject.GetValue() < sInt32(_reference.GetValue()) : true;
		}

		template<typename N32>
		bool operator< (const NativeT<float32> _subject, const NativeT<N32> _reference)
		{
			return Float::ApproxLess(_subject, float32(_reference));
		}

		template<typename N32>
		bool operator< (const NativeT<N32> _subject, const NativeT<float32> _reference)
		{
			return Float::ApproxLess(float32(_subject.GetValue()), _reference.GetValue());
		}

		bool operator< (const NativeT<float32> _subject, const NativeT<float32> _reference)
		{
			return Float::ApproxLess(_subject.GetValue(), _reference.GetValue());
		}

		// Operator >

		bool operator> (const NativeT<uInt32> _subject, const NativeT<sInt32> _reference)
		{
			return _subject.GetValue() > SInt32Max ? sInt32(_subject.GetValue()) > _reference.GetValue() : true;
		}

		bool operator> (const NativeT<sInt32> _subject, const NativeT<uInt32> _reference)
		{
			return _reference.GetValue() > SInt32Max ? _subject.GetValue() > sInt32(_reference.GetValue()) : false;
		}

		template<typename N32>
		bool operator> (const NativeT<float32> _subject, const NativeT<N32> _reference)
		{
			return Float::ApproxGreater(_subject, float32(_reference));
		}

		template<typename N32>
		bool operator>(const NativeT<N32> _subject, const NativeT<float32> _reference)
		{
			return Float::ApproxGreater(float32(_subject.GetValue()), _reference.GetValue());
		}

		bool operator> (const NativeT<float32> _subject, const NativeT<float32> _reference)
		{
			return Float::ApproxGreater(_subject.GetValue(), _reference.GetValue());
		}

		// Arithmetic

		// Operator +

		template<typename N32_S, typename N32_R>
		NativeT<sInt32> operator+ (const NativeT<N32_S> _subject, const NativeT<N32_R> _reference)
		{
			const Sign&& subjSign = _subject.GetSign(), refSign = _reference.GetSign();

			sInt64 result = sInt64(_subject.GetValue()) + sInt64(_reference.GetValue());

			// Note: This can't prevent overflow by providing an uInt32... (Limitation...)

			if (result <= SInt32Min || result >= SInt32Max)
			{
				return NativeT<sInt32>(sInt32(result));
			}
			else
			{
				throw std::overflow_error("Native32 addition signed overflow.");
			}
		}

		NativeT<uInt32> operator+ (const NativeT<uInt32> _subject, const NativeT<uInt32> _reference)
		{
			uInt64 result = uInt64(_subject.GetValue()) + uInt64(_reference.GetValue());

			if (result <= UInt32Max)
			{
				return NativeT<uInt32>(uInt32(result));
			}
			else
			{
				throw std::overflow_error("Native32 addition unsigned overflow.");
			}
		}

		template<typename N32>
		NativeT<float32> operator+ (const NativeT<float32> _subject, const NativeT<N32> _reference)
		{
			float32 result = _subject.GetValue() + float32(_reference.GetValue());

			if (result == Float32Infinity || result == Float32QNaN)
			{
				throw std::overflow_error("Native32 addition float overflow.");
			}
			else
			{
				return NativeT<float32>(result);
			}
		}

		template<typename N32>
		NativeT<float32> operator+ (const NativeT<N32> _subject, const NativeT<float32> _reference)
		{
			float32 result = float32(_subject.GetValue()) + _reference.GetValue();

			if (result == Float32Infinity || result == Float32QNaN)
			{
				throw std::overflow_error("Native32 addition float overflow.");
			}
			else
			{
				return NativeT<float32>(result);
			}
		}

		NativeT<float32> operator+(const NativeT<float32> _subject, const NativeT<float32> _reference)
		{
			float32 result = _subject.GetValue() + _reference.GetValue();

			if (result == Float32Infinity || result == Float32QNaN)
			{
				throw std::overflow_error("Native32 addition float overflow.");
			}
			else
			{
				return NativeT<float32>(float32(result));
			}
		}

		// Operator -

		NativeT<uInt32> operator- (const NativeT<uInt32> _subject, const NativeT<uInt32> _reference)
		{
			uInt64 result = uInt64(_subject.GetValue()) - uInt64(_reference.GetValue());

			if (result <= UInt32Max)
			{
				return NativeT<uInt32>(uInt32(result));
			}
			else
			{
				throw std::overflow_error("Native32 addition unsigned overflow.");
			}
		}

		template<typename N32>
		NativeT<float32> operator- (const NativeT<float32> _subject, const NativeT<N32> _reference)
		{
			float32 result = _subject.GetValue() - float32(_reference.GetValue());

			if (result == Float32Infinity || result == Float32QNaN)
			{
				throw std::overflow_error("Native32 addition float overflow.");
			}
			else
			{
				return NativeT<float32>(result);
			}
		}

		template<typename N32>
		NativeT<float32> operator- (const NativeT<N32> _subject, const NativeT<float32> _reference)
		{
			float32 result = float32(_subject.GetValue()) - _reference.GetValue();

			if (result == Float32Infinity || result == Float32QNaN)
			{
				throw std::overflow_error("Native32 addition float overflow.");
			}
			else
			{
				return NativeT<float32>(result);
			}
		}

		NativeT<float32> operator- (const NativeT<float32> _subject, const NativeT<float32> _reference)
		{
			float32 result = _subject.GetValue() - _reference.GetValue();

			if (result == Float32Infinity || result == Float32QNaN)
			{
				throw std::overflow_error("Native32 addition float overflow.");
			}
			else
			{
				return NativeT<float32>(float32(result));
			}
		}

		// Operator *

		template<typename N32_S, typename N32_R>
		NativeT<sInt32> operator* (const NativeT<N32_S> _subject, const NativeT<N32_R> _reference)
		{
			sInt32 result = _subject.GetValue() * _reference.GetValue();

			if (result != sInt32(0) && result / _subject.GetValue() != _reference.GetValue())
			{
				throw std::overflow_error("Native32 multiplication signed integer overflow.");
			}
			else
			{
				return NativeT<sInt32>(result);
			}
		}

		NativeT<uInt32> operator* (const NativeT<uInt32> _subject, const NativeT<uInt32> _reference)
		{
			uInt32 result = _subject.GetValue() * _reference.GetValue();

			if (result != uInt32(0) && result / _subject.GetValue() != _reference.GetValue())
			{
				throw std::overflow_error("Native32 multiplication unsigned integer overflow.");
			}
			else
			{
				return NativeT<uInt32>(uInt32(result));
			}
		}

		template<typename N32>
		NativeT<float32> operator* (const NativeT<float32> _subject, const NativeT<N32> _reference)
		{
			float32 result = _subject.GetValue() * float32(_reference.GetValue());

			if (result == Float32Infinity || result == Float32QNaN)
			{
				throw std::overflow_error("Native32 multiplication float overflow.");
			}
			else
			{
				return NativeT<float32>(result);
			}
		}

		template<typename N32>
		NativeT<float32> operator* (const NativeT<N32> _subject, const NativeT<float32> _reference)
		{
			float32 result = float32(_subject) * _reference.GetValue();

			if (result == Float32Infinity || result == Float32QNaN)
			{
				throw std::overflow_error("Native32 multiplication float overflow.");
			}
			else
			{
				return NativeT<float32>(result);
			}
		}

		NativeT<float32> operator* (const NativeT<float32> _subject, const NativeT<float32> _reference)
		{
			float32 result = _subject.GetValue() * _reference.GetValue();

			if (result == Float32Infinity || result == Float32QNaN)
			{
				throw std::overflow_error("Native32 multiplication float overflow.");
			}
			else
			{
				return NativeT<float32>(float32(result));
			}
		}

		// Operator /

		template<typename N32_S, typename N32_R>
		NativeT<sInt32> operator/ (const NativeT<N32_S> _subject, const NativeT<N32_R> _reference)
		{
			if 
			(
				_subject  .GetValue() == SInt32Min  && 
				_reference.GetValue() == sInt32(-1) || 
				_reference.GetValue() == sInt32(0)
			)
			{
				throw std::overflow_error("Native32: Two's Complement division overflow or divide by zero.");
			}
			else
			{
				return NativeT<sInt32>(sInt32(_subject.GetValue() / _reference.GetValue()));
			}
		}

		NativeT<uInt32> operator/ (const NativeT<uInt32> _subject, const NativeT<uInt32> _reference)
		{
			if (_reference.GetValue() == uInt32(0U))
			{
				throw std::logic_error("Native32 divide by zero.");
			}
			else
			{
				return NativeT<uInt32>( uInt32(_subject.GetValue() / _reference.GetValue()) );
			}
		}

		template<typename N32>
		NativeT<float32> operator/ (const NativeT<float32> _subject, const NativeT<N32> _reference)
		{
			float32 result = _subject.GetValue() / _reference.GetValue();

			if (result == Float32Infinity || result == Float32QNaN)
			{
				throw std::overflow_error("Native32 multiplication float overflow.");
			}
			else
			{
				return NativeT<float32>(result);
			}
		}

		template<typename N32>
		NativeT<float32> operator/ (const NativeT<N32> _subject, const NativeT<float32> _reference)
		{
			float32 result = _subject.GetValue() / _reference.GetValue();

			if (result == Float32Infinity || result == Float32QNaN)
			{
				throw std::overflow_error("Native32 multiplication float overflow.");
			}
			else
			{
				return NativeT<float32>(result);
			}
		}

		NativeT<float32> operator/ (const NativeT<float32> _subject, const NativeT<float32> _reference)
		{
			float32 result = _subject.GetValue() / _reference.GetValue();

			if (result == Float32Infinity || result == Float32QNaN)
			{
				throw std::overflow_error("Native32 multiplication float overflow.");
			}
			else
			{
				return NativeT<float32>(float32(result));
			}
		}
	}
}
