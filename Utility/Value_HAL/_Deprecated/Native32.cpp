/*
Title       : Native-32 Implementation
Author      : Edward R. Gonzalez
File Name   : Native32.cpp
Date Created: 3-7-2019

Description:
Contains implementation for Native32.
*/

//Parent Header
#include "Native32.hpp"

//Includes

//C++

#include <algorithm>
#include <cmath    >
#include <iostream >
#include <sstream  >

//Notation Engine

#include "PrimitiveValues/PrimitiveValues.hpp"
#include "PrimitiveValues/Native8.hpp"
#include "PrimitiveValues/Native16.hpp"
#include "PrimitiveValues/Native64.hpp"

#include "Utility/DataTypes/FundamentalTypes.hpp"
#include "Utility/DataTypes/FundamentalLimits.hpp"



Context(NotationEngine::Utility::Value)

SAlias
{
	//C++

	using std::abs         ;
	using std::cout        ;
	using std::cerr        ;
	using std::endl        ;
	using std::min         ;
	using std::move        ;
	using std::string      ;
	using std::stringstream;


	//Notation Engine

	using NE_U::SInt8Min;
	using NE_U::SInt8Max;
	using NE_U::UInt8Max;

	using NE_U::SInt16Min;
	using NE_U::SInt16Max;
	using NE_U::UInt16Max;

	using NE_U::Float32Min      ;
	using NE_U::Float32Max      ;
	using NE_U::Float32Precision;
}

SMeta
{
	eGlobal data<ro Ref(TypeData)> Native32_TypeID = typeid(Native32);
}

SSource
{
	ANative32::~ANative32(void)	{}

	Native32::NU_32::NU_32(void)
	{
		UInteger = 0U;
	}

	Native32::NU_32::~NU_32(void) {}

	Native32::Native32(void)
	{
		typeID = N32_ID::UInteger;
	}

	Native32::Native32(ro sInt32 _int) :
		typeID(N32_ID::SInteger)
	{
		nValue.SInteger = _int;
	}

	Native32::Native32(ro uInt32 _int) :
		typeID(N32_ID::UInteger)
	{
		nValue.UInteger = _int;
	}

	Native32::Native32(ro float32 _float) :
		typeID(N32_ID::Float)
	{
		nValue.Float = _float;
	}

	Native32::Native32(ro Ref(Native32) _ori) :
		nValue(_ori.nValue),
		typeID(_ori.typeID)
	{}

	Native32::Native32(rRef(Native32) _n32ToMove) noexcept
	{
		if (this != Address(_n32ToMove))
		{
			nValue = move(_n32ToMove.nValue);
			typeID = move(_n32ToMove.typeID);
		}
	}

	Native32::~Native32(void) {}

	sfn Native32::ApproxEqual(ro float32 _first, ro float32 _second) -> bool
	{
		//Implementation influenced by: https://floating-point-gui.de/errors/comparison/

		ro float32 firstAbs  = abs(_first          ),
				   secondAbs = abs(_second         ),
				   diffAbs   = abs(_first - _second) ;

		bool ExactlyEqual, 
			 CloseToZero  ;

		ExactlyEqual = (_first == _second                                        );
		CloseToZero  = (_first == 0       || _second == 0 || diffAbs < Float32Min);

		if (ExactlyEqual)  //Handles infinites
		{
			return true;
		}
		else if (CloseToZero)   //Close to zero
		{
			return (diffAbs < (Float32Precision * Float32Min));
		}
		else                    //Relative Error
		{
			return (diffAbs / min(firstAbs + secondAbs, Float32Max) < Float32Precision);
		}
	}

	sfn Native32::ApproxGreater(ro float32 _first, ro float32 _second) -> bool
	{
		//Implementation influenced by: https://floating-point-gui.de/errors/comparison/

		stack<ro float32> firstAbs  = abs(_first )        ,
				          secondAbs = abs(_second)        ,
				          diff      = firstAbs - secondAbs ;

		stack<bool> ExactlyEqual,
			        CloseToZero  ;

		ExactlyEqual = (_first == _second                                          ),
		CloseToZero  = (_first == 0       || _second == 0 || abs(diff) < Float32Min) ;

		if (CloseToZero)   //Close to zero
		{
			return (diff > (Float32Precision * Float32Min)) && !signbit(diff);
		}
		else               //Relative Error
		{
			return (diff / min(firstAbs + secondAbs, Float32Max) > Float32Precision) && !signbit(diff);
		}
	}

	sfn Native32::ApproxLess(ro float32 _first, ro float32 _second) -> bool
	{
		//Implementation influenced by: https://floating-point-gui.de/errors/comparison/

		stack<ro float32> firstAbs  = abs(_first )        ,
				          secondAbs = abs(_second)        ,
				          diff      = firstAbs - secondAbs ;

		stack<bool> ExactlyEqual,
			        CloseToZero  ;

		ExactlyEqual = (_first == _second                                          );
		CloseToZero  = (_first == 0       || _second == 0 || abs(diff) < Float32Min);

		if (CloseToZero)   //Close to zero
		{
			return (diff > (Float32Precision * Float32Min)) && signbit(diff);
		}
		else               //Relative Error
		{
			return (diff / min(firstAbs + secondAbs, Float32Max) > Float32Precision) && signbit(diff);
		}
	}

	sfn Native32::InclusiveType(ro Native32 _first, ro Native32 _second) -> N32_ID
	{
		return _first.typeID == _second.typeID ? _first.typeID : N32_ID::Float;
	}

	sfn Native32::GetID(void) ro -> N32_ID
	{
		return typeID;
	}

	sfn Native32::GetSign(void) ro -> Sign
	{
		switch (typeID)
		{
			case N32_ID::SInteger:
			{	
				return NE_U::Int::Signum<sInt32>(nValue.SInteger);
			}
			case N32_ID::UInteger:
			{
				return NE_U::Int::Signum<uInt32>(nValue.UInteger);
			}
			case N32_ID::Float:
			{
				return NE_U::Float::Signum<float32>(nValue.Float);
			}
		}
	}

	sfn Native32::GetSInteger(void) ro -> sInt32
	{
		if (typeID == N32_ID::SInteger)
		{
			return nValue.SInteger;
		}
		else
		{
			throw std::logic_error("Instance of Native32 not set to type signed integer. Returning an integer set to 0");
		}
	}

	sfn Native32::GetUInteger(void) ro -> uInt32
	{
		if (typeID == N32_ID::UInteger)
		{
			return nValue.UInteger;
		}
		else
		{
			throw std::logic_error("Instance of Native32 not set to type unsigned integer. Returning an integer set to 0U");
		}
	}

	sfn Native32::GetFloat(void) ro -> float32
	{
		if (typeID == N32_ID::Float)
		{
			return nValue.Float;
		}
		else
		{
			throw std::logic_error("Instance of Native32 not set to type float. Returning a float set to 0.0F");
		}
	}

	sfn Native32::GetTypeID(void) ro -> ro Ref(TypeData)
	{
		return Native32_TypeID;
	}

	sfn Native32::ReInitalize(void) -> void
	{
		typeID = N32_ID::UInteger;

		nValue.UInteger = 0;
	}

	sfn Native32::Str(void) ro -> string
	{

		switch (typeID)
		{
			case N32_ID::SInteger:
			{
				stringstream result;

				result << "Integer32:" << " " << nValue.SInteger;

				return result.str();
			}
			case N32_ID::UInteger:
			{
				stringstream result;

				result << "Integer32:" << " " << nValue.UInteger;

				return result.str();
			}
			case N32_ID::Float:
			{
				stringstream result;

				result << "Float32:" << " " << nValue.Float;

				return result.str();
			}
		}
	}

	sfn Native32::SetSInteger(ro sInt32 _intToSet) -> void
	{
		nValue.SInteger = _intToSet;

		typeID = N32_ID::SInteger;
	}

	sfn Native32::SetUInteger(ro uInt32 _intToSet) -> void
	{
		nValue.UInteger = _intToSet;

		typeID = N32_ID::UInteger;
	}

	sfn Native32::SetFloat(ro float32 _floatToSet) -> void
	{
		nValue.Float = _floatToSet;

		typeID = N32_ID::Float;
	}

	Native32::operator Native8(void)
	{
		switch (typeID)
		{
			case N32_ID::SInteger :
			{
				if (nValue.SInteger <= SInt8Max)
				{
					if (nValue.SInteger >= SInt8Min)
					{
						return Native8(sInt8(nValue.SInteger));
					}
					else
					{
						throw std::logic_error("Cannot convert Native32 SInteger to Native8. The value is out of signed range.");
					}
				}
				else if (nValue.SInteger <= UInt8Max)
				{
					return Native8(uInt8(nValue.SInteger));
				}
				else
				{
					throw std::logic_error("Cannot convert Native32 SInteger to Native8. The value is out of unsigned range.");
				}
			}
			case N32_ID::UInteger :
			{
				if (nValue.UInteger < UInt8Max)
				{
					return Native8(uInt8(nValue.UInteger));
				}
				else
				{
					throw std::logic_error("Cannot convert Native32 to Native8. The value of this Native32 is beyond the bounds of Native8 values");
				}
			}
			case N32_ID::Float :
			{
				if 
				(
					ApproxLess(nValue.Float , SInt8Max) ||
					ApproxEqual(nValue.Float, SInt8Max)
				)
				{
					if 
					(
						ApproxGreater(nValue.Float, SInt8Min) ||
						ApproxEqual  (nValue.Float, SInt8Max)
					)
					{
						return Native8(sInt8(nValue.Float));
					}
					else
					{
						throw std::logic_error("Cannot convert Native32 to Native8. the value of this Native32 is beyond the bounds of Native8 values.");
					}
				}
				else if (ApproxLess(nValue.Float, UInt8Max))
				{
					return Native8(uInt8(nValue.Float));
				}
				else
				{
					
					throw std::logic_error("Cannot convert Native32 to Native8. The value of this Native32's float is beyond the bounds of the Native8 possible values.");
				}
			}
		}
	}

	Native32::operator Native8(void) ro
	{
		switch (typeID)
		{
			case N32_ID::SInteger :
			{
				if (nValue.SInteger <= SInt8Max)
				{
					if (nValue.SInteger >= SInt8Min)
					{
						return Native8(sInt8(nValue.SInteger));
					}
					else
					{
						throw std::logic_error("Cannot convert Native32 SInteger to Native8. The value is out of signed range.");
					}
				}
				else if (nValue.SInteger <= UInt8Max)
				{
					return Native8(uInt8(nValue.SInteger));
				}
				else
				{
					throw std::logic_error("Cannot convert Native32 SInteger to Native8. The value is out of unsigned range.");
				}
			}
			case N32_ID::UInteger :
			{
				if (nValue.UInteger < UInt8Max)
				{
					return Native8(uInt8(nValue.UInteger));
				}
				else
				{
					throw std::logic_error("Cannot convert Native32 to Native8. The value of this Native32 is beyond the bounds of Native8 values");
				}
			}
			case N32_ID::Float :
			{
				if 
				(
					ApproxLess(nValue.Float , SInt8Max) ||
					ApproxEqual(nValue.Float, SInt8Max)
				)
				{
					if 
					(
						ApproxGreater(nValue.Float, SInt8Min) ||
						ApproxEqual  (nValue.Float, SInt8Max)
					)
					{
						return Native8(sInt8(nValue.Float));
					}
					else
					{
						throw std::logic_error("Cannot convert Native32 to Native8. the value of this Native32 is beyond the bounds of Native8 values.");
					}
				}
				else if (ApproxLess(nValue.Float, UInt8Max))
				{
					return Native8(uInt8(nValue.Float));
				}
				else
				{
					
					throw std::logic_error("Cannot convert Native32 to Native8. The value of this Native32's float is beyond the bounds of the Native8 possible values.");
				}
			}
		}
	}

	Native32::operator Native16(void)
	{
		switch (typeID)
		{
			case N32_ID::SInteger :
			{
				if (nValue.SInteger <= SInt16Max)
				{
					if (nValue.SInteger >= SInt16Min)
					{
						return Native16(sInt16(nValue.SInteger));
					}
					else
					{
						throw std::logic_error("Cannot convert Native32 SInteger to Native8. The value is out of signed range.");
					}
				}
				else if (nValue.SInteger <= UInt8Max)
				{
					return Native16(uInt16(nValue.SInteger));
				}
				else
				{
					throw std::logic_error("Cannot convert Native32 SInteger to Native8. The value is out of unsigned range.");
				}
			}
			case N32_ID::UInteger :
			{
				if (nValue.UInteger < UInt16Max)
				{
					return Native16(uInt16(nValue.UInteger));
				}
				else
				{
					throw std::logic_error("Cannot convert Native32 to Native8. The value of this Native32 is beyond the bounds of Native8 values");
				}
			}
			case N32_ID::Float :
			{
				if 
				(
					ApproxLess (nValue.Float, SInt16Max) ||
					ApproxEqual(nValue.Float, SInt16Max)
				)
				{
					if 
					(
						ApproxGreater(nValue.Float, SInt16Min) ||
						ApproxEqual  (nValue.Float, SInt16Max)
					)
					{
						return Native16(sInt16(nValue.Float));
					}
					else
					{
						throw std::logic_error("Cannot convert Native32 to Native8. the value of this Native32 is beyond the bounds of Native8 values.");
					}
				}
				else if (ApproxLess(nValue.Float, UInt16Max))
				{
					return Native16(uInt16(nValue.Float));
				}
				else
				{

					throw std::logic_error("Cannot convert Native32 to Native8. The value of this Native32's float is beyond the bounds of the Native8 possible values.");
				}
			}
			}
		}
	}

	Native32::operator Native16(void) ro
	{
		switch (typeID)
		{
			case N32_ID::SInteger :
			{
				if (nValue.SInteger <= SInt16Max)
				{
					if (nValue.SInteger >= SInt16Min)
					{
						return Native16(sInt16(nValue.SInteger));
					}
					else
					{
						throw std::logic_error("Cannot convert Native32 SInteger to Native8. The value is out of signed range.");
					}
				}
				else if (nValue.SInteger <= UInt8Max)
				{
					return Native16(uInt16(nValue.SInteger));
				}
				else
				{
					throw std::logic_error("Cannot convert Native32 SInteger to Native8. The value is out of unsigned range.");
				}
			}
			case N32_ID::UInteger :
			{
				if (nValue.UInteger < UInt16Max)
				{
					return Native16(uInt16(nValue.UInteger));
				}
				else
				{
					throw std::logic_error("Cannot convert Native32 to Native8. The value of this Native32 is beyond the bounds of Native8 values");
				}
			}
			case N32_ID::Float :
			{
				if 
				(
					ApproxLess (nValue.Float, SInt16Max) ||
					ApproxEqual(nValue.Float, SInt16Max)
				)
				{
					if 
					(
						ApproxGreater(nValue.Float, SInt16Min) ||
						ApproxEqual  (nValue.Float, SInt16Max)
					)
					{
						return Native16(sInt16(nValue.Float));
					}
					else
					{
						throw std::logic_error("Cannot convert Native32 to Native8. the value of this Native32 is beyond the bounds of Native8 values.");
					}
				}
				else if (ApproxLess(nValue.Float, UInt16Max))
				{
					return Native16(uInt16(nValue.Float));
				}
				else
				{

					throw std::logic_error("Cannot convert Native32 to Native8. The value of this Native32's float is beyond the bounds of the Native8 possible values.");
				}
			}
		}
	}

	Native32::operator Native64(void)
	{
		switch (typeID)
		{
			case N32_ID::SInteger:
			{
				return Native64(sInt64(nValue.SInteger));
			}
			case N32_ID::UInteger:
			{
				return Native64(uInt64(nValue.UInteger));
			}
			case N32_ID::Float:
			{
				return Native64(float64(nValue.Float));
			}
			default:
			{
				return Native64(-1.0F);
			}
		}
	}

	Native32::operator Native64(void) ro
	{
		switch (typeID)
		{
			case N32_ID::SInteger:
			{
				return Native64(sInt64(nValue.SInteger));
			}
			case N32_ID::UInteger:
			{
				return Native64(uInt64(nValue.UInteger));
			}
			case N32_ID::Float:
			{
				return Native64(float64(nValue.Float));
			}
			default:
			{
				return Native64(-1.0F);
			}
		}
	}

	sfn Native32::operator=(ro Ref(Native32) _native32) -> Native32
	{
		nValue = _native32.nValue;
		typeID = _native32.typeID;

		return dref(this);
	}

	sfn Native32::operator=(rRef(Native32) _n32ToMove) noexcept -> Ref(Native32)
	{
		if (this == getAddress(_n32ToMove))
		{
			return obj(this);
		}

		nValue = move(_n32ToMove.nValue);
		typeID = move(_n32ToMove.typeID);

		return obj(this);
	}

Context_End