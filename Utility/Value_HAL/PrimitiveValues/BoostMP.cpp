// Parent Header
#include "BoostMP.hpp"

// Includes

// C++
#include <string>
#include <iostream>
#include <sstream>



Context(NotationEngine::Utility::Value)

SAlias
{
	using std::move        ;
	using std::stringstream;
}

SMeta 
{
	
}

SSource
{
	template<typename MP_Type>
	ABoostMP<MP_Type>::~ABoostMP()
	{}

	template<typename MP_Type>
	BoostMP<MP_Type>::BoostMP()
	{}

	template<typename MP_Type>
	BoostMP<MP_Type>::BoostMP(ro Ref(MP_Type) _mpVal) :
		mValue(_mpVal)
	{}


	template<typename MP_Type>
	BoostMP<MP_Type>::BoostMP(ro Ref(BoostMP<MP_Type>) _boostMP) :
		mValue(_boostMP.mValue)
	{}

	template<typename MP_Type>
	BoostMP<MP_Type>::BoostMP(rRef(MP_Type) _mpVal) noexcept
	{
		mValue = move(_mpVal);
	}

	template<typename MP_Type>
	BoostMP<MP_Type>::BoostMP(rRef(BoostMP<MP_Type>) _boostMP) noexcept
	{
		dref(this) = move(_boostMP);
	}

	template<typename MP_Type>
	BoostMP<MP_Type>::~BoostMP()
	{}

	template<typename MP_Type>
	sfn BoostMP<MP_Type>::GetSign() ro -> ro Sign
	{
		return sign();
	}

	template<typename MP_Type>
	sfn BoostMP<MP_Type>::GetValue() ro -> ro Ref(MP_Type)
	{
		return mValue;
	}

	template<typename MP_Type>
	sfn BoostMP<MP_Type>::GetTypeID() ro -> ro Ref(TypeData)
	{
		return BoostMP_TypeID<MP_Type>;
	}

	template<typename MP_Type>
	sfn BoostMP<MP_Type>::Reinitialize() -> void
	{
		mValue = MP_Type();

		return;
	}

	template<typename MP_Type>
	sfn BoostMP<MP_Type>::Str() ro -> ro string
	{
		stringstream result;

		result << typeid(MP_Type).name() << ": " << mValue;

		return result.str();
	}

	template<typename MP_Type>
	sfn BoostMP<MP_Type>::SetValue(ro Ref(MP_Type) _mpValue) -> void
	{
		mValue = _mpValue;
	}

	template<typename MP_Type>
	sfn BoostMP<MP_Type>::operator=(ro Ref(BoostMP<MP_Type>) _boostMP) -> BoostMP<MP_Type>
	{
		mValue = _boostMP.mValue;

		return dref(this);
	}

	template<typename MP_Type>
	sfn BoostMP<MP_Type>::operator=(rRef(BoostMP<MP_Type>) _boostMP)->Ref(BoostMP<MP_Type>)
	{
		if (this == Address(_boostMP))
		{
			return dref(this);
		}

		mValue = move(_boostMP.mValue);

		return dref(this);
	}

	// TODO: For some reason the integers are not getting filtered properly when doing a compile-time check on what function to call...
	//template class BoostMP<uInt256  >;
	//template class BoostMP<sInt256  >;
	//template class BoostMP<Float_P50>;
}

Context_End