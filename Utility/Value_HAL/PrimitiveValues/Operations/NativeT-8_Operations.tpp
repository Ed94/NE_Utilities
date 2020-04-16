/*
Title       : Native Template 8-bit Operations Implementation
Author      : Edward R. Gonzalez
File Name   : NativeT-8_Operations.tpp
Date Created: 11-10-2019

Description:
Implements the Native Template operations for 8-bit fundamental types.
*/

#pragma once

// Parent Header
//#include "NativeT_Operations.hpp"

#include "FundamentalLimits.hpp"



Context(NotationEngine::Utility::Value)

SAlias
{
	#ifdef __USE_TypeSafe__

		// TypeSafe

		using ts::make_signed  ;
		using ts::make_unsigned;

	#endif
}

SSource
{
	// TODO: Requires optimization.

	// Comparison:

	// Operator ==

	sfn operator==(ro NativeT<sInt8> _subject, ro NativeT<uInt8> _reference) -> bool
	{
		#ifdef __USE_TypeSafe__
			return _reference.GetValue_Stack().get() <= SInt8Max.get() ? _subject.GetValue_Stack() == make_signed(_reference.GetValue_Stack()) : false;
		#else
			return _reference.GetValue_Stack() <= SInt8Max ? _subject.GetValue_Stack() == sInt8(_reference.GetValue_Stack()) : false;
		#endif
	}
	
	sfn operator==(ro NativeT<uInt8> _subject, ro NativeT<sInt8> _reference) -> bool
	{
		#ifdef __USE_TypeSafe__
			return _subject.GetValue_Stack().get() <= SInt8Max.get() ? make_signed(_subject.GetValue_Stack()) == _reference.GetValue_Stack() : false;
		#else
			return _subject.GetValue_Stack() <= SInt8Max ? sInt32(_subject.GetValue_Stack()) == _reference.GetValue_Stack() : false;
		#endif
	}

	// Operator !=

	sfn operator!=(ro NativeT<sInt8> _subject, ro NativeT<uInt8> _reference) -> bool
	{
		#ifdef __USE_TypeSafe__
			return _reference.GetValue_Stack().get() <= SInt8Max.get() ? _subject.GetValue_Stack() != make_signed(_reference.GetValue_Stack()) : true;
		#else
			return _reference.GetValue_Stack() <= SInt8Max ? _subject.GetValue_Stack() != sInt8(_reference.GetValue_Stack()) : true;
		#endif
	}

	sfn operator!=(ro NativeT<uInt8> _subject, ro NativeT<sInt8> _reference) -> bool
	{
		#ifdef __USE_TypeSafe__
			return _subject.GetValue_Stack().get() <= SInt8Max.get() ? make_signed(_subject.GetValue_Stack()) != _reference.GetValue_Stack() : true;
		#else
			return _subject.GetValue_Stack() <= SInt8Max ? sInt32(_subject.GetValue_Stack()) != _reference.GetValue_Stack() : true;
		#endif
	}

	// Operator <

	sfn operator<(ro NativeT<sInt8> _subject, ro NativeT<uInt8> _reference) -> bool
	{
		#ifdef __USE_TypeSafe__
			return _reference.GetValue_Stack().get() <= SInt8Max.get() ? _subject.GetValue_Stack() < make_signed(_reference.GetValue_Stack()) : true;
		#else
			return _reference.GetValue_Stack() <= SInt8Max ? _subject.GetValue_Stack() < sInt8(_reference.GetValue_Stack()) : true;
		#endif
	}

	sfn operator<(ro NativeT<uInt8> _subject, ro NativeT<sInt8> _reference) -> bool
	{
		#ifdef __USE_TypeSafe__
			return _subject.GetValue_Stack().get() <= SInt8Max.get() ? make_signed(_subject.GetValue_Stack()) < _reference.GetValue_Stack() : false;
		#else
			return _subject.GetValue_Stack() <= SInt8Max ? sInt32(_subject.GetValue_Stack()) < _reference.GetValue_Stack() : false;
		#endif
	}

	// Operator >

	sfn operator>(ro NativeT<sInt8> _subject, ro NativeT<uInt8> _reference) -> bool
	{
		#ifdef __USE_TypeSafe__
			return _reference.GetValue_Stack().get() <= SInt8Max.get() ? _subject.GetValue_Stack() > make_signed(_reference.GetValue_Stack()) : false;
		#else
			return _reference.GetValue_Stack() <= SInt8Max ? _subject.GetValue_Stack() > sInt8(_reference.GetValue_Stack()) : false;
		#endif
	}

	sfn operator>(ro NativeT<uInt8> _subject, ro NativeT<sInt8> _reference) -> bool
	{
		#ifdef __USE_TypeSafe__
			return _subject.GetValue_Stack().get() <= SInt8Max.get() ? make_signed(_subject.GetValue_Stack()) > _reference.GetValue_Stack() : true;
		#else
			return _subject.GetValue_Stack() <= SInt8Max ? sInt32(_subject.GetValue_Stack()) > _reference.GetValue_Stack() : true;
		#endif
	}


	// Arithmetic

	// Operator +

	template<typename N8_S, typename N8_R>
	sfn operator+ (ro NativeT<N8_S> _subject, ro NativeT<N8_R> _reference) -> NativeT<sInt8>
	{
		#ifdef __USE_TypeSafe__

			return NativeT<sInt8>(_subject.GetValue_Stack() + _reference.GetValue_Stack());

		#else

			stack<sInt16> result = sInt16(_subject.GetValue_Stack()) + sInt16(_reference.GetValue_Stack());

			// Note: This can't prevent overflow by providing an uInt8... (Limitation...)

			if (result <= SInt8Min || result >= SInt8Max)
			{
				return NativeT<sInt8>(sInt8(result));
			}
			else
			{
				throw std::overflow_error("Native8 addition overflow.");
			}

		#endif
	}

	sfn operator+ (ro NativeT<uInt8> _subject, ro NativeT<uInt8> _reference) -> NativeT<uInt8>
	{
		#ifdef __USE_TypeSafe__

			return NativeT<uInt8>(_subject.GetValue_Stack() + _reference.GetValue_Stack());

		#else

			stack<sInt16> result = sInt16(_subject.GetValue_Stack()) + sInt16(_reference.GetValue_Stack());

			if (result <= UInt8Max)
			{
				return NativeT<uInt8>(uInt8(result));
			}
			else
			{
				throw std::overflow_error("Native8 addition overflow.");
			}

		#endif
	}

	// Operator -

	template<typename N8_S, typename N8_R>
	sfn operator- (ro NativeT<N8_S> _subject, ro NativeT<N8_R> _reference) -> NativeT<sInt8>
	{
		#ifdef __USE_TypeSafe__

			return NativeT<sInt8>(_subject.GetValue_Stack() - _reference.GetValue_Stack());
			
		#else

			stack<sInt16> result = sInt16(_subject.GetValue_Stack()) - sInt16(_reference.GetValue_Stack());

			if (result <= SInt8Min || result >= SInt8Max)
			{
				return NativeT<sInt8>(sInt8(result));
			}
			else
			{
				throw std::overflow_error("Native8 subtraction overflow.");
			}

		#endif
	}

	sfn operator- (ro NativeT<uInt8>_subject, ro NativeT<uInt8> _reference) -> NativeT<uInt8>
	{
		#ifdef __USE_TypeSafe__

			return NativeT<uInt8>(_subject.GetValue_Stack() - _reference.GetValue_Stack());

		#else

			stack<sInt16> result = sInt16(_subject.GetValue_Stack()) - sInt16(_reference.GetValue_Stack());

			if (result >= 0)
			{
				return NativeT<uInt8>(uInt8(result));
			}
			else
			{
				throw std::overflow_error("Native8 subtraction overflow.");
			}

		#endif
	}

	template<typename N8_S, typename N8_R>
	sfn operator* (ro NativeT<N8_S> _subject, ro NativeT<N8_R> _reference) -> NativeT<sInt8>
	{
		#ifdef __USE_TypeSafe__

			return NativeT<sInt8>(_subject.GetValue_Stack() * _reference.GetValue_Stack());

		#else

			stack<sInt8> result = _subject.GetValue_Stack() * _reference.GetValue_Stack();

			if (result != sInt8(0) && result / _subject.GetValue_Stack() != _reference.GetValue_Stack())
			{
				throw std::overflow_error("Native8 multiplication overflow.");
			}
			else
			{
				return NativeT<sInt8>(result);
			}

		#endif
	}

	sfn operator* (ro NativeT<uInt8> _subject, ro NativeT<uInt8> _reference) -> NativeT<uInt8>
	{
		#ifdef __USE_TypeSafe__

			return NativeT<uInt8>(_subject.GetValue_Stack() * _reference.GetValue_Stack());

		#else

			stack<uInt8> result = _subject.GetValue_Stack() + _reference.GetValue_Stack();

			if (result / _subject.GetValue_Stack() == _reference.GetValue_Stack())
			{
				return NativeT<uInt8>(uInt8(result));
			}
			else
			{
				throw std::overflow_error("Native8 multiplication overflow.");
			}

		#endif
	}

	template<typename N8_S, typename N8_R>
	sfn operator/ (ro NativeT<N8_S> _subject, ro NativeT<N8_R> _reference) -> NativeT<sInt8>
	{
		#ifdef __USE_TypeSafe__

			return NativeT<sInt8>(_subject.GetValue_Stack() / _reference.GetValue_Stack());

		#else

			ro rRef(bool) subjSigned = IsSameType<N8_S, sInt8>() ? true : false,
						   refSigned = IsSameType<N8_R, sInt8>() ? true : false ;

			ro rRef(Sign ) subjSign = _subject.GetSign(), refSign = _reference.GetSign();

			if 
			(
				subjSigned                  == true      &&
				 refSigned                  == true      &&
				_subject  .GetValue_Stack() == SInt8Min  && 
				_reference.GetValue_Stack() == sInt8(-1) ||
				_reference.GetValue_Stack() == sInt8(0 )
			)
			{
				throw std::overflow_error("Native8: Two's Complement division overflow or Divide by zero.");
			}
			else
			{
				return NativeT<sInt8>( sInt8(_subject.GetValue_Stack() / _reference.GetValue_Stack()) );
			}

		#endif
	}

	sfn operator/ (ro NativeT<uInt8> _subject, ro NativeT<uInt8> _reference) -> NativeT<uInt8>
	{
		#ifdef __USE_TypeSafe__

			return _subject.GetValue_Stack() / _reference.GetValue_Stack();

		#else

			if (_reference.GetValue_Stack() == sInt8(0))
			{
				throw std::logic_error("Native8: Divide by zero.");
			}
			else
			{
				return NativeT<uInt8>( _subject.GetValue_Stack() / _reference.GetValue_Stack() );
			}

		#endif
	}
}

Context_End
