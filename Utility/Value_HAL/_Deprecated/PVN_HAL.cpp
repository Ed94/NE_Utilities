/*
Title       : Value Implementation
Author      : Edward R. Gonzalez
File Name   : Value.cpp
Date Created: 2-10-2019

Description:
Contains implementation for Value.
*/

//Parent Header
#include "PVN_HAL.hpp"

//Includes

//C++

#include <iostream>
#include <sstream >
#include <string  >
#include <utility >

//Notation Engine

#include "DataTypes/FundamentalTypes.hpp"
#include "DataTypes/FundamentalLimits.hpp"



Context(NotationEngine::Utility::Value)

SAlias
{
	//C++

	using std::cout        ;
	using std::endl        ;
	using std::move        ;
	using std::stringstream;

	//Notation Engine

	using NE_U::UInt8Max;
}

SMeta
{
	eGlobal data<ro Ref(TypeData)> PV_HAL_TypeID = typeid(PVN_HAL);
}

SSource
{
	APVN_HAL::~APVN_HAL(void) {}

	PVN_HAL::PV_Union::PV_Union(void) :
		Native_8(uInt8(0U))
	{}

	PVN_HAL::PV_Union::~PV_Union(void) {}

	PVN_HAL::PVN_HAL(void) :
		typeID(ValueType::Native8)
	{}

	PVN_HAL::PVN_HAL(ro Ref(Native8) _native8)
	{
		SetValue(_native8);
	}

	PVN_HAL::PVN_HAL(ro Ref(Native16) _native16)
	{
		SetValue(_native16);
	}

	PVN_HAL::PVN_HAL(ro Ref(Native32) _native32)
	{
		SetValue(_native32);
	}

	PVN_HAL::PVN_HAL(ro Ref(Native64) _native64)
	{
		SetValue(_native64);
	}

	PVN_HAL::PVN_HAL(ro Ref(ptr<ro ANative8>) _native8)
	{
		SetValue(_native8);
	}

	PVN_HAL::PVN_HAL(ro Ref(ptr<ro ANative16>) _native16)
	{
		SetValue(_native16);
	}

	PVN_HAL::PVN_HAL(ro Ref(ptr<ro ANative32>) _native32)
	{
		SetValue(_native32);
	}

	PVN_HAL::PVN_HAL(ro Ref(ptr<ro ANative64>) _native64)
	{
		SetValue(_native64);
	}

	PVN_HAL::PVN_HAL(ro Ref(PVN_HAL) _original)
	{
		switch (_original.typeID)
		{
		case ValueType::Native8 : this->SetValue(_original.pValue.Native_8 ); return;
		case ValueType::Native16: this->SetValue(_original.pValue.Native_16); return;
		case ValueType::Native32: this->SetValue(_original.pValue.Native_32); return;
		case ValueType::Native64: this->SetValue(_original.pValue.Native_64); return;
		}
	}

	PVN_HAL::PVN_HAL(rRef(PVN_HAL) _pvHal) noexcept :
		typeID(move(_pvHal.typeID))
	{
		switch (_pvHal.typeID)
		{
		case ValueType::Native8 : this->pValue.Native_8  = move(_pvHal.pValue.Native_8 ); break;
		case ValueType::Native16: this->pValue.Native_16 = move(_pvHal.pValue.Native_16); break;
		case ValueType::Native32: this->pValue.Native_32 = move(_pvHal.pValue.Native_32); break;
		case ValueType::Native64: this->pValue.Native_64 = move(_pvHal.pValue.Native_64); break;
		};
	}

	PVN_HAL::~PVN_HAL()
	{
		pValue.~PV_Union();
	}

	sfn PVN_HAL::InclusiveType(ro Ref(PVN_HAL) _subject, ro Ref(PVN_HAL) _reference) -> ValueType
	{
		if (_subject.GetValueType() == _reference.GetValueType())
		{
			return _subject.GetValueType();
		}
		else
		{
			if (_subject.GetValueType() > _reference.GetValueType())
			{
				return _subject.GetValueType();
			}
			else
			{
				return _reference.GetValueType();
			}
		}
	}

	sfn PVN_HAL::Zero(void) -> PVN_HAL
	{
		return PVN_HAL(Native8(uInt8(0U)));
	}

	sfn PVN_HAL::MakeI64(uInt64 _uInteger64) -> PVN_HAL
	{
		return PVN_HAL(Native64(_uInteger64));
	}

	sfn PVN_HAL::GetANative8(void) ro -> ro ptr<ro ANative8>
	{
		return typeID == ValueType::Native8 ? Address(pValue.Native_8) : nullptr;
	}

	sfn PVN_HAL::GetANative16(void) ro -> ro ptr<ro ANative16>
	{
		return typeID == ValueType::Native16 ? Address(pValue.Native_16) : nullptr;
	}

	sfn PVN_HAL::GetANative32(void) ro -> ro ptr<ro ANative32>
	{
		return typeID == ValueType::Native32 ? Address(pValue.Native_32) : nullptr;
	}

	sfn PVN_HAL::GetANative64(void) ro -> ro ptr<ro ANative64>
	{
		return typeID == ValueType::Native64 ? Address(pValue.Native_64) : nullptr;
	}

	sfn PVN_HAL::GetNative8(void) ro -> ro Ref(Native8)
	{
		if (typeID == ValueType::Native8)
		{
			return pValue.Native_8;
		}
		else
		{
			throw std::logic_error("This value is not set to Native8.");
		}
	}

	sfn PVN_HAL::GetNative16(void) ro -> ro Ref(Native16)
	{
		if (typeID == ValueType::Native16)
		{
			return pValue.Native_16;
		}
		else
		{
			throw std::logic_error("This value is not set to Native16.");
		}
	}

	sfn PVN_HAL::GetNative32(void) ro -> ro Ref(Native32)
	{
		if (typeID == ValueType::Native32)
		{
			return pValue.Native_32;
		}
		else
		{
			throw std::logic_error("This value is not set to Native32.");
		}
	}

	sfn PVN_HAL::GetNative64(void) ro -> ro Ref(Native64)
	{
		if (typeID == ValueType::Native64)
		{
			return pValue.Native_64;
		}
		else
		{
			throw std::logic_error("This value is not set to Native64.");
		}
	}

	sfn PVN_HAL::GetSign(void) ro -> Sign
	{
		switch (typeID)
		{
			case ValueType::Native8 : return pValue.Native_8 .GetSign(); 
			case ValueType::Native16: return pValue.Native_16.GetSign();
			case ValueType::Native32: return pValue.Native_32.GetSign();
			case ValueType::Native64: return pValue.Native_64.GetSign();
		}
	}

	sfn PVN_HAL::GetValueType(void) ro -> ro Ref(ValueType)
	{
		return typeID;
	}

	sfn PVN_HAL::SetValue(ro Ref(ptr<ro APVN_HAL>) _value) -> void
	{
		ptr<ro PVN_HAL> cast = DCast<ro PVN_HAL>(_value);

		dref(this) = dref(cast);
	}

	sfn PVN_HAL::SetValue(uInt64 _value) -> void
	{
		pValue.Native_64 = _value;

		typeID = ValueType::Native64;
	}

	sfn PVN_HAL::SetValue(ro Ref(ptr<ro ANative8>) _aNative8) -> void
	{
		pValue.Native_8 = dref(DCast<ro Native8>(_aNative8));

		typeID = ValueType::Native8;
	}

	sfn PVN_HAL::SetValue(ro Ref(ptr<ro ANative16>) _aNative16) -> void
	{
		pValue.Native_16 = dref(DCast<ro Native16>(_aNative16));

		typeID = ValueType::Native16;
	}

	sfn PVN_HAL::SetValue(ro Ref(ptr<ro ANative32>) _aNative32) -> void
	{
		pValue.Native_32 = dref(DCast<ro Native32>(_aNative32));

		typeID = ValueType::Native32;
	}

	sfn PVN_HAL::SetValue(ro Ref(ptr<ro ANative64>) _aNative64) -> void
	{
		pValue.Native_64 = dref(DCast<ro Native64>(_aNative64));

		typeID = ValueType::Native64;
	}

	sfn PVN_HAL::SetValue(ro Ref(Native8) _native8) -> void
	{
		pValue.Native_8 = _native8;

		typeID = ValueType::Native8;
	}

	sfn PVN_HAL::SetValue(ro Ref(Native16) _native16) -> void
	{
		pValue.Native_16 = _native16;

		typeID = ValueType::Native16;
	}

	sfn PVN_HAL::SetValue(ro Ref(Native32) _native32) -> void
	{
		pValue.Native_32 = _native32;

		typeID = ValueType::Native32;
	}

	sfn PVN_HAL::SetValue(ro Ref(Native64) _native64) -> void
	{
		pValue.Native_64 = _native64;

		typeID = ValueType::Native64;
	}

	sfn PVN_HAL::SetZero(void) -> void
	{
		switch (typeID)
		{
		case ValueType::Native8 : pValue.Native_8 .SetUnsigned(uInt8 (0U)); return;
		case ValueType::Native16: pValue.Native_16.SetUnsigned(uInt16(0U)); return;
		case ValueType::Native32: pValue.Native_32.SetUInteger(uInt32(0U)); return;
		case ValueType::Native64: pValue.Native_64.SetUInteger(uInt64(0U)); return;
		}
	}

	sfn PVN_HAL::GetTypeID(void) ro -> ro Ref(TypeData)
	{
		return PV_HAL_TypeID;
	}

	sfn PVN_HAL::ReInitalize(void) -> void
	{
		typeID = ValueType::Native64;

		pValue.Native_64.ReInitalize();
	}

	sfn PVN_HAL::Str(void) ro -> string
	{
		switch (typeID)
		{
		case ValueType::Native8:
		{
			stringstream result;

			result << "Value: " << "Integer8: " << pValue.Native_8.Str();

			return result.str();
		}
		case ValueType::Native16:
		{
			stringstream result;

			result << "Value: " << "Integer16: " <<  pValue.Native_16.Str();

			return result.str();
		}
		case ValueType::Native32:
		{
			stringstream result;

			result << "Value: " << pValue.Native_32.Str();

			return result.str();
		}
		case ValueType::Native64:
		{
			stringstream result;

			result << "Value: " << pValue.Native_64.Str();

			return result.str();
		}
		}
	}

	// Operators

	PVN_HAL::operator Native8(void)
	{
		switch (typeID)
		{
			case ValueType::Native8 : return         pValue.Native_8  ;
			case ValueType::Native16: return Native8(pValue.Native_16);
			case ValueType::Native32: return Native8(pValue.Native_32);
			case ValueType::Native64: return Native8(pValue.Native_64);
		}
	}

	PVN_HAL::operator Native8(void) ro
	{
		switch (typeID)
		{
			case ValueType::Native8 : return         pValue.Native_8;
			case ValueType::Native16: return Native8(pValue.Native_16);
			case ValueType::Native32: return Native8(pValue.Native_32);
			case ValueType::Native64: return Native8(pValue.Native_64);
		}
	}

	PVN_HAL::operator Native16(void)
	{
		switch (typeID)
		{
			case ValueType::Native8 : return Native16(pValue.Native_8 );
			case ValueType::Native16: return          pValue.Native_16 ;
			case ValueType::Native32: return Native16(pValue.Native_32);
			case ValueType::Native64: return Native16(pValue.Native_64);
		}
	}

	PVN_HAL::operator Native16(void) ro
	{
		switch (typeID)
		{
			case ValueType::Native8 : return Native16(pValue.Native_8 );
			case ValueType::Native16: return          pValue.Native_16 ;
			case ValueType::Native32: return Native16(pValue.Native_32);
			case ValueType::Native64: return Native16(pValue.Native_64);
		}
	}

	PVN_HAL::operator Native32(void)
	{
		switch (typeID)
		{
			case ValueType::Native8 : return Native32(pValue.Native_8 );
			case ValueType::Native16: return Native32(pValue.Native_16);
			case ValueType::Native32: return          pValue.Native_32 ;
			case ValueType::Native64: return Native32(pValue.Native_64);
		}
	}

	PVN_HAL::operator Native32(void) ro
	{
		switch (typeID)
		{
			case ValueType::Native8 : return Native32(pValue.Native_8 );
			case ValueType::Native16: return Native32(pValue.Native_16);
			case ValueType::Native32: return          pValue.Native_32 ;
			case ValueType::Native64: return Native32(pValue.Native_64);
		}
	}

	PVN_HAL::operator Native64(void)
	{
		switch (typeID)
		{
			case ValueType::Native8 : return Native64(pValue.Native_8 );
			case ValueType::Native16: return Native64(pValue.Native_16);
			case ValueType::Native32: return Native64(pValue.Native_32);
			case ValueType::Native64: return          pValue.Native_64 ;
		}
	}

	PVN_HAL::operator Native64(void) ro
	{
		switch (typeID)
		{
			case ValueType::Native8 : return Native64(pValue.Native_8 );
			case ValueType::Native16: return Native64(pValue.Native_16);
			case ValueType::Native32: return Native64(pValue.Native_32);
			case ValueType::Native64: return          pValue.Native_64 ;
		}
	}
	
	sfn PVN_HAL::operator=(ro Ref(PVN_HAL) _value) -> PVN_HAL
	{
		switch (_value.typeID)
		{
		case ValueType::Native8:
		{
			this->SetValue(_value.pValue.Native_8);

			return dref(this);
		}
		case ValueType::Native16:
		{
			this->SetValue(_value.pValue.Native_16);

			return dref(this);
		}
		case ValueType::Native32:
		{
			this->SetValue(_value.pValue.Native_32);

			return dref(this);
		}
		case ValueType::Native64:
		{
			this->SetValue(_value.pValue.Native_64);

			return dref(this);
		}
		}

	}

	sfn PVN_HAL::operator=(rRef(PVN_HAL) _value) noexcept -> Ref(PVN_HAL)
	{
		if (this == Address(_value))
		{
			return dref(this);
		}

		switch (_value.typeID)
		{
		case ValueType::Native8:
		{
			this->pValue.Native_8 = move(_value.pValue.Native_8);

			break;
		}
		case ValueType::Native16:
		{
			this->pValue.Native_16 = move(_value.pValue.Native_16);

			break;
		}
		case ValueType::Native32:
		{
			this->pValue.Native_32 = move(_value.pValue.Native_32);

			break;
		}
		case ValueType::Native64:
		{
			this->pValue.Native_64 = move(_value.pValue.Native_64);

			break;
		}
		};

		this->typeID = move(_value.typeID);

		return dref(this);
	}

	sfn PVN_HAL::SwitchValueLevel(ValueType _valueType) -> void
	{
		switch (_valueType)
		{
		case ValueType::Native8:
		{
			switch (typeID)
			{
			case ValueType::Native8:
			{
				break;
			}
			case ValueType::Native16:
			{
				SetValue(Native8(pValue.Native_16));

				break;
			}
			case ValueType::Native32:
			{
				SetValue(Native8(pValue.Native_32));
				
				break;
			}
			case ValueType::Native64:
			{
				SetValue(Native8(pValue.Native_64));

				break;
			}
			default:
			{
				throw std::exception("Error: Got to default switch on SwitchValueLevel().");

				break;
			}
			}

			break;
		}
		case ValueType::Native16:
		{
			switch (typeID)
			{
			case ValueType::Native8:
			{
				SetValue(Native16(pValue.Native_8));

				break;
			}
			case ValueType::Native16:
			{
				break;
			}
			case ValueType::Native32:
			{
				SetValue(Native16(pValue.Native_32));

				break;
			}
			case ValueType::Native64:
			{
				SetValue(Native16(pValue.Native_64));

				break;
			}
			default:
			{
				throw std::exception("Error: Got to default switch on SwitchValueLevel().");
			}
			}

			break;
		}
		case ValueType::Native32:
		{
			switch (typeID)
			{
			case ValueType::Native8:
			{
				SetValue(Native32(pValue.Native_8));

				break;
			}
			case ValueType::Native16:
			{
				SetValue(Native32(pValue.Native_16));

				break;
			}
			case ValueType::Native32:
			{
				break;
			}
			case ValueType::Native64:
			{
				SetValue(Native32(pValue.Native_64));

				break;
			}
			default:
			{
				throw std::exception("Error: Got to default of switch on SwitchValueLevel().");
			}
			}

			break;
		}
		case ValueType::Native64:
		{
			switch (typeID)
			{
			case ValueType::Native8:
			{
				SetValue(Native64(pValue.Native_8));
				
				break;
			}
			case ValueType::Native16:
			{
				SetValue(Native64(pValue.Native_16));

				break;
			}
			case ValueType::Native32:
			{
				SetValue(Native64(pValue.Native_32));

				break;
			}
			case ValueType::Native64:
			{
				break;
			}
			default:
			{
				throw std::exception("Error: Got to default on switch for SwitchValueLevel.");
			}
			}

			break;
		}
		default:
		{
			throw std::exception("Error: Got to default on switch for SwitchValueLevel().");
		}
		}
	}
}

Context_End