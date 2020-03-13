#pragma once

// Parent Header
//#include "Native8_T_Operations.hpp"

// Includes
#include "ANative8.hpp"



Context(NotationEngine::Utility::Value)

SSource
{
	// TODO: Requires optimization.

	// Comparison:

	// Operator ==

	template<typename N8_S, typename N8_R>
	sfn operator== (ro Ref(Native8_T<N8_S>) _subject, ro Ref(Native8_T<N8_R>) _reference) -> bool
	{
		return _subject.GetValue() == _reference.GetValue();
	}

	sfn operator==(ro Ref(Native8_T<sInt8>) _subject, ro Ref(Native8_T<uInt8>) _reference) -> bool
	{
		return _reference.GetValue() <= SInt8Max ? _subject.GetValue() == sInt8(_reference.GetValue()) : false;
	}
	
	sfn operator==(ro Ref(Native8_T<uInt8>) _subject, ro Ref(Native8_T<sInt8>) _reference) -> bool
	{
		return _subject.GetValue() <= SInt8Max ? sInt32(_subject.GetValue()) == _reference.GetValue() : false;
	}

	// Operator !=

	template<typename N8_S, typename N8_R>
	sfn operator!= (ro Ref(Native8_T<N8_S>) _subject, ro Ref(Native8_T<N8_R>) _reference) -> bool
	{
		return _subject.GetValue() != _reference.GetValue();
	}

	sfn operator!=(ro Ref(Native8_T<sInt8>) _subject, ro Ref(Native8_T<uInt8>) _reference) -> bool
	{
		return _reference.GetValue() <= SInt8Max ? _subject.GetValue() != sInt8(_reference.GetValue()) : true;
	}

	sfn operator!=(ro Ref(Native8_T<uInt8>) _subject, ro Ref(Native8_T<sInt8>) _reference) -> bool
	{
		return _subject.GetValue() <= SInt8Max ? sInt32(_subject.GetValue()) != _reference.GetValue() : true;
	}

	// Operator <

	template<typename N8_S, typename N8_R>
	sfn operator< (ro Ref(Native8_T<N8_S>) _subject, ro Ref(Native8_T<N8_R>) _reference) -> bool
	{
		return _subject.GetValue() < _reference.GetValue();
	}

	sfn operator<(ro Ref(Native8_T<sInt8>) _subject, ro Ref(Native8_T<uInt8>) _reference) -> bool
	{
		return _reference.GetValue() <= SInt8Max ? _subject.GetValue() < sInt8(_reference.GetValue()) : true;
	}

	sfn operator<(ro Ref(Native8_T<uInt8>) _subject, ro Ref(Native8_T<sInt8>) _reference) -> bool
	{
		return _subject.GetValue() <= SInt8Max ? sInt32(_subject.GetValue()) < _reference.GetValue() : false;
	}

	// Operator >

	template<typename N8_S, typename N8_R>
	sfn operator> (ro Ref(Native8_T<N8_S>) _subject, ro Ref(Native8_T<N8_R>) _reference) -> bool
	{
		return _subject.GetValue() > _reference.GetValue();
	}

	sfn operator>(ro Ref(Native8_T<sInt8>) _subject, ro Ref(Native8_T<uInt8>) _reference) -> bool
	{
		return _reference.GetValue() <= SInt8Max ? _subject.GetValue() > sInt8(_reference.GetValue()) : false;
	}

	sfn operator>(ro Ref(Native8_T<uInt8>) _subject, ro Ref(Native8_T<sInt8>) _reference) -> bool
	{
		return _subject.GetValue() <= SInt8Max ? sInt32(_subject.GetValue()) > _reference.GetValue() : true;
	}


	// Arithmetic

	// Operator +

	template<typename N8_S, typename N8_R>
	sfn operator+ (ro Ref(Native8_T<N8_S>) _subject, ro Ref(Native8_T<N8_R>) _reference) -> Native8_T<sInt8>
	{
		ro rRef(N8_ID) subjID = IsSameType<N8_S, sInt8>() ? N8_ID::Signed : N8_ID::Unsigned,
			            refID = IsSameType<N8_R, sInt8>() ? N8_ID::Signed : N8_ID::Unsigned ;

		ro rRef(Sign) subjSign = _subject.GetSign(), refSign = _reference.GetSign(); 

		stack<sInt16> result = sInt16(_subject.GetValue()) + sInt16(_reference.GetValue());

		// Note: This can't prevent overflow by providing an uInt8... (Limitation...)

		if (result <= SInt8Min || result >= SInt8Max)
		{
			return Native8_T<sInt8>(sInt8(result));
		}
		else
		{
			throw std::overflow_error("Native8 addition overflow.");
		}
	}

	sfn operator+ (ro Ref(Native8_T<uInt8>) _subject, ro Ref(Native8_T<uInt8>) _reference) -> Native8_T<uInt8>
	{
		stack<sInt16> result = sInt16(_subject.GetValue()) + sInt16(_reference.GetValue());

		if (result <= UInt8Max)
		{
			return Native8_T<uInt8>(uInt8(result));
		}
		else
		{
			throw std::overflow_error("Native8 addition overflow.");
		}
	}

	// Operator -

	template<typename N8_S, typename N8_R>
	sfn operator- (ro Ref(Native8_T<N8_S>) _subject, ro Ref(Native8_T<N8_R>) _reference) -> Native8_T<sInt8>
	{
		ro rRef(N8_ID) subjID = IsSameType<N8_S, sInt8>() ? N8_ID::Signed : N8_ID::Unsigned,
			            refID = IsSameType<N8_R, sInt8>() ? N8_ID::Signed : N8_ID::Unsigned ;

		ro rRef(Sign) subjSign = _subject.GetSign(), refSign = _reference.GetSign();

		stack<sInt16> result = sInt16(_subject.GetValue()) - sInt16(_reference.GetValue());

		if (result <= SInt8Min || result >= SInt8Max)
		{
			return Native8_T<sInt8>(sInt8(result));
		}
		else
		{
			throw std::overflow_error("Native8 subtraction overflow.");
		}
	}

	sfn operator- (ro Ref(Native8_T<uInt8>) _subject, ro Ref(Native8_T<uInt8>) _reference) -> Native8_T<uInt8>
	{
		stack<sInt16> result = sInt16(_subject.GetValue()) - sInt16(_reference.GetValue());

		if (result >= 0)
		{
			return Native8_T<uInt8>(uInt8(result));
		}
		else
		{
			throw std::overflow_error("Native8 subtraction overflow.");
		}
	}

	template<typename N8_S, typename N8_R>
	sfn operator* (ro Ref(Native8_T<N8_S>) _subject, ro Ref(Native8_T<N8_R>) _reference) -> Native8_T<sInt8>
	{
		ro rRef(N8_ID) subjID = IsSameType<N8_S, sInt8>() ? N8_ID::Signed : N8_ID::Unsigned,
			            refID = IsSameType<N8_R, sInt8>() ? N8_ID::Signed : N8_ID::Unsigned ;

		ro rRef(Sign ) subjSign = _subject.GetSign(), refSign = _reference.GetSign();

		stack<sInt8> result = _subject.GetValue() * _reference.GetValue();

		if (result != sInt8(0) && result / _subject.GetValue() != _reference.GetValue())
		{
			throw std::overflow_error("Native8 multiplication overflow.");
		}
		else
		{
			return Native8_T<sInt8>(result);
		}
	}

	sfn operator* (ro Ref(Native8_T<uInt8>) _subject, ro Ref(Native8_T<uInt8>) _reference) -> Native8_T<uInt8>
	{
		stack<uInt8> result = _subject.GetValue() + _reference.GetValue();

		if (result / _subject.GetValue() == _reference.GetValue())
		{
			return Native8_T<uInt8>(result);
		}
		else
		{
			throw std::overflow_error("Native8 multiplication overflow.");
		}
	}

	template<typename N8_S, typename N8_R>
	sfn operator/ (ro Ref(Native8_T<N8_S>) _subject, ro Ref(Native8_T<N8_R>) _reference) -> Native8_T<sInt8>
	{
		ro rRef(N8_ID) subjID = IsSameType<N8_S, sInt8>() ? N8_ID::Signed : N8_ID::Unsigned,
			            refID = IsSameType<N8_R, sInt8>() ? N8_ID::Signed : N8_ID::Unsigned ;

		ro rRef(Sign ) subjSign = _subject.GetSign(), refSign = _reference.GetSign();

		if 
		(
			subjID                == N8_ID::Signed &&
			 refID                == N8_ID::Signed &&
			_subject  .GetValue() == SInt8Min      && 
			_reference.GetValue() == sInt8(-1)     ||
			_reference.GetValue() == sInt8(0 )
		)
		{
			throw std::overflow_error("Native8: Two's Complement division overflow or Divide by zero.");
		}
		else
		{
			return Native8_T<sInt8>( sInt8(_subject.GetValue() / _reference.GetValue()) );
		}
	}

	sfn operator/ (ro Ref(Native8_T<uInt8>) _subject, ro Ref(Native8_T<uInt8>) _reference) -> Native8_T<uInt8>
	{
		if (_reference.GetValue() == sInt8(0))
		{
			throw std::logic_error("Native8: Divide by zero.");
		}
		else
		{
			return Native8_T<uInt8>( _subject.GetValue() / _reference.GetValue() );
		}
	}
}

Context_End