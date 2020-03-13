/*
Title       : Primitive Values Implementation
Author      : Edward R. Gonzalez
File Name   : PrimitiveValues.cpp
Date Created: 3-7-2019

Description:
Contains implementation for the primitive value's context functions.
*/

//Includes

//Parent Header
#include "PrimitiveValues_Casts.hpp"

//C++
#include <iostream>

//Notation Engine
#include "PrimitiveValues/Native32.hpp"
#include "PrimitiveValues/Native64.hpp"

#include "Utility/FundamentalTypes/FundamentalTypes.hpp"
#include "Utility/FundamentalTypes/FundamentalLimits.hpp"



Context(NotationEngine::Utility::Value)

SAlias
{
	//C++
	using std::cout;
	using std::endl;

	//Notation Engine
	using NE_U::UInt8Max ;
	using NE_U::UInt16Max;
}

SSource
{
	//Context Functions

	//sfn CastToNative8(ro Ref(Native16) _native16) -> Native8
	//{
	//	if (_native16 < UInt8Max)
	//	{
	//		return Native8(_native16);
	//	}
	//	else
	//	{
	//		cout << "Cannot convert value to Native8. Native16 value is too large." << endl;

	//		return Native8();
	//	};
	//}

	//sfn CastToNative8(ro Ref(Native32) _native32) -> Native8
	//{
	//	switch (_native32.GetID())
	//	{
	//	case N32_ID::Integer:
	//	{
	//		if (_native32.GetInteger() < UInt8Max)
	//		{
	//			return Native8(_native32.GetInteger());
	//		}
	//		else
	//		{
	//			cout << "Cannot convert value to Native8. Native32's integer value is too large." << endl;

	//			return Native8();
	//		}
	//	}
	//	case N32_ID::Float:
	//	{
	//		//TODO: Make sure this check is correct.
	//		if 
	//		(
	//			Native32::ApproxGreater(_native32.GetFloat(), 0.0F    ) &&
	//			Native32::ApproxLess   (_native32.GetFloat(), UInt8Max)
	//		)
	//		{
	//			return Native8(_native32.GetFloat());
	//		}
	//		else
	//		{
	//			cout << "Cannot convert value to Native8. Native32's float value is not within range of uInt8's." << endl;

	//			return Native8();
	//		}
	//	}
	//	default:
	//	{
	//		return Native8();
	//	}
	//	}
	//}

	//sfn CastToNative8(ro Ref(Native64) _native64) -> Native8
	//{
	//	switch (_native64.GetID())
	//	{
	//	case N64_ID::Integer:
	//	{
	//		if (_native64.GetInteger() < UInt8Max)
	//		{
	//			return Native8(_native64.GetInteger());
	//		}
	//		else
	//		{
	//			cout << "Cannot convert value to Native8. Native64's integer value is to large." << endl;

	//			return Native8();
	//		}
	//	}
	//	case N64_ID::Float:
	//	{
	//		if
	//		(
	//			Native64::ApproxGreater(_native64.GetFloat(), 0.0F    ) &&
	//			Native64::ApproxLess   (_native64.GetFloat(), UInt8Max)
	//		)
	//		{
	//			return Native8(_native64.GetFloat());
	//		}
	//		else
	//		{
	//			cout << "Cannot convert value to native8. Native64's float value is not within range of uInt8's." << endl;

	//			return Native8();
	//		}
	//	}
	//	default:
	//	{
	//		return Native8();
	//	}
	//	}
	//}

	//sfn CastToNative16(ro Ref(Native32) _native32) -> Native16
	//{
	//	switch (_native32.GetID())
	//	{
	//	case N32_ID::Integer:
	//	{
	//		if (_native32.GetInteger() < UInt16Max)
	//		{
	//			return Native16(_native32.GetInteger());
	//		}
	//		else
	//		{
	//			cout << "Cannot convert value to native16. Native32's integer value is not within range of uIn16's." << endl;

	//			return Native16();
	//		}
	//	}
	//	case N32_ID::Float:
	//	{
	//		if
	//		(
	//			Native32::ApproxGreater(_native32.GetFloat(), 0.0F     ) &&
	//			Native32::ApproxLess   (_native32.GetFloat(), UInt16Max)
	//		)
	//		{
	//			return Native16(_native32.GetFloat());
	//		}
	//		else
	//		{
	//			cout << "Cannot convert value to native16. Native32's float value is not within range of uInt16's." << endl;

	//			return Native16();
	//		}
	//	}
	//	default:
	//	{
	//		return Native16();
	//	}
	//	}
	//}

	//sfn CastToNative16(ro Ref(Native64) _native64) -> Native16
	//{
	//	switch (_native64.GetID())
	//	{
	//	case N64_ID::Integer:
	//	{
	//		if (_native64.GetInteger() < UInt16Max)
	//		{
	//			return Native16(_native64.GetInteger());
	//		}
	//		else
	//		{
	//			cout << "Cannot convert to Native16. Native64's integer value is greater than uInt16's range." << endl;

	//			return Native16();
	//		}
	//	}
	//	case N64_ID::Float:
	//	{
	//		if 
	//		(
	//			Native64::ApproxGreater(_native64.GetFloat(), 0.0F     ) &&
	//			Native64::ApproxLess   (_native64.GetFloat(), UInt16Max)
	//		)
	//		{
	//			return Native16(_native64.GetFloat());
	//		}
	//		else
	//		{
	//			cout << "Cannot convert to Native16. Native64's float value is not within range of uInt16's." << endl;

	//			return Native16();
	//		}
	//	}
	//	default:
	//	{
	//		return Native16();
	//	}
	//	}
	//}

	//sfn CastToNative32(ro Ref(Native8) _native8) -> Native32
	//{
	//	Native32 result;

	//	result.SetToInteger(_native8);

	//	return result;
	//}

	//sfn CastToNative32(ro Ref(Native16) _native16) -> Native32
	//{
	//	Native32 result;

	//	result.SetToInteger(_native16);

	//	return result;
	//}

	//sfn CastToNative64(ro Ref(Native8) _native8) -> Native64
	//{
	//	Native64 result;

	//	result.SetToInteger(_native8);

	//	return result; //Native64((uInt64)_aNative8Ptr);
	//}

	//sfn CastToNative64(ro Ref(Native16) _native16) -> Native64
	//{
	//	Native64 result;

	//	result.SetToInteger(_native16);

	//	return result; //Native64((uInt64)_native16);
	//}
}

Context_End