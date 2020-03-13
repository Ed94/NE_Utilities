#pragma once

// Includes

// Notation Engine
#include "ABoostMP.hpp"



namespace NotationEngine::Utility::Value
{
	inline namespace Source
	{
		template<typename MP_Type>
		class BoostMP : ABoostMP<MP_Type>
		{
		public:
			explicit BoostMP(void);

			BoostMP(const MP_Type& MPValue_ToAssign);

			BoostMP(const BoostMP<MP_Type>& MP_ToAssign);

			BoostMP(MP_Type&& MPValue_ToMove) noexcept;

			BoostMP(BoostMP<MP_Type>& MP_ToMove) noexcept;

			~BoostMP(void);

			virtual const Sign     GetSign (void) const final;
			virtual const MP_Type& GetValue(void) const final;

			virtual const TypeData& GetTypeID(void) const final;

			virtual void Reinitialize(void) final;

			virtual const string Str(void) const final;

			virtual void SetValue(const MP_Type& ValueToSet) final;

			BoostMP<MP_Type>  operator=(const BoostMP<MP_Type>&  MP_ToAssign);
			BoostMP<MP_Type>& operator=(      BoostMP<MP_Type>&& MP_ToMove  );

		private:
			constexpr const Sign sign(void) const
			{
				return (IsBoostInt<MP_Type>()) ? BInt::Signum(mValue) : BFloat::Signum(mValue);
			}

			MP_Type mValue;
		};
	}

	inline namespace Meta
	{
		template<typename MP_Type>
		extern const TypeData& BoostMP_TypeID = typeid(BoostMP<MP_Type>);
	}
}
