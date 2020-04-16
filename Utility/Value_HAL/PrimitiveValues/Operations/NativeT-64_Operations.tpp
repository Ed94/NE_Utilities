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


#include <cmath>



Context(NotationEngine::Utility::Value)

SAlias
{
	using std::fmod;
}

SSource
{
// Comparison

	// Operator ==

	sfn operator== (ro NativeT<sInt64> _subject, ro NativeT<uInt64> _reference) -> bool
	{
		#ifdef __USE_TypeSafe__
			return _reference.GetValue_Stack().get() <= SInt64Max.get() ? _subject.GetValue_Stack() == make_signed(_reference.GetValue_Stack()) : false;
		#else
			return _reference.GetValue_Stack() <= SInt64Max ? _subject.GetValue_Stack() == sInt64(_reference.GetValue_Stack()) : false;
		#endif
	}

	sfn operator== (ro NativeT<uInt64> _subject, ro NativeT<sInt64> _reference) -> bool
	{
		#ifdef __USE_TypeSafe__
			return _subject.GetValue_Stack().get() <= SInt64Max.get() ? make_signed(_subject.GetValue_Stack()) == _reference.GetValue_Stack() : false;
		#else
			return _subject.GetValue_Stack() <= SInt64Max ? sInt64(_subject.GetValue_Stack()) == _reference.GetValue_Stack() : false;
		#endif
	}

	template<typename N64>
	sfn operator== (ro NativeT<float64> _subject, ro NativeT<N64> _reference) -> bool
	{
		return Float::ApproxEqual(_subject, float64(_reference));
	}

	template<typename N64>
	sfn operator== (ro NativeT<N64> _subject, ro NativeT<float64> _reference) -> bool
	{
		return Float::ApproxEqual(float64(_subject.GetValue_Stack()), _reference.GetValue_Stack());
	}

	sfn operator== (ro NativeT<float64> _subject, ro NativeT<float64> _reference) -> bool
	{
		return Float::ApproxEqual(_subject.GetValue_Stack(), _reference.GetValue_Stack());
	}

	// Operator !=

	sfn operator!= (ro NativeT<sInt64> _subject, ro NativeT<uInt64> _reference) -> bool
	{
		#ifdef __USE_TypeSafe__
			return _reference.GetValue_Stack().get() <= SInt64Max.get() ? _subject.GetValue_Stack() != make_signed(_reference.GetValue_Stack()) : true;
		#else
			return _reference.GetValue_Stack() <= SInt64Max ? _subject.GetValue_Stack() != sInt64(_reference.GetValue_Stack()) : true;
		#endif
	}

	sfn operator!= (ro NativeT<uInt64> _subject, ro NativeT<sInt64> _reference) -> bool
	{
		#ifdef __USE_TypeSafe__
			return _subject.GetValue_Stack().get() <= SInt64Max.get() ? make_signed(_subject.GetValue_Stack()) != _reference.GetValue_Stack() : true;
		#else
			return _subject.GetValue_Stack() <= SInt64Max ? sInt64(_subject.GetValue_Stack()) != _reference.GetValue_Stack() : true;
		#endif
	}

	template<typename N64>
	sfn operator!= (ro NativeT<float64> _subject, ro NativeT<N64> _reference) -> bool
	{
		return !Float::ApproxEqual(_subject.GetValue, float64(_reference.GetValue));
	}

	template<typename N64>
	sfn operator!= (ro NativeT<N64> _subject, ro NativeT<float64> _reference) -> bool
	{
		return !Float::ApproxEqual(float64(_subject.GetValue_Stack()), _reference.GetValue_Stack());
	}

	sfn operator!= (ro NativeT<float64> _subject, ro NativeT<float64> _reference) -> bool
	{
		return !Float::ApproxEqual(_subject.GetValue_Stack(), _reference.GetValue_Stack());
	}

	// Operator <

	sfn operator< (ro NativeT<sInt64> _subject, ro NativeT<uInt64> _reference) -> bool
	{
		#ifdef __USE_TypeSafe__
			return _reference.GetValue_Stack().get() <= SInt64Max.get() ? _subject.GetValue_Stack() < make_signed(_reference.GetValue_Stack()) : true;
		#else
			return _reference.GetValue_Stack() <= SInt64Max ? _subject.GetValue_Stack() < sInt64(_reference.GetValue_Stack()) : true;
		#endif
	}

	sfn operator< (ro NativeT<uInt64> _subject, ro NativeT<sInt64> _reference) -> bool
	{
		#ifdef __USE_TypeSafe__
			return _subject.GetValue_Stack().get() <= SInt64Max.get() ? make_signed(_subject.GetValue_Stack()) < _reference.GetValue_Stack() : false;
		#else
			return _subject.GetValue_Stack() <= SInt64Max ? sInt64(_subject.GetValue_Stack()) < _reference.GetValue_Stack() : false;
		#endif
	}

	template<typename N64>
	sfn operator< (ro NativeT<float64> _subject, ro NativeT<N64> _reference) -> bool
	{
		return Float::ApproxLess(_subject, float64(_reference));
	}

	template<typename N64>
	sfn operator< (ro NativeT<N64> _subject, ro NativeT<float64> _reference) -> bool
	{
		return Float::ApproxLess(float64(_subject.GetValue_Stack()), _reference.GetValue_Stack());
	}

	sfn operator< (ro NativeT<float64> _subject, ro NativeT<float64> _reference) -> bool
	{
		return Float::ApproxLess(_subject.GetValue_Stack(), _reference.GetValue_Stack());
	}

	// Operator >

	sfn operator> (ro NativeT<sInt64> _subject, ro NativeT<uInt64> _reference) -> bool
	{
		#ifdef __USE_TypeSafe__
			return _reference.GetValue_Stack().get() <= SInt64Max.get() ? _subject.GetValue_Stack() > make_signed(_reference.GetValue_Stack()) : false;
		#else
			return _reference.GetValue_Stack() <= SInt64Max ? _subject.GetValue_Stack() > sInt64(_reference.GetValue_Stack()) : false;
		#endif
	}

	sfn operator> (ro NativeT<uInt64> _subject, ro NativeT<sInt64> _reference) -> bool
	{
		#ifdef __USE_TypeSafe__
			return _subject.GetValue_Stack().get() <= SInt64Max.get() ? make_signed(_subject.GetValue_Stack()) > _reference.GetValue_Stack() : true;
		#else
			return _subject.GetValue_Stack() <= SInt64Max ? sInt64(_subject.GetValue_Stack()) > _reference.GetValue_Stack() : true;
		#endif
	}

	template<typename N64>
	sfn operator> (ro NativeT<float64> _subject, ro NativeT<N64> _reference) -> bool
	{
		return Float::ApproxGreater(_subject, float64(_reference));
	}

	template<typename N64>
	sfn operator>(ro NativeT<N64> _subject, ro NativeT<float64> _reference) -> bool
	{
		return Float::ApproxGreater(float64(_subject.GetValue_Stack()), _reference.GetValue_Stack());
	}

	sfn operator> (ro NativeT<float64> _subject, ro NativeT<float64> _reference) -> bool
	{
		return Float::ApproxGreater(_subject.GetValue_Stack(), _reference.GetValue_Stack());
	}

	sfn operator<= (ro NativeT<float64> _subject, ro NativeT<float64> _reference) -> bool
	{
		return _subject < _reference || _subject == _reference;   // May not be the most efficient but it works for now...
	}

	sfn operator>= (ro NativeT<float64> _subject, ro NativeT<float64> _reference) -> bool
	{
		return _subject < _reference || _subject == _reference;   // May not be the most efficient but it works for now...
	}

	// Arithmetic

	// Operator +

	// Note: This is unsafe currently type_as no overflow check occurs.
	// If using typesafe for native types its ok.
	template<typename N64_S, typename N64_R>
	sfn operator+ (ro NativeT<N64_S> _subject, ro NativeT<N64_R> _reference) -> NativeT<sInt64>
	{
		#ifdef __USE_TypeSafe__

			return NativeT<sInt64>(_subject.GetValue_Stack() + _reference.GetValue_Stack());

		#else

			stack<sInt64> result = sInt64(_subject.GetValue_Stack()) + sInt64(_reference.GetValue_Stack());

			return NativeT<sInt64>(result);

		#endif
	}

	// Note: This is unsafe currently type_as no overflow check occurs.
	// If using typesafe for native types its ok.
	sfn operator+ (ro NativeT<uInt64> _subject, ro NativeT<uInt64> _reference) -> NativeT<uInt64>
	{
		#ifdef __USE_TypeSafe__

			return NativeT<uInt64>(_subject.GetValue_Stack() + _reference.GetValue_Stack());

		#else

			stack<uInt64> result = uInt64(_subject.GetValue_Stack()) + uInt64(_reference.GetValue_Stack());

			return NativeT<uInt64>(uInt64(result));

		#endif
	}

	template<typename N64>
	sfn operator+ (ro NativeT<float64> _subject, ro NativeT<N64> _reference) -> NativeT<float64>
	{
		#ifdef __USE_TypeSafe__

			return NativeT<float64>(_subject.GetValue_Stack() + float64(_reference.GetValue_Stack()));

		#else

			stack<float64> result = _subject.GetValue_Stack() + float64(_reference.GetValue_Stack());

			if (result == Float64Infinity || result == Float64QNaN)
			{
				throw std::overflow_error("Native64 addition float overflow.");
			}
			else
			{
				return NativeT<float64>(result);
			}

		#endif
	}

	template<typename N64>
	sfn operator+ (ro NativeT<N64> _subject, ro NativeT<float64> _reference) -> NativeT<float64>
	{
		#ifdef __USE_TypeSafe__

			return NativeT<float64>(float64(_subject.GetValue_Stack()) + _reference.GetValue_Stack());

		#else

			stack<float64> result = float64(_subject.GetValue_Stack()) + _reference.GetValue_Stack();

			if (result == Float64Infinity || result == Float64QNaN)
			{
				throw std::overflow_error("Native64 addition float overflow.");
			}
			else
			{
				return NativeT<float64>(result);
			}

		#endif
	}

	sfn operator+(ro NativeT<float64> _subject, ro NativeT<float64> _reference) -> NativeT<float64>
	{
		#ifdef __USE_TypeSafe__

			return NativeT<float64>(_subject.GetValue_Stack() + _reference.GetValue_Stack());

		#else

			stack<float64> result = _subject.GetValue_Stack() + _reference.GetValue_Stack();

			if (result == Float64Infinity || result == Float64QNaN)
			{
				throw std::overflow_error("Native64 addition float overflow.");
			}
			else
			{
				return NativeT<float64>(float64(result));
			}

		#endif
	}

	// Operator -

	// Note: This is unsafe currently type_as no overflow check occurs.
	// If using typesafe for native types its ok.
	template<typename N64_S, typename N64_R>
	sfn operator- (ro NativeT<N64_S> _subject, ro NativeT<N64_R> _reference) -> NativeT<sInt64>
	{
		#ifdef __USE_TypeSafe__

			return NativeT<sInt64>(_subject.GetValue_Stack() - _reference.GetValue_Stack());

		#else

			stack<sInt64> result = sInt64(_subject.GetValue_Stack()) - sInt64(_reference.GetValue_Stack());

			return NativeT<sInt64>(result);

		#endif
	}

	// Note: This is unsafe currently type_as no overflow check occurs.
	// If using typesafe for native types its ok.
	sfn operator- (ro NativeT<uInt64> _subject, ro NativeT<uInt64> _reference) -> NativeT<uInt64>
	{
		#ifdef __USE_TypeSafe__

			return NativeT<uInt64>(_subject.GetValue_Stack() - _reference.GetValue_Stack());

		#else

			stack<uInt64> result = uInt64(_subject.GetValue_Stack()) - uInt64(_reference.GetValue_Stack());

			return NativeT<uInt64>(uInt64(result));

		#endif
	}

	template<typename N64>
	sfn operator- (ro NativeT<float64> _subject, ro NativeT<N64> _reference) -> NativeT<float64>
	{
		#ifdef __USE_TypeSafe__

			return NativeT<float64>(_subject.GetValue_Stack() - float64(_reference.GetValue_Stack()));

		#else

			stack<float64> result = _subject.GetValue_Stack() - float64(_reference.GetValue_Stack());

			if (result == Float64Infinity || result == Float64QNaN)
			{
				throw std::overflow_error("Native64 addition float overflow.");
			}
			else
			{
				return NativeT<float64>(result);
			}

		#endif
	}

	template<typename N64>
	sfn operator- (ro NativeT<N64> _subject, ro NativeT<float64> _reference) -> NativeT<float64>
	{
		#ifdef __USE_TypeSafe__

			return NativeT<float64>(_subject.GetValue_Stack() - _reference.GetValue_Stack());

		#else

			stack<float64> result = float64(_subject.GetValue_Stack()) - _reference.GetValue_Stack();

			if (result == Float64Infinity || result == Float64QNaN)
			{
				throw std::overflow_error("Native64 addition float overflow.");
			}
			else
			{
				return NativeT<float64>(result);
			}

		#endif
	}

	sfn operator- (ro NativeT<float64> _subject, ro NativeT<float64> _reference) -> NativeT<float64>
	{
		#ifdef __USE_TypeSafe__

			return NativeT<float64>(_subject.GetValue_Stack() - _reference.GetValue_Stack());

		#else

			stack<float64> result = _subject.GetValue_Stack() - _reference.GetValue_Stack();

			if (result == Float64Infinity || result == Float64QNaN)
			{
				throw std::overflow_error("Native64 addition float overflow.");
			}
			else
			{
				return NativeT<float64>(float64(result));
			}

		#endif
	}

	// Operator *

	// Note: This is unsafe currently type_as no overflow check occurs.
	// If using typesafe for native types its ok.
	template<typename N64_S, typename N64_R>
	sfn operator* (ro NativeT<N64_S> _subject, ro NativeT<N64_R> _reference) -> NativeT<sInt64>
	{
		#ifdef __USE_TypeSafe__

			return NativeT<sInt64>(_subject.GetValue_Stack() * _reference.GetValue_Stack());

		#else

			stack<sInt64> result = _subject.GetValue_Stack() * _reference.GetValue_Stack();

			if (result != sInt64(0) && result / _subject.GetValue_Stack() != _reference.GetValue_Stack())
			{
				throw std::overflow_error("Native64 multiplication signed integer overflow.");
			}
			else
			{
				return NativeT<sInt64>(result);
			}

		#endif
	}

	// Note: This is unsafe currently type_as no overflow check occurs.
	// If using typesafe for native types its ok.
	sfn operator* (ro NativeT<uInt64> _subject, ro NativeT<uInt64> _reference) -> NativeT<uInt64>
	{
		#ifdef __USE_TypeSafe__

			return NativeT<uInt64>(_subject.GetValue_Stack() * _reference.GetValue_Stack());

		#else

			stack<uInt64> result = _subject.GetValue_Stack() * _reference.GetValue_Stack();

			return NativeT<uInt64>(uInt64(result));

		#endif
	}

	template<typename N64>
	sfn operator* (ro NativeT<float64> _subject, ro NativeT<N64> _reference) -> NativeT<float64>
	{
		#ifdef __USE_TypeSafe__
			
			return NativeT<float64>(_subject.GetValue_Stack() * _reference.GetValue_Stack());

		#else

			stack<float64> result = _subject.GetValue_Stack() * float64(_reference.GetValue_Stack());

			if (result == Float64Infinity || result == Float64QNaN)
			{
				throw std::overflow_error("Native64 multiplication float overflow.");
			}
			else
			{
				return NativeT<float64>(result);
			}

		#endif
	}

	template<typename N64>
	sfn operator* (ro NativeT<N64> _subject, ro NativeT<float64> _reference) -> NativeT<float64>
	{
		#ifdef __USE_TypeSafe__

			return NativeT<float64>(_subject.GetValue_Stack() * _reference.GetValue_Stack());

		#else

			stack<float64> result = float64(_subject) * _reference.GetValue_Stack();

			if (result == Float64Infinity || result == Float64QNaN)
			{
				throw std::overflow_error("Native64 multiplication float overflow.");
			}
			else
			{
				return NativeT<float64>(result);
			}

		#endif
	}

	sfn operator* (ro NativeT<float64> _subject, ro NativeT<float64> _reference) -> NativeT<float64>
	{
		#ifdef __USE_TypeSafe__

			return NativeT<float64>(_subject.GetValue_Stack() * _reference.GetValue_Stack());

		#else

			stack<float64> result = _subject.GetValue_Stack() * _reference.GetValue_Stack();

			if (result == Float64Infinity || result == Float64QNaN)
			{
				throw std::overflow_error("Native64 multiplication float overflow.");
			}
			else
			{
				return NativeT<float64>(float64(result));
			}

		#endif
	}

	// Operator /

	template<typename N64_S, typename N64_R>
	sfn operator/ (ro NativeT<N64_S> _subject, ro NativeT<N64_R> _reference) -> NativeT<sInt64>
	{
		#ifdef __USE_TypeSafe__

			return NativeT<sInt64>(_subject.GetValue_Stack() / _reference.GetValue_Stack());

		#else

			if 
			(
				_subject  .GetValue_Stack() == SInt64Min  && 
				_reference.GetValue_Stack() == sInt64(-1) || 
				_reference.GetValue_Stack() == sInt64(0)
			)
			{
				throw std::overflow_error("Native64: Two's Complement division overflow or divide by zero.");
			}
			else
			{
				return NativeT<sInt64>(sInt64(_subject.GetValue_Stack() / _reference.GetValue_Stack()));
			}

		#endif
	}

	sfn operator/ (ro NativeT<uInt64> _subject, ro NativeT<uInt64> _reference) -> NativeT<uInt64>
	{
		#ifdef __USE_TypeSafe__

			return NativeT<uInt64>(_subject.GetValue_Stack() / _reference.GetValue_Stack());

		#else

			if (_reference.GetValue_Stack() == uInt64(0U))
			{
				throw std::logic_error("Native64 divide by zero.");
			}
			else
			{
				return NativeT<uInt64>( uInt64(_subject.GetValue_Stack() / _reference.GetValue_Stack()) );
			}

		#endif
	}

	template<typename N64>
	sfn operator/ (ro NativeT<float64> _subject, ro NativeT<N64> _reference) -> NativeT<float64>
	{
		#ifdef __USE_TypeSafe__

			return NativeT<float64>(_subject.GetValue_Stack() / float64(_reference.GetValue_Stack()));

		#else

			stack<float64> result = _subject.GetValue_Stack() / _reference.GetValue_Stack();

			if (result == Float64Infinity || result == Float64QNaN)
			{
				throw std::overflow_error("Native64 multiplication float overflow.");
			}
			else
			{
				return NativeT<float64>(result);
			}

		#endif
	}

	template<typename N64>
	sfn operator/ (ro NativeT<N64> _subject, ro NativeT<float64> _reference) -> NativeT<float64>
	{
		#ifdef __USE_TypeSafe__

			return NativeT<float64>(float64(_subject.GetValue_Stack()) / _reference.GetValue_Stack());

		#else

			stack<float64> result = _subject.GetValue_Stack() / _reference.GetValue_Stack();

			if (result == Float64Infinity || result == Float64QNaN)
			{
				throw std::overflow_error("Native64 multiplication float overflow.");
			}
			else
			{
				return NativeT<float64>(result);
			}

		#endif
	}

	sfn operator/ (ro NativeT<float64> _subject, ro NativeT<float64> _reference) -> NativeT<float64>
	{
		#ifdef __USE_TypeSafe__

			return NativeT<float64>(_subject.GetValue_Stack() / _reference.GetValue_Stack());

		#else

			stack<float64> result = _subject.GetValue_Stack() / _reference.GetValue_Stack();

			if (result == Float64Infinity || result == Float64QNaN)
			{
				throw std::overflow_error("Native64 multiplication float overflow.");
			}
			else
			{
				return NativeT<float64>(float64(result));
			}

		#endif
	}

	/*template<typename N64>
	sfn operator% (ro NativeT<float64> _subject, ro NativeT<N64> _reference) -> NativeT<float64>
	{
		throw std::runtime_error("Not Implemented exception");
	}*/

	sfn operator% (ro NativeT<float64> _subject, ro NativeT<float64> _reference) -> NativeT<float64>
	{
		stack<float64> result = fmod(_subject.GetValue_Stack().get(), _reference.GetValue_Stack().get());

		return NativeT<float64>(float64(result));
	}
}

Context_End