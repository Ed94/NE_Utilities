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

SSource
{
	// TODO: Requires optimization.

	// Comparison:

	// Operator ==

	sfn operator==(ro NativeT<sInt8> _subject, ro NativeT<uInt8> _reference) -> bool
	{
		return _reference.GetValue() <= SInt8Max ? _subject.GetValue() == sInt8(_reference.GetValue()) : false;
	}
	
	sfn operator==(ro NativeT<uInt8> _subject, ro NativeT<sInt8> _reference) -> bool
	{
		return _subject.GetValue() <= SInt8Max ? sInt32(_subject.GetValue()) == _reference.GetValue() : false;
	}

	// Operator !=

	sfn operator!=(ro NativeT<sInt8> _subject, ro NativeT<uInt8> _reference) -> bool
	{
		return _reference.GetValue() <= SInt8Max ? _subject.GetValue() != sInt8(_reference.GetValue()) : true;
	}

	sfn operator!=(ro NativeT<uInt8> _subject, ro NativeT<sInt8> _reference) -> bool
	{
		return _subject.GetValue() <= SInt8Max ? sInt32(_subject.GetValue()) != _reference.GetValue() : true;
	}

	// Operator <

	sfn operator<(ro NativeT<sInt8> _subject, ro NativeT<uInt8> _reference) -> bool
	{
		return _reference.GetValue() <= SInt8Max ? _subject.GetValue() < sInt8(_reference.GetValue()) : true;
	}

	sfn operator<(ro NativeT<uInt8> _subject, ro NativeT<sInt8> _reference) -> bool
	{
		return _subject.GetValue() <= SInt8Max ? sInt32(_subject.GetValue()) < _reference.GetValue() : false;
	}

	// Operator >

	sfn operator>(ro NativeT<sInt8> _subject, ro NativeT<uInt8> _reference) -> bool
	{
		return _reference.GetValue() <= SInt8Max ? _subject.GetValue() > sInt8(_reference.GetValue()) : false;
	}

	sfn operator>(ro NativeT<uInt8> _subject, ro NativeT<sInt8> _reference) -> bool
	{
		return _subject.GetValue() <= SInt8Max ? sInt32(_subject.GetValue()) > _reference.GetValue() : true;
	}


	// Arithmetic

	// Operator +

	template<typename N8_S, typename N8_R>
	sfn operator+ (ro NativeT<N8_S> _subject, ro NativeT<N8_R> _reference) -> NativeT<sInt8>
	{
		ro rRef(Sign) subjSign = _subject.GetSign(), refSign = _reference.GetSign(); 

		stack<sInt16> result = sInt16(_subject.GetValue()) + sInt16(_reference.GetValue());

		// Note: This can't prevent overflow by providing an uInt8... (Limitation...)

		if (result <= SInt8Min || result >= SInt8Max)
		{
			return NativeT<sInt8>(sInt8(result));
		}
		else
		{
			throw std::overflow_error("Native8 addition overflow.");
		}
	}

	sfn operator+ (ro NativeT<uInt8> _subject, ro NativeT<uInt8> _reference) -> NativeT<uInt8>
	{
		stack<sInt16> result = sInt16(_subject.GetValue()) + sInt16(_reference.GetValue());

		if (result <= UInt8Max)
		{
			return NativeT<uInt8>(uInt8(result));
		}
		else
		{
			throw std::overflow_error("Native8 addition overflow.");
		}
	}

	// Operator -

	template<typename N8_S, typename N8_R>
	sfn operator- (ro NativeT<N8_S> _subject, ro NativeT<N8_R> _reference) -> NativeT<sInt8>
	{
		ro rRef(Sign) subjSign = _subject.GetSign(), refSign = _reference.GetSign();

		stack<sInt16> result = sInt16(_subject.GetValue()) - sInt16(_reference.GetValue());

		if (result <= SInt8Min || result >= SInt8Max)
		{
			return NativeT<sInt8>(sInt8(result));
		}
		else
		{
			throw std::overflow_error("Native8 subtraction overflow.");
		}
	}

	sfn operator- (ro NativeT<uInt8>_subject, ro NativeT<uInt8> _reference) -> NativeT<uInt8>
	{
		stack<sInt16> result = sInt16(_subject.GetValue()) - sInt16(_reference.GetValue());

		if (result >= 0)
		{
			return NativeT<uInt8>(uInt8(result));
		}
		else
		{
			throw std::overflow_error("Native8 subtraction overflow.");
		}
	}

	template<typename N8_S, typename N8_R>
	sfn operator* (ro NativeT<N8_S> _subject, ro NativeT<N8_R> _reference) -> NativeT<sInt8>
	{
		ro rRef(Sign ) subjSign = _subject.GetSign(), refSign = _reference.GetSign();

		stack<sInt8> result = _subject.GetValue() * _reference.GetValue();

		if (result != sInt8(0) && result / _subject.GetValue() != _reference.GetValue())
		{
			throw std::overflow_error("Native8 multiplication overflow.");
		}
		else
		{
			return NativeT<sInt8>(result);
		}
	}

	sfn operator* (ro NativeT<uInt8> _subject, ro NativeT<uInt8> _reference) -> NativeT<uInt8>
	{
		stack<uInt8> result = _subject.GetValue() + _reference.GetValue();

		if (result / _subject.GetValue() == _reference.GetValue())
		{
			return NativeT<uInt8>(uInt8(result));
		}
		else
		{
			throw std::overflow_error("Native8 multiplication overflow.");
		}
	}

	template<typename N8_S, typename N8_R>
	sfn operator/ (ro NativeT<N8_S> _subject, ro NativeT<N8_R> _reference) -> NativeT<sInt8>
	{
		ro rRef(bool) subjSigned = IsSameType<N8_S, sInt8>() ? true : false,
			           refSigned = IsSameType<N8_R, sInt8>() ? true : false ;

		ro rRef(Sign ) subjSign = _subject.GetSign(), refSign = _reference.GetSign();

		if 
		(
			subjSigned            == true      &&
			 refSigned            == true      &&
			_subject  .GetValue() == SInt8Min  && 
			_reference.GetValue() == sInt8(-1) ||
			_reference.GetValue() == sInt8(0 )
		)
		{
			throw std::overflow_error("Native8: Two's Complement division overflow or Divide by zero.");
		}
		else
		{
			return NativeT<sInt8>( sInt8(_subject.GetValue() / _reference.GetValue()) );
		}
	}

	sfn operator/ (ro NativeT<uInt8> _subject, ro NativeT<uInt8> _reference) -> NativeT<uInt8>
	{
		if (_reference.GetValue() == sInt8(0))
		{
			throw std::logic_error("Native8: Divide by zero.");
		}
		else
		{
			return NativeT<uInt8>( _subject.GetValue() / _reference.GetValue() );
		}
	}
}

Context_End
