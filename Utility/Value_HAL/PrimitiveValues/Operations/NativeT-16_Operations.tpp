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



namespace NotationEngine::Utility::Value
{
	inline namespace Source
	{
		// TODO: Requires optimization.

		// Comparison:

		// Operator ==

		bool operator== (const NativeT<sInt16> _subject, const NativeT<uInt16> _reference)
		{
			return _reference.GetValue() <= SInt16Max ? _subject.GetValue() == sInt16(_reference.GetValue()) : false;
		}

		bool operator== (const NativeT<uInt16> _subject, const NativeT<sInt16> _reference)
		{
			return _subject.GetValue() <= SInt16Max ? sInt16(_subject.GetValue()) == _reference.GetValue() : false;
		}

		// Operator !=

		bool operator!= (const NativeT<sInt16> _subject, const NativeT<uInt16> _reference)
		{
			return _reference.GetValue() <= SInt16Max ? _subject.GetValue() != sInt16(_reference.GetValue()) : true;
		}

		bool operator!= (const NativeT<uInt16> _subject, const NativeT<sInt16> _reference)
		{
			return _subject.GetValue() <= SInt16Max ? sInt16(_subject.GetValue()) != _reference.GetValue() : true;
		}

		// Operator <

		bool operator< (const NativeT<sInt16> _subject, const NativeT<uInt16> _reference)
		{
			return _reference.GetValue() <= SInt16Max ? _subject.GetValue() < sInt16(_reference.GetValue()) : false;
		}

		bool operator< (const NativeT<uInt16> _subject, const NativeT<sInt16> _reference)
		{
			return _subject.GetValue() <= SInt16Max ? sInt16(_subject.GetValue()) < _reference.GetValue() : true;
		}

		// Operator >

		bool operator> (const NativeT<sInt16> _subject, const NativeT<uInt16> _reference)
		{
			return _reference.GetValue() <= SInt16Max ? _subject.GetValue() > sInt16(_reference.GetValue()) : true;
		}

		bool operator> (const NativeT<uInt16> _subject, const NativeT<sInt16> _reference)
		{
			return _subject.GetValue() <= SInt16Max ? sInt16(_subject.GetValue()) > _reference.GetValue() : false;
		}


		// Arithmetic	

		// Operator +

		template<typename N16_S, typename N16_R>
		NativeT<sInt16> operator+ (const NativeT<N16_S> _subject, const NativeT<N16_R> _reference)
		{
			const Sign&& subjSign = _subject.GetSign(), refSign = _reference.GetSign(); 

			sInt32 result = sInt32(_subject.GetValue()) + sInt32(_reference.GetValue());

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

		NativeT<uInt16> operator+ (const NativeT<uInt16> _subject, const NativeT<uInt16> _reference)
		{
			uInt32 result = uInt32(_subject.GetValue()) + uInt32(_reference.GetValue());

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
		NativeT<sInt16> operator- (const NativeT<N16_S> _subject, const NativeT<N16_R> _reference)
		{
			const Sign&& subjSign = _subject.GetSign(), refSign = _reference.GetSign();

			sInt32 result = sInt32(_subject.GetValue()) - sInt32(_reference.GetValue());

			if (result <= SInt16Min || result >= SInt16Max)
			{
				return NativeT<sInt16>(sInt16(result));
			}
			else
			{
				throw std::overflow_error("Native16 subtraction overflow.");
			}
		}

		NativeT<uInt16> operator- (const NativeT<uInt16> _subject, const NativeT<uInt16> _reference)
		{
			sInt32 result = sInt32(_subject.GetValue()) - sInt32(_reference.GetValue());

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
		NativeT<sInt16> operator* (const NativeT<N16_S> _subject, const NativeT<N16_R> _reference)
		{
			const Sign&& subjSign = _subject.GetSign(), refSign = _reference.GetSign();

			sInt16 result = _subject.GetValue() * _reference.GetValue();

			if (result != sInt16(0) && result / _subject.GetValue() != _reference.GetValue())
			{
				throw std::overflow_error("Native16 multiplication overflow.");
			}
			else
			{
				return NativeT<sInt16>(result);
			}
		}

		NativeT<uInt16> operator* (const NativeT<uInt16> _subject, const NativeT<uInt16> _reference)
		{
			uInt16 result = _subject.GetValue() + _reference.GetValue();

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
		NativeT<sInt16> operator/ (const NativeT<N16_S> _subject, const NativeT<N16_R> _reference)
		{
			const bool&& subjSigned = IsSameType<N16_S, sInt16>() ? true : false,
						  refSigned = IsSameType<N16_R, sInt16>() ? true : false ;

			const Sign&& subjSign = _subject.GetSign(), refSign = _reference.GetSign();

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

		NativeT<uInt16> operator/ (const NativeT<uInt16> _subject, const NativeT<uInt16> _reference)
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
}


