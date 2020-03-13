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



Context(NotationEngine::Utility::Value)

SSource
{
	template<typename NType>
	class NativeT : public ANativeT<NType>
	{
	public:
		explicit NativeT(void);

		//NativeT(ro NType NativeToAssign);

		NativeT(ro Ref(NativeT<NType>) NativeT_ToAssign);

		NativeT(rRef(NType) NativeToMove) noexcept;

		NativeT(rRef(NativeT<NType>) NativeT_ToMove) noexcept;

		~NativeT(void);

		implem sfn GetSign (void) ro -> ro     Sign   final;
		implem sfn GetValue(void) ro -> ro Ref(NType) final;

		implem sfn GetTypeID(void) ro -> ro Ref(TypeData) final;

		implem sfn Reinitialize(void) -> void final;

		implem sfn Str(void) ro -> ro string final;

		implem sfn SetZero(void) -> void final;

		implem sfn SetValue(ro        uInt64      ValueToSet) -> void;
		//implem sfn SetValue(ro        sInt64      ValueToSet) -> void = NULL;
		//implem sfn SetValue(ro        float32     ValueToSet) -> void = NULL;
		//implem sfn SetValue(ro        float64     ValueToSet) -> void = NULL;
		implem sfn SetValue(ro ptr<ro AValue_HAL> ValueToSet) -> void;

		implem sfn SetValue(ro Ref(NType) ValueToSet) -> void final;

		sfn operator=(ro Ref(NativeT<NType>) NativeT_ToAssign)          ->     NativeT<NType> ;
		sfn operator=(  rRef(NativeT<NType>) NativeT_ToMove  ) noexcept -> Ref(NativeT<NType>);


		// Stack options

		sfn GetValue_Stack(void) ro -> ro NType;

		sfn SetValue_Stack(ro NType ValueToSet) -> void;

	private:
		constant sfn sign(void) ro -> ro Sign
		{
			return IsInt<NType>() ? Int::Signum(nValue) : Float::Signum(nValue);
		}

		NType nValue;
	};
}

SMeta
{
	template<typename NType>
	eGlobal data<ro Ref(TypeData)> NativeT_TypeID = typeid(NativeT<NType>);
}

Context_End
