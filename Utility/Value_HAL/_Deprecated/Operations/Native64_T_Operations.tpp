#pragma once

// Parent Header
//#include "Native64_T_Operations.hpp"


// Includes
#include "DataTypes/FundamentalLimits.hpp"
#include "ANative64T.hpp"
#include "Native64T.hpp"
#include "Native64.hpp"


Context(NotationEngine::Utility::Value)

SAlias
{
	using NE_U::UInt64Max;
}

SSource
{
	// Comparison

	// Operator ==

	template<typename N64_S, typename N64_R>
	sfn operator== (ro Ref(Native64T<N64_S>) _subject, ro Ref(Native64T<N64_R>) _reference) -> bool
	{
		return _subject.GetValue() == _reference.GetValue();
	}

	sfn operator== (ro Ref(Native64T<sInt64>) _subject, ro Ref(Native64T<uInt64>) _reference) -> bool
	{
		return _reference.GetValue() <= SInt64Max ? _subject.GetValue() == sInt64(_reference.GetValue()) : false;
	}

	sfn operator== (ro Ref(Native64T<sInt64>) _subject, ro Ref(Native64T<uInt64>) _reference) -> bool
	{
		return _subject.GetValue() <= SInt64Max ? sInt64(_subject.GetValue()) == _reference.GetValue() : false;
	}

	template<typename N64>
	sfn operator== (ro Ref(Native64T<float64>) _subject, ro Ref(Native64T<N64>) _reference) -> bool
	{
		return Native64::ApproxEqual(_subject, float64(_reference));
	}

	template<typename N64>
	sfn operator== (ro Ref(Native64T<N64>) _subject, ro Ref(Native64T<float64>) _reference) -> bool
	{
		return Native64::ApproxEqual(float64(_subject.GetValue()), _reference.GetValue());
	}

	sfn operator== (ro Ref(Native64T<float64>) _subject, ro Ref(Native64T<float64>) _reference) -> bool
	{
		return Native64::ApproxEqual(_subject.GetValue(), _reference.GetValue());
	}

	// Operator !=

	template<typename N64_S, typename N64_R>
	sfn operator!= (ro Ref(Native64T<N64_S>) _subject, ro Ref(Native64T<N64_R>) _reference) -> bool
	{
		return _subject.GetValue() != _reference.GetValue();
	}

	sfn operator== (ro Ref(Native64T<sInt64>) _subject, ro Ref(Native64T<uInt64>) _reference) -> bool
	{
		return _reference.GetValue() <= SInt64Max ? _subject.GetValue() != sInt64(_reference.GetValue()) : true;
	}

	sfn operator== (ro Ref(Native64T<sInt64>) _subject, ro Ref(Native64T<uInt64>) _reference) -> bool
	{
		return _subject.GetValue() <= SInt64Max ? sInt64(_subject.GetValue()) != _reference.GetValue() : true;
	}

	template<typename N64>
	sfn operator!= (ro Ref(Native64T<float64>) _subject, ro Ref(Native64T<N64>) _reference) -> bool
	{
		return !Native64::ApproxEqual(_subject.GetValue, float64(_reference.GetValue));
	}

	template<typename N64>
	sfn operator!= (ro Ref(Native64T<N64>) _subject, ro Ref(Native64T<float64>) _reference) -> bool
	{
		return !Native64::ApproxEqual(float64(_subject.GetValue()), _reference.GetValue());
	}

	sfn operator!= (ro Ref(Native64T<float64>) _subject, ro Ref(Native64T<float64>) _reference) -> bool
	{
		return !Native64::ApproxEqual(_subject.GetValue(), _reference.GetValue());
	}

	// Operator <

	template<typename N64_S, typename N64_R>
	sfn operator< (ro Ref(Native64T<N64_S>) _subject, ro Ref(Native64T<N64_R>) _reference) -> bool
	{
		return _subject.GetValue() < _reference.GetValue();
	}

	sfn operator< (ro Ref(Native64T<sInt64>) _subject, ro Ref(Native64T<uInt64>) _reference) -> bool
	{
		return _reference.GetValue() <= SInt64Max ? _subject.GetValue() < sInt64(_reference.GetValue()) : true;
	}

	sfn operator< (ro Ref(Native64T<sInt64>) _subject, ro Ref(Native64T<uInt64>) _reference) -> bool
	{
		return _subject.GetValue() <= SInt64Max ? sInt64(_subject.GetValue()) < _reference.GetValue() : false;
	}

	template<typename N64>
	sfn operator< (ro Ref(Native64T<float64>) _subject, ro Ref(Native64T<N64>) _reference) -> bool
	{
		return Native64::ApproxLess(_subject, float64(_reference));
	}

	template<typename N64>
	sfn operator< (ro Ref(Native64T<N64>) _subject, ro Ref(Native64T<float64>) _reference) -> bool
	{
		return Native64::ApproxLess(float64(_subject.GetValue()), _reference.GetValue());
	}

	sfn operator< (ro Ref(Native64T<float64>) _subject, ro Ref(Native64T<float64>) _reference) -> bool
	{
		return Native64::ApproxLess(_subject.GetValue(), _reference.GetValue());
	}

	// Operator >

	template<typename N64_S, typename N64_R>
	sfn operator> (ro Ref(Native64T<N64_S>) _subject, ro Ref(Native64T<N64_R>) _reference) -> bool
	{
		return _subject.GetValue() > _reference.GetValue();
	}

	sfn operator> (ro Ref(Native64T<sInt64>) _subject, ro Ref(Native64T<uInt64>) _reference) -> bool
	{
		return _reference.GetValue() <= SInt64Max ? _subject.GetValue() > sInt64(_reference.GetValue()) : false;
	}

	sfn operator> (ro Ref(Native64T<sInt64>) _subject, ro Ref(Native64T<uInt64>) _reference) -> bool
	{
		return _subject.GetValue() <= SInt64Max ? sInt64(_subject.GetValue()) > _reference.GetValue() : true;
	}

	template<typename N64>
	sfn operator> (ro Ref(Native64T<float64>) _subject, ro Ref(Native64T<N64>) _reference) -> bool
	{
		return Native64::ApproxGreater(_subject, float64(_reference));
	}

	template<typename N64>
	sfn operator>(ro Ref(Native64T<N64>) _subject, ro Ref(Native64T<float64>) _reference) -> bool
	{
		return Native64::ApproxGreater(float64(_subject.GetValue()), _reference.GetValue());
	}

	sfn operator> (ro Ref(Native64T<float64>) _subject, ro Ref(Native64T<float64>) _reference) -> bool
	{
		return Native64::ApproxGreater(_subject.GetValue(), _reference.GetValue());
	}

	// Arithmetic

	// Operator +

	// Note: This is unsafe currently type_as no overflow check occurs.
	template<typename N64_S, typename N64_R>
	sfn operator+ (ro Ref(Native64T<N64_S>) _subject, ro Ref(Native64T<N64_R>) _reference) -> Native64T<sInt64>
	{
		ro rRef(Sign) subjSign = _subject.GetSign(), refSign = _reference.GetSign();

		stack<sInt64> result = sInt64(_subject.GetValue()) + sInt64(_reference.GetValue());

		return Native64T<sInt64>(result);
	}

	// Note: This is unsafe currently type_as no overflow check occurs.
	sfn operator+ (ro Ref(Native64T<uInt64>) _subject, ro Ref(Native64T<uInt64>) _reference) -> Native64T<uInt64>
	{
		stack<uInt64> result = uInt64(_subject.GetValue()) + uInt64(_reference.GetValue());

		return Native64T<uInt64>(result);
	}

	template<typename N64>
	sfn operator+ (ro Ref(Native64T<float64>) _subject, ro Ref(Native64T<N64>) _reference) -> Native64T<float64>
	{
		stack<float64> result = _subject.GetValue() + float64(_reference.GetValue());

		if (result == Float64Infinity || result == Float64QNaN)
		{
			throw std::overflow_error("Native64 addition float overflow.");
		}
		else
		{
			return Native64T<float64>(result);
		}
	}

	template<typename N64>
	sfn operator+ (ro Ref(Native64T<N64>) _subject, ro Ref(Native64T<float64>) _reference) -> Native64T<float64>
	{
		stack<float64> result = float64(_subject.GetValue()) + _reference.GetValue();

		if (result == Float64Infinity || result == Float64QNaN)
		{
			throw std::overflow_error("Native64 addition float overflow.");
		}
		else
		{
			return Native64T<float64>(result);
		}
	}

	sfn operator+(ro Ref(Native64T<float64>) _subject, ro Ref(Native64T<float64>) _reference) -> Native64T<float64>
	{
		stack<float64> result = _subject.GetValue() + _reference.GetValue();

		if (result == Float64Infinity || result == Float64QNaN)
		{
			throw std::overflow_error("Native64 addition float overflow.");
		}
		else
		{
			return Native64T<float64>(result);
		}
	}

	// Operator -

	// Note: This is unsafe currently type_as no overflow check occurs.
	template<typename N64_S, typename N64_R>
	sfn operator- (ro Ref(Native64T<N64_S>) _subject, ro Ref(Native64T<N64_R>) _reference) -> Native64T<sInt64>
	{
		stack<sInt64> result = sInt64(_subject.GetValue()) - sInt64(_reference.GetValue());

		return Native64T<sInt64>(result);
	}

	// Note: This is unsafe currently type_as no overflow check occurs.
	sfn operator- (ro Ref(Native64T<uInt64>) _subject, ro Ref(Native64T<uInt64>) _reference) -> Native64T<uInt64>
	{
		stack<uInt64> result = uInt64(_subject.GetValue()) - uInt64(_reference.GetValue());

		return Native64T<uInt64>(result);
	}

	template<typename N64>
	sfn operator- (ro Ref(Native64T<float64>) _subject, ro Ref(Native64T<N64>) _reference) -> Native64T<float64>
	{
		stack<float64> result = _subject.GetValue() - float64(_reference.GetValue());

		if (result == Float64Infinity || result == Float64QNaN)
		{
			throw std::overflow_error("Native64 addition float overflow.");
		}
		else
		{
			return Native64T<float64>(result);
		}
	}

	template<typename N64>
	sfn operator- (ro Ref(Native64T<N64>) _subject, ro Ref(Native64T<float64>) _reference) -> Native64T<float64>
	{
		stack<float64> result = float64(_subject.GetValue()) - _reference.GetValue();

		if (result == Float64Infinity || result == Float64QNaN)
		{
			throw std::overflow_error("Native64 addition float overflow.");
		}
		else
		{
			return Native64T<float64>(result);
		}
	}

	sfn operator- (ro Ref(Native64T<float64>) _subject, ro Ref(Native64T<float64>) _reference) -> Native64T<float64>
	{
		stack<float64> result = _subject.GetValue() - _reference.GetValue();

		if (result == Float64Infinity || result == Float64QNaN)
		{
			throw std::overflow_error("Native64 addition float overflow.");
		}
		else
		{
			return Native64T<float64>(result);
		}
	}

	// Operator *

	// Note: This is unsafe currently type_as no overflow check occurs.
	template<typename N64_S, typename N64_R>
	sfn operator* (ro Ref(Native64T<N64_S>) _subject, ro Ref(Native64T<N64_R>) _reference) -> Native64T<sInt64>
	{
		stack<sInt64> result = _subject.GetValue() * _reference.GetValue();

		if (result != sInt64(0) && result / _subject.GetValue() != _reference.GetValue())
		{
			throw std::overflow_error("Native64 multiplication signed integer overflow.");
		}
		else
		{
			return Native64T<sInt64>(result);
		}
	}

	// Note: This is unsafe currently type_as no overflow check occurs.
	sfn operator* (ro Ref(Native64T<uInt64>) _subject, ro Ref(Native64T<uInt64>) _reference) -> Native64T<uInt64>
	{
		stack<uInt64> result = _subject.GetValue() * _reference.GetValue();

		return Native64T<uInt64>(result);
	}

	template<typename N64>
	sfn operator* (ro Ref(Native64T<float64>) _subject, ro Ref(Native64T<N64>) _reference) -> Native64T<float64>
	{
		stack<float64> result = _subject.GetValue() * float64(_reference.GetValue());

		if (result == Float64Infinity || result == Float64QNaN)
		{
			throw std::overflow_error("Native64 multiplication float overflow.");
		}
		else
		{
			return Native64T<float64>(result);
		}
	}

	template<typename N64>
	sfn operator* (ro Ref(Native64T<N64>) _subject, ro Ref(Native64T<float64>) _reference) -> Native64T<float64>
	{
		stack<float64> result = float64(_subject) * _reference.GetValue();

		if (result == Float64Infinity || result == Float64QNaN)
		{
			throw std::overflow_error("Native64 multiplication float overflow.");
		}
		else
		{
			return Native64T<float64>(result);
		}
	}

	sfn operator* (ro Ref(Native64T<float64>) _subject, ro Ref(Native64T<float64>) _reference) -> Native64T<float64>
	{
		stack<float64> result = _subject.GetValue() * _reference.GetValue();

		if (result == Float64Infinity || result == Float64QNaN)
		{
			throw std::overflow_error("Native64 multiplication float overflow.");
		}
		else
		{
			return Native64T<float64>(result);
		}
	}

	// Operator /

	template<typename N64_S, typename N64_R>
	sfn operator/ (ro Ref(Native64T<N64_S>) _subject, ro Ref(Native64T<N64_R>) _reference) -> Native64T<sInt64>
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
			return Native64T<sInt64>(sInt64(_subject.GetValue() / _reference.GetValue()));
		}
	}

	sfn operator/ (ro Ref(Native64T<uInt64>) _subject, ro Ref(Native64T<uInt64>) _reference) -> Native64T<uInt64>
	{
		if (_reference.GetValue() == uInt64(0U))
		{
			throw std::logic_error("Native64 divide by zero.");
		}
		else
		{
			return Native64T<uInt64>( uInt64(_subject.GetValue() / _reference.GetValue()) );
		}
	}

	template<typename N64>
	sfn operator/ (ro Ref(Native64T<float64>) _subject, ro Ref(Native64T<N64>) _reference) -> Native64T<float64>
	{
		stack<float64> result = _subject.GetValue() / _reference.GetValue();

		if (result == Float64Infinity || result == Float64QNaN)
		{
			throw std::overflow_error("Native64 multiplication float overflow.");
		}
		else
		{
			return Native64T<float64>(result);
		}
	}

	template<typename N64>
	sfn operator/ (ro Ref(Native64T<N64>) _subject, ro Ref(Native64T<float64>) _reference) -> Native64T<float64>
	{
		stack<float64> result = _subject.GetValue() / _reference.GetValue();

		if (result == Float64Infinity || result == Float64QNaN)
		{
			throw std::overflow_error("Native64 multiplication float overflow.");
		}
		else
		{
			return Native64T<float64>(result);
		}
	}

	sfn operator/ (ro Ref(Native64T<float64>) _subject, ro Ref(Native64T<float64>) _reference) -> Native64T<float64>
	{
		stack<float64> result = _subject.GetValue() / _reference.GetValue();

		if (result == Float64Infinity || result == Float64QNaN)
		{
			throw std::overflow_error("Native64 multiplication float overflow.");
		}
		else
		{
			return Native64T<float64>(result);
		}
	}
}

Context_End