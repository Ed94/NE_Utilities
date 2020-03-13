#pragma once

// Parent Header
//#include "Native32_T_Operations.hpp"


// Includes
#include "DataTypes/FundamentalLimits.hpp"
#include "../ANative32T.hpp"
#include "../Native32T.hpp"
#include "Native32.hpp"



Context(NotationEngine::Utility::Value)

SAlias
{
	using NE_U::UInt32Max;
}
		   
SSource
{
	// Comparison

	// Operator==

	template<typename N32_S, typename N32_R>
	sfn operator== (ro Ref(Native32T<N32_S>) _subject, ro Ref(Native32T<N32_R>) _reference) -> bool
	{
		return _subject.GetValue() == _reference.GetValue();
	}

	sfn operator==(ro Ref(Native32T<uInt32>) _subject, ro Ref(Native32T<sInt32>) _reference) -> bool
	{
		return _subject.GetValue() <= SInt32Max ? sInt32(_subject.GetValue()) == _reference.GetValue() : false;
	}

	sfn operator==(ro Ref(Native32T<sInt32>) _subject, ro Ref(Native32T<uInt32>) _reference) -> bool
	{
		return _reference.GetValue() <= SInt32Max ? _subject.GetValue() == sInt32(_reference.GetValue()) : false;
	}

	template<typename N32>
	sfn operator== (ro Ref(Native32T<float32>) _subject, ro Ref(Native32T<N32>) _reference) -> bool
	{
		return Native32::ApproxEqual(_subject, float32(_reference));
	}

	template<typename N32>
	sfn operator== (ro Ref(Native32T<N32>) _subject, ro Ref(Native32T<float32>) _reference) -> bool
	{
		return Native32::ApproxEqual(float32(_subject.GetValue()), _reference.GetValue());
	}
	
	sfn operator== (ro Ref(Native32T<float32>) _subject, ro Ref(Native32T<float32>) _reference) -> bool
	{
		return Native32::ApproxEqual(_subject.GetValue(), _reference.GetValue());
	}

	// Operator !=

	template<typename N32_S, typename N32_R>
	sfn operator!= (ro Ref(Native32T<N32_S>) _subject, ro Ref(Native32T<N32_R>) _reference) -> bool
	{
		return _subject.GetValue() != _reference.GetValue();
	}

	sfn operator!=(ro Ref(Native32T<uInt32>) _subject, ro Ref(Native32T<sInt32>) _reference) -> bool
	{
		return _subject.GetValue() <= SInt32Max ? sInt32(_subject.GetValue()) != _reference.GetValue() : true;
	}

	sfn operator!=(ro Ref(Native32T<sInt32>) _subject, ro Ref(Native32T<uInt32>) _reference) -> bool
	{
		return _reference.GetValue() <= SInt32Max ? _subject.GetValue() != sInt32(_reference.GetValue()) : true;
	}

	template<typename N32>
	sfn operator!= (ro Ref(Native32T<float32>) _subject, ro Ref(Native32T<N32>) _reference) -> bool
	{
		return !Native32::ApproxEqual(_subject, float32(_reference));
	}

	template<typename N32>
	sfn operator!= (ro Ref(Native32T<N32>) _subject, ro Ref(Native32T<float32>) _reference) -> bool
	{
		return !Native32::ApproxEqual(float32(_subject.GetValue()), _reference.GetValue());
	}

	sfn operator!= (ro Ref(Native32T<float32>) _subject, ro Ref(Native32T<float32>) _reference) -> bool
	{
		return !Native32::ApproxEqual(_subject.GetValue(), _reference.GetValue());
	}

	// Operator <

	template<typename N32_S, typename N32_R>
	sfn operator< (ro Ref(Native32T<N32_S>) _subject, ro Ref(Native32T<N32_R>) _reference) -> bool
	{
		return _subject.GetValue() < _reference.GetValue();
	}

	sfn operator<(ro Ref(Native32T<uInt32>) _subject, ro Ref(Native32T<sInt32>) _reference) -> bool
	{
		return _subject.GetValue() <= SInt32Max ? sInt32(_subject.GetValue()) < _reference.GetValue() : false;
	}

	sfn operator<(ro Ref(Native32T<sInt32>) _subject, ro Ref(Native32T<uInt32>) _reference) -> bool
	{
		return _reference.GetValue() <= SInt32Max ? _subject.GetValue() < sInt32(_reference.GetValue()) : true;
	}

	template<typename N32>
	sfn operator< (ro Ref(Native32T<float32>) _subject, ro Ref(Native32T<N32>) _reference) -> bool
	{
		return Native32::ApproxLess(_subject, float32(_reference));
	}

	template<typename N32>
	sfn operator< (ro Ref(Native32T<N32>) _subject, ro Ref(Native32T<float32>) _reference) -> bool
	{
		return Native32::ApproxLess(float32(_subject.GetValue()), _reference.GetValue());
	}

	sfn operator< (ro Ref(Native32T<float32>) _subject, ro Ref(Native32T<float32>) _reference) -> bool
	{
		return Native32::ApproxLess(_subject.GetValue(), _reference.GetValue());
	}

	// Operator >

	template<typename N32_S, typename N32_R>
	sfn operator> (ro Ref(Native32T<N32_S>) _subject, ro Ref(Native32T<N32_R>) _reference) -> bool
	{
		return _subject.GetValue() > _reference.GetValue();
	}

	sfn operator> (ro Ref(Native32T<uInt32>) _subject, ro Ref(Native32T<sInt32>) _reference) -> bool
	{
		return _subject.GetValue() > SInt32Max ? sInt32(_subject.GetValue()) > _reference.GetValue() : true;
	}

	sfn operator> (ro Ref(Native32T<sInt32>) _subject, ro Ref(Native32T<uInt32>) _reference) -> bool
	{
		return _reference.GetValue() > SInt32Max ? _subject.GetValue() > sInt32(_reference.GetValue()) : false;
	}

	template<typename N32>
	sfn operator> (ro Ref(Native32T<float32>) _subject, ro Ref(Native32T<N32>) _reference) -> bool
	{
		return Native32::ApproxGreater(_subject, float32(_reference));
	}

	template<typename N32>
	sfn operator>(ro Ref(Native32T<N32>) _subject, ro Ref(Native32T<float32>) _reference) -> bool
	{
		return Native32::ApproxGreater(float32(_subject.GetValue()), _reference.GetValue());
	}

	sfn operator> (ro Ref(Native32T<float32>) _subject, ro Ref(Native32T<float32>) _reference) -> bool
	{
		return Native32::ApproxGreater(_subject.GetValue(), _reference.GetValue());
	}

	// Arithmetic

	// Operator +

	template<typename N32_S, typename N32_R>
	sfn operator+ (ro Ref(Native32T<N32_S>) _subject, ro Ref(Native32T<N32_R>) _reference) -> Native32T<sInt32>
	{
		ro rRef(Sign) subjSign = _subject.GetSign(), refSign = _reference.GetSign();

		stack<sInt64> result = sInt64(_subject.GetValue()) + sInt64(_reference.GetValue());

		// Note: This can't prevent overflow by providing an uInt32... (Limitation...)

		if (result <= SInt32Min || result >= SInt32Max)
		{
			return Native32T<sInt32>(sInt32(result));
		}
		else
		{
			throw std::overflow_error("Native32 addition signed overflow.");
		}
	}

	sfn operator+ (ro Ref(Native32T<uInt32>) _subject, ro Ref(Native32T<uInt32>) _reference) -> Native32T<uInt32>
	{
		stack<uInt64> result = uInt64(_subject.GetValue()) + uInt64(_reference.GetValue());

		if (result <= UInt32Max)
		{
			return Native32T<uInt32>(uInt32(result));
		}
		else
		{
			throw std::overflow_error("Native32 addition unsigned overflow.");
		}
	}

	template<typename N32>
	sfn operator+ (ro Ref(Native32T<float32>) _subject, ro Ref(Native32T<N32>) _reference) -> Native32T<float32>
	{
		stack<float32> result = _subject.GetValue() + float32(_reference.GetValue());

		if (result == Float32Infinity || result == Float32QNaN)
		{
			throw std::overflow_error("Native32 addition float overflow.");
		}
		else
		{
			return Native32T<float32>(result);
		}
	}

	template<typename N32>
	sfn operator+ (ro Ref(Native32T<N32>) _subject, ro Ref(Native32T<float32>) _reference) -> Native32T<float32>
	{
		stack<float32> result = float32(_subject.GetValue()) + _reference.GetValue();

		if (result == Float32Infinity || result == Float32QNaN)
		{
			throw std::overflow_error("Native32 addition float overflow.");
		}
		else
		{
			return Native32T<float32>(result);
		}
	}

	sfn operator+(ro Ref(Native32T<float32>) _subject, ro Ref(Native32T<float32>) _reference) -> Native32T<float32>
	{
		stack<float32> result = _subject.GetValue() + _reference.GetValue();

		if (result == Float32Infinity || result == Float32QNaN)
		{
			throw std::overflow_error("Native32 addition float overflow.");
		}
		else
		{
			return Native32T<float32>(result);
		}
	}

	// Operator -

	sfn operator- (ro Ref(Native32T<uInt32>) _subject, ro Ref(Native32T<uInt32>) _reference) -> Native32T<uInt32>
	{
		stack<uInt64> result = uInt64(_subject.GetValue()) - uInt64(_reference.GetValue());

		if (result <= UInt32Max)
		{
			return Native32T<uInt32>(uInt32(result));
		}
		else
		{
			throw std::overflow_error("Native32 addition unsigned overflow.");
		}
	}

	template<typename N32>
	sfn operator- (ro Ref(Native32T<float32>) _subject, ro Ref(Native32T<N32>) _reference) -> Native32T<float32>
	{
		stack<float32> result = _subject.GetValue() - float32(_reference.GetValue());

		if (result == Float32Infinity || result == Float32QNaN)
		{
			throw std::overflow_error("Native32 addition float overflow.");
		}
		else
		{
			return Native32T<float32>(result);
		}
	}

	template<typename N32>
	sfn operator- (ro Ref(Native32T<N32>) _subject, ro Ref(Native32T<float32>) _reference) -> Native32T<float32>
	{
		stack<float32> result = float32(_subject.GetValue()) - _reference.GetValue();

		if (result == Float32Infinity || result == Float32QNaN)
		{
			throw std::overflow_error("Native32 addition float overflow.");
		}
		else
		{
			return Native32T<float32>(result);
		}
	}

	sfn operator- (ro Ref(Native32T<float32>) _subject, ro Ref(Native32T<float32>) _reference) -> Native32T<float32>
	{
		stack<float32> result = _subject.GetValue() - _reference.GetValue();

		if (result == Float32Infinity || result == Float32QNaN)
		{
			throw std::overflow_error("Native32 addition float overflow.");
		}
		else
		{
			return Native32T<float32>(result);
		}
	}

	// Operator *

	template<typename N32_S, typename N32_R>
	sfn operator* (ro Ref(Native32T<N32_S>) _subject, ro Ref(Native32T<N32_R>) _reference) -> Native32T<sInt32>
	{
		stack<sInt32> result = _subject.GetValue() * _reference.GetValue();

		if (result != sInt32(0) && result / _subject.GetValue() != _reference.GetValue())
		{
			throw std::overflow_error("Native32 multiplication signed integer overflow.");
		}
		else
		{
			return Native32T<sInt32>(result);
		}
	}

	sfn operator* (ro Ref(Native32T<uInt32>) _subject, ro Ref(Native32T<uInt32>) _reference) -> Native32T<uInt32>
	{
		stack<uInt32> result = _subject.GetValue() * _reference.GetValue();

		if (result != uInt32(0) && result / _subject.GetValue() != _reference.GetValue())
		{
			throw std::overflow_error("Native32 multiplication unsigned integer overflow.");
		}
		else
		{
			return Native32T<uInt32>(result);
		}
	}

	template<typename N32>
	sfn operator* (ro Ref(Native32T<float32>) _subject, ro Ref(Native32T<N32>) _reference) -> Native32T<float32>
	{
		stack<float32> result = _subject.GetValue() * float32(_reference.GetValue());

		if (result == Float32Infinity || result == Float32QNaN)
		{
			throw std::overflow_error("Native32 multiplication float overflow.");
		}
		else
		{
			return Native32T<float32>(result);
		}
	}

	template<typename N32>
	sfn operator* (ro Ref(Native32T<N32>) _subject, ro Ref(Native32T<float32>) _reference) -> Native32T<float32>
	{
		stack<float32> result = float32(_subject) * _reference.GetValue();

		if (result == Float32Infinity || result == Float32QNaN)
		{
			throw std::overflow_error("Native32 multiplication float overflow.");
		}
		else
		{
			return Native32T<float32>(result);
		}
	}

	sfn operator* (ro Ref(Native32T<float32>) _subject, ro Ref(Native32T<float32>) _reference) -> Native32T<float32>
	{
		stack<float32> result = _subject.GetValue() * _reference.GetValue();

		if (result == Float32Infinity || result == Float32QNaN)
		{
			throw std::overflow_error("Native32 multiplication float overflow.");
		}
		else
		{
			return Native32T<float32>(result);
		}
	}

	// Operator /

	template<typename N32_S, typename N32_R>
	sfn operator/ (ro Ref(Native32T<N32_S>) _subject, ro Ref(Native32T<N32_R>) _reference) -> Native32T<sInt32>
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
			return Native32T<sInt32>(sInt32(_subject.GetValue() / _reference.GetValue()));
		}
	}

	sfn operator/ (ro Ref(Native32T<uInt32>) _subject, ro Ref(Native32T<uInt32>) _reference) -> Native32T<uInt32>
	{
		if (_reference.GetValue() == uInt32(0U))
		{
			throw std::logic_error("Native32 divide by zero.");
		}
		else
		{
			return Native32T<uInt32>( uInt32(_subject.GetValue() / _reference.GetValue()) );
		}
	}

	template<typename N32>
	sfn operator/ (ro Ref(Native32T<float32>) _subject, ro Ref(Native32T<N32>) _reference) -> Native32T<float32>
	{
		stack<float32> result = _subject.GetValue() / _reference.GetValue();

		if (result == Float32Infinity || result == Float32QNaN)
		{
			throw std::overflow_error("Native32 multiplication float overflow.");
		}
		else
		{
			return Native32T<float32>(result);
		}
	}

	template<typename N32>
	sfn operator/ (ro Ref(Native32T<N32>) _subject, ro Ref(Native32T<float32>) _reference) -> Native32T<float32>
	{
		stack<float32> result = _subject.GetValue() / _reference.GetValue();

		if (result == Float32Infinity || result == Float32QNaN)
		{
			throw std::overflow_error("Native32 multiplication float overflow.");
		}
		else
		{
			return Native32T<float32>(result);
		}
	}

	sfn operator/ (ro Ref(Native32T<float32>) _subject, ro Ref(Native32T<float32>) _reference) -> Native32T<float32>
	{
		stack<float32> result = _subject.GetValue() / _reference.GetValue();

		if (result == Float32Infinity || result == Float32QNaN)
		{
			throw std::overflow_error("Native32 multiplication float overflow.");
		}
		else
		{
			return Native32T<float32>(result);
		}
	}
}

Context_End