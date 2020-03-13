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



namespace NotationEngine::Utility::Value
{
	inline namespace Alias
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

	inline namespace Meta
	{
		
	}

	inline namespace Source 
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
		NativeT<NType>::NativeT(const NativeT<NType>& _nativeT) :
			nValue(_nativeT.nValue)
		{}

		template<typename NType>
		NativeT<NType>::NativeT(NType&& _nType) noexcept
		{
			nValue = move(_nType);
		}

		template<typename NType>
		NativeT<NType>::NativeT(NativeT<NType>&& _nType) noexcept
		{
			*this = move(_nType);
		}

		template<typename NType>
		NativeT<NType>::~NativeT()
		{}

		template<typename NType>
		const Sign NativeT<NType>::GetSign() const
		{
			return sign();
		}

		template<typename NType>
		const NType& NativeT<NType>::GetValue() const
		{
			return nValue;
		}

		template<typename NType>
		const TypeData& NativeT<NType>::GetTypeID() const
		{
			return NativeT_TypeID<NType>;
		}

		template<typename NType>
		void NativeT<NType>::Reinitialize()
		{
			nValue = NType();

			return;
		}

		template<typename NType>
		const string NativeT<NType>::Str(void) const
		{
			stringstream result;

			result << typeid(NType).name() << ": " << nValue;

			return result.str();
		}

		template<typename NType>
		void NativeT<NType>::SetZero()
		{
			nValue = NType(0);
		}

		// TODO: Needs safety check.
		template<typename NType>
		void NativeT<NType>::SetValue(const uInt64 _value)
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
		void NativeT<NType>::SetValue(const AValue_HAL* const _value)
		{
			switch (GetValueHAL_Option())
			{
				case ValueHAL_Mode::Force_FloatingPoint64:
				{
					nValue = NType(static_cast<NativeT<float64>* const>(_value)->GetValue_Stack());

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
		void NativeT<NType>::SetValue(const NType& _value)
		{
			nValue = _value;

			return;
		}

		template<typename NType>
		NativeT<NType> NativeT<NType>::operator=(const NativeT<NType>& _nativeT)
		{
			nValue = _nativeT.nValue;

			return *this;
		}

		template<typename NType>
		NativeT<NType>& NativeT<NType>::operator=(NativeT<NType>&& _nativeT) noexcept;
		{
			if (this == &_nativeT)
			{
				return *this;
			}

			nValue = move(_nativeT.nValue);

			return *this;
		}

		// Stack options

		template<typename NType>
		const NType NativeT<NType>::GetValue_Stack() const
		{
			return nValue;
		}

		template<typename NType>
		void NativeT<NType>::SetValue_Stack(const NType _value)
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
}
