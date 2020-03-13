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

SSource
{
	// TODO: Requires optimization.

	// Comparison:

	// Operator ==

	sfn operator== (ro NativeT<sInt16> _subject, ro NativeT<uInt16> _reference) -> bool
	{
		return _reference.GetValue() <= SInt16Max ? _subject.GetValue() == sInt16(_reference.GetValue()) : false;
	}

	sfn operator== (ro NativeT<uInt16> _subject, ro NativeT<sInt16> _reference) -> bool
	{
		return _subject.GetValue() <= SInt16Max ? sInt16(_subject.GetValue()) == _reference.GetValue() : false;
	}

	// Operator !=

	sfn operator!= (ro NativeT<sInt16> _subject, ro NativeT<uInt16> _reference) -> bool
	{
		return _reference.GetValue() <= SInt16Max ? _subject.GetValue() != sInt16(_reference.GetValue()) : true;
	}

	sfn operator!= (ro NativeT<uInt16> _subject, ro NativeT<sInt16> _reference) -> bool
	{
		return _subject.GetValue() <= SInt16Max ? sInt16(_subject.GetValue()) != _reference.GetValue() : true;
	}

	// Operator <

	sfn operator< (ro NativeT<sInt16> _subject, ro NativeT<uInt16> _reference) -> bool
	{
		return _reference.GetValue() <= SInt16Max ? _subject.GetValue() < sInt16(_reference.GetValue()) : false;
	}

	sfn operator< (ro NativeT<uInt16> _subject, ro NativeT<sInt16> _reference) -> bool
	{
		return _subject.GetValue() <= SInt16Max ? sInt16(_subject.GetValue()) < _reference.GetValue() : true;
	}

	// Operator >

	sfn operator> (ro NativeT<sInt16> _subject, ro NativeT<uInt16> _reference) -> bool
	{
		return _reference.GetValue() <= SInt16Max ? _subject.GetValue() > sInt16(_reference.GetValue()) : true;
	}

	sfn operator> (ro NativeT<uInt16> _subject, ro NativeT<sInt16> _reference) -> bool
	{
		return _subject.GetValue() <= SInt16Max ? sInt16(_subject.GetValue()) > _reference.GetValue() : false;
	}


	// Arithmetic	

	// Operator +

	template<typename N16_S, typename N16_R>
	sfn operator+ (ro NativeT<N16_S> _subject, ro NativeT<N16_R> _reference) -> NativeT<sInt16>
	{
		ro rRef(Sign) subjSign = _subject.GetSign(), refSign = _reference.GetSign(); 

		stack<sInt32> result = sInt32(_subject.GetValue()) + sInt32(_reference.GetValue());

		// Note: This can't prevent overflow by providing an uInt16... (Limitation...)

		if (result <= SInt16Min || result >= SInt16Max)
		{
			return NativeT<sInt16>(sInt16(result));
		}
		else
		{
			throw std::overflow_error("Native16 addition overflow.");
		}
	}

	sfn operator+ (ro NativeT<uInt16> _subject, ro NativeT<uInt16> _reference) -> NativeT<uInt16>
	{
		stack<uInt32> result = uInt32(_subject.GetValue()) + uInt32(_reference.GetValue());

		if (result <= UInt16Max)
		{
			return NativeT<uInt16>(uInt16(result));
		}
		else
		{
			throw std::overflow_error("Native16 addition overflow.");
		}
	}

	// Operator -

	template<typename N16_S, typename N16_R>
	sfn operator- (ro NativeT<N16_S> _subject, ro NativeT<N16_R> _reference) -> NativeT<sInt16>
	{
		ro rRef(Sign) subjSign = _subject.GetSign(), refSign = _reference.GetSign();

		stack<sInt32> result = sInt32(_subject.GetValue()) - sInt32(_reference.GetValue());

		if (result <= SInt16Min || result >= SInt16Max)
		{
			return NativeT<sInt16>(sInt16(result));
		}
		else
		{
			throw std::overflow_error("Native16 subtraction overflow.");
		}
	}

	sfn operator- (ro NativeT<uInt16> _subject, ro NativeT<uInt16> _reference) -> NativeT<uInt16>
	{
		stack<sInt32> result = sInt32(_subject.GetValue()) - sInt32(_reference.GetValue());

		if (result >= sInt32(0))
		{
			return NativeT<uInt16>(uInt16(result));
		}
		else
		{
			throw std::overflow_error("Native16 subtraction overflow.");
		}
	}

	// Operator *

	template<typename N16_S, typename N16_R>
	sfn operator* (ro NativeT<N16_S> _subject, ro NativeT<N16_R> _reference) -> NativeT<sInt16>
	{
		ro rRef(Sign ) subjSign = _subject.GetSign(), refSign = _reference.GetSign();

		stack<sInt16> result = _subject.GetValue() * _reference.GetValue();

		if (result != sInt16(0) && result / _subject.GetValue() != _reference.GetValue())
		{
			throw std::overflow_error("Native16 multiplication overflow.");
		}
		else
		{
			return NativeT<sInt16>(result);
		}
	}

	sfn operator* (ro NativeT<uInt16> _subject, ro NativeT<uInt16> _reference) -> NativeT<uInt16>
	{
		stack<uInt16> result = _subject.GetValue() + _reference.GetValue();

		if (result / _subject.GetValue() == _reference.GetValue())
		{
			return NativeT<uInt16>(uInt16(result));
		}
		else
		{
			throw std::overflow_error("Native16 multiplication overflow.");
		}
	}

	// Operator /

	template<typename N16_S, typename N16_R>
	sfn operator/ (ro NativeT<N16_S> _subject, ro NativeT<N16_R> _reference) -> NativeT<sInt16>
	{
		ro rRef(bool) subjSigned = IsSameType<N16_S, sInt16>() ? true : false,
			           refSigned = IsSameType<N16_R, sInt16>() ? true : false ;

		ro rRef(Sign) subjSign = _subject.GetSign(), refSign = _reference.GetSign();

		if 
		(
			subjSigned            == true       &&
			refSigned             == false      &&
			_subject  .GetValue() == SInt8Min   && 
			_reference.GetValue() == sInt16(-1) ||
			_reference.GetValue() == sInt16(0)
		)
		{
			throw std::overflow_error("Native16: Two's Complement division overflow or Divide by zero.");
		}
		else
		{
			return NativeT<sInt16>( sInt16(_subject.GetValue() / _reference.GetValue()) );
		}
	}

	sfn operator/ (ro NativeT<uInt16> _subject, ro NativeT<uInt16> _reference) -> NativeT<uInt16>
	{
		if (_subject.GetValue() == uInt8(0))
		{
			throw std::logic_error("Native 16: Divide by zero.");
		}
		else
		{
			return NativeT<uInt16>( _subject.GetValue() / _reference.GetValue());
		}
	}
}

Context_End