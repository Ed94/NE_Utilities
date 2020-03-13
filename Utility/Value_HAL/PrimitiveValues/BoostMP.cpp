// Parent Header
#include "BoostMP.hpp"

// Includes

// C++
#include <string>
#include <iostream>
#include <sstream>



namespace NotationEngine::Utility::Value
{
	inline namespace Alias
	{
		using std::move        ;
		using std::stringstream;
	}

	inline namespace Meta 
	{
		
	}

	inline namespace Source
	{
		template<typename MP_Type>
		ABoostMP<MP_Type>::~ABoostMP()
		{}

		template<typename MP_Type>
		BoostMP<MP_Type>::BoostMP()
		{}

		template<typename MP_Type>
		BoostMP<MP_Type>::BoostMP(const MP_Type& _mpVal) :
			mValue(_mpVal)
		{}


		template<typename MP_Type>
		BoostMP<MP_Type>::BoostMP(const BoostMP<MP_Type>& _boostMP) :
			mValue(_boostMP.mValue)
		{}

		template<typename MP_Type>
		BoostMP<MP_Type>::BoostMP(MP_Type&& _mpVal) noexcept
		{
			mValue = move(_mpVal);
		}

		template<typename MP_Type>
		BoostMP<MP_Type>::BoostMP(BoostMP<MP_Type>& _boostMP) noexcept
		{
			*this = move(_boostMP);
		}

		template<typename MP_Type>
		BoostMP<MP_Type>::~BoostMP()
		{}

		template<typename MP_Type>
		const Sign BoostMP<MP_Type>::GetSign() const
		{
			return sign();
		}

		template<typename MP_Type>
		const MP_Type& BoostMP<MP_Type>::GetValue() const
		{
			return mValue;
		}

		template<typename MP_Type>
		const TypeData& BoostMP<MP_Type>::GetTypeID() const
		{
			return BoostMP_TypeID<MP_Type>;
		}

		template<typename MP_Type>
		void BoostMP<MP_Type>::Reinitialize()
		{
			mValue = MP_Type();

			return;
		}

		template<typename MP_Type>
		const string BoostMP<MP_Type>::Str() const
		{
			stringstream result;

			result << typeid(MP_Type).name() << ": " << mValue;

			return result.str();
		}

		template<typename MP_Type>
		void BoostMP<MP_Type>::SetValue(const MP_Type& _mpValue)
		{
			mValue = _mpValue;
		}

		template<typename MP_Type>
		BoostMP<MP_Type> BoostMP<MP_Type>::operator=(const BoostMP<MP_Type>& _boostMP)
		{
			mValue = _boostMP.mValue;

			return dref(this);
		}

		template<typename MP_Type>
		BoostMP<MP_Type>& BoostMP<MP_Type>::operator=(BoostMP<MP_Type>&& _boostMP)
		{
			if (this == &_boostMP)
			{
				return *this;
			}

			mValue = move(_boostMP.mValue);

			return *this;
		}

		// TODO: For some reason the integers are not getting filtered properly when doing a compile-time check on what function to call...
		//template class BoostMP<uInt256  >;
		//template class BoostMP<sInt256  >;
		//template class BoostMP<Float_P50>;
	}
}