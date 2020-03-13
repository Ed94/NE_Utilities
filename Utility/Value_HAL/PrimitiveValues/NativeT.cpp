/*
Title       : Native Template Implementation
Author      : Edward R. Gonzalez
File Name   : NativeT.cpp
Date Created: 11-3-2019

Description:
Implements the Native-T type.
*/

#pragma once

// Includes

// C++
#include <string>
#include <iostream>
#include <sstream >

// Parent Header
#include "NativeT.hpp"
#include "EngineConfig.hpp"



Context(NotationEngine::Utility::Value)

SAlias
{
	// C++

	using std::move        ;
	using std::string      ;
	using std::stringstream;

	// Notation Engine

	using NE_Cfg::GetValueHAL_Option;
	using NE_Cfg::ValueHAL_Mode     ;

	using NE_U_R::IsSameType;

	using NE_U::NumLimits;
}

SMeta
{
	
}

SSource 
{
	template<typename NType>
	ANativeT<NType>::~ANativeT()
	{}

	template<typename NType>
	NativeT<NType>::NativeT() : nValue()
	{}

	//template<typename NType>
	//NativeT<NType>::NativeT(ro NType _nType) :
	//	nValue(_nType)
	//{}

	template<typename NType>
	NativeT<NType>::NativeT(ro Ref(NativeT<NType>) _nativeT) :
		nValue(_nativeT.nValue)
	{}

	template<typename NType>
	NativeT<NType>::NativeT(rRef(NType) _nType) noexcept
	{
		nValue = move(_nType);
	}

	template<typename NType>
	NativeT<NType>::NativeT(rRef(NativeT<NType>) _nType) noexcept
	{
		dref(this) = move(_nType);
	}

	template<typename NType>
	NativeT<NType>::~NativeT()
	{}

	template<typename NType>
	sfn NativeT<NType>::GetSign() ro -> ro Sign
	{
		return sign();
	}

	template<typename NType>
	sfn NativeT<NType>::GetValue() ro -> ro Ref(NType)
	{
		return nValue;
	}

	template<typename NType>
	sfn NativeT<NType>::GetTypeID() ro -> ro Ref(TypeData)
	{
		return NativeT_TypeID<NType>;
	}

	template<typename NType>
	sfn NativeT<NType>::Reinitialize() -> void
	{
		nValue = NType();

		return;
	}

	template<typename NType>
	sfn NativeT<NType>::Str(void) ro -> ro string
	{
		stringstream result;

		result << typeid(NType).name() << ": " << nValue;

		return result.str();
	}

	template<typename NType>
	sfn NativeT<NType>::SetZero() -> void
	{
		nValue = NType(0);
	}

	// TODO: Needs safety check.
	template<typename NType>
	sfn NativeT<NType>::SetValue(ro uInt64 _value) -> void
	{
		if (IsSameType<NType, uInt64>() || IsFloat<NType>())
		{
			nValue = NType(_value);
		}
		else if (_value <= uInt64(NumLimits<NType>().max()))
		{
			nValue = NType(_value);
		}
		else
		{
			throw std::logic_error(""); //  "Attempted to assign an unsigned integer value to : " << typeid(NType).name()
		}
	}

	//// TODO: Needs safety check.
	//template<typename NType>
	//sfn NativeT<NType>::SetValue(ro sInt64 _value) -> void
	//{
	//	nValue = _value;
	//}

	//// TODO: Needs safety check.
	//template<typename NType>
	//sfn NativeT<NType>::SetValue(ro float32 _value) -> void
	//{
	//	nValue = _value;
	//}

	template<typename NType>
	sfn NativeT<NType>::SetValue(ro ptr<ro AValue_HAL> _value) -> void
	{
		switch (GetValueHAL_Option())
		{
			case ValueHAL_Mode::Force_FloatingPoint64:
			{
				nValue = NType(SCast<ro NativeT<float64> >(_value)->GetValue_Stack());

				return;
			}
			default:
			{
				throw std::logic_error("Not Implemented.");
			}
		}
	}

	// TODO: Needs safety check.
	/*template<typename NType>
	sfn NativeT<NType>::SetValue(ro float64 _value) -> void
	{
		nValue = _value;
	}*/

	template<typename NType>
	sfn NativeT<NType>::SetValue(ro Ref(NType) _value) -> void
	{
		nValue = _value;

		return;
	}

	template<typename NType>
	sfn NativeT<NType>::operator=(ro Ref(NativeT<NType>) _nativeT) -> NativeT<NType>
	{
		nValue = _nativeT.nValue;

		return dref(this);
	}

	template<typename NType>
	sfn NativeT<NType>::operator=(rRef(NativeT<NType>) _nativeT) noexcept->Ref(NativeT<NType>)
	{
		if (this == Address(_nativeT))
		{
			return dref(this);
		}

		nValue = move(_nativeT.nValue);

		return dref(this);
	}

	// Stack options

	template<typename NType>
	sfn NativeT<NType>::GetValue_Stack() ro -> ro NType
	{
		return nValue;
	}

	template<typename NType>
	sfn NativeT<NType>::SetValue_Stack(ro NType _value) -> void
	{
		nValue = _value;
	}


	template class NativeT<sInt8>;
	template class NativeT<uInt8>;

	template class NativeT<sInt16>;
	template class NativeT<uInt16>;

	template class NativeT<sInt32 >;
	template class NativeT<uInt32 >;
	template class NativeT<float32>;

	template class NativeT<sInt64 >;
	template class NativeT<uInt64 >;
	template class NativeT<float64>;

	template class NativeT<floatEP>;   // Note: Will just be a float64 in MSVC
}

Context_End
