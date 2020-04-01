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



namespace NotationEngine::Utility::Value
{
	inline namespace Source
	{
		// TODO: Requires optimization.

		// Comparison:

		// Operator ==

		bool operator==(const NativeT<sInt8> _subject, const NativeT<uInt8> _reference)
		{
			return _reference.GetValue() <= SInt8Max ? _subject.GetValue() == sInt8(_reference.GetValue()) : false;
		}
		
		bool operator==(const NativeT<uInt8> _subject, const NativeT<sInt8> _reference) 
		{
			return _subject.GetValue() <= SInt8Max ? sInt32(_subject.GetValue()) == _reference.GetValue() : false;
		}

		// Operator !=

		bool operator!=(const NativeT<sInt8> _subject, const NativeT<uInt8> _reference)
		{
			return _reference.GetValue() <= SInt8Max ? _subject.GetValue() != sInt8(_reference.GetValue()) : true;
		}

		bool operator!=(const NativeT<uInt8> _subject, const NativeT<sInt8> _reference)
		{
			return _subject.GetValue() <= SInt8Max ? sInt32(_subject.GetValue()) != _reference.GetValue() : true;
		}

		// Operator <

		bool operator<(const NativeT<sInt8> _subject, const NativeT<uInt8> _reference)
		{
			return _reference.GetValue() <= SInt8Max ? _subject.GetValue() < sInt8(_reference.GetValue()) : true;
		}

		bool operator<(const NativeT<uInt8> _subject, const NativeT<sInt8> _reference)
		{
			return _subject.GetValue() <= SInt8Max ? sInt32(_subject.GetValue()) < _reference.GetValue() : false;
		}

		// Operator >

		bool operator>(const NativeT<sInt8> _subject, const NativeT<uInt8> _reference)
		{
			return _reference.GetValue() <= SInt8Max ? _subject.GetValue() > sInt8(_reference.GetValue()) : false;
		}

		bool operator>(const NativeT<uInt8> _subject, const NativeT<sInt8> _reference)
		{
			return _subject.GetValue() <= SInt8Max ? sInt32(_subject.GetValue()) > _reference.GetValue() : true;
		}


		// Arithmetic

		// Operator +

		template<typename N8_S, typename N8_R>
		Native<sInt8> operator+ (const NativeT<N8_S> _subject, const NativeT<N8_R> _reference)
		{
			const Sign&& subjSign = _subject.GetSign(), refSign = _reference.GetSign(); 

			sInt16 result = sInt16(_subject.GetValue()) + sInt16(_reference.GetValue());

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

		Native<uInt8> operator+ (const NativeT<uInt8> _subject, const NativeT<uInt8> _reference)
		{
			sInt16 result = sInt16(_subject.GetValue()) + sInt16(_reference.GetValue());

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
		NativeT<sInt8> operator- (const NativeT<N8_S> _subject, const NativeT<N8_R> _reference)
		{
			const Sign&& subjSign = _subject.GetSign(), refSign = _reference.GetSign();

			sInt16 result = sInt16(_subject.GetValue()) - sInt16(_reference.GetValue());

			if (result <= SInt8Min || result >= SInt8Max)
			{
				return NativeT<sInt8>(sInt8(result));
			}
			else
			{
				throw std::overflow_error("Native8 subtraction overflow.");
			}
		}

		NativeT<uInt8> operator- (ro NativeT<uInt8>_subject, ro NativeT<uInt8> _reference)
		{
			sInt16 result = sInt16(_subject.GetValue()) - sInt16(_reference.GetValue());

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
		NativeT<sInt8> operator* (const NativeT<N8_S> _subject, const NativeT<N8_R> _reference)
		{
			const Sign&& subjSign = _subject.GetSign(), refSign = _reference.GetSign();

			sInt8 result = _subject.GetValue() * _reference.GetValue();

			if (result != sInt8(0) && result / _subject.GetValue() != _reference.GetValue())
			{
				throw std::overflow_error("Native8 multiplication overflow.");
			}
			else
			{
				return NativeT<sInt8>(result);
			}
		}

		NativeT<uInt8> operator* (const NativeT<uInt8> _subject, const NativeT<uInt8> _reference)
		{
			uInt8 result = _subject.GetValue() + _reference.GetValue();

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
		Native<sInt8> operator/ (const NativeT<N8_S> _subject, const NativeT<N8_R> _reference)
		{
			const bool&& subjSigned = IsSameType<N8_S, sInt8>() ? true : false,
						  refSigned = IsSameType<N8_R, sInt8>() ? true : false ;

			const Sign&& subjSign = _subject.GetSign(), refSign = _reference.GetSign();

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

		Native<uInt8> operator/ (const NativeT<uInt8> _subject, const NativeT<uInt8> _reference)
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
}
