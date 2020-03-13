/*
Title       : Native-16 Implementation
Author      : Edward R. Gonzalez
File Name   : Native16.cpp
Date Created: 10-4-2019

Description:
Implements Native-16.
*/

// Parent Header
#include "Native16.hpp"

// Includes

// C++
#include <iostream >
#include <sstream  >
#include <utility  >

// Notation Engine
#include "DataTypes/FundamentalLimits.hpp"
#include "Native8.hpp"
#include "Native32.hpp"
#include "Native64.hpp"



Context(NotationEngine::Utility::Value)

SAlias
{
	// C++

	using std::cerr        ;
	using std::cout        ;
	using std::endl        ;
	using std::move        ;
	using std::stringstream;

	// Notation Engine
	using NE_U::SInt8Min;
	using NE_U::SInt8Max;

	using NE_U::UInt8Max;
}

SMeta
{
	eGlobal data<ro Ref(TypeData)> Native16_TypeID = typeid(Native16);
}

SSource
{
	Native16::NU_16:: NU_16() {}
	Native16::NU_16::~NU_16() {}

	Native16::Native16() :
		typeID(N16_ID::Unsigned)
	{
		nValue.UInteger = 0U;
	}

	Native16::Native16(ro sInt16 _sInt) :
		typeID(N16_ID::Signed)
	{
		nValue.SInteger = _sInt;
	}

	Native16::Native16(ro uInt16 _uInt) :
		typeID(N16_ID::Unsigned)
	{
		nValue.UInteger = _uInt;
	}

	Native16::Native16(ro Ref(Native16) _n16) :
		typeID(_n16.typeID),
		nValue(_n16.nValue)
	{}

	Native16::Native16(rRef(Native16) _n16) noexcept
	{
		if (this != Address(_n16))
		{
			typeID = move(_n16.typeID);
			nValue = move(_n16.nValue);
		}
	}

	ANative16::~ANative16() {}

	Native16::~Native16() {}

	sfn Native16::GetID() ro -> N16_ID
	{
		return typeID;
	}

	sfn Native16::GetSign() ro -> Sign
	{
		switch (typeID)
		{
			case N16_ID::Signed:
			{
				return NE_U::Int::Signum<sInt16>(nValue.SInteger);
			}
			case N16_ID::Unsigned:
			{
				return nValue.UInteger == uInt16(0U) ? Sign::Neutral : Sign::Positive;
			}
		}
	}

	sfn Native16::GetSigned() ro -> sInt16
	{
		if (typeID == N16_ID::Signed)
		{
			return nValue.SInteger;
		}
		else
		{
			throw std::logic_error("Instance of Native8 not set to a signed integer.");
		}
	}

	sfn Native16::GetUnsigned() ro -> uInt16
	{
		if (typeID == N16_ID::Unsigned)
		{
			return nValue.UInteger;
		}
		else
		{
			throw std::logic_error("Instance of Native8 not set to a unsigned integer.");
		}
	}

	sfn Native16::GetTypeID(void) ro -> ro Ref(TypeData)
	{
		return Native16_TypeID;
	}

	sfn Native16::ReInitalize() -> void
	{
		typeID = N16_ID::Unsigned;

		nValue.UInteger = uInt16(0U);
	}

	sfn Native16::Str() ro -> string
	{
		switch (typeID)
		{
		case N16_ID::Signed:
		{
			stringstream result;
			result << "Signed Int8:" << " " << nValue.SInteger;

			return result.str();
		}
		case N16_ID::Unsigned:
		{
			stringstream result;
			
			result << "Unsigned Int8: " << " " << nValue.UInteger;

			return result.str();
		}
		}
	}

	sfn Native16::SetSigned(ro sInt16 _sInt) -> void
	{
		nValue.SInteger = _sInt         ;
		typeID          = N16_ID::Signed;
	}

	sfn Native16::SetUnsigned(ro uInt16 _uInt) -> void
	{
		nValue.UInteger = _uInt           ;
		typeID          = N16_ID::Unsigned;
	}

	Native16::operator Native8(void)
	{
		switch (typeID)
		{
			case N16_ID::Signed:
			{
				if (nValue.SInteger > SInt8Min && nValue.SInteger < SInt8Max)
				{
					return Native8(sInt8(nValue.SInteger));
				}
				else
				{
					throw std::logic_error("Cannot convert to Native8 from Native16. The value of this Native16 is beyond the accepted value bounds of Native8.");
				}
			}
			case N16_ID::Unsigned:
			{
				if (nValue.UInteger < UInt8Max)
				{
					return Native8(uInt8(nValue.UInteger));
				}
				else
				{
					throw std::logic_error("Cannot convert to Native8 from Native16. The value of this native16 is beyond the accepted value bounds of Native8.");
				}
			}
		}
	}

	Native16::operator Native8(void) ro
	{
		switch (typeID)
		{
			case N16_ID::Signed:
			{
				if (nValue.SInteger > SInt8Min && nValue.SInteger < SInt8Max)
				{
					return (ro Native8)(sInt8(nValue.SInteger));
				}
				else
				{
					throw std::logic_error("Cannot convert to Native8 from Native16. The value of this Native16 is beyond the accepted value bounds of Native8.");
				}
			}
			case N16_ID::Unsigned:
			{
				if (nValue.UInteger < UInt8Max)
				{
					return (ro Native8)(uInt8(nValue.UInteger));
				}
				else
				{
					throw std::logic_error("Cannot convert to Native8 from Native16. The value of this native16 is beyond the accepted value bounds of Native8.");
				}
			}
		}
	}

	Native16::operator Native32(void)
	{
		switch (typeID)
		{
			case N16_ID::Signed:
			{
				return Native32(sInt32(nValue.SInteger));
			}
			case N16_ID::Unsigned:
			{
				return Native32(uInt32(nValue.UInteger));
			}
		}
	}

	Native16::operator Native32(void) ro
	{
		switch (typeID)
		{
			case N16_ID::Signed:
			{
				return Native32(sInt32(nValue.SInteger));
			}
			case N16_ID::Unsigned:
			{
				return Native32(uInt32(nValue.UInteger));
			}
		}
	}

	Native16::operator Native64(void)
	{
		switch (typeID)
		{
			case N16_ID::Signed:
			{
				return Native64(sInt64(nValue.SInteger));
			}
			case N16_ID::Unsigned:
			{
				return Native64(uInt64(nValue.UInteger));
			}
		}
	}

	Native16::operator Native64(void) ro
	{
		switch (typeID)
		{
			case N16_ID::Signed:
			{
				return Native64(sInt64(nValue.SInteger));
			}
			case N16_ID::Unsigned:
			{
				return Native64(uInt64(nValue.UInteger));
			}
		}
	}

	sfn Native16::operator=(ro Ref(Native16) _n16) -> Native16
	{
		nValue = _n16.nValue;
		typeID = _n16.typeID;

		return dref(this);
	}

	sfn Native16::operator=(rRef(Native16) _n16) noexcept -> Ref(Native16)
	{
		if (this == Address(_n16)) return dref(this);

		nValue = move(_n16.nValue);
		typeID = move(_n16.typeID);

		return dref(this);
	}
}

Context_End