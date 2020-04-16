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
	NativeT<NType>::NativeT() : 
		#ifdef __USE_TypeSafe__
			nValue(decltype(nValue.get())(0))
		#else
			nValue(0)
		#endif
	{}

	//template<typename NType>
	//NativeT<NType>::NativeT(ro NType _nType) :
	//	nValue(_nType)
	//{}

	template<typename NType>
	NativeT<NType>::NativeT(ro Ref(NativeT<NType>) _nativeT) :
		nValue(_nativeT.nValue)
	{}

	#ifdef __USE_TypeSafe__

		template<typename NType>
		NativeT<NType>::NativeT(rRef(NType) _nType) : nValue(decltype(nValue.get())(0))
		{
			nValue = move(_nType);
		}

		template<typename NType>
		NativeT<NType>::NativeT(rRef(NativeT<NType>) _nType) : nValue(decltype(nValue.get())(0))
		{
			dref(this) = move(_nType);
		}

	#else

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

	#endif

	template<typename NType>
	NativeT<NType>::~NativeT()
	{}

	template<typename NType>
	sfn NativeT<NType>::GetSign() ro -> ro Sign
	{
		#ifdef __USE_TypeSafe__
			return IsInt<NType>() ? unsafe::Int::Signum(nValue.get()) : unsafe::Float::Signum(nValue.get());
		#else
			return sign();
		#endif
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
		#ifdef __USE_TypeSafe__

			using RawValueType = decltype(nValue.get());

			nValue = NType(RawValueType(0));

		#else

			nValue = 0

		#endif

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
	sfn NativeT<NType>::SetSign(ro Sign _sign) -> void
	{
		#ifdef __USE_TypeSafe__

			if (GetSign() == _sign) return;

			if (IsSigned<NType>() == true)
			{
				nValue =
					NType
					(
						decltype(nValue.get())
						(
							-(nValue.get())
							)
					);
			}
			else
			{
				throw std::logic_error("NativeT: Attempted to set the sign of an unsigned type.");
	}

		#else

			if (sign() == _sign) return;

			if (IsSigned<NType>() == true)
			{
				nValue = -nValue;
			}
			else
			{
				throw std::logic_error("NativeT: Attempted to set the sign of an unsigned type.");
			}

		#endif
	}

	template<typename NType>
	sfn NativeT<NType>::SetZero() -> void
	{
		#ifdef __USE_TypeSafe__
			nValue = decltype(nValue.get())(0);
		#else
			nValue = 0;
		#endif
	}

	// TODO: Needs safety check.
	template<typename NType>
	sfn NativeT<NType>::SetValue(ro uInt64 _value) -> void
	{
		#ifdef __USE_TypeSafe__

			using RawValueType = decltype(nValue.get());

			if (IsSameType<NType, uInt64>() || IsFloat<NType>())
			{
				nValue = RawValueType(_value.get());
			}
			else if (_value <= unsafe::uInt64(NumLimits<RawValueType>().max()))
			{
				nValue = RawValueType(_value.get());
			}
			else
			{
				throw std::logic_error(""); //  "Attempted to assign an unsigned integer value to : " << typeid(NType).name()
			}

		#else

			if (IsSameType<NType, uInt64>() || IsFloat<NType>())
			{
				nValue = _value;
			}
			else if (_value <= uInt64(NumLimits<NType>().max()))
			{
				nValue = _value;
			}
			else
			{
				throw std::logic_error(""); //  "Attempted to assign an unsigned integer value to : " << typeid(NType).name()
			}

		#endif
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
				#ifndef __USE_TypeSafe__
					nValue = NType(SCast<ro NativeT<float64> >(_value)->GetValue_Stack());
				#else
					using RawValueType = decltype(nValue.get());

					nValue = 
						RawValueType
						(
							SCast<ro NativeT<float64> >(_value)->GetValue_Stack().get()
						);
				#endif

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

	#ifndef __USE_TypeSafe__
		template class NativeT<floatEP>;   // Note: Will just be a float64 in MSVC
	#endif
}

Context_End
