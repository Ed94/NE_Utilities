/*
Title       : Native-8 Implementations
Author      : Edward R. Gonzalez
File Name   : Native8.cpp
Date Created: 10-4-2019

Description:
Implements Native-8.
*/

// Parent Header
#include "Native8.hpp"

// Includes

// C++
#include <iostream >
#include <sstream  >
#include <utility>

// Notation Engine
#include "Native16.hpp"
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

	using NE_U::Int::Signum;
}

SMeta
{
	eGlobal data<ro Ref(TypeData)> Native8_TypeID = typeid(Native8);
}

SSource
{
	Native8::NU_8:: NU_8() {}
	Native8::NU_8::~NU_8() {}

	Native8::Native8() :
		typeID(N8_ID::Unsigned)
	{
		nValue.UInteger = 0U;
	}

	Native8::Native8(ro sInt8 _sInt) :
		typeID(N8_ID::Signed)
	{
		nValue.SInteger = _sInt;
	}

	Native8::Native8(ro uInt8 _uInt) :
		typeID(N8_ID::Unsigned)
	{
		nValue.UInteger = _uInt;
	}

	Native8::Native8(ro Ref(Native8) _n8) :
		typeID(_n8.typeID),
		nValue(_n8.nValue)
	{}

	Native8::Native8(rRef(Native8) _n8) noexcept
	{
		if (this != Address(_n8))
		{
			typeID = move(_n8.typeID);
			nValue = move(_n8.nValue);
		}
	}

	ANative8::~ANative8() {}

	Native8::~Native8() {}

	sfn Native8::GetID() ro -> N8_ID
	{
		return typeID;
	}

	sfn Native8::GetSign() ro -> Sign
	{
		switch (typeID)
		{
			case N8_ID::Signed:
			{
				return Signum<sInt8>(nValue.SInteger);
			}
			case N8_ID::Unsigned:
			{
				return nValue.UInteger == uInt8(0U) ? Sign::Neutral : Sign::Positive;
			}
		}
	}

	sfn Native8::GetSigned() ro -> sInt8
	{
		if (typeID == N8_ID::Signed)
		{
			return nValue.SInteger;
		}
		else
		{
			throw std::logic_error("Instance of Native8 not set to a signed integer.");
		}
	}

	sfn Native8::GetUnsigned() ro -> uInt8
	{
		if (typeID == N8_ID::Unsigned)
		{
			return nValue.UInteger;
		}
		else
		{
			throw std::logic_error("Instance of Native8 not set to a unsigned integer.");
		}
	}

	sfn Native8::GetTypeID(void) ro -> ro Ref(TypeData)
	{
		return Native8_TypeID;
	}

	sfn Native8::ReInitalize(void) -> void
	{
		typeID = N8_ID::Unsigned;

		nValue.UInteger = uInt8(0U);
	}

	sfn Native8::Str() ro -> string
	{
		switch (typeID)
		{
		case N8_ID::Signed:
		{
			stringstream result; 
			
			result << "Signed Int8:" << " " << nValue.SInteger;

			return result.str();
		}
		case N8_ID::Unsigned:
		{
			stringstream result;

			result << "Unsigned Int8: " << " " << nValue.UInteger;

			return result.str();
		}
		}
	}

	sfn Native8::SetSigned(ro sInt8 _sInt) -> void
	{
		nValue.SInteger = _sInt        ;
		typeID          = N8_ID::Signed;
	}

	sfn Native8::SetUnsigned(ro uInt8 _uInt) -> void
	{
		nValue.UInteger = _uInt          ;
		typeID          = N8_ID::Unsigned;
	}

	Native8::operator Native16(void)
	{
		switch (typeID)
		{
			case N8_ID::Signed:
			{
				return Native16(sInt16(nValue.SInteger));
			}
			case N8_ID::Unsigned:
			{
				return Native16(uInt16(nValue.UInteger));
			}
		}
	}

	Native8::operator Native16(void) ro
	{
		switch (typeID)
		{
			case N8_ID::Signed:
			{
				return Native16(sInt16(nValue.SInteger));
			}
			case N8_ID::Unsigned:
			{
				return Native16(uInt16(nValue.UInteger));
			}
		}
	}

	Native8::operator Native32(void)
	{
		switch (typeID)
		{
			case N8_ID::Signed:
			{
				return Native32(sInt32(nValue.SInteger));
			}
			case N8_ID::Unsigned:
			{
				return Native32(uInt32(nValue.UInteger));
			}
		}
	}

	Native8::operator Native32(void) ro
	{
		switch (typeID)
		{
			case N8_ID::Signed:
			{
				return Native32(sInt32(nValue.SInteger));
			}
			case N8_ID::Unsigned:
			{
				return Native32(uInt32(nValue.UInteger));
			}
		}
	}

	Native8::operator Native64(void)
	{
		switch (typeID)
		{
			case N8_ID::Signed:
			{
				return Native64(sInt64(nValue.SInteger));
			}
			case N8_ID::Unsigned:
			{
				return Native64(uInt64(nValue.UInteger));
			}
		}
	}

	Native8::operator Native64(void) ro
	{
		switch (typeID)
		{
			case N8_ID::Signed:
			{
				return Native64(sInt64(nValue.SInteger));
			}
			case N8_ID::Unsigned:
			{
				return Native64(uInt64(nValue.UInteger));
			}
		}
	}

	sfn Native8::operator=(ro Ref(Native8) _n8) -> Native8
	{
		nValue = _n8.nValue;
		typeID = _n8.typeID;

		return dref(this);
	}

	sfn Native8::operator=(rRef(Native8) _n8) noexcept -> Ref(Native8) 
	{
		if (this == Address(_n8)) return dref(this);

		nValue = move(_n8.nValue);
		typeID = move(_n8.typeID);

		return dref(this);
	}
}

Context_End