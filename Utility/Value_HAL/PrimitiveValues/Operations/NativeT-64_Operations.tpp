/*
Title       : Native Template 64-bit Operations Implementation
Author      : Edward R. Gonzalez
File Name   : NativeT_Operations.tpp
Date Created: 11-10-2019

Description:
Implements the Native Template operations for 64-bit fundamental types.
*/

#pragma once

// Parent Header
//#include "NativeT_Operations.hpp"

#include "FundamentalLimits.hpp"



Context(NotationEngine::Utility::Value)

SSource
{
// Comparison

	// Operator ==

	sfn operator== (ro NativeT<sInt64> _subject, ro NativeT<uInt64> _reference) -> bool
	{
		return _reference.GetValue() <= SInt64Max ? _subject.GetValue() == sInt64(_reference.GetValue()) : false;
	}

	sfn operator== (ro NativeT<uInt64> _subject, ro NativeT<sInt64> _reference) -> bool
	{
		return _subject.GetValue() <= SInt64Max ? sInt64(_subject.GetValue()) == _reference.GetValue() : false;
	}

	template<typename N64>
	sfn operator== (ro NativeT<float64> _subject, ro NativeT<N64> _reference) -> bool
	{
		return Float::ApproxEqual(_subject, float64(_reference));
	}

	template<typename N64>
	sfn operator== (ro NativeT<N64> _subject, ro NativeT<float64> _reference) -> bool
	{
		return Float::ApproxEqual(float64(_subject.GetValue()), _reference.GetValue());
	}

	sfn operator== (ro NativeT<float64> _subject, ro NativeT<float64> _reference) -> bool
	{
		return Float::ApproxEqual(_subject.GetValue(), _reference.GetValue());
	}

	// Operator !=

	sfn operator!= (ro NativeT<sInt64> _subject, ro NativeT<uInt64> _reference) -> bool
	{
		return _reference.GetValue() <= SInt64Max ? _subject.GetValue() != sInt64(_reference.GetValue()) : true;
	}

	sfn operator!= (ro NativeT<uInt64> _subject, ro NativeT<sInt64> _reference) -> bool
	{
		return _subject.GetValue() <= SInt64Max ? sInt64(_subject.GetValue()) != _reference.GetValue() : true;
	}

	template<typename N64>
	sfn operator!= (ro NativeT<float64> _subject, ro NativeT<N64> _reference) -> bool
	{
		return !Float::ApproxEqual(_subject.GetValue, float64(_reference.GetValue));
	}

	template<typename N64>
	sfn operator!= (ro NativeT<N64> _subject, ro NativeT<float64> _reference) -> bool
	{
		return !Float::ApproxEqual(float64(_subject.GetValue()), _reference.GetValue());
	}

	sfn operator!= (ro NativeT<float64> _subject, ro NativeT<float64> _reference) -> bool
	{
		return !Float::ApproxEqual(_subject.GetValue(), _reference.GetValue());
	}

	// Operator <

	sfn operator< (ro NativeT<sInt64> _subject, ro NativeT<uInt64> _reference) -> bool
	{
		return _reference.GetValue() <= SInt64Max ? _subject.GetValue() < sInt64(_reference.GetValue()) : true;
	}

	sfn operator< (ro NativeT<uInt64> _subject, ro NativeT<sInt64> _reference) -> bool
	{
		return _subject.GetValue() <= SInt64Max ? sInt64(_subject.GetValue()) < _reference.GetValue() : false;
	}

	template<typename N64>
	sfn operator< (ro NativeT<float64> _subject, ro NativeT<N64> _reference) -> bool
	{
		return Float::ApproxLess(_subject, float64(_reference));
	}

	template<typename N64>
	sfn operator< (ro NativeT<N64> _subject, ro NativeT<float64> _reference) -> bool
	{
		return Float::ApproxLess(float64(_subject.GetValue()), _reference.GetValue());
	}

	sfn operator< (ro NativeT<float64> _subject, ro NativeT<float64> _reference) -> bool
	{
		return Float::ApproxLess(_subject.GetValue(), _reference.GetValue());
	}

	// Operator >

	sfn operator> (ro NativeT<sInt64> _subject, ro NativeT<uInt64> _reference) -> bool
	{
		return _reference.GetValue() <= SInt64Max ? _subject.GetValue() > sInt64(_reference.GetValue()) : false;
	}

	sfn operator> (ro NativeT<uInt64> _subject, ro NativeT<sInt64> _reference) -> bool
	{
		return _subject.GetValue() <= SInt64Max ? sInt64(_subject.GetValue()) > _reference.GetValue() : true;
	}

	template<typename N64>
	sfn operator> (ro NativeT<float64> _subject, ro NativeT<N64> _reference) -> bool
	{
		return Float::ApproxGreater(_subject, float64(_reference));
	}

	template<typename N64>
	sfn operator>(ro NativeT<N64> _subject, ro NativeT<float64> _reference) -> bool
	{
		return Float::ApproxGreater(float64(_subject.GetValue()), _reference.GetValue());
	}

	sfn operator> (ro NativeT<float64> _subject, ro NativeT<float64> _reference) -> bool
	{
		return Float::ApproxGreater(_subject.GetValue(), _reference.GetValue());
	}

	// Arithmetic

	// Operator +

	// Note: This is unsafe currently type_as no overflow check occurs.
	template<typename N64_S, typename N64_R>
	sfn operator+ (ro NativeT<N64_S> _subject, ro NativeT<N64_R> _reference) -> NativeT<sInt64>
	{
		ro rRef(Sign) subjSign = _subject.GetSign(), refSign = _reference.GetSign();

		stack<sInt64> result = sInt64(_subject.GetValue()) + sInt64(_reference.GetValue());

		return NativeT<sInt64>(result);
	}

	// Note: This is unsafe currently type_as no overflow check occurs.
	sfn operator+ (ro NativeT<uInt64> _subject, ro NativeT<uInt64> _reference) -> NativeT<uInt64>
	{
		stack<uInt64> result = uInt64(_subject.GetValue()) + uInt64(_reference.GetValue());

		return NativeT<uInt64>(uInt64(result));
	}

	template<typename N64>
	sfn operator+ (ro NativeT<float64> _subject, ro NativeT<N64> _reference) -> NativeT<float64>
	{
		stack<float64> result = _subject.GetValue() + float64(_reference.GetValue());

		if (result == Float64Infinity || result == Float64QNaN)
		{
			throw std::overflow_error("Native64 addition float overflow.");
		}
		else
		{
			return NativeT<float64>(result);
		}
	}

	template<typename N64>
	sfn operator+ (ro NativeT<N64> _subject, ro NativeT<float64> _reference) -> NativeT<float64>
	{
		stack<float64> result = float64(_subject.GetValue()) + _reference.GetValue();

		if (result == Float64Infinity || result == Float64QNaN)
		{
			throw std::overflow_error("Native64 addition float overflow.");
		}
		else
		{
			return NativeT<float64>(result);
		}
	}

	sfn operator+(ro NativeT<float64> _subject, ro NativeT<float64> _reference) -> NativeT<float64>
	{
		stack<float64> result = _subject.GetValue() + _reference.GetValue();

		if (result == Float64Infinity || result == Float64QNaN)
		{
			throw std::overflow_error("Native64 addition float overflow.");
		}
		else
		{
			return NativeT<float64>(float64(result));
		}
	}

	// Operator -

	// Note: This is unsafe currently type_as no overflow check occurs.
	template<typename N64_S, typename N64_R>
	sfn operator- (ro NativeT<N64_S> _subject, ro NativeT<N64_R> _reference) -> NativeT<sInt64>
	{
		stack<sInt64> result = sInt64(_subject.GetValue()) - sInt64(_reference.GetValue());

		return NativeT<sInt64>(result);
	}

	// Note: This is unsafe currently type_as no overflow check occurs.
	sfn operator- (ro NativeT<uInt64> _subject, ro NativeT<uInt64> _reference) -> NativeT<uInt64>
	{
		stack<uInt64> result = uInt64(_subject.GetValue()) - uInt64(_reference.GetValue());

		return NativeT<uInt64>(uInt64(result));
	}

	template<typename N64>
	sfn operator- (ro NativeT<float64> _subject, ro NativeT<N64> _reference) -> NativeT<float64>
	{
		stack<float64> result = _subject.GetValue() - float64(_reference.GetValue());

		if (result == Float64Infinity || result == Float64QNaN)
		{
			throw std::overflow_error("Native64 addition float overflow.");
		}
		else
		{
			return NativeT<float64>(result);
		}
	}

	template<typename N64>
	sfn operator- (ro NativeT<N64> _subject, ro NativeT<float64> _reference) -> NativeT<float64>
	{
		stack<float64> result = float64(_subject.GetValue()) - _reference.GetValue();

		if (result == Float64Infinity || result == Float64QNaN)
		{
			throw std::overflow_error("Native64 addition float overflow.");
		}
		else
		{
			return NativeT<float64>(result);
		}
	}

	sfn operator- (ro NativeT<float64> _subject, ro NativeT<float64> _reference) -> NativeT<float64>
	{
		stack<float64> result = _subject.GetValue() - _reference.GetValue();

		if (result == Float64Infinity || result == Float64QNaN)
		{
			throw std::overflow_error("Native64 addition float overflow.");
		}
		else
		{
			return NativeT<float64>(float64(result));
		}
	}

	// Operator *

	// Note: This is unsafe currently type_as no overflow check occurs.
	template<typename N64_S, typename N64_R>
	sfn operator* (ro NativeT<N64_S> _subject, ro NativeT<N64_R> _reference) -> NativeT<sInt64>
	{
		stack<sInt64> result = _subject.GetValue() * _reference.GetValue();

		if (result != sInt64(0) && result / _subject.GetValue() != _reference.GetValue())
		{
			throw std::overflow_error("Native64 multiplication signed integer overflow.");
		}
		else
		{
			return NativeT<sInt64>(result);
		}
	}

	// Note: This is unsafe currently type_as no overflow check occurs.
	sfn operator* (ro NativeT<uInt64> _subject, ro NativeT<uInt64> _reference) -> NativeT<uInt64>
	{
		stack<uInt64> result = _subject.GetValue() * _reference.GetValue();

		return NativeT<uInt64>(uInt64(result));
	}

	template<typename N64>
	sfn operator* (ro NativeT<float64> _subject, ro NativeT<N64> _reference) -> NativeT<float64>
	{
		stack<float64> result = _subject.GetValue() * float64(_reference.GetValue());

		if (result == Float64Infinity || result == Float64QNaN)
		{
			throw std::overflow_error("Native64 multiplication float overflow.");
		}
		else
		{
			return NativeT<float64>(result);
		}
	}

	template<typename N64>
	sfn operator* (ro NativeT<N64> _subject, ro NativeT<float64> _reference) -> NativeT<float64>
	{
		stack<float64> result = float64(_subject) * _reference.GetValue();

		if (result == Float64Infinity || result == Float64QNaN)
		{
			throw std::overflow_error("Native64 multiplication float overflow.");
		}
		else
		{
			return NativeT<float64>(result);
		}
	}

	sfn operator* (ro NativeT<float64> _subject, ro NativeT<float64> _reference) -> NativeT<float64>
	{
		stack<float64> result = _subject.GetValue() * _reference.GetValue();

		if (result == Float64Infinity || result == Float64QNaN)
		{
			throw std::overflow_error("Native64 multiplication float overflow.");
		}
		else
		{
			return NativeT<float64>(float64(result));
		}
	}

	// Operator /

	template<typename N64_S, typename N64_R>
	sfn operator/ (ro NativeT<N64_S> _subject, ro NativeT<N64_R> _reference) -> NativeT<sInt64>
	{
		if 
			(
				_subject  .GetValue() == SInt64Min  && 
				_reference.GetValue() == sInt64(-1) || 
				_reference.GetValue() == sInt64(0)
				)
		{
			throw std::overflow_error("Native64: Two's Complement division overflow or divide by zero.");
		}
		else
		{
			return NativeT<sInt64>(sInt64(_subject.GetValue() / _reference.GetValue()));
		}
	}

	sfn operator/ (ro NativeT<uInt64> _subject, ro NativeT<uInt64> _reference) -> NativeT<uInt64>
	{
		if (_reference.GetValue() == uInt64(0U))
		{
			throw std::logic_error("Native64 divide by zero.");
		}
		else
		{
			return NativeT<uInt64>( uInt64(_subject.GetValue() / _reference.GetValue()) );
		}
	}

	template<typename N64>
	sfn operator/ (ro NativeT<float64> _subject, ro NativeT<N64> _reference) -> NativeT<float64>
	{
		stack<float64> result = _subject.GetValue() / _reference.GetValue();

		if (result == Float64Infinity || result == Float64QNaN)
		{
			throw std::overflow_error("Native64 multiplication float overflow.");
		}
		else
		{
			return NativeT<float64>(result);
		}
	}

	template<typename N64>
	sfn operator/ (ro NativeT<N64> _subject, ro NativeT<float64> _reference) -> NativeT<float64>
	{
		stack<float64> result = _subject.GetValue() / _reference.GetValue();

		if (result == Float64Infinity || result == Float64QNaN)
		{
			throw std::overflow_error("Native64 multiplication float overflow.");
		}
		else
		{
			return NativeT<float64>(result);
		}
	}

	sfn operator/ (ro NativeT<float64> _subject, ro NativeT<float64> _reference) -> NativeT<float64>
	{
		stack<float64> result = _subject.GetValue() / _reference.GetValue();

		if (result == Float64Infinity || result == Float64QNaN)
		{
			throw std::overflow_error("Native64 multiplication float overflow.");
		}
		else
		{
			return NativeT<float64>(float64(result));
		}
	}
}

Context_End