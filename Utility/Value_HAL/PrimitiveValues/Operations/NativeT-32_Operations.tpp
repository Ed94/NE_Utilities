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



Context(NotationEngine::Utility::Value)

SSource
{
// Comparison

	// Operator==

	sfn operator==(ro NativeT<uInt32> _subject, ro NativeT<sInt32> _reference) -> bool
	{
		return _subject.GetValue() <= SInt32Max ? sInt32(_subject.GetValue()) == _reference.GetValue() : false;
	}

	sfn operator==(ro NativeT<sInt32> _subject, ro NativeT<uInt32> _reference) -> bool
	{
		return _reference.GetValue() <= SInt32Max ? _subject.GetValue() == sInt32(_reference.GetValue()) : false;
	}

	template<typename N32>
	sfn operator== (ro NativeT<float32> _subject, ro NativeT<N32> _reference) -> bool
	{
		return Float::ApproxEqual(_subject, float32(_reference));
	}

	template<typename N32>
	sfn operator== (ro NativeT<N32> _subject, ro NativeT<float32> _reference) -> bool
	{
		return Float::ApproxEqual(float32(_subject.GetValue()), _reference.GetValue());
	}
	
	sfn operator== (ro NativeT<float32> _subject, ro NativeT<float32> _reference) -> bool
	{
		return Float::ApproxEqual(_subject.GetValue(), _reference.GetValue());
	}

	// Operator !=

	sfn operator!=(ro NativeT<uInt32> _subject, ro NativeT<sInt32> _reference) -> bool
	{
		return _subject.GetValue() <= SInt32Max ? sInt32(_subject.GetValue()) != _reference.GetValue() : true;
	}

	sfn operator!=(ro NativeT<sInt32> _subject, ro NativeT<uInt32> _reference) -> bool
	{
		return _reference.GetValue() <= SInt32Max ? _subject.GetValue() != sInt32(_reference.GetValue()) : true;
	}

	template<typename N32>
	sfn operator!= (ro NativeT<float32> _subject, ro NativeT<N32> _reference) -> bool
	{
		return !Float::ApproxEqual(_subject, float32(_reference));
	}

	template<typename N32>
	sfn operator!= (ro NativeT<N32> _subject, ro NativeT<float32> _reference) -> bool
	{
		return !Float::ApproxEqual(float32(_subject.GetValue()), _reference.GetValue());
	}

	sfn operator!= (ro NativeT<float32> _subject, ro NativeT<float32> _reference) -> bool
	{
		return !Float::ApproxEqual(_subject.GetValue(), _reference.GetValue());
	}

	// Operator <

	sfn operator<(ro NativeT<uInt32> _subject, ro NativeT<sInt32> _reference) -> bool
	{
		return _subject.GetValue() <= SInt32Max ? sInt32(_subject.GetValue()) < _reference.GetValue() : false;
	}

	sfn operator<(ro NativeT<sInt32> _subject, ro NativeT<uInt32> _reference) -> bool
	{
		return _reference.GetValue() <= SInt32Max ? _subject.GetValue() < sInt32(_reference.GetValue()) : true;
	}

	template<typename N32>
	sfn operator< (ro NativeT<float32> _subject, ro NativeT<N32> _reference) -> bool
	{
		return Float::ApproxLess(_subject, float32(_reference));
	}

	template<typename N32>
	sfn operator< (ro NativeT<N32> _subject, ro NativeT<float32> _reference) -> bool
	{
		return Float::ApproxLess(float32(_subject.GetValue()), _reference.GetValue());
	}

	sfn operator< (ro NativeT<float32> _subject, ro NativeT<float32> _reference) -> bool
	{
		return Float::ApproxLess(_subject.GetValue(), _reference.GetValue());
	}

	// Operator >

	sfn operator> (ro NativeT<uInt32> _subject, ro NativeT<sInt32> _reference) -> bool
	{
		return _subject.GetValue() > SInt32Max ? sInt32(_subject.GetValue()) > _reference.GetValue() : true;
	}

	sfn operator> (ro NativeT<sInt32> _subject, ro NativeT<uInt32> _reference) -> bool
	{
		return _reference.GetValue() > SInt32Max ? _subject.GetValue() > sInt32(_reference.GetValue()) : false;
	}

	template<typename N32>
	sfn operator> (ro NativeT<float32> _subject, ro NativeT<N32> _reference) -> bool
	{
		return Float::ApproxGreater(_subject, float32(_reference));
	}

	template<typename N32>
	sfn operator>(ro NativeT<N32> _subject, ro NativeT<float32> _reference) -> bool
	{
		return Float::ApproxGreater(float32(_subject.GetValue()), _reference.GetValue());
	}

	sfn operator> (ro NativeT<float32> _subject, ro NativeT<float32> _reference) -> bool
	{
		return Float::ApproxGreater(_subject.GetValue(), _reference.GetValue());
	}

	// Arithmetic

	// Operator +

	template<typename N32_S, typename N32_R>
	sfn operator+ (ro NativeT<N32_S> _subject, ro NativeT<N32_R> _reference) -> NativeT<sInt32>
	{
		ro rRef(Sign) subjSign = _subject.GetSign(), refSign = _reference.GetSign();

		stack<sInt64> result = sInt64(_subject.GetValue()) + sInt64(_reference.GetValue());

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

	sfn operator+ (ro NativeT<uInt32> _subject, ro NativeT<uInt32> _reference) -> NativeT<uInt32>
	{
		stack<uInt64> result = uInt64(_subject.GetValue()) + uInt64(_reference.GetValue());

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
	sfn operator+ (ro NativeT<float32> _subject, ro NativeT<N32> _reference) -> NativeT<float32>
	{
		stack<float32> result = _subject.GetValue() + float32(_reference.GetValue());

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
	sfn operator+ (ro NativeT<N32> _subject, ro NativeT<float32> _reference) -> NativeT<float32>
	{
		stack<float32> result = float32(_subject.GetValue()) + _reference.GetValue();

		if (result == Float32Infinity || result == Float32QNaN)
		{
			throw std::overflow_error("Native32 addition float overflow.");
		}
		else
		{
			return NativeT<float32>(result);
		}
	}

	sfn operator+(ro NativeT<float32> _subject, ro NativeT<float32> _reference) -> NativeT<float32>
	{
		stack<float32> result = _subject.GetValue() + _reference.GetValue();

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

	sfn operator- (ro NativeT<uInt32> _subject, ro NativeT<uInt32> _reference) -> NativeT<uInt32>
	{
		stack<uInt64> result = uInt64(_subject.GetValue()) - uInt64(_reference.GetValue());

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
	sfn operator- (ro NativeT<float32> _subject, ro NativeT<N32> _reference) -> NativeT<float32>
	{
		stack<float32> result = _subject.GetValue() - float32(_reference.GetValue());

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
	sfn operator- (ro NativeT<N32> _subject, ro NativeT<float32> _reference) -> NativeT<float32>
	{
		stack<float32> result = float32(_subject.GetValue()) - _reference.GetValue();

		if (result == Float32Infinity || result == Float32QNaN)
		{
			throw std::overflow_error("Native32 addition float overflow.");
		}
		else
		{
			return NativeT<float32>(result);
		}
	}

	sfn operator- (ro NativeT<float32> _subject, ro NativeT<float32> _reference) -> NativeT<float32>
	{
		stack<float32> result = _subject.GetValue() - _reference.GetValue();

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
	sfn operator* (ro NativeT<N32_S> _subject, ro NativeT<N32_R> _reference) -> NativeT<sInt32>
	{
		stack<sInt32> result = _subject.GetValue() * _reference.GetValue();

		if (result != sInt32(0) && result / _subject.GetValue() != _reference.GetValue())
		{
			throw std::overflow_error("Native32 multiplication signed integer overflow.");
		}
		else
		{
			return NativeT<sInt32>(result);
		}
	}

	sfn operator* (ro NativeT<uInt32> _subject, ro NativeT<uInt32> _reference) -> NativeT<uInt32>
	{
		stack<uInt32> result = _subject.GetValue() * _reference.GetValue();

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
	sfn operator* (ro NativeT<float32> _subject, ro NativeT<N32> _reference) -> NativeT<float32>
	{
		stack<float32> result = _subject.GetValue() * float32(_reference.GetValue());

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
	sfn operator* (ro NativeT<N32> _subject, ro NativeT<float32> _reference) -> NativeT<float32>
	{
		stack<float32> result = float32(_subject) * _reference.GetValue();

		if (result == Float32Infinity || result == Float32QNaN)
		{
			throw std::overflow_error("Native32 multiplication float overflow.");
		}
		else
		{
			return NativeT<float32>(result);
		}
	}

	sfn operator* (ro NativeT<float32> _subject, ro NativeT<float32> _reference) -> NativeT<float32>
	{
		stack<float32> result = _subject.GetValue() * _reference.GetValue();

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
	sfn operator/ (ro NativeT<N32_S> _subject, ro NativeT<N32_R> _reference) -> NativeT<sInt32>
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

	sfn operator/ (ro NativeT<uInt32> _subject, ro NativeT<uInt32> _reference) -> NativeT<uInt32>
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
	sfn operator/ (ro NativeT<float32> _subject, ro NativeT<N32> _reference) -> NativeT<float32>
	{
		stack<float32> result = _subject.GetValue() / _reference.GetValue();

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
	sfn operator/ (ro NativeT<N32> _subject, ro NativeT<float32> _reference) -> NativeT<float32>
	{
		stack<float32> result = _subject.GetValue() / _reference.GetValue();

		if (result == Float32Infinity || result == Float32QNaN)
		{
			throw std::overflow_error("Native32 multiplication float overflow.");
		}
		else
		{
			return NativeT<float32>(result);
		}
	}

	sfn operator/ (ro NativeT<float32> _subject, ro NativeT<float32> _reference) -> NativeT<float32>
	{
		stack<float32> result = _subject.GetValue() / _reference.GetValue();

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

Context_End