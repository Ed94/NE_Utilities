#pragma once

// Parent Header
//#include "Native16T_Operations.hpp"

// Includes
#include "DataTypes/FundamentalLimits.hpp"
#include "ANative16.hpp"
#include "../ANative16T.hpp"
#include "../Native16T.hpp"



Context(NotationEngine::Utility::Value)

SAlias
{
	using NE_U::uInt16;

	using NE_U::UInt16Max;

	using NE_U_V::N16_ID;
}

SSource
{
	// TODO: Requires optimization.

	// Comparison:

	// Operator ==

	template<typename N16_S, typename N16_R>
	sfn operator== (ro Ref(Native16T<N16_S>) _subject, ro Ref(Native16T<N16_R>) _reference) -> bool
	{
		return _subject.GetValue() == _reference.GetValue();
	}

	sfn operator== (ro Ref(Native16T<sInt16>) _subject, ro Ref(Native16T<uInt16>) _reference) -> bool
	{
		return _reference.GetValue() <= SInt16Max ? _subject.GetValue() == sInt16(_reference.GetValue()) : false;
	}

	sfn operator== (ro Ref(Native16T<uInt16>) _subject, ro Ref(Native16T<sInt16>) _reference) -> bool
	{
		return _subject.GetValue() <= SInt16Max ? sInt16(_subject.GetValue()) == _reference.GetValue() : false;
	}

	// Operator !=

	template<typename N16_S, typename N16_R>
	sfn operator!= (ro Ref(Native16T<N16_S>) _subject, ro Ref(Native16T<N16_R>) _reference) -> bool
	{
		return _subject.GetValue() != _reference.GetValue();
	}

	sfn operator!= (ro Ref(Native16T<sInt16>) _subject, ro Ref(Native16T<uInt16>) _reference) -> bool
	{
		return _reference.GetValue() <= SInt16Max ? _subject.GetValue() != sInt16(_reference.GetValue()) : true;
	}

	sfn operator!= (ro Ref(Native16T<uInt16>) _subject, ro Ref(Native16T<sInt16>) _reference) -> bool
	{
		return _subject.GetValue() <= SInt16Max ? sInt16(_subject.GetValue()) != _reference.GetValue() : true;
	}

	// Operator <

	template<typename N16_S, typename N16_R>
	sfn operator< (ro Ref(Native16T<N16_S>) _subject, ro Ref(Native16T<N16_R>) _reference) -> bool
	{
		return _subject.GetValue() < _reference.GetValue();
	}

	sfn operator< (ro Ref(Native16T<sInt16>) _subject, ro Ref(Native16T<uInt16>) _reference) -> bool
	{
		return _reference.GetValue() <= SInt16Max ? _subject.GetValue() < sInt16(_reference.GetValue()) : false;
	}

	sfn operator< (ro Ref(Native16T<uInt16>) _subject, ro Ref(Native16T<sInt16>) _reference) -> bool
	{
		return _subject.GetValue() <= SInt16Max ? sInt16(_subject.GetValue()) < _reference.GetValue() : true;
	}

	// Operator >

	template<typename N16_S, typename N16_R>
	sfn operator> (ro Ref(Native16T<N16_S>) _subject, ro Ref(Native16T<N16_R>) _reference) -> bool
	{
		return _subject.GetValue() > _reference.GetValue();
	}

	sfn operator> (ro Ref(Native16T<sInt16>) _subject, ro Ref(Native16T<uInt16>) _reference) -> bool
	{
		return _reference.GetValue() <= SInt16Max ? _subject.GetValue() > sInt16(_reference.GetValue()) : true;
	}

	sfn operator> (ro Ref(Native16T<uInt16>) _subject, ro Ref(Native16T<sInt16>) _reference) -> bool
	{
		return _subject.GetValue() <= SInt16Max ? sInt16(_subject.GetValue()) > _reference.GetValue() : false;
	}


	// Arithmetic	

	// Operator +

	template<typename N16_S, typename N16_R>
	sfn operator+ (ro Ref(Native16T<N16_S>) _subject, ro Ref(Native16T<N16_R>) _reference) -> Native16T<sInt16>
	{
		ro rRef(Sign) subjSign = _subject.GetSign(), refSign = _reference.GetSign(); 

		stack<sInt32> result = sInt32(_subject.GetValue()) + sInt32(_reference.GetValue());

		// Note: This can't prevent overflow by providing an uInt16... (Limitation...)

		if (result <= SInt16Min || result >= SInt16Max)
		{
			return Native16T<sInt16>(sInt16(result));
		}
		else
		{
			throw std::overflow_error("Native16 addition overflow.");
		}
	}

	sfn operator+ (ro Ref(Native16T<uInt16>) _subject, ro Ref(Native16T<uInt16>) _reference) -> Native16T<uInt16>
	{
		stack<uInt32> result = uInt32(_subject.GetValue()) + uInt32(_reference.GetValue());

		if (result <= UInt16Max)
		{
			return Native16T<uInt16>(uInt16(result));
		}
		else
		{
			throw std::overflow_error("Native16 addition overflow.");
		}
	}

	// Operator -

	template<typename N16_S, typename N16_R>
	sfn operator- (ro Ref(Native16T<N16_S>) _subject, ro Ref(Native16T<N16_R>) _reference) -> Native16T<sInt16>
	{
		ro rRef(N16_ID) subjID = IsSameType<N16_S, sInt16>() ? N16_ID::Signed : N16_ID::Unsigned,
			             refID = IsSameType<N16_R, sInt16>() ? N16_ID::Signed : N16_ID::Unsigned ;

		ro rRef(Sign) subjSign = _subject.GetSign(), refSign = _reference.GetSign();

		stack<sInt32> result = sInt32(_subject.GetValue()) - sInt32(_reference.GetValue());

		if (result <= SInt16Min || result >= SInt16Max)
		{
			return Native16T<sInt16>(sInt16(result));
		}
		else
		{
			throw std::overflow_error("Native16 subtraction overflow.");
		}
	}

	sfn operator- (ro Ref(Native16T<uInt16>) _subject, ro Ref(Native16T<uInt16>) _reference) -> Native16T<uInt16>
	{
		stack<sInt32> result = sInt32(_subject.GetValue()) - sInt32(_reference.GetValue());

		if (result >= sInt32(0))
		{
			return Native16T<uInt16>(uInt16(result));
		}
		else
		{
			throw std::overflow_error("Native16 subtraction overflow.");
		}
	}

	// Operator *

	template<typename N16_S, typename N16_R>
	sfn operator* (ro Ref(Native16T<N16_S>) _subject, ro Ref(Native16T<N16_R>) _reference) -> Native16T<sInt16>
	{
		ro rRef(N16_ID) subjID = IsSameType<N16_S, sInt16>() ? N16_ID::Signed : N16_ID::Unsigned,
			             refID = IsSameType<N16_R, sInt16>() ? N16_ID::Signed : N16_ID::Unsigned ;

		ro rRef(Sign ) subjSign = _subject.GetSign(), refSign = _reference.GetSign();

		stack<sInt16> result = _subject.GetValue() * _reference.GetValue();

		if (result != sInt16(0) && result / _subject.GetValue() != _reference.GetValue())
		{
			throw std::overflow_error("Native16 multiplication overflow.");
		}
		else
		{
			return Native16T<sInt16>(result);
		}
	}

	sfn operator* (ro Ref(Native16T<uInt16>) _subject, ro Ref(Native16T<uInt16>) _reference) -> Native16T<uInt16>
	{
		stack<uInt16> result = _subject.GetValue() + _reference.GetValue();

		if (result / _subject.GetValue() == _reference.GetValue())
		{
			return Native16T<uInt16>(result);
		}
		else
		{
			throw std::overflow_error("Native16 multiplication overflow.");
		}
	}

	// Operator /

	template<typename N16_S, typename N16_R>
	sfn operator/ (ro Ref(Native16T<N16_S>) _subject, ro Ref(Native16T<N16_R>) _reference) -> Native16T<sInt16>
	{
		ro rRef(N16_ID) subjID = IsSameType<N16_S, sInt8>() ? N16_ID::Signed : N16_ID::Unsigned,
			             refID = IsSameType<N16_R, sInt8>() ? N16_ID::Signed : N16_ID::Unsigned ;

		ro rRef(Sign) subjSign = _subject.GetSign(), refSign = _reference.GetSign();

		if 
		(
			subjID                == N16_ID::Signed &&
			 refID                == N16_ID::Signed &&
			_subject  .GetValue() == SInt8Min       && 
			_reference.GetValue() == sInt16(-1)     ||
			_reference.GetValue() == sInt16(0)
		)
		{
			throw std::overflow_error("Native16: Two's Complement division overflow or Divide by zero.");
		}
		else
		{
			return Native16T<sInt16>( sInt16(_subject.GetValue() / _reference.GetValue()) );
		}
	}

	sfn operator/ (ro Ref(Native16T<uInt16>) _subject, ro Ref(Native16T<uInt16>) _reference) -> Native16T<uInt16>
	{
		if (_subject.GetValue() == uInt8(0))
		{
			throw std::logic_error("Native 16: Divide by zero.");
		}
		else
		{
			return Native16T<uInt16>( _subject.GetValue() / _reference.GetValue());
		}
	}
}

Context_End