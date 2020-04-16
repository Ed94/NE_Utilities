/*
Title       : Native Template 16-bit Operations Implementation
Author      : Edward R. Gonzalez
File Name   : NativeT-16_Operations.tpp
Date Created: 11-10-2019

Description:
Implements the Native Template operations for 16-bit fundamental types.
*/

#pragma once

// Parent Header
//#include "NativeT_Operations.hpp"

#include "FundamentalLimits.hpp"



Context(NotationEngine::Utility::Value)

SAlias
{
	using ts::make_signed;
}

SSource
{
	// TODO: Requires optimization.

	// Comparison:

	// Operator ==

	sfn operator== (ro NativeT<sInt16> _subject, ro NativeT<uInt16> _reference) -> bool
	{
		#ifdef __USE_TypeSafe__
			return _reference.GetValue_Stack().get() <= SInt16Max.get() ? _subject.GetValue_Stack() == make_signed(_reference.GetValue_Stack()) : false;
		#else
			return _reference.GetValue_Stack() <= SInt16Max ? _subject.GetValue_Stack() == sInt16(_reference.GetValue_Stack()) : false;
		#endif
	}

	sfn operator== (ro NativeT<uInt16> _subject, ro NativeT<sInt16> _reference) -> bool
	{
		#ifdef __USE_TypeSafe__
			return _subject.GetValue_Stack().get() <= SInt16Max.get() ? make_signed(_subject.GetValue_Stack()) == _reference.GetValue_Stack() : false;
		#else
			return _subject.GetValue_Stack() <= SInt16Max ? sInt16(_subject.GetValue_Stack()) == _reference.GetValue_Stack() : false;
		#endif
	}

	// Operator !=

	sfn operator!= (ro NativeT<sInt16> _subject, ro NativeT<uInt16> _reference) -> bool
	{
		#ifdef __USE_TypeSafe__
			return _reference.GetValue_Stack().get() <= SInt16Max.get() ? _subject.GetValue_Stack() != make_signed(_reference.GetValue_Stack()) : true;
		#else
			return _reference.GetValue_Stack() <= SInt16Max ? _subject.GetValue_Stack() != sInt16(_reference.GetValue_Stack()) : true;
		#endif
	}

	sfn operator!= (ro NativeT<uInt16> _subject, ro NativeT<sInt16> _reference) -> bool
	{
		#ifdef __USE_TypeSafe__
			return _subject.GetValue_Stack().get() <= SInt16Max.get() ? make_signed(_subject.GetValue_Stack()) != _reference.GetValue_Stack() : true;
		#else
			return _subject.GetValue_Stack() <= SInt16Max ? sInt16(_subject.GetValue_Stack()) != _reference.GetValue_Stack() : true;
		#endif
	}

	// Operator <

	sfn operator< (ro NativeT<sInt16> _subject, ro NativeT<uInt16> _reference) -> bool
	{
		#ifdef __USE_TypeSafe__
			return _reference.GetValue_Stack().get() <= SInt16Max.get() ? _subject.GetValue_Stack() < make_signed(_reference.GetValue_Stack()) : false;
		#else
			return _reference.GetValue_Stack() <= SInt16Max ? _subject.GetValue_Stack() < sInt16(_reference.GetValue_Stack()) : false;
		#endif
	}

	sfn operator< (ro NativeT<uInt16> _subject, ro NativeT<sInt16> _reference) -> bool
	{
		#ifdef __USE_TypeSafe__
			return _subject.GetValue_Stack().get() <= SInt16Max.get() ? make_signed(_subject.GetValue_Stack()) < _reference.GetValue_Stack() : true;
		#else
			return _subject.GetValue_Stack() <= SInt16Max ? sInt16(_subject.GetValue_Stack()) < _reference.GetValue_Stack() : true;
		#endif
	}

	// Operator >

	sfn operator> (ro NativeT<sInt16> _subject, ro NativeT<uInt16> _reference) -> bool
	{
		#ifdef __USE_TypeSafe__
			return _reference.GetValue_Stack().get() <= SInt16Max.get() ? _subject.GetValue_Stack() > make_signed(_reference.GetValue_Stack()) : true;
		#else
			return _reference.GetValue_Stack() <= SInt16Max ? _subject.GetValue_Stack() > sInt16(_reference.GetValue_Stack()) : true;
		#endif
	}

	sfn operator> (ro NativeT<uInt16> _subject, ro NativeT<sInt16> _reference) -> bool
	{
		#ifdef __USE_TypeSafe__
			return _subject.GetValue_Stack().get() <= SInt16Max.get() ? make_signed(_subject.GetValue_Stack()) > _reference.GetValue_Stack() : false;
		#else
			return _subject.GetValue_Stack() <= SInt16Max ? sInt16(_subject.GetValue_Stack()) > _reference.GetValue_Stack() : false;
		#endif
	}


	// Arithmetic	

	// Operator +

	template<typename N16_S, typename N16_R>
	sfn operator+ (ro NativeT<N16_S> _subject, ro NativeT<N16_R> _reference) -> NativeT<sInt16>
	{
		#ifdef __USE_TypeSafe__

			return NativeT<sInt16>( _subject.GetValue_Stack() + _reference.GetValue_Stack() );

		#else

			stack<sInt32> result = sInt32(_subject.GetValue_Stack()) + sInt32(_reference.GetValue_Stack());

			// Note: This can't prevent overflow by providing an uInt16... (Limitation...)

			if (result <= SInt16Min || result >= SInt16Max)
			{
				return NativeT<sInt16>(sInt16(result));
			}
			else
			{
				throw std::overflow_error("Native16 addition overflow.");
			}

		#endif
	}

	sfn operator+ (ro NativeT<uInt16> _subject, ro NativeT<uInt16> _reference) -> NativeT<uInt16>
	{
		#ifdef __USE_TypeSafe__

			return NativeT<uInt16>( _subject.GetValue_Stack() + _reference.GetValue_Stack() );

		#else

			stack<uInt32> result = uInt32(_subject.GetValue_Stack()) + uInt32(_reference.GetValue_Stack());

			if (result <= UInt16Max)
			{
				return NativeT<uInt16>(uInt16(result));
			}
			else
			{
				throw std::overflow_error("Native16 addition overflow.");
			}

		#endif
	}

	// Operator -

	template<typename N16_S, typename N16_R>
	sfn operator- (ro NativeT<N16_S> _subject, ro NativeT<N16_R> _reference) -> NativeT<sInt16>
	{
		#ifdef __USE_TypeSafe__

			return NativeT<sInt16>( _subject.GetValue_Stack() - _reference.GetValue_Stack() );

		#else

			stack<sInt32> result = sInt32(_subject.GetValue_Stack()) - sInt32(_reference.GetValue_Stack());

			if (result <= SInt16Min || result >= SInt16Max)
			{
				return NativeT<sInt16>(sInt16(result));
			}
			else
			{
				throw std::overflow_error("Native16 subtraction overflow.");
			}

		#endif
	}

	sfn operator- (ro NativeT<uInt16> _subject, ro NativeT<uInt16> _reference) -> NativeT<uInt16>
	{
		#ifdef __USE_TypeSafe__

			return NativeT<uInt16>( _subject.GetValue_Stack() - _reference.GetValue_Stack() );

		#else

			stack<sInt32> result = sInt32(_subject.GetValue_Stack()) - sInt32(_reference.GetValue_Stack());

			if (result >= sInt32(0))
			{
				return NativeT<uInt16>(uInt16(result));
			}
			else
			{
				throw std::overflow_error("Native16 subtraction overflow.");
			}

		#endif
	}

	// Operator *

	template<typename N16_S, typename N16_R>
	sfn operator* (ro NativeT<N16_S> _subject, ro NativeT<N16_R> _reference) -> NativeT<sInt16>
	{
		#ifdef __USE_TypeSafe__

			return NativeT<sInt16>( _subject.GetValue_Stack() * _reference.GetValue_Stack() );

		#else

			stack<sInt16> result = _subject.GetValue_Stack() * _reference.GetValue_Stack();

			if (result != sInt16(0) && result / _subject.GetValue_Stack() != _reference.GetValue_Stack())
			{
				throw std::overflow_error("Native16 multiplication overflow.");
			}
			else
			{
				return NativeT<sInt16>(result);
			}

		#endif
	}

	sfn operator* (ro NativeT<uInt16> _subject, ro NativeT<uInt16> _reference) -> NativeT<uInt16>
	{
		#ifdef __USE_TypeSafe__

			return NativeT<uInt16>( _subject.GetValue_Stack() * _reference.GetValue_Stack() );
			
		#else

			stack<uInt16> result = _subject.GetValue_Stack() + _reference.GetValue_Stack();

			if (result / _subject.GetValue_Stack() == _reference.GetValue_Stack())
			{
				return NativeT<uInt16>(uInt16(result));
			}
			else
			{
				throw std::overflow_error("Native16 multiplication overflow.");
			}

		#endif
	}

	// Operator /

	template<typename N16_S, typename N16_R>
	sfn operator/ (ro NativeT<N16_S> _subject, ro NativeT<N16_R> _reference) -> NativeT<sInt16>
	{
		#ifdef __USE_TypeSafe__
			
			return NativeT<sInt16>( _subject.GetValue_Stack() / _reference.GetValue_Stack() );

		#else

			ro rRef(bool) subjSigned = IsSameType<N16_S, sInt16>() ? true : false,
						   refSigned = IsSameType<N16_R, sInt16>() ? true : false ;

			ro rRef(Sign) subjSign = _subject.GetSign(), refSign = _reference.GetSign();

			if 
			(
				subjSigned                  == true       &&
				refSigned                   == false      &&
				_subject  .GetValue_Stack() == SInt8Min   && 
				_reference.GetValue_Stack() == sInt16(-1) ||
				_reference.GetValue_Stack() == sInt16(0 )
			)
			{
				throw std::overflow_error("Native16: Two's Complement division overflow or Divide by zero.");
			}
			else
			{
				return NativeT<sInt16>( sInt16(_subject.GetValue_Stack() / _reference.GetValue_Stack()) );
			}

		#endif
	}

	sfn operator/ (ro NativeT<uInt16> _subject, ro NativeT<uInt16> _reference) -> NativeT<uInt16>
	{
		#ifdef __USE_TypeSafe__

			return NativeT<uInt16>( _subject.GetValue_Stack() / _reference.GetValue_Stack() );

		#else

			if (_subject.GetValue_Stack() == uInt8(0))
			{
				throw std::logic_error("Native 16: Divide by zero.");
			}
			else
			{
				return NativeT<uInt16>( _subject.GetValue_Stack() / _reference.GetValue_Stack());
			}

		#endif
	}
}

Context_End