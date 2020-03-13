/*
Title       : Native-64 Implementation
Author      : Edward R. Gonzalez
File Name   : Native64.cpp
Date Created: 2-10-2019

Description:
Contains implementation for Native64.
*/

//Parent Header
#include "Native64.hpp"

//Includes

//C++

#include <algorithm>
#include <cmath    >
#include <iostream >
#include <sstream  >

//Notation Engine

#include "PrimitiveValues/PrimitiveValues.hpp"
//#include "PrimitiveValues/PrimitiveValues_Casts.hpp"
#include "PrimitiveValues/Native8.hpp"
#include "PrimitiveValues/Native16.hpp"
#include "PrimitiveValues/Native32.hpp"

#include "Utility/DataTypes/FundamentalTypes.hpp"
#include "Utility/DataTypes/FundamentalLimits.hpp"



Context(NotationEngine::Utility::Value)

SAlias
{
	//C++
	using std::abs         ;
	using std::cerr        ;
	using std::cout        ;
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

	using NE_U::SInt32Min;
	using NE_U::SInt32Max;

	using NE_U::UInt32Max;

	using NE_U::Float64Min      ;
	using NE_U::Float64Max      ;
	using NE_U::Float64Precision;
}

SMeta
{
	eGlobal data<ro Ref(TypeData)> Native64_TypeID = typeid(Native64);
}

SSource
{
	ANative64::~ANative64() {}

	Native64::NU_64::NU_64()
	{
		UInteger = uInt64(0U);
	}

	Native64::NU_64::~NU_64() {}

	Native64::Native64(void)
	{
		typeID = N64_ID::UInteger;
	}

	Native64::Native64(ro sInt64 _int) :
		typeID(N64_ID::SInteger)
	{
		nValue.SInteger = _int;
	}

	Native64::Native64(ro uInt64 _int) :
		typeID(N64_ID::UInteger)
	{
		nValue.UInteger = _int;	
	}

	Native64::Native64(ro float64 _float) :
		typeID(N64_ID::Float)
	{
		nValue.Float = _float;
	}

	Native64::Native64(ro Ref(Native64) _n64) :
		nValue(_n64.nValue),
		typeID(_n64.typeID)
	{}

	Native64::Native64(rRef(Native64) _n64ToMove) noexcept :
			nValue(move(_n64ToMove.nValue)),
			typeID(move(_n64ToMove.typeID))
	{}

	Native64::~Native64() {}

	sfn Native64::ApproxEqual(ro float64 _first, ro float64 _second) -> bool
	{
		//Implementation influenced by: https://floating-point-gui.de/errors/comparison/, https://randomascii.wordpress.com/2012/02/25/comparing-floating-point-numbers-2012-edition/

		stack<ro float64> firstAbs  = abs(_first          ),
			              secondAbs = abs(_second         ),
			              diffAbs   = abs(_first - _second) ;

		stack<bool> ExactlyEqual,
			        CloseToZero  ;

		ExactlyEqual = (_first == _second                                        );
	    CloseToZero  = (_first == 0       || _second == 0 || diffAbs < Float64Min);

		if (ExactlyEqual)  //Handles infinites
		{
			return true;
		}
		else if (CloseToZero)   //Close to zero
		{
			return (diffAbs < (Float64Precision * Float64Min));
		}
		else                    //Relative Error
		{
			return (diffAbs / min(firstAbs + secondAbs, Float64Max) < Float64Precision);
		}
	}

	sfn Native64::ApproxGreater(ro float64 _first, ro float64 _second) -> bool
	{
		//Implementation influenced by: https://floating-point-gui.de/errors/comparison/, https://randomascii.wordpress.com/2012/02/25/comparing-floating-point-numbers-2012-edition/

		stack<ro float64> firstAbs  = abs(_first )        ,
			              secondAbs = abs(_second)        ,
			              diff      = firstAbs - secondAbs ;

		stack<bool> ExactlyEqual,
			        CloseToZero  ;

		ExactlyEqual = (_first == _second                                          );
		CloseToZero  = (_first == 0       || _second == 0 || abs(diff) < Float64Min);

		if (CloseToZero)   //Close to zero
		{
			return (diff > (Float64Precision * Float64Min)) && !signbit(diff);
		}
		else               //Relative Error
		{
			return (diff / min(firstAbs + secondAbs, Float64Max) > Float64Precision) && !signbit(diff);
		}
	}

	sfn Native64::ApproxLess(ro float64 _first, ro float64 _second) -> bool
	{
		//Implementation influenced by: https://floating-point-gui.de/errors/comparison/, https://randomascii.wordpress.com/2012/02/25/comparing-floating-point-numbers-2012-edition/

		stack<ro float64> firstAbs  = abs(_first )        ,
		                  secondAbs = abs(_second)        ,
			              diff      = firstAbs - secondAbs ;

		stack<bool> ExactlyEqual,
			        CloseToZero  ;

		ExactlyEqual = (_first == _second                                          );
		CloseToZero  = (_first == 0       || _second == 0 || abs(diff) < Float64Min);

		if (CloseToZero)   //Close to zero
		{
			return (diff > (Float64Precision * Float64Min)) && signbit(diff);
		}
		else               //Relative Error
		{
			return (diff / min(firstAbs + secondAbs, Float64Max) > Float64Precision) && signbit(diff);
		}
	}

	sfn Native64::InclusiveType(ro Ref(Native64) _first, ro Ref(Native64) _second) -> N64_ID
	{
		if (_first.typeID == _second.typeID)
		{
			return _first.typeID;
		}
		else
		{
			return N64_ID::Float;
		}
	}

	sfn Native64::GetID(void) ro -> N64_ID
	{
		return typeID;
	}

	sfn Native64::GetSign(void) ro -> Sign
	{
		switch (typeID)
		{
			case N64_ID::SInteger: return Int  ::Signum(nValue.SInteger);
			case N64_ID::UInteger: return Int  ::Signum(nValue.UInteger);
			case N64_ID::Float   : return Float::Signum(nValue.Float   );
		}
	}

	sfn Native64::GetSInteger(void) ro -> sInt64
	{
		if (typeID == N64_ID::SInteger)
		{
			return nValue.SInteger;
		}
		else
		{
			throw std::logic_error("Instance of Native64 is not set to signed integer. Returning an integer set to 0");
		}
	}

	sfn Native64::GetUInteger(void) ro -> uInt64
	{
		if (typeID == N64_ID::UInteger)
		{
			return nValue.UInteger;
		}
		else
		{
			throw std::logic_error("Instance of Native64 is not set to unsigned integer. Returning an integer set to 0U");
		}
	}

	sfn Native64::GetFloat(void) ro -> float64
	{
		if (typeID == N64_ID::Float)
		{
			return nValue.Float;
		}
		else
		{
			throw std::logic_error("Instance of Native64 is not set to float. Returning a float set to -1.0F");
		}
	}

	sfn Native64::GetTypeID(void) ro -> ro Ref(TypeData)
	{
		return Native64_TypeID;
	}

	sfn Native64::ReInitalize(void) -> void
	{
		typeID = N64_ID::UInteger;

		nValue.UInteger = uInt32(0U);
	}

	sfn Native64::Str(void) ro -> string
	{
		switch (typeID)
		{
			case N64_ID::SInteger:
			{
				stringstream result;

				result << "SInteger64:" << " " << nValue.SInteger;
				
				return result.str();
			}
			case N64_ID::UInteger:
			{
				stringstream result;

				result << "UInteger64:" << " " << nValue.UInteger;

				return result.str();
			}
			case N64_ID::Float:
			{
				stringstream result;
				
				result << "Float64:" << " " << nValue.Float;

				return result.str();
			}
		}
	}

	sfn Native64::SetSInteger(ro sInt64 _int) -> void
	{
		nValue.SInteger = _int;

		typeID = N64_ID::SInteger;
	}

	sfn Native64::SetUInteger(ro uInt64 _int) -> void
	{
		nValue.UInteger = _int;

		typeID = N64_ID::UInteger;
	}

	sfn Native64::SetToFloat(ro float64 _float) -> void
	{
		nValue.Float = _float;

		typeID = N64_ID::Float;
	}

	Native64::operator Native8()
	{
		switch (typeID)
		{
			case N64_ID::SInteger :
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
			case N64_ID::UInteger :
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
			case N64_ID::Float :
			{
				if 
				(
					ApproxLess (nValue.Float , SInt8Max) ||
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

	Native64::operator Native8() ro
	{
		switch (typeID)
		{
			case N64_ID::SInteger:
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
			case N64_ID::UInteger:
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
			case N64_ID::Float:
			{
				if
					(
						ApproxLess (nValue.Float, SInt8Max) ||
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

	Native64::operator Native16()
	{
		switch (typeID)
		{
			case N64_ID::SInteger :
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
			case N64_ID::UInteger :
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
			case N64_ID::Float :
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

	Native64::operator Native16() ro
	{
		switch (typeID)
		{
			case N64_ID::SInteger:
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
			case N64_ID::UInteger:
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
			case N64_ID::Float:
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

	Native64::operator Native32()
	{
		switch (typeID)
		{
			case N64_ID::SInteger:
			{
				if (nValue.SInteger <= SInt32Max)
				{
					if (nValue.SInteger >= SInt32Min)
					{
						return Native32(sInt32(nValue.SInteger));
					}
					else
					{
						throw std::logic_error("Cannot convert Native32 SInteger to Native8. The value is out of signed range.");
					}
				}
				else if (nValue.SInteger <= UInt32Max)
				{
					return Native32(uInt32(nValue.SInteger));
				}
				else
				{
					throw std::logic_error("Cannot convert Native32 SInteger to Native8. The value is out of unsigned range.");
				}
			}
			case N64_ID::UInteger:
			{
				if (nValue.UInteger < UInt32Max)
				{
					return Native32(uInt32(nValue.UInteger));
				}
				else
				{
					throw std::logic_error("Cannot convert Native64 to Native32. Native64's integer value is to large.");
				}
			}
			case N64_ID::Float:
			{
				if (nValue.Float > Float32Max)
				{
					if (nValue.Float < Float32Min)
					{
						return Native32(float32(nValue.Float));
					}
					else
					{
						throw std::logic_error("Cannot convert Native64 to Native32. Native64's float value is too small.");
					}
				}
				else
				{
					throw std::logic_error("Cannot convert Native64 to Native32. Native64's float value is too large.");
				}
			}
			}
	}

	Native64::operator Native32() ro
	{
		switch (typeID)
		{
			case N64_ID::SInteger:
			{
				if (nValue.SInteger <= SInt32Max)
				{
					if (nValue.SInteger >= SInt32Min)
					{
						return Native32(sInt32(nValue.SInteger));
					}
					else
					{
						throw std::logic_error("Cannot convert Native32 SInteger to Native8. The value is out of signed range.");
					}
				}
				else if (nValue.SInteger <= UInt32Max)
				{
					return Native32(uInt32(nValue.SInteger));
				}
				else
				{
					throw std::logic_error("Cannot convert Native32 SInteger to Native8. The value is out of unsigned range.");
				}
			}
			case N64_ID::UInteger:
			{
				if (nValue.UInteger < UInt32Max)
				{
					return Native32(uInt32(nValue.UInteger));
				}
				else
				{
					throw std::logic_error("Cannot convert Native64 to Native32. Native64's integer value is to large.");
				}
			}
			case N64_ID::Float:
			{
				if (nValue.Float > Float32Max)
				{
					if (nValue.Float < Float32Min)
					{
						return Native32(float32(nValue.Float));
					}
					else
					{
						throw std::logic_error("Cannot convert Native64 to Native32. Native64's float value is too small.");
					}
				}
				else
				{
					throw std::logic_error("Cannot convert Native64 to Native32. Native64's float value is too large.");
				}
			}
		}
	}

	sfn Native64::operator=(ro Ref(Native64) _native64) -> Native64
	{
		nValue = _native64.nValue;
		typeID = _native64.typeID;

		return dref(this);
	}

	sfn Native64::operator=(rRef(Native64) _n64ToMove) noexcept -> Ref(Native64)
	{
		if (this == getAddress(_n64ToMove))
		{
			return obj(this);
		}

		nValue = move(_n64ToMove.nValue);
		typeID = move(_n64ToMove.typeID);

		return obj(this);
	}
}

Context_End