/*
Title       : Native Template
Author      : Edward R. Gonzalez
File Name   : NativeT.hpp
Date Created: 11-3-2019

Description:
Defines the Native-T type.
*/

#pragma once

// Includes

// Notation Engine
#include "ANativeT.hpp"



namespace NotationEngine::Utility::Value
{
	inline namespace Source
	{
		template<typename NType>
		class NativeT : public ANativeT<NType>
		{
		public:
			explicit NativeT(void);

			//NativeT(ro NType NativeToAssign);

			NativeT(const NativeT<NType>& NativeT_ToAssign);

			NativeT(NType&& NativeToMove) noexcept;

			NativeT(NativeT<NType>&& NativeT_ToMove) noexcept;

			~NativeT(void);

			virtual const Sign   GetSign (void) const final;
			virtual const NType& GetValue(void) const final;

			virtual const TypeData& GetTypeID(void) const final;

			virtual void Reinitialize(void) final;

			virtual const string Str(void) const final;

			virtual void SetZero(void) final;

			virtual void SetValue(const uInt64            ValueToSet);
			virtual void SetValue(const AValue_HAL* const ValueToSet);

			virtual void SetValue(const NType& ValueToSet) final;

			NativeT<NType>  operator=(const NativeT<NType>&  NativeT_ToAssign)         ;
			NativeT<NType>& operator=(      NativeT<NType>&& NativeT_ToMove  ) noexcept;


			// Stack options

			const NType GetValue_Stack(void) const;

			void SetValue_Stack(const NType ValueToSet);

		private:
			constexpr const Sign sign(void) const
			{
				return IsInt<NType>() ? Int::Signum(nValue) : Float::Signum(nValue);
			}

			NType nValue;
		};
	}

	inline namespace Meta
	{
		template<typename NType>
		extern const TypeData& NativeT_TypeID = typeid(NativeT<NType>);
	}
}
