/*
Title       : PVN_HAL_Operations
Author      : Edward R. Gonzalez
File Name   : PVN_HAL_Operations.cpp
Date Created: 10-18-2019

Description:
Implements the operations for Primitive Value Native HAL.
*/

// Parent Header
#include "PVN_HAL_Operations.hpp"

// Includes

// Notation Engine

#include "DataTypes/FundamentalLimits.hpp"



Context(NotationEngine::Utility::Value)

SAlias
{
	using NE_U::SInt8Max;
}

SSource
{
	// Conditions

	sfn operator== (ro Ref(PVN_HAL) _subject, ro Ref(PVN_HAL) _reference) -> bool
	{
		if (_subject.GetSign() != _reference.GetSign())
		{
			return false;
		}
		else
		{
			switch (PVN_HAL::InclusiveType(_subject, _reference))
			{
				case ValueType::Native8 : return _subject.GetNative8() == _reference.GetNative8();
				case ValueType::Native16: return Native16(_subject)    == Native16(_reference)   ;
				case ValueType::Native32: return Native32(_subject)    == Native32(_reference)   ;
				case ValueType::Native64: return Native64(_subject)    == Native64(_reference)   ;
			}
		}
	}

	sfn operator!= (ro Ref(PVN_HAL) _subject, ro Ref(PVN_HAL) _reference) -> bool
	{
		if (_subject.GetSign() == _reference.GetSign())
		{
			return true;
		}
		else
		{
			switch (PVN_HAL::InclusiveType(_subject, _reference))
			{
				case ValueType::Native8 : return _subject.GetNative8() != _reference.GetNative8();
				case ValueType::Native16: return Native16(_subject)    != Native16(_reference)   ;
				case ValueType::Native32: return Native32(_subject)    != Native32(_reference)   ;
				case ValueType::Native64: return Native64(_subject)    != Native64(_reference)   ;
			}
		}
	}

	sfn operator< (ro Ref(PVN_HAL) _subject, ro Ref(PVN_HAL) _reference) -> bool
	{
		if (_subject.GetSign() != _reference.GetSign() && _subject.GetSign() == Sign::Positive)
		{
			return false;
		}
		else
		{
			switch (PVN_HAL::InclusiveType(_subject, _reference))
			{
				case ValueType::Native8 : return _subject.GetNative8() < _reference.GetNative8();
				case ValueType::Native16: return Native16(_subject)    < Native16(_reference)   ;
				case ValueType::Native32: return Native32(_subject)    < Native32(_reference)   ;
				case ValueType::Native64: return Native64(_subject)    < Native64(_reference)   ;
			}
		}
	}

	sfn operator> (ro Ref(PVN_HAL) _subject, ro Ref(PVN_HAL) _reference) -> bool
	{
		if (_subject.GetSign() != _reference.GetSign() && _subject.GetSign() == Sign::Positive)
		{
			return true;
		}
		else
		{
			switch (PVN_HAL::InclusiveType(_subject, _reference))
			{
				case ValueType::Native8 : return _subject.GetNative8() > _reference.GetNative8();
				case ValueType::Native16: return Native16(_subject)    > Native16(_reference)   ;
				case ValueType::Native32: return Native32(_subject)    > Native32(_reference)   ;
				case ValueType::Native64: return Native64(_subject)    > Native64(_reference)   ;
			}
		}
	}

	// Arithmetic

	sfn operator+ (ro Ref(PVN_HAL) _subject, ro Ref(PVN_HAL) _reference) -> bool
	{
		switch (PVN_HAL::InclusiveType(_subject, _reference))
		{
			case ValueType::Native8 : return _subject.GetNative8() + _reference.GetNative8();
			case ValueType::Native16: return Native16(_subject)    + Native16(_reference)   ;
			case ValueType::Native32: return Native32(_subject)    + Native32(_reference)   ;
			case ValueType::Native64: return Native64(_subject)    + Native64(_reference)   ;
		}
	}

	sfn operator- (ro Ref(PVN_HAL) _subject, ro Ref(PVN_HAL) _reference) -> bool
	{
		switch (PVN_HAL::InclusiveType(_subject, _reference))
		{
			case ValueType::Native8 : return _subject.GetNative8() - _reference.GetNative8();
			case ValueType::Native16: return Native16(_subject)    - Native16(_reference)   ;
			case ValueType::Native32: return Native32(_subject)    - Native32(_reference)   ;
			case ValueType::Native64: return Native64(_subject)    - Native64(_reference)   ;
		}
	}

	sfn operator* (ro Ref(PVN_HAL) _subject, ro Ref(PVN_HAL) _reference) -> bool
	{
		switch (PVN_HAL::InclusiveType(_subject, _reference))
		{
			case ValueType::Native8 : return _subject.GetNative8() * _reference.GetNative8();
			case ValueType::Native16: return Native16(_subject)    * Native16(_reference)   ;
			case ValueType::Native32: return Native32(_subject)    * Native32(_reference)   ;
			case ValueType::Native64: return Native64(_subject)    * Native64(_reference)   ;
		}
	}

	sfn operator/ (ro Ref(PVN_HAL) _subject, ro Ref(PVN_HAL) _reference) -> bool
	{
		switch (PVN_HAL::InclusiveType(_subject, _reference))
		{
			case ValueType::Native8 : return _subject.GetNative8() / _reference.GetNative8();
			case ValueType::Native16: return Native16(_subject)    / Native16(_reference)   ;
			case ValueType::Native32: return Native32(_subject)    / Native32(_reference)   ;
			case ValueType::Native64: return Native64(_subject)    / Native64(_reference)   ;
		}
	}
}

Context_End